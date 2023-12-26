#include "Audio.h"

Audio* Audio::GetInstance(){
	static Audio instanc;
	return &instanc;
}

void Audio::Initialize(){
	HRESULT result{};

	result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	result = xAudio2->CreateMasteringVoice(&masterVoice);
}

uint32_t Audio::SoundLoadWave(const char* filename){
	++soundDataIndex_;

	//ファイル入力ストリームのインスタンス
	std::ifstream file;
	//wavファイルをバイナリモードで開く
	file.open(filename, std::ios_base::binary);
	//ファイルオープン失敗を検出する
	assert(file.is_open());

	//RIFFヘッダーの読み込み
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	//ファイルがRIFFかチェック
	if (strncmp(riff.chunk.id, "RIFE", 4) != 0) {
		assert(0);
	}
	//タイプがWAVEかチェック
	if (strncmp(riff.type, "WAVE", 4) != 0) {
		assert(0);
	}

	//Formatチャンクの読み込み
	FormatChunk format = {};
	//チャンクヘッダーの確認
	file.read((char*)&format, sizeof(ChunkHeader));
	if (strncmp(format.chunk.id, "fmt", 4) != 0) {
		assert(0);
	}

	//チャンク本体の読み込み
	assert(format.chunk.size <= sizeof(format.fmt));
	file.read((char*)&format.fmt, format.chunk.size);

	//Dataチャンクの読み込み
	ChunkHeader data;
	file.read((char*)&data, sizeof(data));
	//JUNKチャンクを検出した場合
	if (strncmp(data.id, "JUNK", 4) == 0) {
		//読み取り位置をJUNKチャンクの終わりまで進める
		file.seekg(data.size, std::ios_base::cur);
		//再読み込み
		file.read((char*)&data, sizeof(data));
	}

	if (strncmp(data.id, "data", 4) != 0) {
		assert(0);
	}

	//Dataチャンクのデータ部　(波形でーた)の読み込み
	char* pBuffer = new char[data.size];
	file.read(pBuffer, data.size);

	//Waveファイルを閉じる
	file.close();

	//returnする為の音声データ

	soundData_[soundDataIndex_].wfex = format.fmt;
	soundData_[soundDataIndex_].pBuffer = reinterpret_cast<BYTE*>(pBuffer);
	soundData_[soundDataIndex_].bufferSize = data.size;

	return soundDataIndex_;

}


void Audio::SoundUnload(){
	//バッファのメモリを解放
	for (int i = soundDataIndex_; soundDataIndex_ > 0; --i) {
		delete[] soundData_[i].pBuffer;

		soundData_[i].pBuffer = 0;
		soundData_[i].bufferSize = 0;
		soundData_[i].wfex = {};
	}
	soundDataIndex_ = 0;
}

void Audio::SoundPlayWave(IXAudio2* xAudio2){
	HRESULT result;

	//波形フォーマットを元にsourceVoiceの生成
	result = xAudio2->CreateSourceVoice(&pSourcevoice_[soundDataIndex_], &soundData_[soundDataIndex_].wfex);
	assert(SUCCEEDED(result));

	//再生する波形データの設定
	XAUDIO2_BUFFER buf{};
	buf.pAudioData = soundData_[soundDataIndex_].pBuffer;
	buf.AudioBytes = soundData_[soundDataIndex_].bufferSize;
	buf.Flags = XAUDIO2_END_OF_STREAM;

	//波形データの再生
	result = pSourcevoice_[soundDataIndex_]->SubmitSourceBuffer(&buf);
	result = pSourcevoice_[soundDataIndex_]->Start();

	assert(SUCCEEDED(result));
}

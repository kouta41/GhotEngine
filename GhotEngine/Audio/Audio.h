#pragma once
#include <string>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <cassert>
#include <mutex>
#include <set>
#include <array>
#include <unordered_map>
#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")
#include <wrl.h>


class Audio
{
public:
	//チャンクヘッダ
	struct ChunkHeader {
		char id[4];	//チャンク毎のID
		int32_t size;	//チャンクサイズ
	};

	//RIFFヘッダチャンク
	struct RiffHeader {
		ChunkHeader chunk;	//"RIFF"
		char type[4];	//"WAVE"
	};

	//FMTチャンク
	struct FormatChunk {
		ChunkHeader chunk;	//"fmt"
		WAVEFORMATEX fmt;	//波形フォーマット
	};

	//音声データ
	struct SoundData {
		//波形フォーマット
		WAVEFORMATEX wfex;
		//バッファの先頭アドレス
		BYTE* pBuffer;
		//バッファのサイズ
		unsigned int bufferSize;
	};

private:

	/// <summary>
	///  シングルトンインスタンスの生成
	/// </summary>
	/// <returns></returns>
	static Audio* GetInstance();

	/// <summary>
	///初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 音声データの読み込み
	/// </summary>
	/// <param name="filename"></param>
	/// <returns></returns>
	uint32_t SoundLoadWave(const char* filename);

	/// <summary>
	/// 音声データ解放
	/// </summary>
	/// <param name="soundData"></param>
	void SoundUnload();

	/// <summary>
	/// サウンドの再生
	/// </summary>
	/// <param name="xAudio2"></param>
	/// <param name="soundData"></param>
	void SoundPlayWave(IXAudio2* xAudio2);

private:
	Audio() = default;
	~Audio() = default;
	Audio(const Audio&) = default;
	const Audio& operator=(const Audio&) = delete;

public:
	// 読み込みの最大数
	static const int kMaxSoundData = 256;
	//Audio
	Microsoft::WRL::ComPtr<IXAudio2> xAudio2 = nullptr;
	IXAudio2MasteringVoice* masterVoice = nullptr;
	SoundData soundData_[kMaxSoundData] = {};
	uint32_t soundDataIndex_ = 0;
	IXAudio2SourceVoice* pSourcevoice_[kMaxSoundData] = {};
};


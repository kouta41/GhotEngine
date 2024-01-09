#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	worldTransform_.Initialize();
	viewProjection_.Initialize();
	//テクスチャ追加
	texHandleSkydome_ = TextureManager::Load("resources/skydome.jpg");
	playerTextureHandle_ = TextureManager::Load("resources/uvChecker.png");

	//player
	
	//自キャラの生成
	player_ = std::make_unique<Player>();
	//自キャラの初期化
	playerInitializePosition_ = { 0,0,0 };
	player_->Initialize(playerTextureHandle_, playerInitializePosition_);

	//enemyの生成	
	LoadEnemyPopData();

	//天球の生成と初期化
	//3Dモデルの生成
	skydome_ = std::make_unique<Skydome>();
	skydome_->Init(texHandleSkydome_);

	//メインカメラ
	mainCamera_ = std::make_unique<MainCamera>();
	mainCamera_->Initialize();

	mainCamera_->SetCountOffset({ 0.0f,1.4f,-7.0f });

	count = 0;
}

// 更新
void GameScene::Update() {
	worldTransform_.UpdateMatrix();
	viewProjection_.UpdateMatrix();

	//天球の更新
	skydome_->Update();

	//自キャラの更新
	player_->Update();
	
	//追従カメラのセット
	mainCamera_->SetTarget(&player_->GetWorldTransform());
	mainCamera_->Update();

	XINPUT_STATE joyState{};
	if (Input::GetInstance()->GetJoystickState(joyState)) {

		Input::GetInstance()->UpdateButtonState(a_, joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A);

		if (a_.isPressed && !a_.wasPressed) {
			//sceneNo_ = CLEAR;
		}
	}

	count++;
	if (count >= 900) {
		sceneNo_ = CLEAR;
	}

	viewProjection_.matView = mainCamera_->GetviewProjection_().matView;
	viewProjection_.matProjection = mainCamera_->GetviewProjection_().matProjection;
}

// 描画
void GameScene::Draw() {
	mainCamera_->Draw();
	//天球の描画
	skydome_->Draw(viewProjection_);
	//player
	player_->Draw(viewProjection_);

}

void GameScene::LoadEnemyPopData() {
	// ファイルを開く
	std::ifstream file;
	file.open("resources/enemyPop.csv");
	assert(file.is_open());

	// ファイルも内容を文字列ストリームにコピー
	enemyPopCommands << file.rdbuf();

	// ファイルを閉じる
	file.close();
}

void GameScene::UpdateEnemyPopCommands() {

	// 待機処理
	if (isWait) {
		waitTimer--;
		if (waitTimer <= 0) {
			// 待機完了
			isWait = false;
		}
		return;
	}

	// 1行分の文字列を入れる変数
	std::string line;

	// コマンド実行ループ
	while (getline(enemyPopCommands, line)) {
		// 1行分の文字列をストリームに変換して解析しやすくなる
		std::istringstream line_stream(line);

		std::string word;
		// ,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');

		// "//"から始まる行はコメント
		if (word.find("//") == 0) {
			// コメント行を飛ばす
			continue;
		}

		// POPコマンド
		if (word.find("POP") == 0) {
			// X座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			// Y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			// Z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			// 敵を発生させる
			EnemyInit(Vector3(x, y, z));
		}

		// WAITコマンド
		else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			// 待ち時間
			int32_t waitTime = atoi(word.c_str());

			// 待機開始
			isWait = true;
			waitTimer = waitTime;

			// コマンドループを抜ける
			break;
		}
	}
}

void GameScene::EnemyInit(Vector3 translation) {
	// 敵キャラの生成
	Enemy* enemy_ = new Enemy();
	// 敵キャラの初期化
	enemy_->Initialize(playerTextureHandle_, translation);
	// 敵キャラにゲームシーンを渡す
	//enemy_->SetGameScene(this);
	// 敵キャラに自キャラのアドレスを渡す
	//enemy_->SetPlayer(player_);
	GameScene::AddEnemy(enemy_);
}

void GameScene::AddEnemy(Enemy* enemy) {
	// リストに登録する
	enemys_.push_back(enemy);
}
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

	//天球の生成と初期化
	//3Dモデルの生成
	skydome_ = std::make_unique<Skydome>();
	skydome_->Init(texHandleSkydome_);
}

// 更新
void GameScene::Update() {
	worldTransform_.UpdateMatrix();
	viewProjection_.UpdateMatrix();

	//天球の更新
	skydome_->Update();
}

// 描画
void GameScene::Draw() {
	//天球の描画
	skydome_->Draw(viewProjection_);
}
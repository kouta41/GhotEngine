#pragma once
#include "Sprite.h"
#include "Triangle.h"
#include "Model.h"
#include "ModelSphere.h"
#include "ModelCube.h"
#include "Input.h"
#include "ImGuiManager/ImGuiManager.h"



/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	//3Dモデル
	std::unique_ptr<Model> model_{};

	//テクスチャ
	std::unique_ptr<Sprite> sprite_{};

	uint32_t texHandle_ = 0;

	Vector2 pos_ = { 0.0f,0.0f };
	Vector2 size_ = { 1.0f,1.0f };
	bool Flag = false;
};
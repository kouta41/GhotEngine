#pragma once
#include "Sprite.h"
#include "Triangle.h"
#include "Model.h"
#include "ModelSphere.h"
#include "ModelCube.h"
#include "Input.h"
#include "Skydome.h"
#include "MainCamera.h"
#include "ImGuiManager/ImGuiManager.h"
#include "IsScen.h"
#include "Player.h"
#include "Enemy.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene : public IScene {

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


	/// <summary>
	/// 敵発生データの読み込み
	/// </summary>
	void LoadEnemyPopData();

	/// <summary>
	/// 敵発生コマンドの更新
	/// </summary>
	void UpdateEnemyPopCommands();

	void EnemyInit(Vector3);

	void AddEnemy(Enemy* enemy);

private: // メンバ変数

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	//3Dモデル
	std::unique_ptr<Model> model_{};

	//テクスチャ
	std::unique_ptr<Sprite> sprite_{};

	uint32_t texHandle_ = 0;

	//天球
	std::unique_ptr<Skydome> skydome_{};
	//3Dモデル
	std::unique_ptr<Model> modelSkydome_{};
	//テクスチャ
	uint32_t texHandleSkydome_ = 0;
	
	//敵キャラ
	std::list<Enemy*> enemys_;
	// 待機タイマー
	int32_t waitTimer;
	// 待機フラグ
	bool isWait = false;

	// 敵発生コマンド
	std::stringstream enemyPopCommands;

	//メインカメラ
	std::unique_ptr<MainCamera> mainCamera_;

	/////player
	std::unique_ptr<Player> player_{};
	//Playerのモデル
	std::unique_ptr<Model> playerModel_{};
	//Playerのテクスチャハンドル
	uint32_t playerTextureHandle_{}; 
	Vector3 playerInitializePosition_{};

	Input::ButtonState a_{};

	float count = 0;
};
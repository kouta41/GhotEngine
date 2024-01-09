#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "Math.h"
#include "PlayerBullet.h"

class Enemy;

/// <summary>
/// 自キャラ
/// </summary>
class Player {
public:
	Player();
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void Initialize(uint32_t texHandle,Vector3 position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection& viewProjection);

	WorldTransform& GetWorldTransform() { return worldTransform_; }
	void SetWorldTransform(WorldTransform& worldTransform) { worldTransform_ = worldTransform; };
	void SetIsAlive(bool isAlive) { isAlive_ = isAlive; }

	Vector3& GetMove() { return move; }



	void SetEnemy(Enemy* enemy) { enemy_ = enemy; }
private:
	Enemy* enemy_;
	//ワールド変換データ
	WorldTransform worldTransform_;
	//3Dレティクル用ワールドトランスフォーム
	WorldTransform worldTransform3DReticle_;
	//モデル
	std::unique_ptr<Model> model_{};
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//キーボード入力
	Input* input_ = nullptr;
	//移動ベクトル
	Vector3 move{};

	bool isAlive_ = true;


	//弾
	std::list<PlayerBullet*> bullets_;

	//メインカメラ
	//::unique_ptr<MainCamera> mainCamera_;
};
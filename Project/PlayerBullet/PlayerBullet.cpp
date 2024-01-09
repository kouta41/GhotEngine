#include "PlayerBullet.h"


void PlayerBullet::Initialize(const Vector3& position, const Vector3& velocity) {
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("resources/black.png");
	model_.reset(Model::CreateObj("skydome.obj"));
	model_->SetTexHandle(textureHandle_);

	worldTransform_.Initialize();

	//因数で受け取った初期座標をセット
	worldTransform_.translate = position;

	//因数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;

}

void PlayerBullet::Update() {
	//座標を移動させる。
	worldTransform_.translate.x += velocity_.x;
	worldTransform_.translate.y += velocity_.y;
	worldTransform_.translate.z += velocity_.z;

	//時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	//ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	if (isDead_ == false) {
		model_->Draw(worldTransform_, viewProjection);
	}
}
Vector3 PlayerBullet::GetWorldPosition() {
	Vector3 worldPos;
	//ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.matWorld.m[3][0];
	worldPos.y = worldTransform_.matWorld.m[3][1];
	worldPos.z = worldTransform_.matWorld.m[3][2];

	return worldPos;
}

void PlayerBullet::OnCollision() {
	isDead_ = true;
}
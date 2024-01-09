#include "Enemy.h"

Enemy::~Enemy() {
	
}

void Enemy::Initialize(uint32_t textureHandle, Vector3 translation) {

	model_.reset(Model::CreateObj("skydome.obj"));
	model_->SetTexHandle(textureHandle);

	worldTransform_.Initialize();

	worldTransform_.translate = translation;

	//因数で受け取った初期座標をセット

	Approach();
}

void Enemy::ApproachUpdate() {
	//移動（ベクトルを加算）
	worldTransform_.translate.z -= velocity_.z;
	//規定の位置まで到達したら離脱
	if (worldTransform_.translate.z < 0.0f) {
		phase_ = Phase::Leave;
	}
	//発射タイマーをカウントダウン
	FireTimer--;
	if (FireTimer <= 0) {
		//弾を発射
		Fire();
		//発射タイマーを初期化
		FireTimer = kFireInterval;
	}
}

void Enemy::LeaveUpdate() {
	//移動（ベクトルを加算）
	worldTransform_.translate.y += velocity_.y;
	worldTransform_.translate.x -= velocity_.x;
}

void Enemy::Update() {
	//ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();

	switch (phase_) {
	case Phase::Approach:
	default:
		ApproachUpdate();
		break;

	case Phase::Leave:
		LeaveUpdate();
		break;
	}
}

void Enemy::Fire() {

	assert(player_);

	const float kBulletSpeed = 0.04f;
	Vector3 velocity(0, 0, kBulletSpeed);

	//速度ベクトルを自機の向きに合わせて回転させる
	velocity = TransformNormal(velocity, worldTransform_.matWorld);



	Vector3 end = player_->GetWorldTransform().translate;
	Vector3 start = GetWorldPosition();
	Vector3 kyori;
	kyori.x = end.x - start.x;
	kyori.y = end.y - start.y;
	kyori.z = start.z - end.z;
	Normalize(kyori);
	velocity.x = kyori.x * kBulletSpeed;
	velocity.y = kyori.y * kBulletSpeed;
	velocity.z = kyori.z * kBulletSpeed;

}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}

void Enemy::Approach() {
	//発射タイマーを初期化
	FireTimer = kFireInterval;
}

void Enemy::OnCollision() {

}



Vector3 Enemy::GetWorldPosition() {
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.matWorld.m[3][0];
	worldPos.y = worldTransform_.matWorld.m[3][1];
	worldPos.z = worldTransform_.matWorld.m[3][2];

	return worldPos;
}
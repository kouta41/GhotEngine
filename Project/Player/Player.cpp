#include "Player.h"
#include <cassert>
#include "Math.h"
#include "ImGuiManager.h"
#include <algorithm>


//NULLポインタチェック
Player::Player() {}

Player::~Player() {
	//bullet_の解放
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Player::Initialize(uint32_t texHandle,Vector3 position) {


	model_.reset(Model::CreateObj("skydome.obj"));
	model_->SetTexHandle(texHandle);


	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

	worldTransform_.Initialize();

	worldTransform_.translate = position;


	isAlive_ = true;

}

void Player::Update() {

	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
		});

	//弾更新
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}

	//ゲームパッドの状態を得る変数（XINPUT）
	XINPUT_STATE joyState{};

	//キャラクターの移動ベクトル
	move = { 0, 0, 0 };

	//キャラクターの移動の速さ
	const float kCharacterSpeed = 0.2f;

		//押した方向で移動ベクトルを変更(左右)
		if (input_->PushKey(DIK_LEFT)) {
			move.x -= kCharacterSpeed;
		}
		else if (input_->PushKey(DIK_RIGHT)) {
			move.x += kCharacterSpeed;
		}

		// 押した方向で移動ベクトルを変更(前後)
		if (input_->PushKey(DIK_UP)) {
			move.z += kCharacterSpeed;
		}
		else if (input_->PushKey(DIK_DOWN)) {
			move.z -= kCharacterSpeed;
		}

		//ゲームパッド状態取得
		if (Input::GetInstance()->GetJoystickState(joyState)) {
			//move.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed;
			//move.z += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed;
		}
		
		Attack();
		//move = TransformNormal(move, worldTransform_.matWorld);

		worldTransform_.translate.x += move.x;
		worldTransform_.translate.y += move.y;
		worldTransform_.translate.z += move.z;

}

void Player::Attack(){
	if (input_->PushKey(DIK_SPACE)) {

		//弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		//Vector3 kyori;

		//速度ベクトルを自機の向きに合わせて回転させる
		//velocity = TransformNormal(velocity, worldTransform_.matWorld);

		// 自機から照準オブジェクトへのベクトル
		//velocity.x = worldTransform3DReticle_.translate.x - GetWorldTransform().translate.x;
		//velocity.y = worldTransform3DReticle_.translate.y - GetWorldTransform().translate.y;
		//velocity.z = worldTransform3DReticle_.translate.z - GetWorldTransform().translate.z;

		velocity.x = Normalize(velocity).x * kBulletSpeed;
		velocity.y = Normalize(velocity).y * kBulletSpeed;
		velocity.z = Normalize(velocity).z * kBulletSpeed;


		//弾を生成し。初期化
		PlayerBullet* newBullet = new PlayerBullet();

		newBullet->Initialize(GetWorldTransform().translate, velocity);

		//弾を登録
		bullets_.push_back(newBullet);
	}

	XINPUT_STATE joyState{};


	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		//弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		//Vector3 kyori;

		//速度ベクトルを自機の向きに合わせて回転させる
		velocity = TransformNormal(velocity, worldTransform_.matWorld);

		// 自機から照準オブジェクトへのベクトル
		velocity.x = worldTransform3DReticle_.translate.x - GetWorldTransform().translate.x;
		velocity.y = worldTransform3DReticle_.translate.y - GetWorldTransform().translate.y;
		velocity.z = worldTransform3DReticle_.translate.z - GetWorldTransform().translate.z;

		velocity.x = Normalize(velocity).x * kBulletSpeed;
		velocity.y = Normalize(velocity).y * kBulletSpeed;
		velocity.z = Normalize(velocity).z * kBulletSpeed;


		//弾を生成し。初期化
		PlayerBullet* newBullet = new PlayerBullet();

		newBullet->Initialize(GetWorldTransform().translate, velocity);

		//弾を登録
		bullets_.push_back(newBullet);
	}
	
}



void Player::Draw(ViewProjection& viewProjection) {
//	model_->Draw(worldTransform_, viewProjection);
	// 弾描画
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
	
}

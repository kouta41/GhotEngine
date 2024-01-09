#include "MainCamera.h"

MainCamera::MainCamera()
{
}

MainCamera::~MainCamera()
{
}

//初期化
void MainCamera::Initialize() {
	viewProjection_.Initialize();
	viewProjection_.rotate = { 0.0f,0.0f,0.0f };

}

//更新
void MainCamera::Update() {

	//オフセットの変更
	if (Input::GetInstance()->PushKey(DIK_0)) {
		count.z += 0.1f;
	}
	else if (Input::GetInstance()->PushKey(DIK_9)) {
		count.z -= 0.1f;
	}

	if (Input::GetInstance()->PushKey(DIK_P)) {
		count.x += 0.1f;
	}
	else if (Input::GetInstance()->PushKey(DIK_O)) {
		count.x -= 0.1f;
	}

	if (Input::GetInstance()->PushKey(DIK_L)) {
		count.y += 0.1f;
	}
	else if (Input::GetInstance()->PushKey(DIK_K)) {
		count.y -= 0.1f;
	}

	//追従対象がいれば
	if (target_) {
		//追従対象からカメラまでのオフセット
		offset = { count.x,count.y,count.z };

		//カメラの角度から回転行列を計算
		Matrix4x4 rotateMatrix = MakeRotateMatrix(viewProjection_.rotate);
		// オフセットをカメラの回転に合わせて回転
		offset = TransformNormal(offset, rotateMatrix);


		//座標をコピーしてオフセット分ずらす
		viewProjection_.translate.x = target_->translate.x + offset.x;
		viewProjection_.translate.y = target_->translate.y + offset.y;
		viewProjection_.translate.z = target_->translate.z + offset.z;

	}

	viewProjection_.UpdateMatrix();
}

//描画
void MainCamera::Draw(){


	ImGui::End();
}
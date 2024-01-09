#include "ClearScene.h"

ClearScene::ClearScene()
{
}

ClearScene::~ClearScene()
{
	
}

void ClearScene::Initialize()
{
	texhandle_ = TextureManager::Load("resources/Clear.png");
	model_.reset(Model::CreateObj("cube.obj"));
	model_->SetTexHandle(texhandle_);
}

void ClearScene::Update()
{
	worldTransform_.UpdateMatrix();
	view_.UpdateMatrix();
	worldTransform_.translate.z = -50;

	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(joyState)) {
		Input::GetInstance()->UpdateButtonState(A, joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A);
		if (A.isPressed && !A.wasPressed) {
			sceneNo_ = TITLE;
		}
	}
	if (input_->PushKey(DIK_SPACE)) {
		sceneNo_ = TITLE;
	}
}

void ClearScene::Draw()
{
	model_->Draw(worldTransform_, view_);
	
}
#include "TitleScene.h"

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {
	//delete sprite_;
}

void TitleScene::Initialize()
{
	texhandle_ = TextureManager::Load("resources/Title.png");
	texhandle1_ = TextureManager::Load("resources/Setumei.png");

	model_.reset(Model::CreateObj("cube.obj"));
	model_->SetTexHandle(texhandle_);

	model_1.reset(Model::CreateObj("cube.obj"));
	model_1->SetTexHandle(texhandle1_);
}

void TitleScene::Update() {
	worldTransform_.UpdateMatrix();
	worldTransform1_.UpdateMatrix();
	view_.UpdateMatrix();
	view_1.UpdateMatrix();

	worldTransform1_.translate.z = -50;
	worldTransform_.translate.z = -50;
	worldTransform1_.translate.x = 2;
	XINPUT_STATE joyState{};
	if (Input::GetInstance()->GetJoystickState(joyState)) {

		Input::GetInstance()->UpdateButtonState(a_, joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A);

		if (a_.isPressed && !a_.wasPressed) {
			sceneNo_ = GAME;
		}
	}

	if (input_->PushKey(DIK_SPACE)) {
		sceneNo_ = GAME;
	}
	

}

void TitleScene::Draw()
{
	
	model_->Draw(worldTransform_, view_);
	model_1->Draw(worldTransform1_, view_1);

}
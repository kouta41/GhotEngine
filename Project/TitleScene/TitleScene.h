#pragma once
#include "IsScen.h"
#include "Input/Input.h"
#include "Model/Model.h"
#include "TextureManager.h"
#include "Sprite/Sprite.h"

class TitleScene : public IScene
{
public:

	TitleScene();
	~TitleScene();

	void Initialize()override;

	void Update()override;

	void Draw()override;

private:
	uint32_t texhandle_ = 0;
	uint32_t texhandle1_ = 0;
	Sprite* sprite_;
	//ワールド変換データ
	WorldTransform worldTransform_;
	WorldTransform worldTransform1_;

	ViewProjection view_{};
	ViewProjection view_1{};

	Input::ButtonState a_{};
	//モデル
	std::unique_ptr<Model> model_{};

	std::unique_ptr<Model> model_1{};
	//キーボード入力
	Input* input_ = nullptr;
};
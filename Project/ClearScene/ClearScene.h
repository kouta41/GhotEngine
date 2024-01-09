#pragma once
#include "IsScen.h"
#include "imgui.h"
#include "Input.h"
#include "IsScen.h"
#include "Input/Input.h"
#include "Model/Model.h"
#include "TextureManager.h"
#include "Sprite/Sprite.h"

class ClearScene : public IScene
{
public:

	ClearScene();
	~ClearScene();

	void Initialize()override;

	void Update()override;

	void Draw()override;

private:
	Input* input_{};
	Input::ButtonState A;

	uint32_t texhandle_ = 0;
	Sprite* sprite_;
	//ワールド変換データ
	WorldTransform worldTransform_;
	ViewProjection view_{};
	//モデル
	std::unique_ptr<Model> model_{};
	//キーボード入力
};
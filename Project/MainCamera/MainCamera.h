#pragma once
#include "Input.h"
#include "ImGuiManager/ImGuiManager.h"
#include "CameraRole.h"
#include "WorldTransform.h"
#include "Mathfunction.h"
class MainCamera
{
public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	MainCamera();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MainCamera();

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


	ViewProjection GetviewProjection_() { return viewProjection_; }
	void SetTarget(const WorldTransform* target) { target_ = target; }

	int linearStartFlag = true;

	void SetCountOffset(Vector3 count_) { count = count_; }
	void SetviewProjection_rotate(Vector3 viewProjection) { viewProjection_.rotate = viewProjection; }

private: // メンバ変数
	ViewProjection viewProjection_;

	//追尾対象
	const WorldTransform* target_ = nullptr;

	Vector3 offset;

	//オフセットを変える
	Vector3 count = { 0.0f,0.0f,0.0f };



	int originFlag = true;
	float linearStart = 0.0f;
	Vector3 rotateStart;
	Vector3 originOffsetStart;

	float linearEnd = 0;
	Vector3 rotateEnd;
	Vector3 originOffsetEnd;


	float linearStartFrame = 0;
	float secondStartFrame = 0;
	float endFrame = 180.0f;
	Input::ButtonState A;

};
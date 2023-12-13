#pragma once
#include "DirectX12.h"
#include "StringUtility.h"
#include "ShaderCompile.h"
#include "CreateResource.h"
#include "GraphicsPipeline.h"
#include "Matrix4x4.h"
#include "Mathfunction.h"
#include "WorldTransform.h"
#include "CameraRole.h"
#include "TextureManager.h"
#include "Vector2.h"

class Sprite {
public: // メンバ関数

	Sprite() = default;
	~Sprite();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// スプライト生成
	/// </summary>
	/// <param name="position"></param>
	/// <returns></returns>
	static Sprite* Create(Vector2 position={0.0f,0.0f}, Vector4 color = {1,1,1,1});

#pragma region Getter
	// 座標の取得
	const Vector2& GetPosition() const { return position_; }
	//サイズの取得
	const Vector2& GetSize()const { return size_; }
	//非表示フラグの取得
	const bool GetIsInvisible()const { return isInvisible_; }
#pragma endregion 

#pragma region Setter
	// 座標の設定
	void SetPosition(const Vector2& position) { position_ = position; }
	// 色の設定
	void SetColor(const Vector4& color) { *materialData_ = color; }
	//サイズの設定
	void SetSize(const Vector2& size) { size_ = size; }
	//非表示フラグの設定
	void SetIsInvisible(const bool isInvisible) { isInvisible_ = isInvisible; }
	//テクスチャの設定
	void SetTexHandle(const uint32_t texHandle) { texHandle_ = texHandle; }
#pragma endregion

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="v"></param>
	/// <param name="t"></param>
	void Draw(ViewProjection viewProjection);

private: // メンバ変数

	D3D12_VERTEX_BUFFER_VIEW sVBV_{};
	Resource sResource_ = {};
	WorldTransform worldTransform_ = {};
	Vector2 position_ = {};
	static Sprite* sprite_;
	Vector4* materialData_ = nullptr;
	Vector2 size_ = { 1.0f,1.0f };
	uint32_t texHandle_ = 0;


	//非表示フラグ
	bool isInvisible_ = false;
};


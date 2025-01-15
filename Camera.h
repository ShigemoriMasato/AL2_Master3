#pragma once
#include "Vector.h"
#include <assert.h>
#define WinSizeWidth 1280		//画面の横幅
#define WinSizeHeight 720		//画面の縦幅

class Camera {
public:

	Camera();

	/// <summary>
	/// スクリーン座標に転換する行列を作成する
	/// </summary>
	/// <param name="x">カメラのワールド中心座標</param>
	/// <param name="y">カメラのワールド中心座標</param>
	/// <param name="ratio">カメラの拡大率</param>
	void Update(float ratio = 1.0f);

	/// <summary>
	/// カメラの行列をもってくる
	/// </summary>
	/// <returns>カメラ行列</returns>
	Matrix3x3 GetCameraMatrix();

	Vector2 pos_;		//カメラの座標

private:
	
	/// <summary>
	///	 正規化した状態の行列を作る
	/// </summary>
	/// <param name="LT"></param>
	/// <param name="RB"></param>
	/// <returns></returns>
	Matrix3x3 MakeOrthographicProjectionMatirx(Vector2 LT, Vector2 RB);

	/// <summary>
	/// 実際に描画する大きさに戻す
	/// </summary>
	/// <param name="winSize"></param>
	/// <param name="LT"></param>
	/// <returns></returns>
	Matrix3x3 MakeViewportMatrix(Vector2 winSize, Vector2 LT);

	const Vector2 winSize_ = { WinSizeWidth, WinSizeHeight };
	const Vector2 world_ = { 0, 720 };

	Matrix3x3 matrix_;									//カメラの行列
};

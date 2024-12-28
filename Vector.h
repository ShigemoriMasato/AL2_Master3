#pragma once

struct Matrix3x3 {
	float m_[3][3];
};

struct Vector2 {
	float x;
	float y;
};


namespace M {

	/// <summary>
	/// Vector2 * Matrix
	/// </summary>
	/// <param name="vector"></param>
	/// <param name="matrix"></param>
	/// <returns>ポジション</returns>
	Vector2 Transform(Vector2 vector, Matrix3x3 matrix);

	/// <summary>
	/// matrix1 * matrix2
	/// </summary>
	/// <param name="matrix1"></param>
	/// <param name="matrix2"></param>
	/// <returns></returns>
	Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);

	/// <summary>
	/// 逆行列作成
	/// </summary>
	/// <param name="matrix">逆にしたい行列</param>
	/// <returns>逆行列</returns>
	Matrix3x3 Inverse(Matrix3x3 matrix);

	/// <summary>
	/// 回転行列を作成する
	/// </summary>
	/// <param name="theta">Radianで入力</param>
	/// <returns>回転行列</returns>
	Matrix3x3 MakeRotateMatrix(float theta);

	/// <summary>
	/// 平行移動する行列を作成する
	/// </summary>
	/// <param name="x">xの移動量</param>
	/// <param name="y">yの移動量</param>
	/// <returns>平行移動行列</returns>
	Matrix3x3 MakeTransformMatrix(float x, float y);

	/// <summary>
	/// 拡縮をする行列
	/// </summary>
	/// <param name="x">xの倍率</param>
	/// <param name="y">yの倍率</param>
	/// <returns>拡縮行列</returns>
	Matrix3x3 MakeScaleMatrix(float x, float y);

}

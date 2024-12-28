#pragma once
#include <limits>
#include "Vector.h"
#include "Object.h"

namespace UF {
	
	/// <summary>
	/// ベクトルを正規化する
	/// </summary>
	/// <param name="vector">正規化したいベクトル</param>
	/// <returns>正規化したベクトル</returns>
	Vector2 Normalize(Vector2 vector);

	/// <summary>
	/// float型のベクトル
	/// </summary>
	/// <param name="XorY">正規化したい要素</param>
	/// <param name="length">長さを指定</param>
	/// <returns>正規化したXorY</returns>
	float Normalize(float XorY, float length);

	/// <summary>
	/// 長さを別で指定する正規化
	/// </summary>
	/// <param name="vector">正規化したい値</param>
	/// <param name="length">指定する長さ</param>
	/// <returns></returns>
	Vector2 NormalizeLength(Vector2 vector, float length);

	/// <summary>
	/// その値が-か+かを判別する
	/// </summary>
	/// <param name="value">判別したい値</param>
	/// <returns>0未満なら-1, 0以上なら1</returns>
	float GetSign(float value);

	/// <summary>
	/// ベクトル同士の掛け算
	/// </summary>
	/// <param name="vector1">かけたいベクトル1</param>
	/// <param name="vector2">かけたいベクトル2</param>
	/// <returns></returns>
	Vector2 Multiply(Vector2 vector1, Vector2 vector2);

	/// <summary>
	/// 絶対値に変換する
	/// </summary>
	/// <param name="value">絶対値にしたい値</param>
	/// <returns>絶対値に変換した値</returns>
	float AbsoluteValue(float value);

	/// <summary>
	/// 最大値を求める
	/// </summary>
	/// <returns>最大値</returns>
	float SerchMax(float value1 = std::numeric_limits<float>::lowest(), float value2 = std::numeric_limits<float>::lowest(), float value3 = std::numeric_limits<float>::lowest(), float value4 = std::numeric_limits<float>::lowest(), float value5 = std::numeric_limits<float>::lowest(), float value6 = std::numeric_limits<float>::lowest(), float value7 = std::numeric_limits<float>::lowest(), float value8 = std::numeric_limits<float>::lowest(), float value9 = std::numeric_limits<float>::lowest(), float value10 = std::numeric_limits<float>::lowest());

	/// <summary>
	/// マウスのポジションを取得する
	/// </summary>
	/// <returns>マウスのポジション</returns>
	Vector2 GetMousePos();

};

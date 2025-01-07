#pragma once
#include "Object.h"

class Player;

class Rope {
public:
	
	Rope(bool type);

	void Update(Player* player, Camera* camera);

	void Draw();

	void SetActive(bool isActive);



	Vector2 a_;			//根本
	Vector2 b_;			//先端
	Vector2 mid_;		//垂れ下がるところ

	Vector2 line_[33];

	float length_;

	const int max_ = 32;	//分割数

	bool isActive_;		//座標更新を行うか
	bool type_;			//右側か左側か

private:

};

class Online : public Shape {
public:

	void Update(Camera& camera);

};

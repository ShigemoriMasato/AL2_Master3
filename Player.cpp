#include "Player.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Useful.h"

Player::Player() {

	InitializeShape(0, 16, 32, 32);

	speed_ = 4.0f;

}


void Player::Update(GameManager* gm, Camera* camera, Rope* rope[2]) {

	rope[0]->isActive_ = Novice::IsPressMouse(0);

	if (!rope[0]->isActive_) {
		rope[1]->isActive_ = Novice::IsPressMouse
	}

	for (int i = 0; i < 2; i++) {

		//各座標を設定する
		rope[i]->a_ = GetParentPos();
		Vbuffer = UF::Multiply(GetScale(), GetSize());


		if (isActive_) {
			int X;
			int Y;
			Novice::GetMousePosition(&X, &Y);
			rope[i]->b_ = { float(X), float(Y) };

			//二本より長かったら

		}

		//midの計算
		rope[i]->mid_.x = (rope[i]->a_.x + rope[i]->b_.x) / 2 + rope[i]->a_.y - rope[i]->b_.y;
		rope[i]->mid_.y = (rope[i]->a_.y + rope[i]->b_.y) / 2 + rope[i]->a_.x - rope[i]->b_.x;

		float t = 0;

		//最初の点だけ決めておく
		rope[i]->line_[0] = rope[i]->a_;

		for (int j = 0; j < rope[i]->max_ - 1; j++) {

			t = 1.0f / (rope[i]->max_ - j);

			rope[i]->line_[j + 1].x = (1.0f - t) * (1.0f - t) * rope[i]->a_.x + 2 * t * (1.0f - t) * rope[i]->mid_.x + t * t * rope[i]->b_.x;
			rope[i]->line_[j + 1].y = (1.0f - t) * (1.0f - t) * rope[i]->a_.y + 2 * t * (1.0f - t) * rope[i]->mid_.y + t * t * rope[i]->b_.y;

			rope[i]->line_[j + 1] = M::Transform(rope[i]->line_[j + 1], camera->GetCameraMatrix());

		}
	}
	
	Ready(kSRT, gm->bright_, camera);

}

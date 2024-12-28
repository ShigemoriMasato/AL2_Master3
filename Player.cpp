#include "Player.h"
#define _USE_MATH_DEFINES
#include <math.h>

Player::Player() {

	InitializeShape(0, 16, 32, 32);

	speed_ = 4.0f;

	sExtendT = 0.0f;

	tyakuti_ = true;
	isExtend_ = false;
}


void Player::Update(GameManager* gm, Camera* camera) {

	velocity_.x = 0;

	if (gm->keys_[DIK_A]) {
		velocity_.x = -speed_;
	}

	if (gm->keys_[DIK_D]) {
		velocity_.x = speed_;
	}

	if (gm->keys_[DIK_SPACE] && !gm->preKeys_[DIK_SPACE] && tyakuti_) {
		velocity_.y = 5.0f;
		tyakuti_ = false;
		isExtend_ = true;
		pos_.y++;
	}

	if (!tyakuti_) {

		velocity_.y -= 0.3f;

		if (pos_.y < size_.y) {
			velocity_.y = 0;
			pos_.y = size_.y;
			tyakuti_ = true;
		}
	}

	if (isExtend_) {
		SideExtend();
	}

	pos_.x += velocity_.x;
	pos_.y += velocity_.y;

	this->SReady(kSRT, gm->bright_, camera);

	Novice::ScreenPrintf(0, 0, "%f, %f", this->pos_.x, this->pos_.y);
	Novice::ScreenPrintf(0, 20, "%f, %f", this->LT_.x, this->LT_.y);
	Novice::ScreenPrintf(0, 40, "%f, %f", this->RB_.x, this->RB_.y);
}

void Player::SideExtend() {

	if (!tyakuti_) {



	}
	else {

		sExtendT += 0.3f;

		if (sExtendT > float(M_PI)) {
			sExtendT = 0.0f;
			isExtend_ = false;
		}

		expos_.y = sinf(sExtendT + float(M_PI)) * 0.3f * size_.y;

		scale_.y = sinf(sExtendT + float(M_PI)) * 0.3f + 1.0f;
		scale_.x = sinf(sExtendT) * 0.6f + 1.0f;
	}

}

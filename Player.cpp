#include "Player.h"
#define _USE_MATH_DEFINES
#include <math.h>

Player::Player() {

	InitializeShape(0, 16, 128, 128);

	speed_ = 4.0f;

	sfeT = 0.0f;

	landing_ = true;
	isFExtend_ = false;
}


void Player::Update(GameManager* gm, Camera* camera) {

	velocity_.x = 0;
	scale_ = { 1.0f, 1.0f };

	if (gm->keys_[DIK_A]) {
		velocity_.x = -speed_;
	}

	if (gm->keys_[DIK_D]) {
		velocity_.x = speed_;
	}

	if (velocity_.x != 0) {
		MoveExtend();
	}

	if (gm->keys_[DIK_SPACE] && !gm->preKeys_[DIK_SPACE] && landing_) {
		velocity_.y = 40.0f;
		landing_ = false;
		isFExtend_ = true;
		pos_.y++;
	}

	if (!landing_) {

		velocity_.y -= 1.5f;
	}

	if (pos_.y < size_.y) {
		velocity_.y = 0;
		pos_.y = size_.y;
		landing_ = true;
		sfeT = 0.0f;
	}

	if (isFExtend_) {
		FallExtend();
	}

	pos_.x += velocity_.x;
	pos_.y += velocity_.y;

	this->SReady(kSRT, gm->bright_, camera);

	Novice::ScreenPrintf(0, 0, "%f, %f", this->pos_.x, this->pos_.y);
	Novice::ScreenPrintf(0, 20, "%f, %f", this->LT_.x, this->LT_.y);
	Novice::ScreenPrintf(0, 40, "%f, %f", this->RB_.x, this->RB_.y);
}


//Extend系

void Player::MoveExtend() {

	smeT += 0.1f;

	if (smeT > float(M_PI)) {
		smeT -= float(M_PI);
	}

	expos1_.y = sinf(smeT) * 0.15f * size_.y;

	scale_.y *= 1.0f - sinf(smeT) * 0.15f;

}

void Player::FallExtend() {

	if (!landing_) {

		sfeT -= 0.15f;
		if (sfeT < 0.0f) {
			sfeT += 0.1f;
		}
		if (sfeT < -0.3f) {
			sfeT += 0.035f;
		}
		if (sfeT < -0.5f) {
			sfeT += 0.015f;
		}

		scale_.y *= sinf(sfeT + float(M_PI)) * 0.3f + 1.0f;
		scale_.x *= sinf(sfeT) * 0.6f + 1.0f;

	}
	else {

		sfeT += 0.3f;

		if (sfeT > float(M_PI)) {
			sfeT = 0.0f;
			isFExtend_ = false;
		}

		expos1_.y = sinf(sfeT + float(M_PI)) * 0.3f * size_.y;

		scale_.y *= sinf(sfeT + float(M_PI)) * 0.3f + 1.0f;
		scale_.x *= sinf(sfeT) * 0.6f + 1.0f;
	}

}

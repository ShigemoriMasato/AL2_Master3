#include "Player.h"
#include "Share.h"
#include "Ground.h"
#include "Collition.h"
#define _USE_MATH_DEFINES
#include <math.h>

Player::Player() {

	InitializeShape(0, 24, 48, 48);
	collition_.InitializeShape(0, 16, 48, 24);
	collition_.SetColor(0x555555ff);

	speed_ = 4.0f;

	sfeT = 0.0f;
	smeT = 0.0f;

	expos1_ = { 0 };
	expos2_ = { 0 };
	level_ = 0;

	landing_ = true;
	isFExtend_ = false;
	isAlive_ = true;
	preIsAlive_ = true;
}

void Player::Initialize() {
	SetColor(0xffffffff);
	bright_ = 255;

	pos_ = { 0, 24 };
	velocity_ = { 0, 0 };
	scale_ = { 1.0f, 1.0f };

	sfeT = 0.0f;
	smeT = 0.0f;

	expos1_ = { 0 };
	expos2_ = { 0 };
	level_ = 0;

	landing_ = true;
	isFExtend_ = false;
	isAlive_ = true;
	preIsAlive_ = true;
}

void Player::Update(GameManager* gm, Camera* camera, TEmitter* landemit, Ground* ground) {

	velocity_.x = 0;
	scale_ = { 1.0f, 1.0f };

	if (isAlive_) {

		if (gm->keys_[DIK_A]) {
			velocity_.x = -speed_;

			if (!gm->preKeys_[DIK_D] && !gm->preKeys_[DIK_A]) {
				smeT = 0.0f;
			}

		}

		if (gm->keys_[DIK_D]) {
			velocity_.x = speed_;

			if (!gm->preKeys_[DIK_D] && !gm->preKeys_[DIK_A]) {
				smeT = 0.0f;
			}

		}

		if (gm->keys_[DIK_SPACE] && !gm->preKeys_[DIK_SPACE] && landing_) {
			velocity_.y = 40.0f;
			landing_ = false;
			isFExtend_ = true;
			pos_.y++;
		}

	} else if (preIsAlive_) {
		velocity_.y = 40.0f;
		landing_ = false;
		isFExtend_ = true;
		pos_.y++;
		preIsAlive_ = false;
	}

	if (velocity_.x != 0) {
		MoveExtend();
	}

	if (!landing_ && pos_.y > -2000.0f) {

		velocity_.y -= 1.5f;
		
	}

	if (isAlive_) {
		if (velocity_.y < 0 && !landing_) {
			for (int i = 0; i < ground->step_.size(); i++) {
				if (CL::BtB(&collition_, &ground->step_[i].GetMain())) {
					landing_ = true;
					level_++;
					velocity_.y = 0;
					pos_.y = size_.y + ground->step_[i].pos_.y + 20.0f;
					sfeT = 0.0f;

					landemit->SetIsActive(true);
				} else {
					Vbuffer = this->GetCorner(0);
				}
			}
		}
	}

	if (isFExtend_) {
		FallExtend();
	}

	pos_.x += velocity_.x;
	pos_.y += velocity_.y;

	if (pos_.x < -640.0f + 32) {
		pos_.x = -640.0f + 32;
	}

	if (pos_.x > 640.0f - 32) {
		pos_.x = 640.0f - 32;
	}

	collition_.SetPos({ pos_.x, pos_.y - 12.0f });
	collition_.SetScale(scale_);

	this->SReady(kSRT, gm->bright_, camera);
	(&collition_)->SReady(kSRT, gm->bright_, camera);

	Novice::ScreenPrintf(0, 20, "%d, %d", isAlive_, preIsAlive_);
}


//Extend系

void Player::MoveExtend() {

	smeT += 0.1f;

	if (smeT > float(M_PI)) {
		smeT -= float(M_PI);
	}

	expos2_.y = -sinf(smeT) * 0.15f * size_.y;

	scale_.y *= 1.0f - sinf(smeT) * 0.15f;

}

Shape Player::GetCollition() const {
    return Shape(collition_);
}

int Player::GetLevel() const {
	return this->level_;
}

bool Player::GetIsAlive() const {
	return this->isAlive_;
}

void Player::SetIsAlive(bool isAlive)
{
	this->isAlive_ = isAlive;
}

void Player::SetIsStart(bool isStart) {
	this->isStart_ = isStart;
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


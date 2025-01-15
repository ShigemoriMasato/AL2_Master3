#include "Share.h"
#include "PlayScene.h"
#include "Useful.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace UF;

/*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*

Shape型Particle

+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*/

void SParticle::TestUpdate() {
	isActive_ = false;
}

void SParticle::JumpUpdate(Player* player) {

	if (doInitialize_) {
		doInitialize_ = false;

		pos_ = { player->GetPos().x, player->GetPos().y - 32.0f};
		Fbuffer = (player->GetVelocity().y - 15.0f) / 10.0f;
		alpha_ = 0xff;
		frame_ = 0;

		//今回はPositionではなくScaleとして使う
		endPos_ = { Fbuffer, Fbuffer };
		startPos_ = { 0.0f, 0.0f };
		t_ = 0.0f;

		direction_ = { GetSign(player->GetVelocity().x), 0.0f };

		if (endPos_.y <= 0.0f) {
			this->isActive_ = false;
		}
	}

	frame_++;

	if (frame_ > 5) {

		t_ += 0.1f;
		if (t_ > float(M_PI_2)) {
			t_ = float(M_PI_2);
		}

		//sinfで線形補完を行う
		scale_.x = (1.0f - sinf(t_)) * startPos_.x + sinf(t_) * endPos_.x;
		scale_.y = (1.0f - sinf(t_)) * startPos_.y + sinf(t_) * endPos_.y;

		if(direction_.x > 0.0f){
			Fbuffer = sinf(t_) * float(M_PI_4);
		}
		else {
			Fbuffer = sinf(t_) * float(M_PI_2) + float(M_PI_4);
		}

		direction_ = { cosf(Fbuffer), sinf(Fbuffer) };

		theta_ += 0.1f;
	}
	else {
		scale_.x = 0.0f;
		scale_.y = 0.0f;
	}

	if (t_ == float(M_PI_2)) {
		isActive_ = false;
	}

}

void SParticle::ParticleUpdate() {
	switch (mode_)
	{
	case sTest:
		TestUpdate();
		break;
	}
}

bool SParticle::GetIsActive() {
	return this->isActive_;
}


/*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*

Texture型Particle

+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*/

void TParticle::TestUpdate() {
	isActive_ = false;
}

void TParticle::LandingUpdate(Player* player, Camera* camera, GameManager* gm) {

	if (doInitialize_) {

		doInitialize_ = false;

		pos_ = player->GetPos();
		Fbuffer = -float(rand() % 6283184) / 100000;
		Fbuffer = Fbuffer + float(rand() % 2 * (float(M_PI) + 0.3f));
		direction_ = { cosf(Fbuffer), sinf(Fbuffer) };
		speed_ = float(rand() % 250) / 100 * 5.0f;
		theta_ = Fbuffer * 10;
	}

	theta_ += 0.03f;

	pos_.x += direction_.x * speed_;
	pos_.y += direction_.y * speed_;

	speed_ -= 0.3f;

	if (speed_ < 0) {
		speed_ = 0;
	}

	alpha_ -= 5;

	if (alpha_ < 0.0f) {
		isActive_ = false;
	}

	Ready(kSRT, gm->bright_, camera);

}

void TParticle::ParticleUpdate(PlayScene* ps) {
	switch (mode_)
	{
	case tTest:
		TestUpdate();
		break;

	case tLanding:
		LandingUpdate(ps->GetPlayer(), ps->GetCamera(), ps->GetGameManager());
		break;
	}
}

bool TParticle::GetIsActive() {
	return this->isActive_;
}

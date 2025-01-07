#include "Share.h"
#include "PlayScene.h"
#define _USE_MATH_DEFINES
#include <math.h>

/*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*

Shape型Particle

+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*/

void SParticle::TestUpdate() {
	isActive_ = false;
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
		buffer = -float(rand() % 6283184) / 100000;
		buffer = buffer + float(rand() % 2 * (float(M_PI) + 0.3f));
		direction_ = { cosf(buffer), sinf(buffer) };
		speed_ = float(rand() % 250) / 100 * 5.0f;
		theta_ = buffer * 10;
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

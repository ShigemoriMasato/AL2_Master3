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

void TParticle::ParticleUpdate(PlayScene* ps) {
	ps;
	switch (mode_)
	{
	case tTest:
		TestUpdate();
		break;

	}
}

bool TParticle::GetIsActive() {
	return this->isActive_;
}

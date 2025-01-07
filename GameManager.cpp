#include "GameManager.h"
#include <Novice.h>

GameManager::GameManager() {

	bright_ = 255;
	scene_ = Title;
	
	Novice::GetHitKeyStateAll(keys_);
	Novice::GetHitKeyStateAll(preKeys_);
}

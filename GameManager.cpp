#include "GameManager.h"

GameManager::GameManager() {

	bright_ = 255;
	scene_ = Title;

	for (int i = 0; i < 256; i++) {
		keys_[i] = 0;
		preKeys_[i] = 0;
	}

	enemyFrame2_ = 1;
	enemyFrame_ = 0;

}

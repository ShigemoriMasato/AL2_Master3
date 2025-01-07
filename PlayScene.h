#pragma once
#include "Player.h"
#include "Rope.h"

class PlayScene {
public:

	PlayScene();

	void Update();

	void Draw();

	GameManager* gm_;

private:
	Player* player_;
	Rope* rope_[2];
	Camera* camera_;
};


#include "Ground.h"
#include "Player.h"
#define INTERVAL 450

Ground::Ground() {
	step_.clear();
}

void Ground::Update(Camera* camera, GameManager* gm, Player* player) {

	step_.clear();

	int num = int(roundf(player->GetPosY() / INTERVAL - 3));

	for (int i = num; i < num + 6; i++) {
		Step buff{};
		buff.Initialize(i);
		buff.Update(camera, gm);
		step_.push_back(buff);
	}

}

void Ground::Draw() {
	for (int i = 0; i < step_.size(); i++) {
		step_[i].Draw();
	}
}


void Step::Initialize(int num) {

	pos_ = { 0, float(num) * INTERVAL - 20.0f };

	main.InitializeShape(pos_.x, pos_.y, 1280, 40);
	face.InitializeShape(pos_.x, pos_.y + 15.0f, 1280, 10, -1, 1, 1, 1, -1, -1, 1, -1, kQuad, kFillModeSolid, 0x555555ff);

}

void Step::Update(Camera* camera, GameManager* gm) {

	

	main.SReady(kSRT, gm->bright_, camera);
	face.SReady(kSRT, gm->bright_, camera);

}

void Step::Draw() {
	main.Draw();
	face.Draw();
}



Shape& Step::GetMain() {
	return main;
}

#include "PlayScene.h"

PlayScene::PlayScene() {
	player_ = new Player;
	gm_ = new GameManager();
	camera_ = new Camera();

	for (int i = 0; i < 2; i++) {
		rope_[i] = new Rope(bool(i));
	}

}

void PlayScene::Update() {

	player_->Update(gm_, camera_, rope_);

}

void PlayScene::Draw() {
	player_->Draw();

	for (int i = 0; i < 2; i++) {
		rope_[i]->Draw();
	}
}

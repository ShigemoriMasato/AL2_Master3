#include "Rope.h"
#include "Useful.h"
#include "Player.h"

Rope::Rope(bool type) {
	a_ = {};
	b_ = {};
	mid_ = {};
	length_ = 512.0f;
	type_ = type;
	isActive_ = false;
	for (int i = 0; i < 33; i++) {
		line_[i] = { 0 };
	}
}

void Rope::Update(Player* player, Camera* camera) {
	player;
	camera;
}

void Rope::Draw() {

	for (int i = 0; i < max_; i++) {
		Novice::DrawLine(int(line_[i].x), int(line_[i].y), int(line_[i + 1].x), int(line_[i + 1].y), WHITE);
	}

}

/*+*+*+*+*+*+*+*+*+*+*+*アクセサーメソッド**+*+*+*+*+*+*+*+*+*+*+**/

void Rope::SetActive(bool isActive) {
	this->isActive_ = isActive;
}

#define _USE_MATH_DEFINES
#include <math.h>
#include "Enemy.h"
#include "PlayScene.h"
#include "Collition.h"

void Enemy::Initialize(EnemyType type, float speed, float directionx, float directiony, float x, float y, float sizex, float sizey,
	float LTx, float LTy, float RTx, float RTy, float LBx, float LBy, float RBx, float RBy, DrawMode drawMode,
	FillMode fillMode, unsigned int color, int bright, bool isActive, BlendMode blend) {

	this->InitializeShape(x, y, sizex, sizey, LTx, LTy, RTx, RTy, LBx, LBy, RBx, RBy, drawMode, fillMode, color, bright, isActive, blend);

	this->type_ = type;

	speed_ = speed;
	direction_ = { directionx, directiony };
	initialize_ = true;

}

void Enemy::BulletUpdate(Player* player, GameManager* gm, Camera* camera) {

	//ただの直進
	pos_.x += direction_.x * speed_;
	pos_.y += direction_.y * speed_;

	//画面外退場
	if (pos_.x > 2560 + player->GetPos().x || pos_.x < -1280 || pos_.y > 1440 + player->GetPos().y || pos_.y < -720 + player->GetPos().y) {
		isActive_ = false;
	}

	if(CL::BtB(player, this)) {
		player->SetIsAlive(false);
	}

	SReady(kSRT, gm->bright_, camera);

}

void Enemy::RevolutionUpdate(Player* player, GameManager* gm, Camera* camera) {
	player;
	if (initialize_) {
		rotatePos_ = pos_;
		theta_ = float(rand() % 100000) / 10000;
		pos_ = { 0, 100 };
		initialize_ = false;
	}

	theta_ += 0.1f;

	SReady(kSRT, gm->bright_, camera);

}

void Enemy::AllUpdate(GameManager* gm, Camera* camera, PlayScene* ps) {

	switch (type_) {

	case kBullet:
		BulletUpdate(ps->GetPlayer(), gm, camera);
		break;

	case kRevolution:

		break;

	}

}

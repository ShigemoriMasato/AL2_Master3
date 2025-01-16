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

void PlayScene::EnemysUpdate() {
	//発生処理
	gm_->enemyFrame_++;

	Fbuffer = 60.0f - float(player_->GetLevel() / 2);
	if (Fbuffer < 10) {
		Fbuffer = 10;
	}

	if (gm_->enemyFrame_ > int(Fbuffer)) {
		Enemy enemy;
		enemy.Initialize(kRevolution, 2.0f, -2.0f, -1.0f, 360, player_->GetPos().y + 1280, 32, 32, -1, 1, 1, 1, -1, -1, 1, -1, kQuad, kFillModeSolid, 0x55a0a0ff);
		enemy.SReady(kSRT, gm_->bright_, camera_);
		enemys_.push_back(enemy);
		enemy.Initialize(kRevolution, 2.0f, 2.0f, -1.0f, -360, player_->GetPos().y + 1280, 32, 32, -1, 1, 1, 1, -1, -1, 1, -1, kQuad, kFillModeSolid, 0x55a0a0ff);
		enemy.SReady(kSRT, gm_->bright_, camera_);
		enemys_.push_back(enemy);
	}

	if (gm_->enemyFrame_ > Fbuffer) {

		Enemy enemy;
		enemy.Initialize(kBullet, 3, 0, -1, 0, player_->GetPos().y + 1280, 32, 32, -1, 1, 1, 1, -1, -1, 1, -1, kEllipse, kFillModeSolid, 0xaa5555ff);
		enemy.SReady(kSRT, gm_->bright_, camera_);
		enemys_.push_back(enemy);
		enemy.Initialize(kBullet, 3, 0, -1, -320, player_->GetPos().y + 1280, 32, 32, -1, 1, 1, 1, -1, -1, 1, -1, kEllipse, kFillModeSolid, 0xaa5555ff);
		enemy.SReady(kSRT, gm_->bright_, camera_);
		enemys_.push_back(enemy);
		enemy.Initialize(kBullet, 3, 0, -1, 320, player_->GetPos().y + 1280, 32, 32, -1, 1, 1, 1, -1, -1, 1, -1, kEllipse, kFillModeSolid, 0xaa5555ff);
		enemy.SReady(kSRT, gm_->bright_, camera_);
		enemys_.push_back(enemy);

		enemy.Initialize(kRevolution, 4.0f, -2.0f, -1.0f, 360, player_->GetPos().y + 1280, 32, 32, -1, 1, 1, 1, -1, -1, 1, -1, kQuad, kFillModeSolid, 0x55a0a0ff);
		enemy.SReady(kSRT, gm_->bright_, camera_);
		enemys_.push_back(enemy);
		enemy.Initialize(kRevolution, 4.0f, 2.0f, -1.0f, -360, player_->GetPos().y + 1280, 32, 32, -1, 1, 1, 1, -1, -1, 1, -1, kQuad, kFillModeSolid, 0x55a0a0ff);
		enemy.SReady(kSRT, gm_->bright_, camera_);
		enemys_.push_back(enemy);

		gm_->enemyFrame_ = 0;
	}

	for (int i = 0; i < enemys_.size(); i++) {
		enemys_[i].AllUpdate(gm_, camera_, this);

		if (!enemys_[i].GetIsActive()) {
			enemys_.erase(enemys_.begin() + i--);
		}
	}

	Novice::ScreenPrintf(0, 0, "Enemy:%d", enemys_.size());
}

void Enemy::BulletUpdate(Player* player, GameManager* gm, Camera* camera) {

	//ただの直進
	pos_.x += direction_.x * speed_;
	pos_.y += direction_.y * speed_;

	//画面外退場
	if (pos_.x > 2560 || pos_.x < -1280 || pos_.y > 1440 + player->GetPos().y || pos_.y < -360 + player->GetPos().y) {
		isActive_ = false;
	}

	if(CL::BtB(player, this)) {
		player->SetIsAlive(false);
	}

	SReady(kSRT, gm->bright_, camera);

}

void Enemy::RevolutionUpdate(Player* player, GameManager* gm, Camera* camera) {
	
	if (initialize_) {
		rotatePos_ = pos_;
		pos_ = { 0, 100 };
		initialize_ = false;
	}

	rotatePos_.x += direction_.x * speed_;
	rotatePos_.y += direction_.y * speed_;

	//画面外退場
	if (rotatePos_.x > 2560 || rotatePos_.x < -1280 || rotatePos_.y > 1440 + player->GetPos().y || rotatePos_.y < -360 + player->GetPos().y) {
		isActive_ = false;
	}

	theta_ -= 0.1f;
	rotateTheta_ += 0.1f;

	if(CL::BtB(player, this)) {
		player->SetIsAlive(false);
	}

	SReady(kSTR, gm->bright_, camera);

}

void Enemy::AllUpdate(GameManager* gm, Camera* camera, PlayScene* ps) {

	switch (type_) {

	case kBullet:
		BulletUpdate(ps->GetPlayer(), gm, camera);
		break;

	case kRevolution:
		RevolutionUpdate(ps->GetPlayer(), gm, camera);
		break;

	}

}

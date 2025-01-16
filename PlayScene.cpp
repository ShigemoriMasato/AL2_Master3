#define _USE_MATH_DEFINES
#include <math.h>
#include "PlayScene.h"
#include "Enemy.h"

//初期化(PlaySceneに含まれるすべてのコンストラクタを実行する)
PlayScene::PlayScene() {

	player_ = new Player();
	background_ = new Shape();
	gm_ = new GameManager();
	share_ = new Share();
	camera_ = new Camera();
	ground_ = new Ground();

	cT = float(M_PI);

	sEmitter_.clear();
	tEmitter_.clear();

	//Emitterの初期化
	SEmitter testEmitter;
	testEmitter.Initialize(sTest, 1, 30, false, 0, 0, 60, 60);
	sEmitter_.push_back(testEmitter);

	//ジャンプの煙
	SEmitter jumpEmitter;
	jumpEmitter.Initialize(sJump, 1, 3, true, 0, 0, 30, 30, -1, 1, 1, 1, -1, -1, 1, -1, kQuad, kFillModeSolid, 0xaaaaaaff, 255, true, kBlendModeAdd);
	sEmitter_.push_back(jumpEmitter);

	TEmitter testingEmitter;
	testingEmitter.Initialize(tTest, 1, 30, false, 0, 0, 60, 60, kTest_GH, 1, 1);
	tEmitter_.push_back(testingEmitter);

	//着地の煙
	TEmitter landingEmitter;
	landingEmitter.Initialize(tLanding, 24, 1, false, 0, 0, 60, 60, kParticle_GH, 600, 600, 1, 1, 1, 0x666666ff, 255, true, kBlendModeAdd);
	tEmitter_.push_back(landingEmitter);

	background_->InitializeShape(WinSizeWidth / 2, WinSizeHeight / 2, 1280, 720, -1, 1, 1, 1, -1, -1, 1, -1, kQuad, kFillModeSolid, 0x000000ff);

	window.InitializeShape(0, -480, 400, 320, -1, 1, 1, 1, -1, -1, 1, -1, kQuad, kFillModeSolid, 0x555555ff);

	gm_->bright_ = 0;
	gm_->bSetting_ = kBright;

	initialize = true;

}



void PlayScene::Update() {

	// キー入力を受け取る
	memcpy(gm_->preKeys_, gm_->keys_, 256);
	Novice::GetHitKeyStateAll(gm_->keys_);

	if (initialize) {
		initialize = false;

		gm_->bSetting_ = kBright;
		gm_->bright_ = 0;

		player_->Initialize();

		cooltime = 0;
		windT = 0.0f;

		share_->Initialize();

		window.SetColor(0);

		enemys_.clear();
	}

	//LandingEmitterの探索
	TEmitter* landing{};
	for (int i = 0; i < tEmitter_.size(); i++) {
		if (tEmitter_[i].GetMode() == tLanding) {
			landing = &tEmitter_[i];
			break;
		}
	}

	//ゲーム全体の明るさ処理
	switch (gm_->bSetting_) {
	case kBright:

		if (gm_->bright_ < 255) {
			gm_->bright_ += 3;
		}

		if (gm_->bright_ > 255) {
			gm_->bright_ = 255;
		}

		break;

	case kDark:


		if (gm_->bright_ < 100) {
			gm_->bright_ += 3;
		} else if (gm_->bright_ > 100) {
			gm_->bright_ -= 3;
		}

		if (gm_->bright_ < 103 && gm_->bright_ > 97) {
			gm_->bright_ = 100;
		}

		break;

	case kBlack:

		if (gm_->bright_ > 0) {
			gm_->bright_ -= 3;
		}

		if (gm_->bright_ < 0) {
			gm_->bright_ = 0;
		}

		break;
	}

	/*******************Player*******************/
	player_->Update(gm_, camera_, landing, ground_);
	
	/*******************Camera*******************/
	camera_->pos_.y = player_->GetPos().y - 240.0f;
	if (camera_->pos_.y < -40) {
		camera_->pos_.y = -40;
	}

	if (gm_->keys_[DIK_RSHIFT]) {
		
		if (cT > 0) {
			cT -= 0.1f;
		} else {
			cT = 0.0f;
		}

		Fbuffer = -1.0f;

	} else {

		if (cT < float(M_PI)) {
			cT += 0.1f;
		} else {
			cT = float(M_PI);
		}

		Fbuffer = 1.0f;

	}

	Fbuffer *= sinf(cT) * 0.03f;

	gm_->cRatio_ += Fbuffer;

	if (gm_->cRatio_ > 1.0f) {
		gm_->cRatio_ = 1.0f;
	}

	if (gm_->cRatio_ < 0.4f) {
		gm_->cRatio_ = 0.4f;
	}

	camera_->pos_.y += 1280.0f * (1.0f - gm_->cRatio_);

	camera_->Update(gm_->cRatio_);

	/*******************Enemy*******************/
	EnemysUpdate();

	/*******************Step*******************/
	ground_->Update(camera_, gm_, player_);

	/*******************BackGround*******************/
	background_->SReady(kScreen, gm_->bright_, camera_);

	/*******************GameOver*******************/
	if (!player_->GetIsAlive() && player_->GetPos().y < -240.0f) {
		EndUpdate();
	}

	/*******************Particle*******************/
	//SParticleの処理
	for (int i = 0; i < sEmitter_.size(); i++) {
		sEmitter_[i].Appearance(share_->GetSParticle());
	}

	share_->ShapeParticleUpdate();

	//TParticleの処理
	for (int i = 0; i < tEmitter_.size(); i++) {
		tEmitter_[i].Appearance(share_->GetTParticle());
	}

	share_->TextureParticleUpdate(this);

}

void PlayScene::EndUpdate() {
	
	cooltime++;

	window.SetColor(0x555555ff);

	if(cooltime > 60) {
		windT += 0.05f;

		if(windT > float(M_PI_2)) {
			windT = float(M_PI_2);
		}

		window.SetPos({
			640.0f,
			-360.0f * (1.0f - sinf(windT)) + 360.0f * sinf(windT)
			});

		Novice::ScreenPrintf(520, int(window.GetPos().y - 10.0f), "Game Over");
		Novice::ScreenPrintf(550, int(window.GetPos().y + 40.0f), "Your climbed Num:	%d", player_->GetLevel());

		window.SReady(kScreen, gm_->bright_, camera_);
	}

}



void PlayScene::Draw() {

	//背景
	background_->Draw();

	for(int i = 0; i < enemys_.size(); i++) {
		enemys_[i].Draw();
	}

	player_->Draw();

	ground_->Draw();

	share_->Draw();

	if (!player_->GetIsAlive() && player_->GetPos().y <= -1000.0f) {
		window.Draw();
	}

}




Player* PlayScene::GetPlayer() {
	return player_;
}

GameManager* PlayScene::GetGameManager() {
	return gm_;
}

Camera* PlayScene::GetCamera() {
	return camera_;
}

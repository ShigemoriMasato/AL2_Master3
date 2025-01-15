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

}



void PlayScene::Update() {

	// キー入力を受け取る
	memcpy(gm_->preKeys_, gm_->keys_, 256);
	Novice::GetHitKeyStateAll(gm_->keys_);

	//LandingEmitterの探索
	TEmitter* landing{};
	for (int i = 0; i < tEmitter_.size(); i++) {
		if (tEmitter_[i].GetMode() == tLanding) {
			landing = &tEmitter_[i];
			break;
		}
	}

	/*******************Player*******************/
	player_->Update(gm_, camera_, landing, ground_);
	
	/*******************Camera*******************/
	camera_->pos_.y = player_->GetPos().y + 120;
	if (camera_->pos_.y < 340) {
		camera_->pos_.y = 340;
	}

	if (gm_->keys_[DIK_LSHIFT]) {
		if (gm_->cRatio_ > 0.5f) {
			gm_->cRatio_ -= 0.025f;
		} else {
			gm_->cRatio_ = 0.5f;
		}
	} else {
		if (gm_->cRatio_ < 1.0f) {
			gm_->cRatio_ += 0.025f;
		} else {
			gm_->cRatio_ = 1.0f;
		}
	}

	camera_->Update(gm_->cRatio_);

	/*******************Enemy*******************/
	EnemysUpdate();

	/*******************Step*******************/
	ground_->Update(camera_, gm_, player_);

	/*******************BackGround*******************/
	background_->SReady(kScreen, gm_->bright_, camera_);


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

void PlayScene::Draw() {

	//背景
	background_->Draw();

	for(int i = 0; i < enemys_.size(); i++) {
		enemys_[i].Draw();
	}

	player_->Draw();

	ground_->Draw();

	share_->Draw();

}

void PlayScene::EnemysUpdate()
{
	//発生処理
	gm_->enemyFrame_++;

	Fbuffer = 60.0f - float(player_->GetLevel());
	if (Fbuffer < 1) {
		Fbuffer = 1;
	}

	if(gm_->enemyFrame_ > Fbuffer) {


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

		gm_->enemyFrame_ = 0;
	}

	for (int i = 0; i < enemys_.size(); i++) {
		enemys_[i].AllUpdate(gm_, camera_, this);
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

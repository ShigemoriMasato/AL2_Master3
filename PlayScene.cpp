#include "PlayScene.h"

//初期化(PlaySceneに含まれるすべてのコンストラクタを実行する)
PlayScene::PlayScene() {

	player_ = new Player();
	background_ = new Shape();

	sEmitter_.clear();
	tEmitter_.clear();

	//Emitterの初期化
	SEmitter testEmitter;
	testEmitter.Initialize(sTest, 1, 30, false, 0, 0, 60, 60);
	sEmitter_.push_back(testEmitter);

	TEmitter testingEmitter;
	testingEmitter.Initialize(tTest, 1, 30, false, 0, 0, 60, 60, kTest_GH, 1, 1);
	tEmitter_.push_back(testingEmitter);

	//着地の煙
	TEmitter landingEmitter;
	landingEmitter.Initialize(tLanding, 16, 1, false, 0, 0, 80, 80, kParticle_GH, 80, 80, 1, 1, 0x555555ff, 255, true, kBlendModeAdd);
	tEmitter_.push_back(landingEmitter);

	background_->InitializeShape(WinSizeWidth / 2, WinSizeHeight / 2, 1280, 720, -1, 1, 1, 1, -1, -1, 1, -1, kQuad, kFillModeSolid, 0x888888ff);

}



void PlayScene::Update(GameManager* gm, Share* share, Camera* camera) {
	
	/*******************Player*******************/
	player_->Update(gm, camera);

	/*******************Camera*******************/
	camera->Update();

	/*******************BackGround*******************/
	background_->SReady(kScreen, gm->bright_, camera);


	/*******************Particle*******************/
	//SParticleの処理
	for (int i = 0; i < sEmitter_.size(); i++) {
		sEmitter_[i].Appearance(&sEmitter_[i], share->GetSParticle());
	}

	for (int i = 0; i < sEmitter_.size(); i++) {
		share->ShapeParticleUpdate();
	}

	//TParticleの処理
	for (int i = 0; i < tEmitter_.size(); i++) {
		tEmitter_[i].Appearance(&tEmitter_[i], share->GetTParticle());
	}

	for (int i = 0; i < tEmitter_.size(); i++) {
		share->TextureParticleUpdate();
	}

}

void PlayScene::Draw() {

	//背景
	background_->Draw();

	player_->Draw();

}

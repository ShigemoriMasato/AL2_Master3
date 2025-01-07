#pragma once
#include "Camera.h"
#include "GameManager.h"
#include "Share.h"
#include "Player.h"
#include "Ground.h"

class PlayScene {
public:

	PlayScene();

	/// <summary>
	/// 全体の更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 全体の描画処理
	/// </summary>
	void Draw();

	Player* GetPlayer();
	Camera* GetCamera();
	GameManager* GetGameManager();

private:
	//背景
	Shape* background_;

	//使用するObject
	Player* player_;

	//ゲーム設定
	GameManager* gm_;
	Camera* camera_;
	Share* share_;
	Ground* ground_;

	//Emitter
	std::vector<SEmitter> sEmitter_;
	std::vector<TEmitter> tEmitter_;

};


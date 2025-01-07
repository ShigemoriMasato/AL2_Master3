#pragma once
#include "Camera.h"
#include "GameManager.h"
#include "Share.h"
#include "Player.h"

class PlayScene {
public:

	PlayScene();

	/// <summary>
	/// 全体の更新処理
	/// </summary>
	void Update(GameManager* gm, Share* share, Camera* camera);
	/// <summary>
	/// 全体の描画処理
	/// </summary>
	void Draw();

private:
	//背景
	Shape* background_;

	//使用するObject
	Player* player_;

	//Emitter
	std::vector<SEmitter> sEmitter_;
	std::vector<TEmitter> tEmitter_;

};


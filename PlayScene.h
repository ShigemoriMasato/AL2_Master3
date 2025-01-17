﻿#pragma once
#include "Camera.h"
#include "GameManager.h"
#include "Share.h"
#include "Player.h"
#include "Ground.h"

class Enemy;

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

	/// <summary>
	/// エネミーの全体処理
	/// </summary>
	void EnemysUpdate();

	/// <summary>
	/// ゲームオーバーの時の更新処理
	/// </summary>
	void EndUpdate();

	Player* GetPlayer();
	Camera* GetCamera();
	GameManager* GetGameManager();

	bool initialize;

private:
	//背景
	Shape* background_;

	//使用するObject
	Player* player_;
	std::vector<Enemy> enemys_;

	//ゲーム設定
	GameManager* gm_;
	Camera* camera_;
	Share* share_;
	Ground* ground_;
	float cT;

	int cooltime;		//ゲームオーバーで使う雑なクールタイム
	Shape window;		//背景
	float windT;		//背景制御用

	//Emitter
	std::vector<SEmitter> sEmitter_;
	std::vector<TEmitter> tEmitter_;

};


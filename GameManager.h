#pragma once
#include "Camera.h"

struct GameManager {

	GameManager();

	float cRatio_ = 1.0f;		//カメラの拡大率

	/// <summary>
	/// シーンまとめ
	/// </summary>
	enum Scene {
		Title,
		Play,
		Clear,

	}scene_;					//シーン遷移用

	//ゲーム全体の明るさ
	int bright_ = 255;
	int enemyFrame_ = 0;		//エネミーの生成間隔
	
	char keys_[256];			//キー入力
	char preKeys_[256];		//1frame前のキー入力
	
};

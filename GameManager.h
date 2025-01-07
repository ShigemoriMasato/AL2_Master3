#pragma once
#include "Camera.h"

struct GameManager {

	GameManager();

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
	
	char keys_[256];			//キー入力
	char preKeys_[256];		//1frame前のキー入力
	
};

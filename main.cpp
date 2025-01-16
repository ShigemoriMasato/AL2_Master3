#include <Novice.h>
#include <math.h>
#include <time.h>
#include "PlayScene.h"

const char kWindowTitle[] = "LC1A_10_シゲモリ_マサト_AnkoGaNoboruGame";

int globalTexture[30];
float Fbuffer;
int Ibuffer;
Vector2 Vbuffer;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, WinSizeWidth, WinSizeHeight);

	PlayScene* playscene = new PlayScene();

	globalTexture[kTest_GH] = Novice::LoadTexture("./NoviceResources/white1x1.png");
	globalTexture[kParticle_GH] = Novice::LoadTexture("./Resources/particle.png");

	srand(int(time(nullptr)));

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		///
		/// ↓更新処理ここから
		///
		
		playscene->Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		playscene->Draw();

		///
		/// ↑描画処理ここまで
		///

		//R押すとゲームをリセット
		if (playscene->GetGameManager()->keys_[DIK_R] && !playscene->GetGameManager()->preKeys_[DIK_R]) {
			playscene->GetGameManager()->bSetting_ = kBlack;
		}

		if (playscene->GetGameManager()->bright_ == 0) {
			playscene->initialize = true;
		}

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (playscene->GetGameManager()->preKeys_[DIK_ESCAPE] == 0 && playscene->GetGameManager()->keys_[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

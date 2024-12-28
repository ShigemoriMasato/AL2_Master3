#include <Novice.h>
#include "Player.h"

const char kWindowTitle[] = "学籍番号";

int globalTexture[30];
float buffer;
Vector2 Vbuffer;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Player* player = new Player();
	GameManager* gm = new GameManager();
	Camera* camera = new Camera();

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(gm->preKeys_, gm->keys_, 256);
		Novice::GetHitKeyStateAll(gm->keys_);

		///
		/// ↓更新処理ここから
		///

		player->Update(gm, camera);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		player->Draw();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

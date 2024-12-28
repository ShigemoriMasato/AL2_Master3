#include "Camera.h"
#include "Object.h"

Camera::Camera() {

	Update();

}

Matrix3x3 Camera::MakeCameraMatrix(Vector2 pos) {
	//ビュー行列の作成
	Matrix3x3 ans = {
		{
			{1,0,0},
			{0,1,0},
			{pos.x, pos.y, 1}
		}
	};

	return ans;
}

Matrix3x3 Camera::MakeOrthographicProjectionMatirx(Vector2 LT, Vector2 RB) {
	//正射影行列を作成
	Matrix3x3 ans = {
		{
			{2.0f / (RB.x - LT.x), 0, 0},
			{0, 2.0f / (LT.y - RB.y), 0},
			{(LT.x + RB.x) / (LT.x - RB.x), (LT.y + RB.y) / (RB.x - LT.y), 1}
		}
	};

	return ans;
}

Matrix3x3 Camera::MakeViewportMatrix(Vector2 winSize, Vector2 LT) {
	//ビューポート変換用行列を作成
	Matrix3x3 ans = {
		{
			{winSize.x / 2, 0, 0},
			{0, -winSize.y / 2, 0},
			{LT.x + winSize.x / 2, LT.y + winSize.y / 2, 1}
		}
	};

	return ans;
}

void Camera::Update(float x, float y, float ratio) {
	//各々のパラメータをVector2に代入
	Vector2 pos = { x - this->winSize_.x / 2, this->world_.y - y - this->winSize_.y / 2 };
	Vector2 LT = { -this->winSize_.x / 2, this->winSize_.y / 2 };
	Vector2 RB = { this->winSize_.x / 2, -this->winSize_.y / 2 };
	Vbuffer = { this->winSize_.x * ratio, this->winSize_.y * ratio };

	//カメラのマトリックスを作成
	this->matrix_ = M::Multiply(M::Multiply(MakeCameraMatrix(pos), MakeOrthographicProjectionMatirx(LT, RB)), MakeViewportMatrix(Vbuffer, LT));

}

Matrix3x3 Camera::GetCameraMatrix() {
	return this->matrix_;
}

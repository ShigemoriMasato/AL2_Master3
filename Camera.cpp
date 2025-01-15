#include "Camera.h"
#include "Object.h"

Camera::Camera() {

	pos_ = { 0.0f, -360.0f };
	Update();

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

Matrix3x3 Camera::MakeViewportMatrix(Vector2 winSize, Vector2 localLT) {
	//ビューポート変換用行列を作成
	Matrix3x3 ans = {
		{
			{winSize.x / 2, 0, 0},
			{0, -winSize.y / 2, 0},
			{localLT.x + winSize.x / 2, localLT.y + winSize.y / 2, 1}
		}
	};

	return ans;
}

void Camera::Update(float ratio) {
	//各々のパラメータをVector2に代入
	Vector2 LT = { -WinSizeWidth / 2, WinSizeHeight / 2 };
	Vector2 RB = { WinSizeWidth / 2, -WinSizeHeight / 2 };
	Vbuffer = { 640.0f - 640.0f * ratio, 360.0f * ratio };

	//カメラのマトリックスを作成
	matrix_ = M::Multiply(M::Multiply(M::Inverse(M::MakeTransformMatrix(pos_.x, pos_.y)), MakeOrthographicProjectionMatirx(LT, RB)), MakeViewportMatrix({WinSizeWidth * ratio, WinSizeHeight * ratio}, Vbuffer));
	
}

Matrix3x3 Camera::GetCameraMatrix() {
	return this->matrix_;
}

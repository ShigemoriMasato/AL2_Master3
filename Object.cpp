#include "Object.h"
#include "Useful.h"
#include <math.h>

/// <summary>
/// このファイルでしか使えなくするコマンド
/// </summary>
namespace {
	/// <summary>
	/// Shape型の初期化に使用する
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="length"></param>
	/// <returns></returns>
	Vector2 GetShapePoint(float x, float y, float length) {
		Vbuffer = { UF::Normalize(x, length), UF::Normalize(y, length) };
		return Vbuffer;
	}

	/// <summary>
	/// 一番長い正規化した時の長さを返す
	/// </summary>
	/// <returns></returns>
	float SearchLength(float x, float y, float buff) {
		buffer = x * x + y * y;
		if (buff < buffer) {
			return buffer;
		} else {
			return buff;
		}
	}
}

/*************************************************************************************************
*
*		Object
*
**************************************************************************************************/

void Object::InitializeObj(float x, float y, float sizex, float sizey, unsigned int color, int bright, bool isActive, BlendMode blend) {
	
	size_ = { sizex / 2, sizey / 2 };

	/**********************行列関係****************************/
	this->LT_ = { -sizex / 2, sizey / 2 };
	this->RT_ = { sizex / 2, sizey / 2 };
	this->LB_ = { -sizex / 2, -sizey / 2 };
	this->RB_ = { sizex / 2, -sizey / 2 };
	
	/**********************座標関係****************************/
	this->pos_ = { x, y };
	this->expos1_ = { 0 };
	this->scale_ = { 1.0f, 1.0f };
	this->theta_ = 0.0f;
	this->speed_ = 0;
	this->velocity_ = { 0 };
	this->direction_ = { 0 };

	/***********************色関係*****************************/
	this->red_ = color / 0x1000000;
	color -= this->red_ * 0x1000000;

	this->green_ = color / 0x10000;
	color -= this->green_ * 0x10000;

	this->blue_ = color / 0x100;
	color -= this->blue_ * 0x100;

	this->alpha_ = color;

	this->bright_ = bright;

	this->blendMode_ = blend;

	/*************************flug関係********************************/
	this->isActive_ = isActive;
}

void Object::SetColor(int bright) {
	//明るさの割合を求める
	float ratio = float(this->bright_) / 255;		//オブジェクト固有の明るさ
	ratio *= float(bright) / 255;					//ワールド全体の明るさ

	//明るさの適用
	this->red_ = int(roundf(this->red_ * ratio));
	this->green_ = int(roundf(this->green_ * ratio));
	this->blue_ = int(roundf(this->blue_ * ratio));

	//カラーに当てはめる
	this->color_ = (this->red_ << 24) + (this->green_ << 16) + (this->blue_ << 8) + (this->alpha_);
}

void Object::Ready(MatrixMode mode, int bright, Camera* const camera) {
	//色の設定
	this->SetColor(bright);

	//行列の作成
	switch (mode) {
	case kSRT:

		this->matrix_ = M::Multiply(M::Multiply(M::MakeScaleMatrix(this->scale_.x, this->scale_.y), M::MakeRotateMatrix(this->theta_)), M::MakeTransformMatrix(this->pos_.x, this->pos_.y));

		break;
	case kSTR:

		this->matrix_ = M::Multiply(M::Multiply(M::MakeScaleMatrix(this->scale_.x, this->scale_.y), M::MakeTransformMatrix(this->pos_.x, this->pos_.y)), M::MakeRotateMatrix(this->theta_));

		break;
	}

	//上で作った行列とカメラをかけたものを座標に適用する
	this->sLT_ = M::Transform(this->LT_, M::Multiply(this->matrix_, camera->GetCameraMatrix()));
	this->sRT_ = M::Transform(this->RT_, M::Multiply(this->matrix_, camera->GetCameraMatrix()));
	this->sLB_ = M::Transform(this->LB_, M::Multiply(this->matrix_, camera->GetCameraMatrix()));
	this->sRB_ = M::Transform(this->RB_, M::Multiply(this->matrix_, camera->GetCameraMatrix()));
}

//================================
//	アクセサーメソッド
//================================

float Object::GetPosX() const {
	return this->pos_.x;
}

float Object::GetPosY() const {
	return this->pos_.y;
}

Vector2 Object::GetPos() const {
	return this->pos_;
}

void Object::SetPos(Vector2 pos) {
	this->pos_ = pos;
}

Vector2 Object::GetCorner(int type) {

	switch (type) {
	case 0:
		return M::Transform(LT_, matrix_);
		break;

	case 1:
		return M::Transform(RT_, matrix_);
		break;

	case 2:
		return M::Transform(LB_, matrix_);
		break;

	case 3:
		return M::Transform(RB_, matrix_);
		break;
	}

	return { 0,0 };

}

/*************************************************************************************************
*
*		Shape
*
**************************************************************************************************/


void Shape::InitializeShape(float x, float y, float sizex, float sizey,
	float LTx, float LTy, float RTx, float RTy, float LBx, float LBy, float RBx, float RBy, DrawMode drawMode,
	FillMode fillMode, unsigned int color, int bright, bool isActive, BlendMode blend) {

	///初期化
	this->InitializeObj(x, y, sizex, sizey, color, bright, isActive, blend);

	//modeの入力
	this->fillMode_ = fillMode;
	this->drawMode_ = drawMode;

	//図形を囲む四角形の座標を作成
	this->baseLT_ = this->LT_;
	this->baseRT_ = this->RT_;
	this->baseLB_ = this->LB_;
	this->baseRB_ = this->RB_;

	//一番外側に伸びてる点を探索する
	float buff = LTx * LTx + LTy * LTy;
	buff = SearchLength(RTx, RTy, buff);
	buff = SearchLength(LBx, LBy, buff);
	buff = SearchLength(RBx, RBy, buff);
	buff /= 2;

	//正規化した各点の情報を代入する
	this->infLT_ = GetShapePoint(LTx, LTy, buff);
	this->infRT_ = GetShapePoint(RTx, RTy, buff);
	this->infLB_ = GetShapePoint(LBx, LBy, buff);
	this->infRB_ = GetShapePoint(RBx, RBy, buff);
}

void Shape::SReady(MatrixMode mode, int bright, Camera* const camera) {

	//正規化された座標とサイズをかけ合わせる
	this->LT_ = UF::Multiply(this->baseLT_, this->infLT_);
	this->RT_ = UF::Multiply(this->baseRT_, this->infRT_);
	this->LB_ = UF::Multiply(this->baseLB_, this->infLB_);
	this->RB_ = UF::Multiply(this->baseRB_, this->infRB_);

	parentPos_ = { pos_.x + expos1_.x, pos_.y + expos1_.y };

	//色の設定
	this->SetColor(bright);

	//======================
	//行列の作成
	//======================
	//円の場合
	if (this->drawMode_ == kEllipse) {

		switch (mode) {
		case kSRT:
			//ST(Rは描画で)
			this->matrix_ = M::Multiply(M::MakeScaleMatrix(this->scale_.x, this->scale_.y), M::MakeTransformMatrix(this->parentPos_.x, this->parentPos_.y));

			break;
		case kSTR:
			//回転させる(TRの作成)
			Vbuffer = { cosf(this->theta_) * this->parentPos_.x, sinf(this->theta_) * this->parentPos_.y };
			
			//S TR
			this->matrix_ = M::Multiply(M::MakeScaleMatrix(this->scale_.x, this->scale_.y), M::MakeTransformMatrix(Vbuffer.x, Vbuffer.y));
			//中心をずらす
			this->matrix_ = M::Multiply(this->matrix_, M::MakeTransformMatrix(this->rotatePos_.x, this->rotatePos_.y));

			break;
		}

	} 
	//四角形の場合
	else if(this->drawMode_ == kQuad) {
		switch (mode) {
		case kSRT:
			//SR
			this->matrix_ = M::Multiply(M::MakeScaleMatrix(this->scale_.x, this->scale_.y), M::MakeRotateMatrix(this->theta_));
			//T
			this->matrix_ = M::Multiply(this->matrix_, M::MakeTransformMatrix(this->parentPos_.x, this->parentPos_.y));

			break;
		case kSTR:
			//ST
			this->matrix_ = M::Multiply(M::MakeScaleMatrix(this->scale_.x, this->scale_.y), M::MakeTransformMatrix(this->parentPos_.x, this->parentPos_.y));
			//R
			this->matrix_ = M::Multiply(this->matrix_, M::MakeRotateMatrix(this->theta_));
			//中心ずらす用
			this->matrix_ = M::Multiply(this->matrix_, M::MakeTransformMatrix(this->rotatePos_.x, this->rotatePos_.y));

			break;

		case kScreen:
			//SR
			this->matrix_ = M::Multiply(M::MakeScaleMatrix(this->scale_.x, this->scale_.y), M::MakeRotateMatrix(this->theta_));
			//T
			this->matrix_ = M::Multiply(this->matrix_, M::MakeTransformMatrix(this->parentPos_.x, this->parentPos_.y));

			//カメラの逆行列をかける
			this->matrix_ = M::Multiply(this->matrix_, M::Inverse(camera->GetCameraMatrix()));

			break;
		}
	}


	//上で作った行列とカメラをかけたものを座標に適用する
	this->sLT_ = M::Transform(this->LT_, M::Multiply(this->matrix_, camera->GetCameraMatrix()));
	this->sRT_ = M::Transform(this->RT_, M::Multiply(this->matrix_, camera->GetCameraMatrix()));
	this->sLB_ = M::Transform(this->LB_, M::Multiply(this->matrix_, camera->GetCameraMatrix()));
	this->sRB_ = M::Transform(this->RB_, M::Multiply(this->matrix_, camera->GetCameraMatrix()));
}

void Shape::Draw() {

	Novice::SetBlendMode(this->blendMode_);

	switch (this->drawMode_) {

	case kQuad:

		if (this->fillMode_ == kFillModeSolid) {
			Novice::DrawTriangle(static_cast<int>(this->sLT_.x), static_cast<int>(this->sLT_.y), static_cast<int>(this->sLB_.x), static_cast<int>(this->sLB_.y),
				static_cast<int>(this->sRT_.x), static_cast<int>(this->sRT_.y), this->color_, kFillModeSolid);
			Novice::DrawTriangle(static_cast<int>(this->sLB_.x), static_cast<int>(this->sLB_.y), static_cast<int>(this->sRT_.x), static_cast<int>(this->sRT_.y), 
				static_cast<int>(this->sRB_.x), static_cast<int>(this->sRB_.y), this->color_, kFillModeSolid);
		} else {
			Novice::DrawLine(static_cast<int>(this->sLT_.x), static_cast<int>(this->sLT_.y), static_cast<int>(this->sRT_.x), static_cast<int>(this->sRT_.y), this->color_);
			Novice::DrawLine(static_cast<int>(this->sRT_.x), static_cast<int>(this->sRT_.y), static_cast<int>(this->sRB_.x), static_cast<int>(this->sRB_.y), this->color_);
			Novice::DrawLine(static_cast<int>(this->sRB_.x), static_cast<int>(this->sRB_.y), static_cast<int>(this->sLB_.x), static_cast<int>(this->sLB_.y), this->color_);
			Novice::DrawLine(static_cast<int>(this->sLB_.x), static_cast<int>(this->sLB_.y), static_cast<int>(this->sLT_.x), static_cast<int>(this->sLT_.y), this->color_);
		}

		break;

	case kEllipse:

		Novice::DrawEllipse(int((this->sLT_.x + this->sRT_.x) / 2), int((this->sLT_.y + this->sLB_.y) / 2),
			int((this->sLT_.x - this->sRT_.x) / 2), int((this->sLT_.y - this->sLB_.y) / 2), this->theta_, this->color_, this->fillMode_);

		break;
	}

}


/*************************************************************************************************
*
*		Texture
*
**************************************************************************************************/

void Texture::InitializeTexture(float x, float y, float sizex, float sizey,
	GHName GH, float srcx, float srcy, int cooltime, int widthNum, int heightNum,
	unsigned int color, int bright, bool isActive, BlendMode blend, float nowx, float nowy) {

	//Object部分を初期化する
	this->InitializeObj(x, y, sizex, sizey, color, bright, isActive, blend);

	//各値を代入する
	this->GH_ = GH;
	this->widthNum_ = widthNum;
	this->heightNum_ = heightNum;
	this->src_ = { srcx, srcy };
	this->now_ = { nowx, nowy };
	this->cooltime_ = cooltime;
	this->nowCooltime_ = 0;
}

void Texture::Draw() {

	Novice::SetBlendMode(this->blendMode_);

	Novice::DrawQuad(static_cast<int>(this->sLT_.x), static_cast<int>(this->sLT_.y), static_cast<int>(this->sRT_.x), static_cast<int>(this->sRT_.y), 
		static_cast<int>(this->sLB_.x), static_cast<int>(this->sLB_.y), static_cast<int>(this->sRB_.x), static_cast<int>(this->sRB_.y),
		static_cast<int>(this->now_.x * this->src_.x), static_cast<int>(this->now_.y * this->src_.y), 
		static_cast<int>(this->src_.x * this->widthNum_), static_cast<int>(this->src_.y * this->heightNum_), 
		globalTexture[GH_], this->color_);
}

void Texture::Animation() {
	//クールタイムを上げる
	++nowCooltime_;

	if (nowCooltime_ >= cooltime_) {
		nowCooltime_ = 0;

		//座標を右に1ずらす
		++now_.x;

		//最大になってたら0にする
		if (now_.x >= widthNum_) {
			now_.x = 0;
		}
	}

}

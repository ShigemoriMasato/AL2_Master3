#include "Share.h"
#include "PlayScene.h"

/*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*

Shape型Particle

+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*/

void SParticle::Initialize(SParticleMode mode, float x, float y, float sizex, float sizey,
	float LTx, float LTy, float RTx, float RTy, float LBx, float LBy, float RBx, float RBy, DrawMode drawMode,
	FillMode fillMode, unsigned int color, int bright, bool isActive, BlendMode blend) {

	this->InitializeShape(x, y, sizex, sizey, LTx, LTy, RTx, RTy, LBx, LBy, RBx, RBy, drawMode, fillMode, color, bright, isActive, blend);

	mode_ = mode;
	doInitialize_ = true;
}

void SEmitter::Initialize(SParticleMode mode, int num, int cooltime, bool emitterIsActive, float x, float y, float sizex, float sizey,
	float LTx, float LTy, float RTx, float RTy, float LBx, float LBy, float RBx, float RBy, DrawMode drawMode,
	FillMode fillMode, unsigned int color, int bright, bool isActive, BlendMode blend) {

	info_.Initialize(mode, x, y, sizex, sizey, LTx, LTy, RTx, RTy, LBx, LBy, RBx, RBy, drawMode, fillMode, color, bright, isActive, blend);

	num_ = num;
	cooltime_ = cooltime;
	isActive_ = emitterIsActive;
	mode_ = mode;

}

void SEmitter::Appearance(std::vector<SParticle>* particles) {

	//クールタイムを増加させる(isActiveになった瞬間に一回出すためにクールタイムを増加させておく)
	if (nowCooltime_ <= cooltime_) {
		nowCooltime_++;
	}

	//ActiveなEmitterのクールタイムが満たされた時、一定数のパーティクルをvectorに追加する
	if (isActive_) {

		//クールタイムが満たされたとき、
		if (nowCooltime_ >= cooltime_) {
			nowCooltime_ = 0;

			for (int i = 0; i < num_; i++) {
				SParticle buff = info_;
				particles->push_back(buff);
			}
		}

	}

}

void SParticle::Draws() {
	this->Draw();
}

/*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*

Texture型Particle

+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*/

void TParticle::Initialize(TParticleMode mode, float x, float y, float sizex, float sizey,
	GHName GH, float srcx, float srcy, int cooltime, int widthNum, int heightNum,
	unsigned int color, int bright, bool isActive, BlendMode blend, float nowx, float nowy) {

	this->InitializeTexture(x, y, sizex, sizey, GH, srcx, srcy, cooltime, widthNum, heightNum, color, bright, isActive, blend, nowx, nowy);

	mode_ = mode;
	doInitialize_ = true;
}

void TParticle::Draws() {
	this->Draw();
}

void TEmitter::Initialize(TParticleMode mode, int num, int cooltime, bool emitterIsActive, float x, float y, float sizex, float sizey,
	GHName GH, float srcx, float srcy, int cooltimes, int widthNum, int heightNum,
	unsigned int color, int bright, bool isActive, BlendMode blend, float nowx, float nowy) {

	info_.Initialize(mode, x, y, sizex, sizey, GH, srcx, srcy, cooltimes, widthNum, heightNum, color, bright, isActive, blend, nowx, nowy);

	num_ = num;
	cooltime_ = cooltime;
	isActive_ = emitterIsActive;
	mode_ = mode;

}

void TEmitter::Appearance(std::vector<TParticle>* particles) {

	//クールタイムを増加させる(isActiveになった瞬間に一回出すためにクールタイムを増加させておく)
	if (nowCooltime_ <= cooltime_) {
		nowCooltime_++;
	}

	//ActiveなEmitterのクールタイムが満たされた時、一定数のパーティクルをvectorに追加する
	if (isActive_) {

		//クールタイムが満たされたとき、
		if (nowCooltime_ >= cooltime_) {
			nowCooltime_ = 0;

			for (int i = 0; i < num_; i++) {
				TParticle buff = info_;
				particles->push_back(buff);
			}
		}

		if (mode_ == tLanding) {
			isActive_ = false;
		}

	}

}

/*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*

カード系

+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*/


/*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*

Share

+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*/
Share::Share() {

	sParticle_.clear();
	tParticle_.clear();

}

void Share::ShapeParticleUpdate() {

	//パーティクルの数だけ回す
	for (int i = 0; i < sParticle_.size(); i++) {

		//particleの総合更新処理
		sParticle_[i].ParticleUpdate();

		//Activeでなくなったとき、パーティクルを消去する
		if (!sParticle_[i].GetIsActive()) {
			sParticle_.erase(sParticle_.begin() + i);
		}
	}

}

void Share::TextureParticleUpdate(PlayScene* ps) {

	//パーティクルの数だけ回す
	for (int i = 0; i < tParticle_.size(); i++) {

		//particleの総合更新処理
		tParticle_[i].ParticleUpdate(ps);

		//Activeでなくなったとき、パーティクルを消去する
		if (!tParticle_[i].GetIsActive()) {
			tParticle_.erase(tParticle_.begin() + i);
		}
	}
}


void Share::Initialize() {
	this->sParticle_.clear();
	this->tParticle_.clear();


}

void Share::Draw() {

	for (int i = 0; i < sParticle_.size(); i++) {
		sParticle_[i].Draws();
	}

	for (int i = 0; i < tParticle_.size(); i++) {
		tParticle_[i].Draws();
	}

}



std::vector<SParticle>* Share::GetSParticle() {
	return &this->sParticle_;
}

std::vector<TParticle>* Share::GetTParticle() {
	return &this->tParticle_;
}

int Share::GetSPSize() {
	return int(sParticle_.size());
}

int Share::GetTPSize() {
	return int(tParticle_.size());
}

void TEmitter::SetIsActive(bool isActive) {
	this->isActive_ = isActive;
}

TParticleMode TEmitter::GetMode() {
	return this->mode_;
}


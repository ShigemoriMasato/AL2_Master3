#include "Share.h"

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

void SEmitter::Appearance(SEmitter* emitter, std::vector<SParticle>* particles) {

	//クールタイムを増加させる(isActiveになった瞬間に一回出すためにクールタイムを増加させておく)
	if (emitter->nowCooltime_ <= emitter->cooltime_) {
		emitter->nowCooltime_++;
	}

	//ActiveなEmitterのクールタイムが満たされた時、一定数のパーティクルをvectorに追加する
	if (emitter->isActive_) {

		//クールタイムが満たされたとき、
		if (emitter->nowCooltime_ >= emitter->cooltime_) {
			emitter->nowCooltime_ = 0;

			for (int i = 0; i < emitter->num_; i++) {
				SParticle buff = emitter->info_;
				particles->push_back(buff);
			}
		}

	}

}

/*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*

Texture型Particle

+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*/

void TParticle::Initialize(TParticleMode mode, float x, float y, float sizex, float sizey,
	GHName GH, int maxWith, int maxHeight, float GHsizex, float GHsizey,
	unsigned int color, int bright, bool isActive, BlendMode blend, float nowx, float nowy) {

	this->InitializeTexture(x, y, sizex, sizey, GH, maxWith, maxHeight, 0, GHsizex, GHsizey, color, bright, isActive, blend, nowx, nowy);

	mode_ = mode;
	doInitialize_ = true;
}

void TEmitter::Initialize(TParticleMode mode, int num, int cooltime, bool emitterIsActive, float x, float y, float sizex, float sizey,
	GHName GH, int maxWith, int maxHeight, float GHsizex, float GHsizey,
	unsigned int color, int bright, bool isActive, BlendMode blend, float nowx, float nowy) {

	info_.Initialize(mode, x, y, sizex, sizey, GH, maxWith, maxHeight, GHsizex, GHsizey, color, bright, isActive, blend, nowx, nowy);

	num_ = num;
	cooltime_ = cooltime;
	isActive_ = emitterIsActive;
	mode_ = mode;

}

void TEmitter::Appearance(TEmitter* emitter, std::vector<TParticle>* particles) {

	//クールタイムを増加させる(isActiveになった瞬間に一回出すためにクールタイムを増加させておく)
	if (emitter->nowCooltime_ <= emitter->cooltime_) {
		emitter->nowCooltime_++;
	}

	//ActiveなEmitterのクールタイムが満たされた時、一定数のパーティクルをvectorに追加する
	if (emitter->isActive_) {

		//クールタイムが満たされたとき、
		if (emitter->nowCooltime_ >= emitter->cooltime_) {
			emitter->nowCooltime_ = 0;

			for (int i = 0; i < emitter->num_; i++) {
				TParticle buff = emitter->info_;
				particles->push_back(buff);
			}
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

void Share::TextureParticleUpdate() {

	//パーティクルの数だけ回す
	for (int i = 0; i < tParticle_.size(); i++) {

		//particleの総合更新処理
		tParticle_[i].ParticleUpdate();

		//Activeでなくなったとき、パーティクルを消去する
		if (!tParticle_[i].GetIsActive()) {
			tParticle_.erase(tParticle_.begin() + i);
		}
	}
}


std::vector<SParticle>* Share::GetSParticle() {
	return &this->sParticle_;
}

std::vector<TParticle>* Share::GetTParticle() {
	return &this->tParticle_;
}

#pragma once
#include <vector>
#include "Object.h"


/// <summary>
/// ShareParticleの種類
/// </summary>
enum SParticleMode {
	sTest,

	sMode_count				//モードの数
};

/// <summary>
/// Shape型のパーティクル
/// </summary>
class SParticle :Shape {
public:
	void Initialize(SParticleMode mode, float x, float y, float sizex, float sizey,
		float LTx, float LTy, float RTx, float RTy, float LBx, float LBy, float RBx, float RBy, DrawMode drawMode,
		FillMode fillMode, unsigned int color, int bright, bool isActive, BlendMode blend);


	/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-ここにパーティクルの種類だけ関数を追加していく=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

	/// <summary>
	/// Testモードのパーティクル更新処理
	/// </summary>
	void TestUpdate();



	/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-ここにパーティクルの種類だけ関数を追加していく=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/


	/// <summary>
	/// パーティクルの総合更新処理
	/// </summary>
	void ParticleUpdate();

	bool GetIsActive();

	SParticleMode mode_;

private:

	bool doInitialize_ = true;		//方向とか、rand関数を使用するとき用(使わなくても問題なし)

};

/// <summary>
/// Shape型のパーティクルの発生装置
/// </summary>
class SEmitter {
public:

	void Initialize(SParticleMode mode, int num, int cooltime, bool emitterIsActive, float x, float y, float sizex, float sizey,
		float LTx = -1, float LTy = 1, float RTx = 1, float RTy = 1,
		float LBx = -1, float LBy = -1, float RBx = 1, float RBy = -1, DrawMode drawMode = kQuad,
		FillMode fillMode = kFillModeSolid, unsigned int color = 0xffffffff, int bright = 0xff, bool isActive = true, BlendMode blend = kBlendModeNormal);

	/// <summary>
	/// スタック領域にパーティクルを作り、particlesの末尾にどんどん入れていく
	/// </summary>
	/// <param name="particles">パーティクルの集まり</param>
	void Appearance(SEmitter* emitter, std::vector<SParticle>* particles);

private:

	SParticle info_;

	SParticleMode mode_;
	int cooltime_;			//パーティクルが出現されるまでのクールタイム
	int num_;				//一度に出現するパーティクルの数
	int nowCooltime_ = 0;	//実際に加算されていくクールタイム
	bool isActive_ = true;

};



/// <summary>
/// TextureParticleの種類
/// </summary>
enum TParticleMode {
	tTest,
	tLanding,

	tMode_count				//モードの数
};

/// <summary>
/// Texture型のパーティクル
/// </summary>
class TParticle :Texture {
public:
	/// <summary>
	/// パーティクルの初期化
	/// </summary>
	void Initialize(TParticleMode mode, float x, float y, float sizex, float sizey,
		GHName GH, int maxWith, int maxHeight, float GHsizex, float GHsizey,
		unsigned int color, int bright, bool isActive, BlendMode blend, float nowx, float nowy);


	/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-ここにパーティクルの種類だけ関数を追加していく=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

	/// <summary>
	/// Testモードのパーティクル更新処理
	/// </summary>
	void TestUpdate();

	/// <summary>
	/// Landingモードのパーティクル更新処理
	/// </summary>
	void LandingUpdate();


	/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-ここにパーティクルの種類だけ関数を追加していく=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/


	/// <summary>
	/// パーティクルの総合更新処理
	/// </summary>
	void ParticleUpdate();


	/// <summary>
	/// isActiveのアクセサリーメソッド
	/// </summary>
	bool GetIsActive();

	TParticleMode mode_;

private:

	bool doInitialize_ = true;		//方向とか、rand関数を使用するとき用(使わなくても問題なし)

};

/// <summary>
/// Texture型のParticleの発生装置
/// </summary>
class TEmitter {
public:

	void Initialize(TParticleMode mode, int num, int cooltime, bool emitterIsActive, float x, float y, float sizex, float sizey,
		GHName GH, int maxWith, int maxHeight, float GHsizex = 1, float GHsizey = 1,
		unsigned int color = 0xffffffff, int bright = 0xff, bool isActive = true, BlendMode blend = kBlendModeNormal, float nowx = 0, float nowy = 0);

	/// <summary>
	/// スタック領域にパーティクルを作り、particlesの末尾にどんどん入れていく
	/// </summary>
	/// <param name="particles">パーティクルの集まり</param>
	void Appearance(TEmitter* emitter, std::vector<TParticle>* particles);

private:

	TParticle info_;

	TParticleMode mode_;
	int cooltime_;			//パーティクルが出現されるまでのクールタイム
	int num_;				//一度に出現するパーティクルの数
	int nowCooltime_ = 0;	//実際に加算されていくクールタイム
	bool isActive_ = true;	//EmitterがActiveか否か

};



//共有資産
class Share {
public:

	Share();

	/// <summary>
	/// パーティクルの総合更新処理
	/// </summary>
	/// <param name="particle">パーティクルの値操作用変数</param>
	/// <param name="particles">パーティクル全体のリスト。isActiveがfalseになった際に要素を消去するために用いる</param>
	/// <param name="index">particlesの中のparticleの現在位置。同じく消去に用いる</param>
	void ShapeParticleUpdate();

	/// <summary>
	/// パーティクルの総合更新処理
	/// </summary>
	/// <param name="particle">パーティクルの値操作用変数</param>
	/// <param name="particles">パーティクル全体のリスト。isActiveがfalseになった際に要素を消去するために用いる</param>
	/// <param name="index">particlesの中のparticleの現在位置。同じく消去に用いる</param>
	void TextureParticleUpdate();


	/*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*アクセサーメソッド+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*/
	
	std::vector<SParticle>* GetSParticle();
	std::vector<TParticle>* GetTParticle();

private:

	//画像を用いないパーティクル
	std::vector<SParticle> sParticle_;
	//画像を使用するパーティクル
	std::vector<TParticle> tParticle_;
};

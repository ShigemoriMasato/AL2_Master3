#pragma once
#include "Vector.h"
#include "Camera.h"
#include <Novice.h>

enum MatrixMode {
	kSRT,
	kSTR,
	kScreen,			//Quad && kSRTのみ対応

};

enum GHName {
	kTest_GH,
	kParticle_GH,
	
};

enum DrawMode {
	kQuad,
	kEllipse,

};

extern float Fbuffer;
extern int Ibuffer;
extern Vector2 Vbuffer;
extern int globalTexture[30];

class Object {
public:

	/// <summary>
	/// 行列の作成や色の設定など、描画に必要なものを更新の一番最後にする
	/// </summary>
	void Ready(MatrixMode mode, int bright, Camera* const camera);

	/******************アクセサーメソッド**********************/

	/// <summary>
	/// posを呼び出す
	/// </summary>
	Vector2 GetPos() const;

	/// <summary>
	/// LT, RT, LB, RBを呼び出す
	/// </summary>
	/// <param name="type">上の順番で0~3で呼び出す</param>
	/// <returns>指定された角　エラー時は0,0</returns>
	Vector2 GetCorner(int type);

	/// <summary>
	/// Velocityを呼び出す
	/// </summary>
	/// <returns></returns>
	Vector2 GetVelocity();

	/// <summary>
	/// isActiveを呼び出す
	/// </summary>
	bool GetIsActive() const;

	/// <summary>
	/// sizeを呼び出す
	/// </summary>
	Vector2 GetSize() const;

	/// <summary>
	/// scaleを呼び出す
	/// </summary>
	Vector2 GetScale() const;

	/// <summary>
	/// ポジションをぶち込む
	/// </summary>
	void SetPos(Vector2 pos);

	/// <summary>
	/// 色を変更する
	/// </summary>
	void SetColor(unsigned int color);

	/// <summary>
	/// 拡大率を現在の拡大率にかける
	/// </summary>
	void MultiplyScale(float x, float y);

	/// <summary>
	/// scaleを設定する
	/// </summary>
	void SetScale(Vector2 scale);

	/// <summary>
	/// thetaをぶち込む
	/// </summary>
	void SetTheta(float theta);


protected:
	/// <summary>
	/// 全値の初期化をする
	/// </summary>
	void InitializeObj(float x, float y, float sizex, float sizey,
		unsigned int color = 0xffffffff, int bright = 0xff, bool isActive = true, BlendMode blend = kBlendModeNormal);

	/// <summary>
	/// 色を描画用に調整する
	/// </summary>
	void AdjustColor(int bright);

	//- - - - - - ローカル座標 - - - - - - -//
	Vector2 LT_{};				//左上座標
	Vector2 RT_{};				//右上座標
	Vector2 LB_{};				//左下座標
	Vector2 RB_{};				//右下座標
	//- - - - - - スクリーン座標 - - - - - - -//
	Vector2 sLT_{};				//左上座標
	Vector2 sRT_{};				//右上座標
	Vector2 sLB_{};				//左下座標
	Vector2 sRB_{};				//右下座標
	
	//座標系
	Vector2 parentPos_{};
	Vector2 pos_{};				//ワールド座標系のプレイヤーの中心
	Vector2 expos1_{};			//調整用pos
	Vector2 expos2_{};			//調整用pos
	Vector2 startPos_{};		//初期座標
	Vector2 endPos_{};			//終了座標
	Vector2 size_{};			//オブジェクトの大きさ
	Vector2 scale_{};			//プレイヤーの大きさの倍率
	Vector2 rotatePos_{};		//kSTR行列の中心
	float rotateTheta_{};		//kSTR行列の回転角度
	Vector2 velocity_{};		//速度
	Vector2 direction_{};		//向いている方向
	float speed_{};				//速さ
	float theta_{};				//回転角度(radian)
	float t_{};					//アニメーション用
	Matrix3x3 matrix_{};		//あらゆるパラメータをもとに作成する行列

	int frame_{};					//アニメーション用

	//色関係
	int red_{};					//赤(0 ~ 255)
	int green_{};				//緑(0 ~ 255)
	int blue_{};				//青(0 ~ 255)
	int alpha_{};				//透明度(0 ~ 255)
	int bright_{};				//明るさ(0 ~ 255)
	unsigned int color_{};		//計算後の色

	//フラグ系
	bool isActive_{};

	BlendMode blendMode_ = kBlendModeNormal;	//ブレンドモード
};

class Shape : public Object {
public:

	/// <summary>
	/// 全値を初期化する
	/// </summary>
	void InitializeShape(float x, float y, float sizex, float sizey, 
		float LTx = -1, float LTy = 1, float RTx = 1, float RTy = 1, 
		float LBx = -1, float LBy = -1, float RBx = 1, float RBy = -1, DrawMode drawMode = kQuad,
		FillMode fillMode = kFillModeSolid, unsigned int color = 0xffffffff, int bright = 0xff, bool isActive = true, BlendMode blend = kBlendModeNormal);

	void SReady(MatrixMode mode, int bright, Camera* const camera);

	void Draw();

protected:

	//- - - - - - もともとObjectに入っていたものを保存する - - - - - -//
	Vector2 baseLT_;			//左上座標
	Vector2 baseRT_;			//右上座標
	Vector2 baseLB_;			//左下座標
	Vector2 baseRB_;			//右下座標

	//- - - - - - 各点の情報 - - - - - -//
	Vector2 infLT_;				//左上座標
	Vector2 infRT_;				//右上座標
	Vector2 infLB_;				//左下座標
	Vector2 infRB_;				//右下座標

	FillMode fillMode_;
	DrawMode drawMode_;			//四角形を描画するか、円を描画するか

};

class Texture : public Object {

public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="srcx">画像枚数x(1~)</param>
	/// <param name="srcy">画像枚数y(1~)</param>
	/// <param name="cooltime">アニメーションのクールタイム</param>
	/// <param name="maxWidth">画像1枚の横幅</param>
	/// <param name="maxHeight">画像1枚の縦幅</param>
	/// <param name="nowx">今表示している画像(0~)</param>
	/// <param name="nowy">今表示している画像(0~)</param>
	void InitializeTexture(float x, float y, float sizex, float sizey,
		GHName GH, float srcx, float srcy, int cooltime = 1, int widthNum = 1, int heightNum = 1,
		unsigned int color = 0xffffffff, int bright = 0xff, bool isActive = true, BlendMode blend = kBlendModeNormal, float nowx = 0, float nowy = 0);

	void Draw();

	/// <summary>
	/// アニメーションを行う
	/// </summary>
	void Animation();

protected:

	Vector2 now_;				//現在表示している画像(MapChip形式で、(0, 0)が一番左上)
	Vector2 src_;				//画像1枚あたりのサイズ

	GHName GH_;					//グラフィックハンドル

	int widthNum_;				//画像が横に何枚あるか(1~)
	int heightNum_;				//画像が縦に何枚あるか(1~)

	int cooltime_;
	int nowCooltime_;
	
};

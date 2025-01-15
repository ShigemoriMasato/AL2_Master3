#pragma once
#include "Object.h"
#include "GameManager.h"
#include "Camera.h"

class Player;
class PlayScene;

enum EnemyType {
	kBullet,
	kRevolution,		//公転

};

class Enemy : public Shape {
public:

	void Initialize(EnemyType type, float speed, float directionx, float directiony, float x, float y, float sizex, float sizey,
		float LTx = -1, float LTy = 1, float RTx = 1, float RTy = 1,
		float LBx = -1, float LBy = -1, float RBx = 1, float RBy = -1, DrawMode drawMode = kQuad,
		FillMode fillMode = kFillModeSolid, unsigned int color = 0xffffffff, int bright = 0xff, bool isActive = true, BlendMode blend = kBlendModeNormal);

	void AllUpdate(GameManager* gm, Camera* camera, PlayScene* ps);

	void BulletUpdate(Player* player, GameManager* gm, Camera* camera);

	void RevolutionUpdate(Player* player, GameManager* gm, Camera* camera);

private:

	EnemyType type_;

	bool initialize_;

};


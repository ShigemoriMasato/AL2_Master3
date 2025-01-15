#pragma once
#include "Object.h"
#include "GameManager.h"
#include "Camera.h"
#include <vector>

class TEmitter;
class Share;
class Ground;

class Player : public Shape {
public:

	Player();

	void Update(GameManager* gm, Camera* camera, TEmitter* landemit, Ground* ground);

	void FallExtend();

	void MoveExtend();

	Shape GetCollition() const;
	int GetLevel() const;

	void SetIsAlive(bool isAlive);

private:

	Shape collition_;

	float sfeT;
	float smeT;

	int level_;		//着地したときに更新される、表示用の階層

	bool landing_;
	bool isFExtend_;

};


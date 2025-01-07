#pragma once
#include "Object.h"
#include "GameManager.h"
#include "Camera.h"
#include <vector>

class TEmitter;
class Share;
class Ground;

class Player : public Shape{
public:

	Player();

	void Update(GameManager* gm, Camera* camera, TEmitter* landemit, Ground* ground);

	void FallExtend();

	void MoveExtend();

private:

	float sfeT;
	float smeT;

	bool landing_;
	bool isFExtend_;

};


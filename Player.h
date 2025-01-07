#pragma once
#include "Object.h"
#include "GameManager.h"
#include "Camera.h"

class Player : public Shape{
public:

	Player();

	void Update(GameManager* gm, Camera* camera);

	void FallExtend();

	void MoveExtend();

private:

	float sfeT;
	float smeT;

	bool landing_;
	bool isFExtend_;

};


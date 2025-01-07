#pragma once
#include "Object.h"
#include "GameManager.h"
#include "Camera.h"
#include "Rope.h"

class Player : public Shape{
public:

	Player();

	void Update(GameManager* gm, Camera* camera, Rope* rope[2]);

private:

	float sExtendT_;

	bool death_;
};


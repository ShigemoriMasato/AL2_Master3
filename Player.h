#pragma once
#include "Object.h"
#include "GameManager.h"
#include "Camera.h"

class Player : public Shape{
public:

	Player();

	void Update(GameManager* gm, Camera* camera);

	void SideExtend();

private:

	float sExtendT;

	bool tyakuti_;
	bool isExtend_;

};


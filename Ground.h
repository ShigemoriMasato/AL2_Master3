#pragma once
#include "Object.h"
#include "GameManager.h"
#include <vector>

class Player;

class Step {
public:

	void Initialize(int num);

	void Update(Camera* camera, GameManager* gm);

	void Draw();

	Shape& GetMain();

	Vector2 pos_;

private:
	Shape main;
	Shape face;
};

class Ground {
public:

	Ground();

	void Update(Camera* camera, GameManager* gm, Player* player);

	void Draw();

	std::vector<Step> step_;

};


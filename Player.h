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

	void SetIsAlive(bool isAlive);

private:

	float sfeT;
	float smeT;

	int level_;				//�v���C���[�̌��݈ʒu�����̃C���^�[�o���Ŋ�������
	int displayLevel_;		//���n�����Ƃ��ɍX�V�����A�\���p�̊K�w

	bool landing_;
	bool isFExtend_;

};


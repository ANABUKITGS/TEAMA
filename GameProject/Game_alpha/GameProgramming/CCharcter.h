#ifndef CCHARCTER_H
#define CCHARCTER_H

#include "CRectangle.h"
#include "CTexture.h"
#include "CGamePad.h"
#include "CText.h"
#include "CMap.h"

class CCharcter :public CRectangle{
public:
	float mVelocityX;		//X���̈ړ����x
	float mVelocityY;		//Y���̈ړ����x
	int mVelocityLimit;		//�ړ����E���x
	float mSearch;
	bool mDirection;		//�L�����N�^�[�̌��� true:�E false:��
	bool mAir;
	void Update();			//�X�V����
	void Render();			//�`�揈��
	void Gravity();			//�d�͏���
	void Forward();			//�O�i����
	void Scroll();			//��ʂ̃X�N���[������
	
};
#endif
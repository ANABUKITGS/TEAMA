#ifndef CCHARCTER_H
#define CCHARCTER_H

#include "CRectangle.h"
#include "CTexture.h"
#include "CGamePad.h"
#include "CText.h"
#include "CMap.h"

class CCharcter :public CRectangle{
public:
	int mVelocityLimit;		//�ړ����E���x
	void Update();			//�X�V����
	void Render();			//�`�揈��
	void Gravity();			//�d�͏���
	void Forward();			//�O�i����
	void Scroll();			//��ʂ̃X�N���[������
	
};
#endif
#ifndef CMAPSWITCHGROUND_H
#define CMAPSWITCHGROUND_H

#include "CMapChip.h"

//�X�C�b�`�Ő؂�ւ�鑫��̃}�b�s���O�f�[�^
#define SWITCHGROUND_UV 0, 64, 64 * 6, 64 * 5
//�X�C�b�`�Ő؂�ւ�鑫��̃}�b�s���O�f�[�^
#define SWITCH_UV 0, 64, 64 * 6, 64 * 5

class CMapSwitchGround :public CMapChip{
public:
	static int mNumber;
	CMapSwitchGround(const CVector2& pos, const CVector2& scale, CTexture *texture, int number)
		//CMapChip�ŏ�����
		:CMapChip(pos, scale, texture, SWITCHGROUND_UV, ESWITCH_GROUND1)
	{
		CMapSwitchGround::mNumber = number;
		if (mNumber == 0)
			CMapChip(pos, scale, texture, SWITCHGROUND_UV, ESWITCH_GROUND1);
		else
			CMapChip(pos, scale, texture, SWITCHGROUND_UV, ESWITCH_GROUND2);
	}
	void Update();	//��������������
	//bool Collision(CRectangle *r);	//�Փˎ��̏���
	//Render��CMapChip��Render���g��
};

class CMapSwitch :public CMapChip{
public:
	bool mCollision;	//true:�������Ă��� false:�������ĂȂ�
	CMapSwitch(const CVector2& pos, const CVector2& scale, CTexture *texture)
		//CMapChip�ŏ�����
		:CMapChip(pos, scale, texture, SWITCHGROUND_UV, ESWITCH)
		, mCollision(false)
	{}
	void Update();	//��������������
	bool Collision(CRectangle *r);	//�Փˎ��̏���
	//Render��CMapChip��Render���g��
};
#endif
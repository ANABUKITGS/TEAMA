#ifndef CMAPSWITCHGROUND_H
#define CMAPSWITCHGROUND_H

#define SWITCH_GROUND_POS		mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2
#define SWITCH_GROUND_UV1		0, 64, 64, 0
#define SWITCH_GROUND_UV2		0, 64, 128, 64
#define SWITCH_INTERVAL			30
#define SWITCH_POS				mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2
#define SWITCH_UV				CELLSIZE * switch_ani_count, CELLSIZE * (switch_ani_count + 1), 64, 0
#define SWITCH_ANI_COUNT_FRAME	6

#include "CMapChip.h"

class CMapSwitchGround :public CMapChip{
private:
	CTexture mTexSwitchGround;

public:
	static ECELLNUM mNumber;
	CMapSwitchGround(const CVector2& pos, ECELLNUM number)
		//CMapChip�ŏ�����
		:CMapChip(pos, CVector2(CELLSIZE / 2, CELLSIZE / 2), NULL, NULL, NULL, NULL, NULL, ECELLNUM::ESWITCH_GROUND1)
	{
		CMapSwitchGround::mNumber = number;
		if (mNumber==ESWITCH_GROUND1)
			mTag = ESWITCH_GROUND1;
		else
			mTag = ESWITCH_GROUND2;

		if (mTexSwitchGround.id == NULL)
			mTexSwitchGround.Load(".\\Data\\Images\\Map\\MapSwitchGround.tga");
		mRender = false;
	}
	void Update();	//��������������
	bool Collision(CRectangle *r);	//�Փˎ��̏���
	void Render();					//�`�揈��
	//Render��CMapChip��Render���g��

};

class CMapSwitch :public CMapChip{
private:
	int switch_ani_count;
	int switch_ani_count_frame;
	CTexture mTexSwitch;

public:
	bool mCollision;	//true:�������Ă��� false:�������ĂȂ�
	int mCollisionInterval;	//���ɏՓ˂ł���܂ł̃C���^�[�o��
	CMapSwitch(const CVector2& pos)
		//CMapChip�ŏ�����
		:CMapChip(pos, CVector2(CELLSIZE / 4, CELLSIZE / 2), NULL, NULL, NULL, NULL, NULL, ECELLNUM::ESWITCH)
		, mCollision(false)
	{
		mRender = false;
		switch_ani_count = 0;
		switch_ani_count_frame = 0;
		if (mTexSwitch.id == NULL)
			mTexSwitch.Load(".\\Data\\Images\\Map\\MapSwitch.tga");
		mCollisionInterval = SWITCH_INTERVAL;
	}
	void Update();					//��������������
	bool Collision(CRectangle *r);	//�Փˎ��̏���
	void Render();					//�`�����������
};
#endif
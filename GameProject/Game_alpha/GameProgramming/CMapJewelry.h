#ifndef CMAPJEWELRY_H
#define CMAPJEWELRY_H

#include "CMapChip.h"
#include "CMapScroll.h"


//��΂̃}�b�s���O�f�[�^
#define JEWELRY_UV mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 0, 64, 64, 0
#define JEWELRY2_UV mPosition.x - CELLSIZE / 4, mPosition.x + CELLSIZE / 4, mPosition.y - CELLSIZE / 4, mPosition.y + CELLSIZE / 4, 0, 64, 128, 64
#define SDIAMOND_UV mPosition.x - CELLSIZE * 0.75, mPosition.x + CELLSIZE * 0.75, mPosition.y - CELLSIZE * 0.75, mPosition.y + CELLSIZE * 0.75, 0, 128, 128, 0
#define EFECT_INTERVAL 10

class CWeapon;
/*
�}�b�v�`�b�v���p������
��΃N���X���`
*/
class CMapJewelry : public CMapChip {
private:
	CTexture mTexJewel;
	CRectangle *mpWeapon;

public:
	int mIntervalEfe;
	CMapJewelry()
		: CMapChip(CVector2(0,0), CVector2(CELLSIZE / 3, CELLSIZE / 2), NULL, NULL, NULL, NULL, NULL, EJEWELRY)
	{
		mIntervalEfe = EFECT_INTERVAL;
	}
	CMapJewelry(const CVector2& pos) 
		//CMapChip�ŏ�����
		: CMapChip(pos, CVector2(CELLSIZE * 0.75 / 2, CELLSIZE * 0.75), NULL, NULL, NULL, NULL, NULL, EJEWELRY)
	{
		mRender = false;
		mTexJewel.Load(".\\Data\\Images\\Map\\MapJewel.tga");
		mpWeapon = 0;
	}
	void Update();	//��������������
	void Render();	//�`�����������
	bool Collision(CRectangle *r);	//�Փˎ��̏���
};


/*
�}�b�v�`�b�v���p������
�~�j��΃N���X���`
*/
class CMapMiniJewelry : public CMapChip {
private:
	CTexture mTexJewel;
	CRectangle *mpWeapon;

public:
	int mIntervalEfe;
	CMapMiniJewelry(const CVector2& pos)
		//CMapChip�ŏ�����
		: CMapChip(pos, CVector2(CELLSIZE / 4, CELLSIZE / 2), NULL, NULL, NULL, NULL, NULL, EJEWELRY2)
	{
		mRender = false;
		mTexJewel.Load(".\\Data\\Images\\Map\\MapJewel.tga");
		mpWeapon = 0;
		mIntervalEfe = EFECT_INTERVAL;
	}
	void Update();	//��������������
	void Render();	//�`�����������
	bool Collision(CRectangle *r);	//�Փˎ��̏���
};


class CSDiamond : public CRectangle{
private:
	CTexture mTexSDiamond;
	CRectangle *mpWeapon;

public:
	static CSDiamond *mpSDiamond;
	int mIntervalEfe;
	static bool mGetFlg;
	CSDiamond(CVector2 pos)
		:CRectangle(pos + CVector2(0.0f, 10.0f), CVector2(CELLSIZE / 3 * 2, CELLSIZE), NULL)
	{
		mIntervalEfe = EFECT_INTERVAL;
		mpWeapon = 0;
		mGetFlg = false;
		if (mTexSDiamond.id == NULL)
			mTexSDiamond.Load(".\\Data\\Images\\Boss\\SDiamond.tga");
		mRender = false;
		mTag = ECELLNUM::ESDIAMOND;
		mVelocityX = 0.0f;
		mVelocityY = 30.0f;
		mPriority = -2;
		CTaskManager::Get()->Add(this);
	}
	~CSDiamond(){
		mpSDiamond = NULL;
	}

	void Update();
	bool Collision(CRectangle*);
	void Render();
	void Gravity();
};
#endif
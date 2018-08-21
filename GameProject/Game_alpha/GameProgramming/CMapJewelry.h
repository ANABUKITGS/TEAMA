#ifndef CMAPJEWELRY_H
#define CMAPJEWELRY_H

#include "CMapChip.h"

//��΂̃}�b�s���O�f�[�^
#define JEWELRY_UV mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 0, 64, 64, 0
#define JEWELRY2_UV mPosition.x - CELLSIZE / 4, mPosition.x + CELLSIZE / 4, mPosition.y - CELLSIZE / 4, mPosition.y + CELLSIZE / 4, 0, 64, 128, 64
/*
�}�b�v�`�b�v���p������
��΃N���X���`
*/
class CMapJewelry : public CMapChip {
private:
	CTexture mTexJewel;

public:
	CMapJewelry()
		: CMapChip(CVector2(0,0), CVector2(CELLSIZE / 3, CELLSIZE / 2), NULL, NULL, NULL, NULL, NULL, EJEWELRY)
	{}
	CMapJewelry(const CVector2& pos) 
		//CMapChip�ŏ�����
		: CMapChip(pos, CVector2(CELLSIZE / 3, CELLSIZE / 2), NULL, NULL, NULL, NULL, NULL, EJEWELRY)
	{
		mRender = false;
		mTexJewel.Load(".\\Data\\Images\\Map\\MapJewel.tga");
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

public:
	CMapMiniJewelry(const CVector2& pos)
		//CMapChip�ŏ�����
		: CMapChip(pos, CVector2(CELLSIZE / 4, CELLSIZE / 2), NULL, NULL, NULL, NULL, NULL, EJEWELRY2)
	{
		mRender = false;
		mTexJewel.Load(".\\Data\\Images\\Map\\MapJewel.tga");
	}
	void Update();	//��������������
	void Render();	//�`�����������
	bool Collision(CRectangle *r);	//�Փˎ��̏���
};

#endif

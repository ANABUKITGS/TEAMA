#ifndef CMAPBOX_H
#define CMAPBOX_H
#include "CMapChip.h"

#define BOX_UV mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, 0, 256, 256 , 0

class CMapBox : public CMapChip {
private:
	CTexture mTexBox;
	CVector2 mDefaultPos;

public:
	float mVelocityY;
	CMapBox(const CVector2& pos)
		//CMapChip�ŏ�����
		: CMapChip(pos + CVector2(0.0f, CELLSIZE / 2), CVector2(CELLSIZE, CELLSIZE), NULL, NULL, NULL, NULL, NULL, ECELLNUM::EBOX)
		, mVelocityY(0.0f)
	{
		mVelocityX = 0.0f;
		mRender = false;
		mBreak = false;
		mTexBox.Load(".\\Data\\Images\\Map\\MapBox.tga");
		mDefaultPos = pos + CVector2(0.0f, CELLSIZE / 2);
	}
	void Update();	//��������������
	void Render();	//�`�����������
	bool Collision(CRectangle *r);	//�Փˎ��̏���
	void Gravity();
	//Render��CMapChip��Render���g��
};

#endif
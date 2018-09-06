#ifndef CMAPSTEEL_H
#define CMAPSTEEL_H
#include "CMapChip.h"

#define STEEL_UV mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 0, 256, 64 , 0

class CMapSteel : public CMapChip{
private:
	CTexture mTexSteel;
	CVector2 mDefaultPos;

public:
	float mVelocityY;
	CMapSteel(const CVector2& pos)
		//CMapChip�ŏ�����
		: CMapChip(pos, CVector2(CELLSIZE * 2, CELLSIZE / 2), NULL, NULL, NULL, NULL, NULL, ECELLNUM::ESTEEL)
		, mVelocityY(0.0f)
	{
		mVelocityX = 0.0f;
		mRender = false;
		mBreak = false;
		mTexSteel.Load(".\\Data\\Images\\Map\\MapSteel.tga");
		mDefaultPos = pos;
		mAlpha = 1.0f;
	}
	void Update();	//��������������
	void Render();	//�`�����������
	bool Collision(CRectangle *r);	//�Փˎ��̏���
	void Gravity();
	//Render��CMapChip��Render���g��
};
#endif
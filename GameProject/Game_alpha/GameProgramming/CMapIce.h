#ifndef CMAPICE_H
#define CMAPICE_H
#include "CMapChip.h"

//�� �[
#define ICE_UV_L	mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 0, 64, 64 , 0, 1.0f
//����
#define ICE_UV_C	mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 0, 64, 128 , 64, 1.0f
//�E �[
#define ICE_UV_R	mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 0, 64, 192 , 128, 1.0f

class CMapIce : public CMapChip{
private:
	CTexture mTexMapIce;

public:
	enum ETEXTURE_POSNUM{
		ELEFT = 1,
		ECENTER,
		ERIGHT,
		EONE,
		ESIZE,
	};
	ETEXTURE_POSNUM texture_pos;

	CMapIce(const CVector2& pos, ETEXTURE_POSNUM texpos)
		//CMapChip�ŏ�����
		: CMapChip(pos, CVector2(CELLSIZE / 2, CELLSIZE / 2), NULL, NULL, NULL, NULL, NULL, ECELLNUM::EICE)
	{
		mRender = false;
		mTag = ECELLNUM::EICE;
		texture_pos = texpos;
		mTexMapIce.Load(".\\Data\\Images\\Map\\MapIce.tga");
	}
	void Update();
	bool Collision(CRectangle *r);	//�Փˎ��̏���
	void Render();
};
#endif
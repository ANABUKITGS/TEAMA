#ifndef CMAPBOX_H
#define CMAPBOX_H

#include "CMapChip.h"

#define BOX_UV 0.0f,0.0f,0.0f,0.0f

class CMapBox : public CMapChip {
public:
	float mVelocityY;
	bool mBreak;
	CMapBox(const CVector2& pos, const CVector2& scale, CTexture *texture)
		//CMapChip�ŏ�����
		: CMapChip(pos, scale, texture, BOX_UV, EBOX)
	{
		mBreak = false;
	}
	void Update();	//��������������
	bool Collision(CRectangle *r);	//�Փˎ��̏���
	void Gravity();
	//Render��CMapChip��Render���g��
};

#endif
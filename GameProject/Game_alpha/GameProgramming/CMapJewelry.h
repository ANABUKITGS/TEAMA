#ifndef CMAPJEWELRY_H
#define CMAPJEWELRY_H

#include "CMapChip.h"

//��΂̃}�b�s���O�f�[�^
#define JEWELRY_UV 0, 64, 64 * 6, 64 * 5
#define JEWELRY2_UV 0, 64, 64 * 7, 64 * 6
/*
�}�b�v�`�b�v���p������
��΃N���X���`
*/
class CMapJewelry : public CMapChip {
public:
	CMapJewelry(const CVector2& pos, const CVector2& scale, CTexture *texture) 
		//CMapChip�ŏ�����
		: CMapChip(pos, scale, texture, JEWELRY_UV, EJEWELRY)
	{}
	void Update();	//��������������
	bool Collision(CRectangle *r);	//�Փˎ��̏���
	//Render��CMapChip��Render���g��
};

class CMapMiniJewelry : public CMapChip {
public:
	CMapMiniJewelry(const CVector2& pos, const CVector2& scale, CTexture *texture)
		//CMapChip�ŏ�����
		: CMapChip(pos, scale, texture, JEWELRY2_UV, EJEWELRY2)
	{}
	void Update();	//��������������
	bool Collision(CRectangle *r);	//�Փˎ��̏���
	//Render��CMapChip��Render���g��
};

#endif

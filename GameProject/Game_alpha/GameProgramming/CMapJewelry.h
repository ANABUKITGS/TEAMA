#ifndef CMAPJEWELRY_H
#define CMAPJEWELRY_H

#include "CMapChip.h"
#include "CSound.h"

//��΂̃}�b�s���O�f�[�^
#define JEWELRY_UV 0, 64, 64 * 6, 64 * 5
/*
�}�b�v�`�b�v���p������
��΃N���X���`
*/
class CMapJewelry : public CMapChip {
public:
	CSound mSoundJewelry;
	CMapJewelry(const CVector2& pos, const CVector2& scale, CTexture *texture) 
		//CMapChip�ŏ�����
		: CMapChip(pos, scale, texture, JEWELRY_UV, EJEWELRY)
	{
		mSoundJewelry.Load(".\\Data\\Sound\\hoge02.wav");
	}
	void Update();	//��������������
	bool Collision(CRectangle *r);	//�Փˎ��̏���
	//Render��CMapChip��Render���g��
};

#endif

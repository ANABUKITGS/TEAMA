#ifndef CMAPUNDER_H
#define CMAPUNDER_H

#include "CMapChip.h"

#define UNDER_UV mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 0, 64, 64, 0	//�e�N�X�`���̃}�b�s���O�f�[�^
/*
�����甲���鏰
*/
class CMapUnder : public CMapChip{
private:
	CTexture mTexUnder;

public:
	/*
	�R���X�g���N�^�ŏ���������
	pos:�ʒu���W
	scale:�R���W�����̑傫��(�l�p�`�̑傫�������̂܂܃R���W�����ɂȂ�)
	*/
	CMapUnder(CVector2 pos, CVector2 scale)
		:CMapChip(pos, scale, NULL, NULL, NULL, NULL, NULL, ECELLNUM::EUNDER)
	{
		mTexUnder.Load(".\\Data\\Images\\Map\\MapUnder.tga");
		mPriority = 9;
		mRender = false;
	}

	//�X�V����
	void Update();
	//�`�揈��
	void Render();
	//�Փˏ���
	bool Collision(CRectangle*);
};

#endif
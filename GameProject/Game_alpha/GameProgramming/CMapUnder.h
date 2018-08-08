#ifndef CMAPUNDER_H
#define CMAPUNDER_H

#include "CMapChip.h"

#define TEXUV 0, 64, 64 * 6, 64 * 5	//�e�N�X�`���̃}�b�s���O�f�[�^
/*
�����甲���鏰
*/
class CMapUnder : public CMapChip{
public:
	/*
	�R���X�g���N�^�ŏ���������
	pos:�ʒu���W
	scale:�R���W�����̑傫��(�l�p�`�̑傫�������̂܂܃R���W�����ɂȂ�)
	*/
	CMapUnder(CVector2 pos, CVector2 scale, CTexture*Texture)
		:CMapChip(pos, scale, Texture, TEXUV, ECELLNUM::EUNDER)
	{}

	//�X�V����
	void Update();
	//�Փˏ���
	bool Collision(CRectangle*);
};

#endif
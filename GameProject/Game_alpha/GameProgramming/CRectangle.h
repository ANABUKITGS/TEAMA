#ifndef CRECTANGLE_H
#define CRECTANGLE_H
#include "CTask.h"
#include "CVector2.h"
#include "CTexture.h"
#include "CMatrix33.h"
//#include "CMap.h"

#define BLACK 0.0f, 0.0f, 0.0f
#define WHITE 1.0f, 1.0f, 1.0f

class CRectangle : public CTask{
public:
	ECELLNUM mTag;
	CVector2 mPosition;	//�l�p�`�̒��S���W	x�l�p�`�̒��S��X���W	y�l�p�`�̒��SY���W
	CVector2 mVector[4];	//�l�p�`�������\�b�h�Ɏg���C���X�^���X�ϐ�
	CVector2 mScale;	//�l�p�`�̕��ƍ���
	CTexture*mpTexture;	//�l�p�`���g�p����e�N�X�`���ւ̃|�C���^
	CMatrix33 mMatrix;	//�}�g���N�X���C���X�^���X�ɂ���(����͈ړ��s��p)
	float mRotation;	//�l�p�`�̉�]�p�x
	float mUv[4];	//�e�N�X�`���}�b�s���O�f�[�^
	float mRight, mLeft, mTop, mBottom;
	float mAlpha;
	CRectangle()
		: mRotation(0.0f), mpTexture(0), mAlpha(1.0f)
	{}
	/*
	position:�ʒu
	scale:�傫��
	texture:�e�N�X�`���̗L��(�L:�e�N�X�`���̃C���X�^���X,��:0)
	*/
	CRectangle(const CVector2&position, const CVector2&scale, CTexture*texture);
	void SetVertex(float mLeft, float mRight, float mBottom, float mTop);	//�l�p�`�������\�b�h
	void Update();	//�X�V����
	virtual void Render(float, float, float, float);	//�`�揈��
	void Render();
	virtual bool Collision(CRectangle *target);
	bool Collision(CRectangle *target, CVector2 *adjust);
	void SetRectangle(const CVector2&position, const CVector2&scale, CTexture*texture);

};
#endif
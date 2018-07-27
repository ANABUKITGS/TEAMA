#include "CRectangle.h"

CRectangle::CRectangle(const CVector2&position, const CVector2&scale, CTexture*texture)
:mPosition(position), mScale(scale)
{
	mPosition.x = position.x;
	mPosition.y = position.y;
};

void CRectangle::SetVertex(float mLeft, float mRight, float mBottom, float mTop){
	/*�l�p�`��
	����A�����A�E���A�E��̒��_���ō��
	*/
	mVector[0].x = mLeft;	mVector[0].y = mTop;
	mVector[1].x = mLeft;	mVector[1].y = mBottom;
	mVector[2].x = mRight;	mVector[2].y = mBottom;
	mVector[3].x = mRight;	mVector[3].y = mTop;
}
void CRectangle::Update(){
	//�ړ��s��
	mMatrix.SetTranslate(mPosition.x, mPosition.y);
	//�}�g���N�X�N���X����]�A�g�h�p�s��
	CMatrix33 rot, sca;
	//��]�s��
	rot.SetRotation(mRotation);
	//�g��k���s��
	sca.SetScale(mScale.x, mScale.y);
}

void CRectangle::Render(){
	CVector2 mv[4];	//���W�Ŏl�p�`�������邽�߂̃C���X�^���X
	//�����s���������
	mv[0] = mMatrix.MultiVector2(mVector[0]);
	mv[1] = mMatrix.MultiVector2(mVector[1]);
	mv[2] = mMatrix.MultiVector2(mVector[2]);
	mv[3] = mMatrix.MultiVector2(mVector[3]);
	if (!mEnabled)	//�L���t���O�������Ȏ��͖߂�l��Ԃ�
		return;
	else{	//�t���O���L���Ȏ��͎l�p�`�𐶐�����
		glBegin(GL_QUADS);
		glVertex2f(mv[0].x, mv[0].y);
		glVertex2f(mv[1].x, mv[1].y);
		glVertex2f(mv[2].x, mv[2].y);
		glVertex2f(mv[3].x, mv[3].y);
		glEnd();
	}
}
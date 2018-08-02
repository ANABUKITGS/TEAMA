#include "CRectangle.h"

CRectangle::CRectangle(const CVector2&position, const CVector2&scale, CTexture*texture)
:mPosition(position), mScale(scale)
{
//	mPosition.x = position.x;
//	mPosition.y = position.y;
};

void CRectangle::SetVertex(float Left, float Right, float Bottom, float Top){
	/*�l�p�`��
	����A�����A�E���A�E��̒��_���ō��
	*/
	mVector[0].x = Left;	mVector[0].y = Top;
	mVector[1].x = Left;	mVector[1].y = Bottom;
	mVector[2].x = Right;	mVector[2].y = Bottom;
	mVector[3].x = Right;	mVector[3].y = Top;

	mLeft = Left;
	mRight = Right;
	mBottom = Bottom;
	mTop = Top;
	mPosition.x = (Left + Right) / 2;
	mPosition.y = (Bottom + Top) / 2;
	mScale.x = abs(Right - Left) / 2;
	mScale.y = abs(Top - Bottom) / 2;

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
	mMatrix = mMatrix * rot * sca;
}

void CRectangle::Render() {
	glPushMatrix();
	glMultMatrixf(&mMatrix.m[0][0]);
	if (mpTexture) {
		mpTexture->DrawImage(-1, 1, -1, 1, mUv[0], mUv[1], mUv[2], mUv[3], 1.0f);
	}
	else {
		glBegin(GL_QUADS);
		glVertex2d(1, 1);
		glVertex2d(-1, 1);
		glVertex2d(-1, -1);
		glVertex2d(1, -1);
		glEnd();
	}
	glPopMatrix();
}

void CRectangle::Render(float r, float g, float b, float a){
	glColor4f(r, g, b, a);
	Render();
	return;
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
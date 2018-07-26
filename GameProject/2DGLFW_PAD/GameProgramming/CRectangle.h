#ifndef CRECTANGLE_H
#define CRECTANGLE_H
//OpenGL���C�u����
#include "glut.h"
//�e�N�X�`���N���X�̃C���N���[�h
#include "CTexture.h"

/*
CRectangle�N���X
�l�p�`�Ɋւ���N���X
*/
class CRectangle {
public:
	//�񋓌^�̒�`
	enum ETag {
		EBLOCK,	//�u���b�N
		EPLAYERBULLET,	//�v���C���[�e
		EPLAYER,	//�v���C���[
	};
	ETag mTag;	//�񋓌^�̕ϐ�
	//�f�t�H���g�R���X�g���N�^
	CRectangle()
		: mTag(EBLOCK)	//�����l�u���b�N
	{}
	int x;	//���S��X���W
	int y, w, h;	//���S��Y���W,��,����

	/*
	DrawTriangle
	�O�p�`��`�悷��֐�
	*/
	void DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2) {
		//�O�p�`�̕`��
		glBegin(GL_TRIANGLES);	//�O�p�`�̕`��J�n
		glVertex2d(x0, y0);		//���_�P�̍��W���w��
		glVertex2d(x1, y1);		//���_�Q�̍��W���w��
		glVertex2d(x2, y2);		//���_�R�̍��W���w��
		glEnd();	//�`��I��
	}

	/*
	DrawRectangle
	�l�p�`��`�悷��֐�
	x0,y0:�E��
	x1,y1:����
	x2,y2:����
	x3,y3:�E��
	*/
	void DrawRectangle(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3) {
		DrawTriangle(x0, y0, x1, y1, x2, y2);
		DrawTriangle(x0, y0, x2, y2, x3, y3);
	}

	/*
	Draw
	�l�p�`��`�悷��֐�
	*/
	void Draw() {
		//�N���X�����o�̕ϐ�x,y,w,h���g�p���܂�
		DrawRectangle(x + w, y + h, x - w, y + h, x - w, y - h, x + w, y - h);
	}

	/*28
	�e�N�X�`���̕`��
	*/
	void Draw(const CTexture &t, int left, int right, int bottom, int top) {
		t.DrawImage(x - w, x + w, y - h, y + h, left, right, bottom, top);
	}

	/*
	Collision
	�l�p�`*pr�ƏՓ˂��Ă����true��
	���Ă��Ȃ����false��Ԃ��܂��B
	*/
	bool Collision(const CRectangle &r) {
		//X���̏d�Ȃ�𔻒�
		//���S��X���W�̋��������߂�
		int lenX = x - r.x;
		//�����̐�Βl�����߂�
		lenX = lenX < 0 ? -lenX : lenX;
		//���������̍��v���傫���Ƃ��AX���͏d�Ȃ��Ă��Ȃ�
		if (lenX > w + r.w) {
			//�d�Ȃ��ĂȂ���΁A�Փ˂��Ă��Ȃ�
			//false��Ԃ�
			return false;
		}
		//Y���̏d�Ȃ蔻��
		int lenY = y - r.y;
		lenY = lenY < 0 ? -lenY : lenY;
		if (lenY > h + r.h) {
			return false;
		}
		//X���AY���Ƃ��ɏd�Ȃ��Ă���̂ŁAtrue��Ԃ�
		return true;
	}
	/*
	Collision
	����*pr�̎l�p�`�ƏՓ˂��Ă��邩���o���A
	�Փ˂��Ă����true���A���Ă��Ȃ����false��Ԃ��B
	�܂��A�Փ˂��Ă����ꍇ�A*px��X�������ɏd�Ȃ����ʂ��A
	*py��Y�������֏d�Ȃ����ʂ�ݒ肷��B
	*/
	bool Collision(CRectangle *pr, int *px, int *py) {
		//x��y��0��0����
		*px = 0;
		*py = 0;
		//X���̏d�Ȃ�𔻒�
		//���S��X���W�̋��������߂�
		int lenX = x - pr->x;
		//�����̐�Βl�����߂�
		lenX = lenX < 0 ? -lenX : lenX;
		//���������̍��v��菬�����Ƃ��AX���͏d�Ȃ��Ă���
		if (lenX < w + pr->w) {
			//�d�Ȃ����v�Z
			if (x < pr->x) {
				//���肪�E�̎��͍��ֈړ�
				*px = lenX - w - pr->w;
			}
			else {
				//���肪���̎��͉E�ֈړ�
				*px = w + pr->w - lenX;
			}
		}
		else {
			//�d�Ȃ��ĂȂ���΁A�Փ˂��Ă��Ȃ�
			//false��Ԃ�
			return false;
		}
		//Y���̏d�Ȃ蔻��
		int lenY = y - pr->y;
		lenY = lenY < 0 ? -lenY : lenY;
		if (lenY < h + pr->h) {
			if (y < pr->y) {
				*py = lenY - h - pr->h;
			}
			else {
				*py = h + pr->h - lenY;
			}
		}
		else {
			return false;
		}
		//X���AY���Ƃ��ɏd�Ȃ��Ă���̂ŁAtrue��Ԃ�
		return true;
	}
};


#endif

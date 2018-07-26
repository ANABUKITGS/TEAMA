#include "CCharacter.h"
#include "CKey.h"
#include <math.h>
#include "CSceneGame2.h"

//�v���C���[�̃C���X�^���X
CPlayer2 *CPlayer2::spInstance = 0;

//�v���C���[�ړ����x
#define VELOCITY_P 2
//�W�����v����
#define VELOCITY_JUMP 15
//�d�͉����x
#define GRAVITY 1
//�G�ړ����x
#define VELOCITY_E 1

//UV�}�b�s���O �G�̕���
#define UVENEMYWALK1 136, 156, 190, 161
#define UVENEMYWALK2 168, 188, 190, 161
#define UVENEMYWALK1L 156, 136, 190, 161
#define UVENEMYWALK2L 188, 168, 190, 161
//�G����
#define UVENEMYCRY 196, 216, 190, 161
//UV�}�b�s���O �v���C���[�̕���
#define UVPLAYERWALK1 136, 156, 158, 130
#define UVPLAYERWALK2 168, 188, 158, 130
#define UVPLAYERWALK1L 156, 136, 158, 130
#define UVPLAYERWALK2L 188, 168, 158, 130
//�v���C���[����
#define UVPLAYERCRY 196, 216, 158, 130

/*
�v���C���[�̍X�V����
*/
void CPlayer2::Update() {
	//�E�ֈړ�
	if (CKey::Push('D') || CSceneGame2::mGamePad.mpButtons[PAD_RIGHT]
		|| CSceneGame2::mGamePad.mpPositions[0] > 0.08f) {
		x += VELOCITY_P;
		//X���W�ɂ���ĉ摜��ς���
		if (x % 30 < 15) {
			//�E�摜1
			SetUv(UVPLAYERWALK1);
		}
		else {
			//�E�摜2
			SetUv(UVPLAYERWALK2);
		}
	}
	//���ֈړ�
	if (CKey::Push('A') || CSceneGame2::mGamePad.mpButtons[PAD_LEFT]
		|| CSceneGame2::mGamePad.mpPositions[0] < -0.08f) {
		//�J�n�ʒu��荶�֍s�����Ȃ�
		if (mStartX < x)
			x -= VELOCITY_P;
		//X���W�ɂ���ĉ摜��ς���
		if (x % 30 < 15) {
			//���摜1
			SetUv(UVPLAYERWALK1L);
		}
		else {
			//���摜2
			SetUv(UVPLAYERWALK2L);
		}
	}
	//�W�����v����
	if ((CKey::Once(' ') || CSceneGame2::mGamePad.mpButtons[PAD_3]) && mState == ERUN) {
		mGravityV = VELOCITY_JUMP;
		//43
		//�W�����v��
		mState = EJUMPUP;
		//1��Đ�
		mSound.Play();
	}
	if (mGravityV < -GRAVITY)
		//�W�����v��
		mState = EJUMPDOWN;
	//�d�͑��x���ړ�
	y += mGravityV;
	//�d�͑��x�X�V
	mGravityV -= GRAVITY;
}
/*
�v���C���[�̏Փˏ���
*/
bool CPlayer2::Collision(CCharacter *m, CCharacter *yo) {
	int dx, dy;
	//����ƏՓ˂��Ă��邩����
	if (CRectangle::Collision(yo, &dx, &dy)) {
		switch (yo->mTag) {
		//43
		case EENEMY: //���肪�G�̎�
			switch (yo->mState) {
			case ERUN:
				if (mState == ERUN) {
					mState = ECRY;
					SetUv(UVPLAYERCRY);
				}
				break;
			case ECRY:
				//�߂肪���������֖߂�
				if (abs(dx) < abs(dy)) {
					x += dx;
				}
				else {
					y += dy;
					//�d�͏�����
					mGravityV = 0;
					//43
					//����
					mState = ERUN;
				}
				break;
			}
			break;
		case EBLOCK: //���肪�u���b�N
			//�߂肪���������֖߂�
			if (abs(dx) < abs(dy)) {
				x += dx;
			}
			else {
				y += dy;
				//�d�͏�����
				mGravityV = 0;
				//43
				//����
				mState = ERUN;
			}
			break;
		}
		//�Փ˂��Ă���
		return true;
	}
	//�Փ˂��Ă��Ȃ�
	return false;
}
/*
�G�̍X�V����
*/
void CEnemy2::Update() {
	//43
	//�����Ă鎞�͓����Ȃ�
	if (mState == ECRY) return;
	//�ړ�����
	x += mForward * VELOCITY_E;
	//�d�͑��x���ړ�
	y += mGravityV;
	//�d�͑��x�X�V
	mGravityV -= GRAVITY;
	//X���W�ɂ���ĉ摜�̐؂�ւ�
	if (x % 30 < 15) {
		if (mForward > 0)
			//�E�摜
			SetUv(UVENEMYWALK1);
		else
			//���摜
			SetUv(UVENEMYWALK1L);
	}
	else {
		if (mForward > 0)
			//�E�摜
			SetUv(UVENEMYWALK2);
		else
			//���摜
			SetUv(UVENEMYWALK2L);
	}
}
/*
�G�̏Փˏ���
*/
bool CEnemy2::Collision(CCharacter *m, CCharacter *yo) {
	int dx, dy;
	//����ƏՓ˂��Ă��邩����
	if (CRectangle::Collision(yo, &dx, &dy)) {
		switch (yo->mTag) {
		case EBLOCK: //���肪�u���b�N
			//�߂肪���������֖߂�
			if (abs(dx) < abs(dy)) {
				x += dx;
				//�����𔽓]������
				mForward *= -1;
			}
			else {
				y += dy;
				//�d�͏�����
				mGravityV = 0;
			}
			break;
		//43
		case EPLAYER: //���肪�v���C���[
			//�W�����v�~����
			if (yo->mState == EJUMPDOWN) {
				//�����܂�
				SetUv(UVENEMYCRY);
				mState = ECRY;
			}
			break;
		}
		//�Փ˂��Ă���
		return true;
	}
	//�Փ˂��Ă��Ȃ�
	return false;
}
//�e�N�X�`���}�b�s���O�̐ݒ�
void CCharacter::SetUv(int u0, int u1, int v0, int v1) {
	mU[0] = u0;
	mU[1] = u1;
	mV[0] = v0;
	mV[1] = v1;
}

#ifndef CCHARACTER_H
#define CCHARACTER_H
//�l�p�`�N���X�̃C���N���[�h
#include "CRectangle.h"
#include "CSound.h"
/*
�L�����N�^�N���X
*/
class CCharacter : public CRectangle {
public:
	//�L�����N�^���ʎq
	enum EChara {
		EBLOCK,
		EPLAYER,
		EENEMY, //�G�ǉ�
	};
	EChara mTag; //�L�����N�^���ʎq
//43
	//��Ԏ��ʎq
	enum EState {
		ERUN, //�ړ���
		EJUMPUP, //�W�����v��
		EJUMPDOWN, //�W�����v��
		ECRY, //�����Ă���
	};
	EState mState; //���
	CTexture *mpTexture; //�e�N�X�`��
	int mU[2]; //�}�b�s���O��
	int mV[2]; //�}�b�s���O�c
	//�R���X�g���N�^
	CCharacter(CTexture *t, int ax, int ay, int aw, int ah, int u0, int u1, int v0, int v1)
		: mpTexture(t)
		//43
		, mState(ERUN) //�ړ����
	{
		x = ax; //X���W
		y = ay; //Y���W
		w = aw; //��
		h = ah; //����
		mU[0] = u0; //UV��
		mU[1] = u1; //UV�E
		mV[0] = v0; //UV��
		mV[1] = v1; //UV��
	}
	//���z�֐� �`�揈��
	virtual void Render() {
		//�摜�`��
		Draw(*mpTexture, mU[0], mU[1], mV[0], mV[1]);
	}
	//���z�֐� �X�V����
	virtual void Update() {}
	//�Փˏ���
	virtual bool Collision(CCharacter *m, CCharacter *y) { return false; };
	//�e�N�X�`���}�b�s���O�̐ݒ�
	void SetUv(int u0, int u1, int v0, int v1);
};
/*
�u���b�N�N���X
*/
class CBlock : public CCharacter {
public:
	CBlock(CTexture *t, int x, int y, int w, int h, int u0, int u1, int v0, int v1)
		: CCharacter(t, x, y, w, h, u0, u1, v0, v1)
	{
		mTag = CCharacter::EBLOCK;
	}
};
/*
�v���C���[�N���X
*/
class CPlayer2 : public CCharacter {
private:
	int mGravityV; //�d�͑��x
	int mStartX; //�X�^�[�gX���W
	CSound mSound;
public:
	static CPlayer2 *spInstance; //�C���X�^���X�̃|�C���^
	CPlayer2(CTexture *t, int x, int y, int w, int h, int u0, int u1, int v0, int v1)
		: CCharacter(t, x, y, w, h, u0, u1, v0, v1)
		, mGravityV(0)
		, mStartX(x)
	{
		mTag = CCharacter::EPLAYER;
		//�C���X�^���X�|�C���^�ɐݒ�
		spInstance = this;
		//�T�E���h���[�h
		mSound.Load("jump.mp3");
	}
	//�X�V����
	void Update();
	//�Փˏ���
	bool Collision(CCharacter *m, CCharacter *y);
};

/*
�G�N���X
*/
class CEnemy2 : public CCharacter {
private:
	int mGravityV; //�d�͑��x
	int mForward; //���� -1:�� 1:�E
public:
	CEnemy2(CTexture *t, int x, int y, int w, int h, int u0, int u1, int v0, int v1)
		: CCharacter(t, x, y, w, h, u0, u1, v0, v1)
		, mGravityV(0)
		, mForward(1) //�E��
	{
		mTag = CCharacter::EENEMY;
	}
	//�X�V����
	void Update();
	//�Փˏ���
	bool Collision(CCharacter *m, CCharacter *y);
};

#endif

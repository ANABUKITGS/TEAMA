#ifndef CPLAYERT_H
#define CPLAYERT_H

#include "CCharcter.h"
#include "CTaskManager.h"
#include "CWeapon.h"
#include "CGame2.h"

#define PLAYER_VELOCITY_X 5.0f
#define PLAYER_VELOCITY_Y 20.0f
#define JUMP_TIME_LIMIT 15
#define VELOCITYX_LIMIT 5.0f
#define DAMAGE_INTERVAL 180


class CPlayerT : public CCharcter {
private:
	CTexture mTexPlayer;

public:
	enum EPLAYERANI{
		EIDOL = 1,	//�A�C�h�����
		ERUN,		//����
		ETURN,		//�����]��
		EJUMP,		//�W�����v
		EDAMAGE,	//�_���[�W
		EYOYO,	//���[���[�U��
		EDOWN,		//����
		ESIZE,		//EPLAYERANI �T�C�Y
	};
	static int player_ani;
	int player_ani_count;
	int player_ani_count_frame;
	int PLAYER_ANI_COUNT_FRAME;
	static CPlayerT *mpPlayer;

	bool mJump;				//true:�W�����v�{�^�����͒�  false:�W�����v���͂��Ă��Ȃ�
	bool mDash;				//true:�_�b�V����  false:�_�b�V�����Ă��Ȃ�
	int mJumpCount;			//�W�����v��
	bool mAerialAttack;		//�󒆍U��  true:�\  false:�s�\
	bool mAir;				//true:�� false:�n��
	int mLife;				//�v���C���[�̎c�@
	int mJewel;				//�W���G��������
	int mMiniJewel;			//�~�j�W���G��������
	int mDamageInterval;	//�_���[�W�C���^�[�o��
	bool mUnrivaled;		//true:���G���
	float mAlpha;			//�A���t�@�l
	CVector2 mReSpornPos;	//���X�|�[���n�_

	CWeapon *mpWeapon;
	CPlayerT() 
		:mpWeapon(0)
	
	{
		mpPlayer = this;
		mPriority = 1;
		mTag = EPLAYER;
		mJump = false;
		mDash = false;
		mVelocityY = 0;
		mVelocityX = 0;
		mDirection = true;
		mAerialAttack = false;
		mAir = false;
		mJumpCount = 0;
		CTaskManager::Get()->Add(this);
		mTexPlayer.Load(".\\Data\\Images\\Player\\Player.tga");
		player_ani = EIDOL;
		player_ani_count = 0;
		player_ani_count_frame = 0;
		PLAYER_ANI_COUNT_FRAME = 1;
		mJewel = 1;
		mMiniJewel = 0;
		mLife = 3;
		mDamageInterval = DAMAGE_INTERVAL;
		mUnrivaled = false;
		mAlpha = 1.0f;
	}

	CPlayerT::CPlayerT(const CVector2&position)
		: CPlayerT()
	{
		SetRectangle(position, CVector2(16, 60), NULL);
		mReSpornPos = position;
	}
	~CPlayerT(){
		mpPlayer = 0;
	}

	void Update();
	void Forward();
	void Attack();
	void Render();
	void Dash();

	bool Collision(CRectangle *p);

};



#endif

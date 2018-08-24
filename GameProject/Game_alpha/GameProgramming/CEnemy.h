#ifndef CENEMY_H
#define CENEMY_H

#include "CRectangle.h"
#include "CTaskManager.h"
#include "CWeapon.h"
#include "CCharcter.h"
#include "CPlayerT.h"

#define MONITOR_TIME			180
#define WALK_TIME				180
#define ENEMY_VELOCITY_X_LIMIT	4.5f
#define ENEMY_VELOCITY_X		1.25f	//����
#define ENEMY_VELOCITY_X_ICE	0.15f	//���� �X����
#define ENEMY_VELOCITY_X2		0.25f	//�����
#define ENEMY_VELOCITY_X2_ICE	0.05f	//����� �X����
#define E_SEARCHRANGE			250		//���G�͈�
#define DOWN_TIME				100
#define ATTACK_INTERVAL			120
#define ATTACK_INTERVAL2		30

class CSearch :public CRectangle{
public:
	bool mDiscovery;	//true:���G�͈͓�
	CSearch(){
		mTag = ECELLNUM::ESEARCH;
		mDiscovery = false;
		mRender = false;
		CTaskManager::Get()->Add(this);
	}
	CSearch::CSearch(const CVector2&position)
		:CSearch()
	{
		SetRectangle(position, CVector2(128, 32), NULL);
	}
	void Update();
	bool Collision(CRectangle *p);
	void Render();
};

class CEnemy :public CCharcter{
private:
	CTexture mTexEnemy01;
	CTexture mTexEnemy02;
	CTexture mTexEnemy03;

public:
	enum EENEMYANI{
		EIDOL = 1,	//�A�C�h�����
		EWALK,		//����
		ETURN,		//�����]��
		EJUMP,		//�W�����v
		EDAMAGE,	//�_���[�W
		EYOYO,		//���[���[�U��
		EDOWN,		//����
		EBOX,		//���𗎂Ƃ�����
		ESIZE,		//EPLAYERANI �T�C�Y
	};
	int enemy_ani;
	int enemy_ani_count;
	int enemy_ani_count_flame;
	int ENEMY_ANI_COUNT_FLAME;

	CWeapon*mpEWeapon;	//�G���o�����[���[�̃C���X�^���X
	CSearch* mpSearch;
	static CEnemy *mpEnemy;
	int mMonitorTime;	//�����~�܂鎞��
	int mWalkTime;		//��������
	int mDownTime;		//�_�E�����Ă��������܂ł̎���
	int mAttackInterval;//���̍U���܂ł̎���
	int mAttackInterval2;	//���G�͈͓��ɓ����Ă���̎���


	CEnemy(){
		mVelocityY = 0.0f;	//�d�͂̏����l��0�ɂ���
		mVelocityX = 0.0f;
		mpEWeapon=0;	//�G�̃��[���[�̒l��0�ɂ��Ă���
		mPriority = 1;
		mDirection = true;
		enemy_ani = EENEMYANI::EWALK;
		mMonitorTime = MONITOR_TIME;
		mWalkTime = WALK_TIME;
		mDownTime = DOWN_TIME;
		mAttackInterval = ATTACK_INTERVAL;
		mAttackInterval2 = ATTACK_INTERVAL2;
		CTaskManager::Get()->Add(this);
	}

	CEnemy::CEnemy(const CVector2&position, ECELLNUM tag)
		: CEnemy()
	{
		SetRectangle(position, CVector2(32, 60), NULL);
		mpSearch = new CSearch(CVector2(position.x + 128, position.y));
		mTag = tag;
		mRender = false;
		mIce = false;
		enemy_ani = EENEMYANI::EWALK;
		enemy_ani_count = 0;
		enemy_ani_count_flame = 0;
		ENEMY_ANI_COUNT_FLAME = 0;

		if (tag == ECELLNUM::EENEMY1)
			mTexEnemy01.Load(".\\Data\\Images\\Enemy\\Enemy01.tga");

		else if (tag == ECELLNUM::EENEMY2)
			mTexEnemy02.Load(".\\Data\\Images\\Enemy\\Enemy02.tga");

		else if (tag == ECELLNUM::EENEMY3)
			mTexEnemy03.Load(".\\Data\\Images\\Enemy\\Enemy03.tga");
	}
	~CEnemy(){
		mpEnemy = 0;
	}

	void Update();
	void Render();
	bool Collision(CRectangle *p);
	//�G�̍U���F���͈� �w�肵���͈͓��ɓ���ƍU�����J�n����
	//bool SearchCollision(CCharcter*, CCharcter*);
};

#endif
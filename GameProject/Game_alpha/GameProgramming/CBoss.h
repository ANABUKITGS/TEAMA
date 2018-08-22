#ifndef CBOSS_H
#define CBOSS_H

#include "CCharcter.h"
#include "CEnemy.h"
#include "CPlayerT.h"
#include <stdlib.h>
#include <time.h>

#define BOSS_SEARCH 256					//�{�X�̍��G�͈͂�ݒ�
#define BEHAVIOR 300.0f					//�{�X�̍s���؂�ւ��萔
#define BOSS_DELCNT 100					//�{�X�̏��ŃJ�E���g�i�Ƃ肠����100frame�ɐݒ�j
#define ANI_FPS 60						//�{�X�̃A�j���[�V�����t���[��
#define BOSSDAMAGECNT 180				//�{�X���_���[�W���󂯂Ė��G�ɂȂ鎞��
#define BOSSGVELOCITY 30.0f				//�{�X�̏d�͒萔
#define BOSSJUMPTIME 60					//�{�X�̃W�����v�J�E���g(����60�t���[���ɐݒ�)
#define BOSSANIMESIZE 512				//�{�X�̃e�N�X�`���T�C�Y
#define BOSSMOVESPEED 6					//�{�X�̈ړ����x
#define STARTBEHAVIOR BEHAVIOR			//�{�X��J�n���̂ݎg�p
#define BOSSINVINCIBLE 120	

class CBoss : public CCharcter{
//���N���X�����g�p�\
private:
	CTexture mTexture;					//�{�X�ɓ\��t����e�N�X�`��
	CVector2 mAttack_Search;			//�{�X�ƃv���C���[�Ƃ̋������o��
	CVector2 mForward;					//�����Ă��������O�ɂ���C���X�^���X
	CWeapon*mpBWeapon;					//�{�X�̕���g�p�N���X���C���X�^���X�ɂ���
	float mBossBehavior;				//�G�̊e�s���ɓ��锻�ʋ���
	float BossFowrd(float);				//�{�X�̌����ɉ�����
	//float BossJump(bool);				//�{�X�̃W�����v����(��float�^���\�b�h)
	int mBossAttackItr;					//�{�X�̃��[���[���ˊԊu
	int Boss_Ani_Count;					//���̃R�}�ɍs��
	int mBossAnimeFream;				//�{�X�̃A�j���[�V�����̃e�N�X�`���̖���
	int mBehaviorPattern;				//�{�X�̈ꕔ�̍s���Ƀ����_���v�f��ǉ�
	int mBossDeleteTime;				//�{�X�����ł��鎞�Ԃ̕ϐ�
	int mBossDamageCnt;					//�{�X���_���[�W���󂯂����ɉ��Z����ϐ�
	int mBossJumprad;					//�{�X�̃W�����v������^�C�~���O�������_���ɂ���
	int mBossJcnt;						//�{�X�̃W�����v�Ԋu
	int Boss_Ani_Count_Frame;			//��R�}�̃t���[����
	int mBossInvincibleTime;			//�{�X�̖��G����
	bool Invincible;					//���G���ԗp�ϐ���ǉ�
	void BossJump();
	enum AttackBehavior{
		ENONE,							//�������Ȃ�(�������������̂�)
		EIDOL,							//�ҋ@
		EMANTO,							//�}���g�̂������H
		EBWEAPON,						//������g�p
		EDASH,							//����
		EJUMP,							//�W�����v
		EDAMAGE,						//�_���[�W
		EDOWN,							//�_�E��
	};
	AttackBehavior mAttackBehavior;
	//���������R���X�g���N�^�ŕϐ����̏���������
	CBoss()
		:mpBWeapon(0)
	{
		srand((unsigned)clock());	//������������(���̂�)
		mVelocityY = 0;				//�����d�͒l��0�ɂ���
		mBossInvincibleTime = BOSSINVINCIBLE;
		Boss_Ani_Count=NULL;
		Boss_Ani_Count_Frame=NULL;
		mBossAnimeFream=NULL;
		mBossDamageCnt=NULL;
		mBossJcnt=NULL;					//�W�����v�Ԋu�ϐ��̒l��0�ɂ���
		mBossJumprad=NULL;				//�ŏ��̃W�����v�^�C�~���O������������
		mBossDeleteTime = BOSS_DELCNT;	//�{�X�̏��Ŏ��Ԃ�������
		Invincible = false;
		mDirection = false;				//�ŏ��̌������������ɂ���
		mBossBehavior = BEHAVIOR;		//�G�̍s���l����
		mBossAttackItr = ATTACK_INTERVAL;
		mAttackBehavior = ENONE;		//�������Ȃ���Ԃɂ���
		mTag = EBOSS;					//�^�O���{�X�ɂ���
		mPriority = 10;					//�D��x��ݒ�
		mRender = false;				//�����蔻��̕`����폜
		mTexture.Load(".\\Data\\Images\\Boss\\Boss.tga");//�e�N�X�`���f�[�^��ǂݍ���
		CTaskManager::Get()->Add(this);	//�^�X�N���X�g�Ƀ{�X�L�����N�^�[��ǉ�
	}

//���ʎg�p�\
public:
	//�����L�̃R���X�g���N�^�ŏo���ʒu��ݒ�
	CBoss(CVector2 Pos)
		:CBoss()
	{
		//�T�C�Y���w��i�e�N�X�`���͕ʂŗp�ӂ���̂ň����ɂ͓���Ȃ��j
		SetRectangle(Pos, CVector2(32,90),NULL);
	}
	static CBoss*mpBoss;
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
	//�Փˏ���
	bool Collision(CRectangle*);
};

#endif
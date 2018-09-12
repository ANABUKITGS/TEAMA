#ifndef CBOSS_H
#define CBOSS_H

#include "CCharcter.h"
#include "CEnemy.h"
#include "CPlayerT.h"
#include "CEfect.h"
#include "CSE.h"
#include <stdlib.h>
#include <time.h>

#define BEHAVIOR 270.0f					//�{�X�̍s���؂�ւ��萔(�ړ�����U��)
#define BOSS_DELCNT 200					//�{�X�̏��ŃJ�E���g�i�Ƃ肠����100frame�ɐݒ�j
#define BOSSDAMAGECNT 180				//�{�X���_���[�W���󂯂Ė��G�ɂȂ鎞��
#define BOSSGVELOCITY 30.0f				//�{�X�̃W�����v�萔
#define BOSSJUMPTIME 60					//�{�X�̃W�����v�J�E���g(����60�t���[���ɐݒ�)
#define BOSSANIMESIZE 512				//�{�X�̃e�N�X�`���T�C�Y
#define BOSSMOVESPEED 6					//�{�X�̈ړ����x
#define STARTBEHAVIOR 600				//�{�X��J�n���̂ݎg�p
#define BOSSINVINCIBLE 120	
#define BOSSNEXTBEHAVIOR 70				//�{�X�̑ҋ@���玟�̍s���܂ł̎���
#define BOSS_DOWN_TIME 120				//����Ă���̑҂�����
#define BOSS_LIFE 100					//�{�X�̏���HP
#define BOSSTELEPOA 180					//�����ɂȂ��ő厞��
#define BOSSTELEPO 120					//�u�Ԉړ��ꏊ�̒l

#define BOSS_TEX_POS mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - mScale.y, mPosition.y - mScale.y + CELLSIZE * 4	//�e�N�X�`���[ Position

class CBoss : public CCharcter{
//���N���X�����g�p�\
private:
	CTexture mTexture;					//�{�X�ɓ\��t����e�N�X�`��
	CVector2 mAttack_Search;			//�{�X�ƃv���C���[�Ƃ̋������o��
	CVector2 mBossDefaultPos;			//�{�X�̏����ʒu
	CVector2 mWeaponVec;
	CWeapon*mpBWeapon;					//�{�X�̕���g�p�N���X���C���X�^���X�ɂ���
	float mBossBehavior;				//�G�̊e�s���ɓ��锻�ʋ���
	int mBossTelepo;					//�u�Ԉړ������ꏊ�������_���ɂ���
	int mBossAttackItr;					//�{�X�̓������Ԃ𗐐��ŏo���ϐ�
	int Boss_Ani_Count;					//���̃R�}�ɍs��
	int mBossAnimeFreamT;				//�u�Ԉړ��p�ϐ��i��ŏ����\���j
	int mBossAnimeFream;				//�{�X�̃A�j���[�V�����̃e�N�X�`���̖���
	int mBehaviorPattern;				//�{�X�̈ꕔ�̍s���Ƀ����_���v�f��ǉ�
	int mBossDeleteTime;				//�{�X�����ł��鎞�Ԃ̕ϐ�
	int mBossJumprad;					//�{�X�̃W�����v������^�C�~���O�������_���ɂ���
	int mBossJcnt;						//�{�X�̃W�����v�Ԋu
	int Boss_Ani_Count_Frame;			//��R�}�̃t���[����
	int mBossInvincibleTime;			//�{�X�̖��G����
	int mBossIBehavior;					//�ҋ@��Ԃ���̃����_���s��
	int IdolInterval;					//�ҋ@��Ԃ��玟�̍s���Ɉڂ�܂ł̎���
	int mBossSpeedUp;					//�{�X�̍s���̑������グ��
	bool Invincible;					//���G���ԗp�ϐ���ǉ�
	bool mTelepoEnabled;
	bool mJumpTmEnabled;
	enum BossSE{
		ETELEPOIN,
		ETELEPOOUT,
	};
	enum BehP{
		EDASH_0,
		EDASH_1,
		EDASH_2,
		EJUMP_3,
		ETELEPO_4,
		EIDOL_5,
		EIDOL_6,

		ESIZE_7,
	};
	void BossBehP(BehP);				//�{�X���ҋ@����s���N�����֐��v���g�^�C�v
	int GetRand(int);					//�������擾����֐�

	//���������R���X�g���N�^�ŕϐ����̏���������
	CBoss()
		:mpBWeapon(0)
	{
		srand((unsigned)clock());	//������������(���̂�)
		mWeaponVec = CVector2(0, 0);
		mVelocityY = 0;
		mVelocityX = 0;
		mBossInvincibleTime = BOSSINVINCIBLE;
		Boss_Ani_Count=0;
		Boss_Ani_Count_Frame=0;
		mBossAnimeFream=0;
		mBossLife = mBossMaxLife = BOSS_LIFE;
		mBossLifeProportion = 0.0f;
		mBossSpeedUp = 0;				//������
		mBossAnimeFreamT = 4;			//�t�Đ��A�j���[�V�����ϐ���������
		mBossIBehavior = 0;				//�ҋ@��Ԃ���s���J�n����ϐ�
		mBossTelepo = 0;				//�u�Ԉړ��̒l��������
		mBossJcnt=0;					//�W�����v�Ԋu�ϐ��̒l��0�ɂ���
		mBossJumprad=0;					//�ŏ��̃W�����v�^�C�~���O������������
		IdolInterval = 0;				//�ҋ@��Ԃ��玟�̍s���Ɉڂ�܂ł̎��Ԃ�������
		mBossDeleteTime = BOSS_DELCNT;	//�{�X�̏��Ŏ��Ԃ�������
		Invincible = false;				//���G���Ԃ͍ŏ��U�ɂ��ď�����
		mDirection = false;				//�ŏ��̌������������ɂ���
		mJumpTmEnabled = true;
		mBossBehavior = BEHAVIOR;		//�G�̍s���l����
		mBossBattle = false;
		mAttackBehavior = EIDOL;		//�ҋ@��Ԃɂ���
		mTag = EBOSS;					//�^�O���{�X�ɂ���
		mPriority = 10;					//�D��x��ݒ�
		mRender = false;				//�����蔻��̕`����폜
		mTexture.Load(".\\Data\\Images\\Boss\\Boss.tga");//�e�N�X�`���f�[�^��ǂݍ���
		new CBossEfect(this);
		CTaskManager::Get()->Add(this);	//�^�X�N���X�g�Ƀ{�X�L�����N�^�[��ǉ�
	}

//���ʎg�p�\
public:
	enum AttackBehavior{
		EIDOL,							//�ҋ@
		EMANTO,							//�}���g
		EBWEAPON,						//������g�p
		EDASH,							//����
		EJUMP,							//�W�����v
		EDAMAGE,						//�_���[�W
		EDOWN,							//�_�E��
		ETELEPO,						//�u�Ԉړ�
		EGUARD,							//�K�[�h
		EAVOIDANCE,						//���
		ESIZE,
	};

	int mBossLife;						//�{�X��HP
	int mBossMaxLife;					//�{�X��HP�̍ő�l
	float mBossLifeProportion;			//�{�X��HP�̊���
	bool mBossBattle;					//�o�g���J�n�t���O
	AttackBehavior mAttackBehavior;
	static CBoss*mpBoss;
	//�����L�̃R���X�g���N�^�ŏo���ʒu��ݒ�
	CBoss(CVector2 Pos)
		:CBoss()
	{
		//�T�C�Y���w��i�e�N�X�`���͕ʂŗp�ӂ���̂ň����ɂ͓���Ȃ��j
		SetRectangle(Pos + CVector2(0.0f, 56.0f), CVector2(32, 90), NULL);
		mBossDefaultPos = Pos + CVector2(0.0f, 56.0f);
	}
	~CBoss(){
		mpBoss = 0;
	}
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
	//�Փˏ���
	bool Collision(CRectangle*);

protected:
	void Boss_A_BehP();
	friend class CPlayerT;
};

#endif
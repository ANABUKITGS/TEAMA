#ifndef CBOSS_H
#define CBOSS_H

#include "CCharcter.h"
#include "CEnemy.h"
#include "CPlayerT.h"
#include <stdlib.h>

#define BOSS_SEARCH 256					//�{�X�̍��G�͈͂�ݒ�
#define BEHAVIOR 6.0f					//�{�X�̍s���؂�ւ��萔

class CBoss : public CCharcter{
//���N���X�����g�p�\
private:
	CVector2 mAttack_Search;			//�{�X�ƃv���C���[�Ƃ̋������o��
	CWeapon*mpBWeapon;					//�{�X�̕���g�p�N���X���C���X�^���X�ɂ���
	float mBossBehavior;				//�G�̊e�s���ɓ��锻�ʋ���
	int mBehaviorPattern;				//�{�X�̈ꕔ�̍s���Ƀ����_���v�f��ǉ�
	float mBossFowrd(float);			//�{�X�̌����ɉ�����
	enum AttackBehavior{
		ENONE,							//�������Ȃ�(�������������̂�)
		EBWEAPON,						//������g�p
		EDASH,							//����
		EJUMP							//�W�����v
	};
	AttackBehavior mAttackBehavior;
	//���������R���X�g���N�^�ŕϐ����̏���������
	CBoss()
	{
		mBossBehavior = BEHAVIOR;		//�G�̍s���l����
		mAttackBehavior = ENONE;		//�������Ȃ���Ԃɂ���
		mTag = EBOSS;					//�^�O���{�X�ɂ���
		mPriority = mTag;				//�D��x���^�O�ɓ����Ă���ԍ��ɂ���
		mRotation = NULL;				//��]�l��0�ɂ���
		CTaskManager::Get()->Add(this);	//�^�X�N���X�g�Ƀ{�X�L�����N�^�[��ǉ�
	}

//���ʎg�p�\
public:
	//�����L�̃R���X�g���N�^�ŏo���ʒu�A�傫���i�R���W�����̑傫���j��ݒ�
	CBoss(CVector2 Pos, CVector2 scale)
		:CBoss()
	{
		SetRectangle(Pos, scale, NULL);	//�T�C�Y���w��i�e�N�X�`���͕ʂŗp�ӂ���̂ň����ɂ͓���Ȃ��j

	}
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
	//�Փˏ���
	bool Collision(CRectangle*);
};

#endif
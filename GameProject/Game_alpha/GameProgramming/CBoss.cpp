#include "CBoss.h"

void CBoss::Update(){
	//�{�X�ƃv���C���[�Ƃ̃x�N�g�����o��
	mAttack_Search = CPlayerT::mpPlayer->mPosition - mPosition;

	//�s���p�^�[������
	switch (mAttackBehavior){
	case EDASH:				//�{�X�̑��鏈��
		if (mPosition.x<=mBossBehavior)
		mPosition.x -= 3;	//�{�X�̈ړ����x���w��
		break;

	case EBWEAPON:																//�{�X�̍U������
		mpBWeapon = new CWeapon(EEWEAPON,mPosition,CVector2(10,10),true,NULL);	//������Ăяo��
		//�{�X�̃��[���[�����˂���Ă���ꍇ
		if (mpBWeapon){
			//���[���[�������̈ʒu�Ɠ����ʒu�ɖ߂��Ă�����폜����
			if (mpBWeapon->mPosition.x == mPosition.x){
				mpBWeapon = false;
			}
		}
		break;

	default:						//�ʏ�ł͋����̉��߂Ŕ��肷��
		if (mAttack_Search.x > mBossBehavior)
			mAttackBehavior = EDASH;
		else

		break;
	}
	Gravity();
	//���N���X�̍X�V����
	CRectangle::Update();
}

void CBoss::Render(){
	//���N���X�̕`�揈��
	CRectangle::Render();
}

bool CBoss::Collision(CRectangle*r){
	if (r->GetEnabled()){
		//�߂荞�񂾕��߂��l���C���X�^���X��
		CVector2 ajust;
		//�v���C���[�ȊO�ƏՓ˂������ɂ͖߂�
		if (r->mTag != EPLAYER){
			if (CRectangle::Collision(r)){
				mPosition.x = mPosition.x + ajust.x;
				mPosition.y = mPosition.y + ajust.y;
			}
			return true;
		}
	}
	return false;
}
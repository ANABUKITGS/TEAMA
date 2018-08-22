#include "CWeapon.h"
#include "CPlayerT.h"
#include "CEnemy.h"
void CWeapon::Update(){
	mRotation += 10;			//���t���[��10����]������
	mLife--;
	if (mLife > 0){	//�������Ԃ�20�𒴉�
		if (mDirection)	//�E����
			mVelocity = WEAPOM_VELOCITY;
		else			//������
			mVelocity = -WEAPOM_VELOCITY;
	}
	else{				//�������Ԃ�15�ȉ�
		if (mDirection)	//�E����
			mVelocity = -WEAPOM_VELOCITY;
		else			//������
			mVelocity = WEAPOM_VELOCITY;
	}
	mPosition.x += mVelocity;
	if (mDirection){
		if (mPosition.x < mPosInit.x){
			mReturn = true;
			mEnabled = false;
			if (CPlayerT::mpPlayer->mAir)
				CPlayerT::mpPlayer->player_ani = CPlayerT::EPLAYERANI::EJUMP;
			else
				CPlayerT::mpPlayer->player_ani = CPlayerT::EPLAYERANI::EIDOL;
			CPlayerT::mpPlayer->player_ani_count = 0;
			CPlayerT::mpPlayer->player_ani_count_flame = 0;
		}
	}
	else{
		if (mPosition.x > mPosInit.x){
			mReturn = true;
			mEnabled = false;
			if (CPlayerT::mpPlayer->mAir)
				CPlayerT::mpPlayer->player_ani = CPlayerT::EPLAYERANI::EJUMP;
			else
				CPlayerT::mpPlayer->player_ani = CPlayerT::EPLAYERANI::EIDOL;
			CPlayerT::mpPlayer->player_ani_count = 0;
			CPlayerT::mpPlayer->player_ani_count_flame = 0;
		}
	}

	CRectangle::Update();

}
void CWeapon::Render(){
	if (mTag == ECELLNUM::EPWEAPON){
		if (mDirection)
			mTexYoyo.DrawImage(PSTRING_UV_R, 1.0f);

		else
			mTexYoyo.DrawImage(PSTRING_UV_L, 1.0f);
	}

	/*------ �G�̃��[���[�̕R�� CEnemy::Render()�ɂ��� ------*/

	CRectangle::Render();
}

bool CWeapon::Collision(CRectangle *p){
	if (CRectangle::Collision(p)){
		switch (mTag){
		case EPWEAPON:
			if (p->mTag == EENEMY1 || p->mTag == EENEMY2 || p->mTag == EENEMY3 || p->mTag == EBOSS ||
				p->mTag == EJEWELRY || p->mTag == EJEWELRY2 || p->mTag == EBOX || p->mTag == ESTEEL)
				mLife = 0;
			break;
		case EEWEAPON:
			if (p->mTag == EBOX || p->mTag == ESTEEL)
				mLife = 0;
			break;
		default:
			break;
		}
		
		return true;
	}
	return false;
}
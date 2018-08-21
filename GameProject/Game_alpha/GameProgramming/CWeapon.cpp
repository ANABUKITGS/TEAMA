#include "CWeapon.h"
#include "CPlayerT.h"



void CWeapon::Update(){
	mRotation+=10;			//���t���[��10����]������
	mLife--;
	if (mLife > 0){
		if (mLife > 20){	//�������Ԃ�20�𒴉�
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
		if (mJewelry){
			mJewelry->mPosition = mPosition;
		}

	}
	else{					//�������Ԃ�0�ȉ�
		mEnabled = false;
		if (CPlayerT::mpPlayer->mAir)
			CPlayerT::mpPlayer->player_ani = CPlayerT::EPLAYERANI::EJUMP;
		else
			CPlayerT::mpPlayer->player_ani = CPlayerT::EPLAYERANI::EIDOL;
		CPlayerT::mpPlayer->player_ani_count = 0;
		CPlayerT::mpPlayer->player_ani_count_flame = 0;
	}
	CRectangle::Update();

}
void CWeapon::Render(){
	CRectangle::Render();
}

bool CWeapon::Collision(CRectangle *p){
	if (CRectangle::Collision(p)){
		if (mTag == EPWEAPON && p->mTag == EENEMY1 && !mJewel_flg){
			/*mJewelry = new CMapJewelry(mPosition);*/
			mJewel_flg = true;
		}
		return true;
	}
	return false;
}
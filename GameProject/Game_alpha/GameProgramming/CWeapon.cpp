#include "CWeapon.h"
#include "CPlayerT.h"
void CWeapon::Update(){
	mRotation+=5;			//���t���[��5����]������
	mLife--;
	if (mLife > 0){
		if (mLife > 15){	//�������Ԃ�15�ȏ�
			if (mDirection)	//�E����
				mVelocity = WEAPOM_VELOCITY;
			else            //������
				mVelocity = -WEAPOM_VELOCITY;
		}
		else{				//�������Ԃ�15�ȉ�
			if (mDirection)	//�E����
				mVelocity = -WEAPOM_VELOCITY;
			else            //������
				mVelocity = WEAPOM_VELOCITY;
		}
		mPosition.x += mVelocity;
		

	}
	else                    //�������Ԃ�0�ȉ�
		mEnabled = false;	
	
	CRectangle::Update();

}
void CWeapon::Render(){
	CRectangle::Render();
}
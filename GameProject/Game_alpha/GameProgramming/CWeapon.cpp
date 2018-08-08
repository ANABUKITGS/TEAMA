#include "CWeapon.h"
#include "CPlayerT.h"
void CWeapon::Update(){
	mRotation+=10;			//���t���[��10����]������
	mLife--;
	if (mLife > 0){
		if (mLife > 20){	//�������Ԃ�20�𒴉�
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
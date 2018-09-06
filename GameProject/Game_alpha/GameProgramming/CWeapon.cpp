#include "CWeapon.h"
#include "CPlayerT.h"
#include "CEnemy.h"
#include "CBoss.h"
void CWeapon::Update(){

	mPosInit = mpCharcter->mPosition;
	/*if (mTag == EPWEAPON && CPlayerT::mpPlayer->player_ani==CPlayerT::EYOYO){
		if (mDirection)
			mPosInit.x += 51;
		else
			mPosInit.x -= 51;
	}*/
	mRotation += 10;			//毎フレーム10ずつ回転させる
	mLife--;
	if (mLife > 0){	//生存時間が20を超過
		if (mDirection)	//右向き
			mVelocity = WEAPOM_VELOCITY;
		else			//左向き
			mVelocity = -WEAPOM_VELOCITY;
	}
	else{				//生存時間が15以下
		if (mTag == EPWEAPON){
			if (mDirection)	//右向き
				mVelocity = -WEAPOM_VELOCITY + CPlayerT::mpPlayer->mVelocityX;
			else			//左向き
				mVelocity = WEAPOM_VELOCITY + CPlayerT::mpPlayer->mVelocityX;
		}
		else{
			if (mDirection)	//右向き
				mVelocity = -WEAPOM_VELOCITY;
			else			//左向き
				mVelocity = WEAPOM_VELOCITY;
		}
		float mVelocityY = (mPosition.y - mPosInit.y) / abs((mPosition.x - mPosInit.x) / WEAPOM_VELOCITY);
		mPosition.y -= mVelocityY;
	}
	
	mPosition.x += mVelocity;
	if (mDirection){
		if (mPosition.x < mPosInit.x){
			mReturn = true;
			mEnabled = false;
			//if (CPlayerT::player_ani != CPlayerT::EPLAYERANI::EDOWN){
			//	if (CPlayerT::mpPlayer->mAir)
			//		CPlayerT::mpPlayer->player_ani = CPlayerT::EPLAYERANI::EJUMP;
			//	else
			//		CPlayerT::mpPlayer->player_ani = CPlayerT::EPLAYERANI::EIDOL;
			//	CPlayerT::mpPlayer->player_ani_count = 0;
			//	CPlayerT::mpPlayer->player_ani_count_frame = 0;
			//}
		}
	}
	else{
		if (mPosition.x > mPosInit.x){
			mReturn = true;
			mEnabled = false;
			//if (CPlayerT::player_ani != CPlayerT::EPLAYERANI::EDOWN){
			//	if (CPlayerT::mpPlayer->mAir)
			//		CPlayerT::mpPlayer->player_ani = CPlayerT::EPLAYERANI::EJUMP;
			//	else
			//		CPlayerT::mpPlayer->player_ani = CPlayerT::EPLAYERANI::EIDOL;
			//	CPlayerT::mpPlayer->player_ani_count = 0;
			//	CPlayerT::mpPlayer->player_ani_count_frame = 0;
			//}
		}
	}

	CRectangle::Update();

}
void CWeapon::Render(){
	//線描画スタイルの指定
	glBegin(GL_LINES);

	//頂点指定
	if (mTag == EBWEAPON){
		glVertex2d(mPosInit.x, mPosInit.y + 32);
		glVertex2d(mPosition.x, mPosition.y);
	}
	else if(mTag == EPWEAPON && CPlayerT::mpPlayer->player_ani == CPlayerT::EYOYO){
		if (mDirection){
			glVertex2d(mPosInit.x+51, mPosInit.y + 16);
			glVertex2d(mPosition.x, mPosition.y);
		}
		else{
			glVertex2d(mPosInit.x-51, mPosInit.y + 16);
			glVertex2d(mPosition.x, mPosition.y);
		}
	}
	else{
		glVertex2d(mPosInit.x, mPosInit.y + 16);
		glVertex2d(mPosition.x, mPosition.y);
	}
	

	//線描画スタイルの指定終了
	glEnd();

	
}

bool CWeapon::Collision(CRectangle *p){
	if (CRectangle::Collision(p)){
		switch (mTag){
		case EPWEAPON:
			switch (p->mTag){
			case EENEMY1:
			case EENEMY2:
			case EENEMY3:
				if (p->mAlpha < 1)
					break;
			case EBOSS:
				if (CBoss::mpBoss != NULL && CBoss::mpBoss->mAttackBehavior != CBoss::AttackBehavior::EDOWN)
					mLife = 0;
				break;

			case EJEWELRY:
			case EJEWELRY2:
			case EBOX:
			case ESTEEL:
			case ESWITCH:
			case ESDIAMOND:
			mLife = 0;
				break;

			default:
				break;
			}
			break;
		case EEWEAPON:
		case EBWEAPON:
			if (p->mTag == EBOX || p->mTag == ESTEEL || p->mTag == EPLAYER)
				mLife = 0;
			break;

		default:
			break;
		}
		
		return true;
	}
	return false;
}
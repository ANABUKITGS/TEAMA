#ifndef CPLAYERT_H
#define CPLAYERT_H

#include "CCharcter.h"
#include "CTaskManager.h"
#include "CWeapon.h"
#include "CGame2.h"

#define PLAYER_VELOCITY_X 5.0f
#define PLAYER_VELOCITY_Y 20.0f
#define JUMP_TIME_LIMIT 15
#define VELOCITYX_LIMIT 5.0f


class CPlayerT : public CCharcter {
public:
	enum EPLAYERANI{
		EIDOL = 1,	//アイドル状態
		ERUN,		//走る
		ETURN,		//方向転換
		EJUMP,		//ジャンプ
		EDAMAGE,	//ダメージ
		EYOHYOH,	//ヨーヨー攻撃
		EDOWN,		//やられ
		ESIZE,		//EPLAYERANI サイズ
	};
	static int player_ani;
	int player_ani_count;
	int player_ani_count_flame;
	int PLAYER_ANI_COUNT_FLAME;
	static CPlayerT *mpPlayer;
	CTexture mTexPlayer;
	bool mJump;				// true : ジャンプ中  false : ジャンプしてない
	int mJumpCount;			//ジャンプ回数
	bool mAttack;			//攻撃  true : 可能  false : 不可能

	CWeapon *mWeapon;
	CPlayerT() 
		:mWeapon(0)
	
	{
		mpPlayer = this;
		mPriority = 1;
		mTag = EPLAYER;
		mJump = false;
		mAttack = true;
		mJumpCount = 0;
		CTaskManager::Get()->Add(this);
		mTexPlayer.Load(".\\Data\\Images\\Player\\Player.tga");
		player_ani = EIDOL;
		player_ani_count = 0;
		player_ani_count_flame = 0;
		PLAYER_ANI_COUNT_FLAME = 1;
	}

	CPlayerT::CPlayerT(const CVector2&position, const CVector2&scale, CTexture*texture)
		: CPlayerT()
	{
		SetRectangle(position, scale, texture);
		mVelocityY = 0;
		mVelocityX = 0;
		mDirection = true;
		
	}

	void Update();
	void Forward();
	void Attack();
	void Render();
	void Dash();

	bool Collision(CRectangle *p);

};



#endif

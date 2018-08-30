#ifndef CPLAYERT_H
#define CPLAYERT_H

#include "CCharcter.h"
#include "CTaskManager.h"
#include "CWeapon.h"
#include "CGame2.h"

#define PLAYER_VELOCITY_X		5.0f
#define PLAYER_VELOCITY_Y		20.0f
#define JUMP_TIME_LIMIT			15
#define VELOCITYX_LIMIT			5.0f
#define DAMAGE_INTERVAL			180
#define PLAYER_DOWN_TIME		60
#define PLAYER_GAMEOVER_TIME	120

#define PLAYER_TEX_POS mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - mScale.y, mPosition.y - mScale.y + CELLSIZE * 2


class CPlayerT : public CCharcter {
private:
	CTexture mTexPlayer;

public:
	enum EPLAYERANI{
		EIDOL = 1,	//アイドル状態
		ERUN,		//走る
		ETURN,		//方向転換
		EJUMP,		//ジャンプ
		EDAMAGE,	//ダメージ
		EYOYO,	//ヨーヨー攻撃
		EDOWN,		//やられ
		ESIZE,		//EPLAYERANI サイズ
	};
	static int player_ani;
	int player_ani_count;
	int player_ani_count_frame;
	int PLAYER_ANI_COUNT_FRAME;
	static CPlayerT *mpPlayer;

	bool mJump;				//true:ジャンプボタン入力中  false:ジャンプ入力していない
	bool mDash;				//true:ダッシュ中  false:ダッシュしていない
	int mJumpCount;			//ジャンプ回数
	bool mAerialAttack;		//空中攻撃  true:可能  false:不可能
	bool mAir;				//true:空中 false:地上
	int mLife;				//プレイヤーの残機
	int mJewel;				//ジュエル所持数
	int mMaxJewel;			//ボスの部屋でのジュエル所持数
	int mMiniJewel;			//ミニジュエル所持数
	int mDamageInterval;	//ダメージインターバル
	bool mUnrivaled;		//true:無敵状態
	float mAlpha;			//アルファ値
	int mBackupJewel;		//チェックポイント通過時のジュエル数
	CVector2 mReSpornPos;	//リスポーン地点
	int mDamage;			//ダメージを受けた際のジュエルを減らす量

	CWeapon *mpWeapon;
	CPlayerT() 
		:mpWeapon(0)
	
	{
		mRender = false;
		mpPlayer = this;
		mPriority = 1;
		mTag = EPLAYER;
		mJump = false;
		mDash = false;
		mVelocityY = 0;
		mVelocityX = 0;
		mDirection = true;
		mAerialAttack = false;
		mAir = false;
		mJumpCount = 0;
		CTaskManager::Get()->Add(this);
		mTexPlayer.Load(".\\Data\\Images\\Player\\Player.tga");
		player_ani = EIDOL;
		player_ani_count = 0;
		player_ani_count_frame = 0;
		PLAYER_ANI_COUNT_FRAME = 1;
		mBackupJewel=mJewel = 3;
		mMaxJewel = 0;
		mMiniJewel = 0;
		mLife = 3;
		mDamageInterval = DAMAGE_INTERVAL;
		mUnrivaled = false;
		mAlpha = 1.0f;
	}

	CPlayerT::CPlayerT(const CVector2&position)
		: CPlayerT()
	{
		SetRectangle(position + CVector2(0.0f, 28.0f), CVector2(16, 60), NULL);
		mReSpornPos = position;
	}
	~CPlayerT(){
		mpPlayer = 0;
	}

	void Update();
	void Forward();
	void Attack();
	void Render();
	void Dash();
	void Damage(ECELLNUM);
	void Die();

	bool Collision(CRectangle *p);

};



#endif

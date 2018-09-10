#include "CBossGimmick.h"
#include <iostream>

CBossGimmick *CBossGimmick::mpBossGimmick = NULL;
CBossGimmickSign *CBossGimmickSign::mpBossGimmickSign = NULL;

void CBossGimmick::Update(){
	mPosition = CPlayerT::mpPlayer->mPosition;
	if (!mGimmickFlg && !mWait && GetRandom(BOX_PROBABILITY) && CBoss::mpBoss->mBossLife > 0)
		mGimmickFlg = true;


	if (mGimmickFlg){
		if (CBossGimmickSign::mpBossGimmickSign == NULL){
			mFallingPos = CVector2(CPlayerT::mpPlayer->mPosition.x, 640.0f);
			CBossGimmickSign::mpBossGimmickSign = new CBossGimmickSign(mFallingPos);
		}
		if (mLag >= LAG_TIME){
			new CMapBox(mFallingPos, true);
			mWait = 1;
			mLag = 0;
			mGimmickFlg = false;
			return;
		}
		mLag++;
		return;
	}
	if (mWait < WAIT_TIME){
		mWait++;
		mLag = 0;
		mGimmickFlg = false;
	}
	else
		mWait = 0;

	if (CPlayerT::mpPlayer->mJewel <= 0)
		mEnabled = false;
}

bool CBossGimmick::GetRandom(int probability){
	int num = 0;					//配列 番号
	static int max = probability;	//配列 範囲
	int ans = 0;					//結果
	int temp = 0;					//値 一時保管

	if (max <= 0)
		max = probability;

	srand((unsigned int)time(NULL) - clock());
	num = rand() % max;
	ans = mBoxProbability[num];

	//出た値と最後の値の入れ替え
	max -= 1;
	mBoxProbability[num] = mBoxProbability[max];
	mBoxProbability[max] = ans;

#ifdef _DEBUG
	std::cout << ans << std::endl;
#endif
	
	if (!ans){
		max = probability;
		return true;
	}
	else
		return false;
}

void CBossGimmickSign::Update(){
	if (CBossGimmick::mpBossGimmick != NULL){
		if (mAnime >= LAG_TIME){
			mEnabled = false;
			return;
		}

		if (mAnime % 8 >= 0 && mAnime % 8 < 4)
			mAlpha = 1.0f;
		else
			mAlpha = 0.0f;
		mAnime++;
	}
	else
		mEnabled = false;
}

void CBossGimmickSign::Render(){
	mTexExclamation.DrawImage(EXCLAMATION_UV, mAlpha);
}
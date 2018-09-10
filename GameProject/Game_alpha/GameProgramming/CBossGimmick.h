#ifndef CBOSSGIMMICK_H
#define CBOSSGIMMICK_H
#include <random>
#include "CRectangle.h"
#include "CPlayerT.h"
#include "CBoss.h"
#include "CMapBox.h"
#include "CMapSign.h"

#define WAIT_TIME		90	//���̗����܂ł̃N�[���^�C��
#define LAG_TIME		30	//���� �x�� ����
#define BOX_PROBABILITY	5	//�R���e�i�𗎂Ƃ��m��

#define EXCLAMATION_UV	mPosition.x - 32, mPosition.x + 32, mPosition.y - 32, mPosition.y + 32, 0, 64, 64, 0

class CBossGimmick : public CRectangle{
private:
	int mWait;								//�N�[���^�C�� �v��
	int mLag;								//���� �x�� ����
	int mBoxProbability[BOX_PROBABILITY];	//�m��
	CVector2 mFallingPos;					//�����ʒu

public:
	static CBossGimmick *mpBossGimmick;
	bool mGimmickFlg;

	CBossGimmick()
		:CRectangle(CMapBossRoomSign::mpBossRoomSign->mPosition, CVector2(0.0f, 0.0f), NULL)
		, mLag(0)
		, mWait(1)
		, mGimmickFlg(false)
	{
		mFallingPos = CVector2(0.0f, 0.0f);
		mRender = false;
		for (int i = 0; i < BOX_PROBABILITY; i++)
			mBoxProbability[i] = i;

		mTag = ECELLNUM::ENONE;
		CTaskManager::Get()->Add(this);
	}
	~CBossGimmick(){
		mpBossGimmick = NULL;
	}
	void Update();
	bool GetRandom(int);
};

class CBossGimmickSign : public CRectangle{
private:
	CTexture mTexExclamation;
	int mAnime;

public:
	static CBossGimmickSign *mpBossGimmickSign;
	CBossGimmickSign(CVector2 pos)
		:CRectangle(pos, CVector2(0.0f, 0.0f), NULL)
	{
		mRender = false;
		mAlpha = 1.0f;
		if (mTexExclamation.id == NULL)
			mTexExclamation.Load(".\\Data\\Images\\Boss\\Exclamation.tga");
		mAnime = 0;
		mTag = ECELLNUM::ENONE;
		CTaskManager::Get()->Add(this);
	}
	~CBossGimmickSign(){
		mpBossGimmickSign = NULL;
	}

	void Update();
	void Render();
};
#endif
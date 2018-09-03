#ifndef CMAPSIGN_H
#define CMAPSIGN_H
#include "CMapChip.h"
#include "CMap.h"
#include "CCamera2D.h"
#include "CGame2.h"

#define SIGN_UV				mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 0, 64, 64, 0
#define BOSSROOM_SIGN_UV	mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, 0, 64, mTexPosY + 128, mTexPosY
#define BOSSROOM_SIGN_UV2	mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, 0, 64, 256, 128
#define TEXTVIEW_UV			CGame2::mCamera.x - 256, CGame2::mCamera.x + 256, CGame2::mCamera.y - 128, CGame2::mCamera.y + 128, 0, 512, 512, 0

#define DRAWSTRING_UV	text_buf, -256, 192, 32, 3, 1.0f

#define SIGN_NUM		5

//チュートリアル 看板
class CMapSign : public CMapChip {
private:
	CTexture mTexSign;
	struct SMapSign{
		bool flg;
		wchar_t text[MAX_PATH];
	};
	static SMapSign mSignText[SIGN_NUM];

public:
	int sign_num;
	static bool mView;
	CMapSign(const CVector2& pos)
		//CMapChipで初期化
		: CMapChip(pos, CVector2(CELLSIZE / 2, CELLSIZE / 2), NULL, NULL, NULL, NULL, NULL, ECELLNUM::ESIGN)
	{
		if (mTexSign.id == NULL)
			mTexSign.Load(".\\Data\\Images\\Map\\MapSign.tga");
		mRender = false;
		mTag = ECELLNUM::ESIGN;
		mView = false;
	}
	void Update();
	bool Collision(CRectangle *r);	//衝突時の処理
	void Render();
};

class CMapTextView : public CRectangle{
private:
	CTexture mTexTextView;

public:
	static CMapTextView *mpTextView;
	CMapTextView::CMapTextView()
		: CRectangle(CVector2(CGame2::mCamera.x, CGame2::mCamera.y), CVector2(0, 0), NULL)
	{
		mPriority = -100;
		mRender = false;
		CTaskManager::Get()->Add(this);
	}
	~CMapTextView(){
		mpTextView = 0;
	}
	void Update();
	void Render();
};

//チュートリアル終了 看板
class CMapEndSign : public CMapChip {
private:
	CTexture mTexEndSign;

public:
	static CMapEndSign *mpEndSign;
	CMapEndSign(const CVector2& pos)
		//CMapChipで初期化
		: CMapChip(pos, CVector2(CELLSIZE / 2, CELLSIZE / 2), NULL, NULL, NULL, NULL, NULL, ECELLNUM::EENDSIGN)
	{
		if (mTexEndSign.id == NULL)
			mTexEndSign.Load(".\\Data\\Images\\Map\\MapSign.tga");
		mRender = false;
		mTag = ECELLNUM::EENDSIGN;
	}
	~CMapEndSign(){
		mpEndSign = 0;
	}
	void Update();
	bool Collision(CRectangle *r);	//衝突時の処理
	void Render();
};

//ボスの部屋 看板
class CMapBossRoomSign : public CMapChip {
private:
	CTexture mTexBossRoomSign;
	int mTexPosY;

public:
	bool mColFlg;
	static CMapBossRoomSign *mpBossRoomSign;
	CMapBossRoomSign(const CVector2& pos)
		//CMapChipで初期化
		: CMapChip(pos + CVector2(0.0f, CELLSIZE / 2), CVector2(CELLSIZE / 2, CELLSIZE), NULL, NULL, NULL, NULL, NULL, ECELLNUM::EBOSSROOM)
	{
		if (mTexBossRoomSign.id == NULL)
			mTexBossRoomSign.Load(".\\Data\\Images\\Map\\MapBossRoomSign.tga");
		mTexPosY = 0;
		mColFlg = false;
		mRender = false;
		mTag = ECELLNUM::EBOSSROOM;
	}
	~CMapBossRoomSign(){
		mpBossRoomSign = 0;
	}
	void Update();
	bool Collision(CRectangle *r);	//衝突時の処理
	void Render();
};
#endif
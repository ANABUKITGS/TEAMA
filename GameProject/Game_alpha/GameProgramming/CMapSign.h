#ifndef CMAPSIGN_H
#define CMAPSIGN_H
#include "CMapChip.h"
#include "CMap.h"
#include "CCamera2D.h"
#include "CGame2.h"

#define SIGN_UV			0, 64, 64 * 6, 64 * 5
#define TEXTVIEW_UV		CGame2::mCamera.x - 256, CGame2::mCamera.x + 255, CGame2::mCamera.y - 256, CGame2::mCamera.y + 256, 0, 512, 512, 0

#define DRAWSTRING_UV	text_buf, -256, 192, 32, 3, 1.0f
#define TEXT1			L"hogehogehoge\nあいうえおかきくけこ\n0123456789"

//チュートリアル 看板
class CMapSign : public CMapChip {
private:
	CTexture mTexSign;

public:
	int sign_num;
	bool mView;
	CMapSign(const CVector2& pos)
		//CMapChipで初期化
		: CMapChip(pos, CVector2(CELLSIZE / 2, CELLSIZE / 2), NULL, SIGN_UV, ECELLNUM::ESIGN)
	{
		mTexSign.Load(".\\Data\\Images\\Map\\MapSign.tga");
		mRender = false;
		mTag = ECELLNUM::ESIGN;
	}
	void Update();
	bool Collision(CRectangle *r);	//衝突時の処理
	void Render();
};

class CMapTextView : public CRectangle{
private:
	CTexture mTexTextView;
	wchar_t text_buf[256];

public:
	CMapTextView::CMapTextView()
		: CRectangle(CVector2(CGame2::mCamera.x, CGame2::mCamera.y), CVector2(0, 0), NULL)
	{
		mPriority = -10;
		mTexTextView.Load(".\\Data\\Images\\Map\\TextView.tga");
		mRender = false;
		swprintf(text_buf, TEXT1);
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
		: CMapChip(pos, CVector2(CELLSIZE / 2, CELLSIZE / 2), NULL, SIGN_UV, ECELLNUM::EENDSIGN)
	{
		mTexEndSign.Load(".\\Data\\Images\\Map\\MapEndSign.tga");
		mRender = false;
		mTag = ECELLNUM::EENDSIGN;
	}
	void Update();
	bool Collision(CRectangle *r);	//衝突時の処理
	void Render();
};

//ボスの部屋 看板
class CMapBossRoomSign : public CMapChip {
private:
	CTexture mTexBossRoomSign;

public:
	static CMapBossRoomSign *mpBossRoomSign;
	CMapBossRoomSign(const CVector2& pos)
		//CMapChipで初期化
		: CMapChip(pos, CVector2(CELLSIZE / 2, CELLSIZE / 2), NULL, SIGN_UV, ECELLNUM::EBOSSROOM)
	{
		mTexBossRoomSign.Load(".\\Data\\Images\\Map\\MapEndSign.tga");
		mRender = false;
		mTag = ECELLNUM::EBOSSROOM;
	}
	void Update();
	bool Collision(CRectangle *r);	//衝突時の処理
	void Render();
};
#endif
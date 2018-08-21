#ifndef CMAPSIGN_H
#define CMAPSIGN_H
#include "CMapChip.h"
#include "CMap.h"
#include "CCamera2D.h"
#include "CGame2.h"

#define SIGN_UV			0, 64, 64 * 6, 64 * 5
#define TEXTVIEW_UV		CGame2::mCamera.x - 256, CGame2::mCamera.x + 255, CGame2::mCamera.y - 256, CGame2::mCamera.y + 256, 0, 512, 512, 0

#define DRAWSTRING_UV	text_buf, -256, 192, 32, 3, 1.0f
#define TEXT1			L"hogehogehoge\nÇ†Ç¢Ç§Ç¶Ç®Ç©Ç´Ç≠ÇØÇ±\n0123456789"

class CMapSign : public CMapChip {
public:
	int sign_num;
	bool mView;
	CTexture mTexSignhoge;
	CMapSign(const CVector2& pos)
		//CMapChipÇ≈èâä˙âª
		: CMapChip(pos, CVector2(CELLSIZE / 2, CELLSIZE / 2), NULL, SIGN_UV, ECELLNUM::ESIGN)
	{
		mTexSignhoge.Load(".\\Data\\Images\\Map\\MapSign.tga");
		mPriority = 0;
		mRender = false;
		static int sign_num_temp = 0;
		sign_num_temp++;
		sign_num = sign_num_temp;
		mTag = ECELLNUM::ESIGN;
	}
	void Update();
	bool Collision(CRectangle *r);	//è’ìÀéûÇÃèàóù
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
#endif
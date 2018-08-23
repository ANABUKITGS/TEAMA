#ifndef CMAPBELT_H
#define CMAPBELT_H
#include "CMapChip.h"
#include "CMap.h"
#include "CPlayerT.h"
#include "CEnemy.h"

//左 端
#define BELT_UV1L	mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 0, 64, 64 , 0, 1.0f
//右 端
#define BELT_UV1R	mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 64, 0, 64 , 0, 1.0f
//中央
#define BELT_UV2	mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 0, 64, 128 , 64, 1.0f
//1つのみ
#define BELT_UV3	mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 0, 64, 192, 128, 1.0f
//矢印
//#define BELTSIGN_UV	0, 64, 256, 192, 1.0f
//ベルトコンベアの速度
#define BELT_SPEED	3.0f

class CMapBeltSign : public CRectangle{
private:
	ECELLNUM mDirection;
	CTexture mTexBeltSign;

public:
	CMapBeltSign(){
		if (mTexBeltSign.id == NULL)
			mTexBeltSign.Load(".\\Data\\Images\\Map\\MapBelt.tga");
		mTag = ECELLNUM::ENONE;
		mRotation = 0.0f;
		mPriority = -2;
		CTaskManager::Get()->Add(this);
	}
	CMapBeltSign::CMapBeltSign(const CVector2& pos, ECELLNUM tag)
		:CMapBeltSign()
	{
		SetRectangle(pos, CVector2(32, 32), &mTexBeltSign);
		mDirection = tag;
		if (tag == ECELLNUM::EBELTL){
			mUv[0] = 64;
			mUv[1] = 0;
		}
		if (tag == ECELLNUM::EBELTR){
			mUv[0] = 0;
			mUv[1] = 64;
		}
		mUv[2] = 256;
		mUv[3] = 192;
	}
	void Update();
	void Render();
};

class CMapBelt : public CMapChip{
private:
	ECELLNUM mDirection;
	CTexture mTexBelt;

public:
	enum ETEXTURE_POSNUM{
		ELEFT = 1,
		ECENTER,
		ERIGHT,
		EONE,
		ESIZE,
	};
	ETEXTURE_POSNUM texture_pos;

	CMapBelt(const CVector2& pos, const CVector2& scale, ECELLNUM tag, ETEXTURE_POSNUM texpos)
		//CMapChipで初期化
		: CMapChip(pos, scale, NULL, NULL, NULL, NULL, NULL, tag)
	{
		mRender = false;
		mDirection = tag;
		texture_pos = texpos;
		if (mTexBelt.id == NULL)
			mTexBelt.Load(".\\Data\\Images\\Map\\MapBelt.tga");
		if (texpos != CMapBelt::ETEXTURE_POSNUM::ECENTER){
			new CMapBeltSign(pos, tag);
		}
	}

	static CMapBelt *mpBelt;

	void Update();
	bool Collision(CRectangle *r);	//衝突時の処理
	void Render();
};
#endif
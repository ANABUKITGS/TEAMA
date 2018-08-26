#ifndef CRECTANGLE_H
#define CRECTANGLE_H
#include "CTask.h"
#include "CVector2.h"
#include "CTexture.h"
#include "CMatrix33.h"
//#include "CMap.h"

#define BLACK 0.0f, 0.0f, 0.0f
#define WHITE 1.0f, 1.0f, 1.0f

class CRectangle : public CTask{
public:
	char mColFlg;	//ブロック空き方向フラグ
	bool mBreak;	//落下オブジェクト 落下判定
	ECELLNUM mTag;
	CVector2 mPosition;	//四角形の中心座標	x四角形の中心のX座標	y四角形の中心Y座標
	CVector2 mVector[4];	//四角形生成メソッドに使うインスタンス変数
	CVector2 mScale;	//四角形の幅と高さ
	CTexture*mpTexture;	//四角形が使用するテクスチャへのポインタ
	CMatrix33 mMatrix;	//マトリクスをインスタンスにする(これは移動行列用)
	float mVelocityX;		//X軸の移動速度
	float mVelocityY;		//Y軸の移動速度
	bool mDirection;		//キャラクターの向き true:右 false:左
	float mRotation;	//四角形の回転角度
	float mUv[4];	//テクスチャマッピングデータ
	float mRight, mLeft, mTop, mBottom;
	float mAlpha;
	bool mIce;			//氷の足場
	CRectangle()
		: mRotation(0.0f)
		, mpTexture(0)
		, mAlpha(1.0f)
		, mColFlg(0)
		, mVelocityX(0.0f)
		, mVelocityY(0.0f)
		, mDirection(false)
		, mIce(false)
		, mBreak(false)
	{}
	/*
	position:位置
	scale:大きさ
	texture:テクスチャの有無(有:テクスチャのインスタンス,無:0)
	*/
	CRectangle(const CVector2&position, const CVector2&scale, CTexture*texture);
	void SetVertex(float mLeft, float mRight, float mBottom, float mTop);	//四角形生成メソッド
	void Update();	//更新処理
	virtual void Render(float, float, float, float);	//描画処理
	virtual void Render();
	virtual bool Collision(CRectangle *target);
	bool Collision(CRectangle *target, CVector2 *adjust);
	void SetRectangle(const CVector2&position, const CVector2&scale, CTexture*texture);
	bool Collision(CRectangle *target, CVector2 *adjust, CVector2 *ad);
};
#endif
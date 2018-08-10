#ifndef CCHARCTER_H
#define CCHARCTER_H

#include "CRectangle.h"
#include "CTexture.h"
#include "CGamePad.h"
#include "CText.h"
#include "CMap.h"

class CCharcter :public CRectangle{
public:
	int mVelocityLimit;		//移動限界速度
	void Update();			//更新処理
	void Render();			//描画処理
	void Gravity();			//重力処理
	void Forward();			//前進処理
	void Scroll();			//画面のスクロール処理
	
};
#endif
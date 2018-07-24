#ifndef CTITLE_H
#define CTITLE_H
#include <Windows.h>
#include "CRectangle.h"
#include "CKey.h"
#include "CTexture.h"
#include "CText.h"

class CTitle{
public:
#define TITLE_TEXT_SET01	0, 0, 64, 1.0f, 0	//タイトル
#define TITLE_TEXT_SET02	0, -64, 16, 1.0f, 0	//項目
	unsigned int title_num;				//タイトル 項目
	CTexture mTexture;					//テクスチャー

	void Init();
	void Update();
	void GameExit();
	void Render();
};
#endif
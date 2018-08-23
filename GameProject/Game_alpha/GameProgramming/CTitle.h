#ifndef CTITLE_H
#define CTITLE_H
#include "CText.h"
#include "CGamePad.h"
//hoge
class CTitle{
private:
	wchar_t cursor_buf[32];

public:
	int cursor_num;
	CTexture mTexTitle;
	void Init();
	void Update();
	void Render();
};
#endif
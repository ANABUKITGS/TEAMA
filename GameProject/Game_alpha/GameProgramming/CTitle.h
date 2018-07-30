#ifndef CTITLE_H
#define CTITLE_H
#include "CText.h"
#include "CGamePad.h"

class CTitle{
private:
	int cursor_num;
	wchar_t cursor_buf[32];

public:
	void Init();
	void Update();
	void Render();
};
#endif
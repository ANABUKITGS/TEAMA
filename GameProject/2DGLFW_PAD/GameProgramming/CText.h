#include "CTexture.h"

/*
文字の描画
*/
class CText {
public:
	//テクスチャの指定
	static CTexture mFont;
	//29 文字の描画
	static void DrawChar(char ch, int x, int y, int w, int h);
	//30
	static void DrawString(char *s, int x, int y, int w, int h);
};

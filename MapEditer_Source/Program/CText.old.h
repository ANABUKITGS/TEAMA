#ifndef CTEXT_H
#define CTEXT_H

#include <ctype.h>
#include <wchar.h>
#include "CTexture.h"

class CText{
public:
	static CTexture mTexture;	//ƒeƒLƒXƒg ƒeƒNƒXƒ`ƒƒ[
	static float uv[4];
	static int ds;
	static void Init();
	//”¼Šp•¶šê—p
	static void DrawText(char a, float left, float right, float bottom, float top, float r, float g, float b, float alpha);
	//”¼Šp•¶šê—p | ˆ—
	static void SetDrawString(char s[], float left, float bottom, float size, float r, float g, float b, float alpha, int drawspeed);
	//”¼Šp•¶šê—p | F‚Ì‰ÁZ ‚È‚µ
	static void DrawString(char s[], float left, float bottom, float size, float alpha, int drawspeed);
	//”¼Šp•¶šê—p | F‚Ì‰ÁZ ‚ ‚è
	static void DrawStringSetColor(char s[], float left, float bottom, float size, float r, float g, float b, float alpha, int drawspeed);

	//‘SŠp”¼Šp•¶š—p
	static void DrawTextW(wchar_t a, float left, float right, float bottom, float top, float r, float g, float b, float alpha);
	//‘SŠp”¼Šp•¶š | ˆ—
	static void SetDrawStringW(wchar_t s[], float left, float bottom, float size, float r, float g, float b, float alpha, int drawspeed);
	//‘SŠp”¼Šp•¶š | F‚Ì‰ÁZ ‚È‚µ
	static void DrawStringW(wchar_t s[], float left, float bottom, float size, float alpha, int drawspeed);
	//‘SŠp”¼Šp•¶š | F‚Ì‰ÁZ ‚ ‚è
	static void DrawStringWSetColor(wchar_t s[], float left, float bottom, float size, float r, float g, float b, float alpha, int drawspeed);
};
#endif
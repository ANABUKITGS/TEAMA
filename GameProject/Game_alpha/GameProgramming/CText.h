#ifndef CTEXT_H
#define CTEXT_H

#include <ctype.h>
#include <wchar.h>
#include "CTexture.h"

class CText{
public:
	static CTexture mTexture01;	//テキスト テクスチャー M+ 1m bold
	static CTexture mTexture02;	//テキスト テクスチャー nintendoP Seurat
	static float uv[4];
	static int ds;
	static void Init();
	//半角文字専用
	static void DrawText(char a, float left, float right, float bottom, float top, float r, float g, float b, float alpha);
	//半角文字専用 | 処理
	static void SetDrawString(char s[], float left, float bottom, float size, float r, float g, float b, float alpha, int drawspeed);
	//半角文字専用 | 色の加算 なし
	static void DrawString(char s[], float left, float bottom, float size, float alpha, int drawspeed);
	//半角文字専用 | 色の加算 あり
	static void DrawStringSetColor(char s[], float left, float bottom, float size, float r, float g, float b, float alpha, int drawspeed);

	//全角半角文字用
	static void DrawTextW(wchar_t a, float left, float right, float bottom, float top, float r, float g, float b, float alpha);
	//全角半角文字 | 処理
	static void SetDrawStringW(wchar_t s[], float left, float bottom, float size, float r, float g, float b, float alpha, int drawspeed);
	//全角半角文字 | 色の加算 なし
	static void DrawStringW(wchar_t s[], float left, float bottom, float size, float alpha, int drawspeed);
	//全角半角文字 | 色の加算 あり
	static void DrawStringWSetColor(wchar_t s[], float left, float bottom, float size, float r, float g, float b, float alpha, int drawspeed);
};
#endif
#ifndef CTEXT_H
#define CTEXT_H

#include <ctype.h>
#include <wchar.h>
#include "CTexture.h"

class CText{
public:
	static CTexture mTexture;	//�e�L�X�g �e�N�X�`���[
	static float uv[4];
	static int ds;
	static void Init();
	//���p������p
	static void DrawText(char a, float left, float right, float bottom, float top, float r, float g, float b, float alpha);
	//���p������p | ����
	static void SetDrawString(char s[], float left, float bottom, float size, float r, float g, float b, float alpha, int drawspeed);
	//���p������p | �F�̉��Z �Ȃ�
	static void DrawString(char s[], float left, float bottom, float size, float alpha, int drawspeed);
	//���p������p | �F�̉��Z ����
	static void DrawStringSetColor(char s[], float left, float bottom, float size, float r, float g, float b, float alpha, int drawspeed);

	//�S�p���p�����p
	static void DrawTextW(wchar_t a, float left, float right, float bottom, float top, float r, float g, float b, float alpha);
	//�S�p���p���� | ����
	static void SetDrawStringW(wchar_t s[], float left, float bottom, float size, float r, float g, float b, float alpha, int drawspeed);
	//�S�p���p���� | �F�̉��Z �Ȃ�
	static void DrawStringW(wchar_t s[], float left, float bottom, float size, float alpha, int drawspeed);
	//�S�p���p���� | �F�̉��Z ����
	static void DrawStringWSetColor(wchar_t s[], float left, float bottom, float size, float r, float g, float b, float alpha, int drawspeed);
};
#endif
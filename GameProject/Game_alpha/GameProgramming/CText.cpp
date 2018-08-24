#include "CText.h"

#define CSIZE 64

int CText::ds = 0;
float CText::uv[4];

CTexture CText::mTexture01;	//テキスト テクスチャー M+ 1m bold
CTexture CText::mTexture02;	//テキスト テクスチャー nintendoP Seurat
CTexture CText::mTexture03;	//テキスト テクスチャー アイテム
int CText::soundtime;		//文字表示音 間隔
bool CText::textlimit;		//変数 加算時間

void CText::Init(){
	mTexture01.Load(".\\Data\\Images\\Font\\Mplus_1m_bold-Unicode_064.tga");
	mTexture02.Load(".\\Data\\Images\\Font\\nintendoP_Seurat_064.tga");
	mTexture03.Load(".\\Data\\Images\\Font\\Item.tga");
}

void CText::DrawText(char a, float left, float right, float bottom, float top, float r, float g, float b, float alpha){
	if (isupper(a)){	//U+0041 ~ U+005A
		a = a - 'A';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 2;
		CText::uv[3] = CSIZE * 1;
	}
	else if (islower(a)){	//U+0061 ~ U+007A
		a = a - 'a';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 1;
		CText::uv[3] = CSIZE * 0;
	}
	else if (a >= ' ' && a <= '@'){	//U+0020 ~ U+0040
		a = a - ' ';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 3;
		CText::uv[3] = CSIZE * 2;
	}
	else if (a >= '[' && a <= '`'){	//U+005B ~ U+0060
		a = a - '[';
		CText::uv[0] = 33 * CSIZE + a*CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 3;
		CText::uv[3] = CSIZE * 2;
	}
	else if (a >= '{' && a <= '~'){	//U+007B ~ U+007E
		a = a - '{';
		CText::uv[0] = 39 * CSIZE + a*CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 3;
		CText::uv[3] = CSIZE * 2;
	}
	else if (a == '\n'){	//U+000D, U+000A
		CText::uv[0] = CText::uv[1] = CText::uv[2] = CText::uv[3] = 0.0f;
#ifdef _DEBUG
		CText::uv[0] = 43 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 3;
		CText::uv[3] = CSIZE * 2;
#endif
	}
	else{
		CText::uv[0] = CSIZE * 0;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 6;
		CText::uv[3] = CSIZE * 5;
	}
	mTexture01.DrawImageSetColor(left, right, bottom, top, CText::uv[0], CText::uv[1], CText::uv[2], CText::uv[3], r, g, b, alpha);
}

void CText::SetDrawString(char s[], float left, float bottom, float size, float r, float g, float b, float alpha, int drawspeed){
	int j = 0;	//改行回数
	int k = 0;	//改行位置
	//文字列の長さを取得
	int DSMAX = 0;
	for (int i = 0; true; i++){
		if (s[i] == '\0'){
			DSMAX = drawspeed * i;
			break;
		}
	}

	for (int i = 0; s[i] != '\0'; i++){
		if (s[i - 1] == '\n'){
			k = i;
			j++;
		}
		if (drawspeed <= 0)
			CText::DrawText(s[i], left + (i - k)*size, left + (i - k)*size + size, bottom - (size * j), bottom + size - (size * j), r, g, b, alpha);
		else if (drawspeed > 0){
			if (ds >= drawspeed * (i + 1)){
				CText::DrawText(s[i], left + (i - k)*size, left + (i - k)*size + size, bottom - (size * j), bottom + size - (size * j), r, g, b, alpha);
			}
			else if (ds < drawspeed){
				CText::DrawText(s[i], left + (i - k)*size, left + (i - k)*size + size, bottom - (size * j), bottom + size - (size * j), r, g, b, 0.0f);
				if (soundtime > drawspeed){
					CSE::mSoundText.Play();
					soundtime = 0;
				}
			}
		}
	}
	if (drawspeed > 0 && ds < DSMAX){
		ds++;
		soundtime++;
	}
}

void CText::DrawString(char s[], float left, float bottom, float size, float alpha, int drawspeed){
	CText::SetDrawString(s, left, bottom, size, 1.0f, 1.0f, 1.0f, alpha, drawspeed);
}

void CText::DrawStringSetColor(char s[], float left, float bottom, float size, float r, float g, float b, float alpha, int drawspeed){
	CText::SetDrawString(s, left, bottom, size, r, g, b, alpha, drawspeed);
}

void CText::DrawTextW(wchar_t a, float left, float right, float bottom, float top,float r, float g, float b, float alpha){
	/*Unicode*/
	if (a >= L'ぁ' && a <= 0x30A0){	//U+3041 ~ U+30A0
		a = a - L'ぁ';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 4;
		CText::uv[3] = CSIZE * 3;
	}
	else if (a >= L'ァ' && a <= 0x30FF){	//U+30A1 ~ U+30FF
		a = a - L'ァ';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 5;
		CText::uv[3] = CSIZE * 4;
	}
	else if (a >= L'　' && a <= 0x301B){	//U+3000 ~ U+301B
		a = a - L'　';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 6;
		CText::uv[3] = CSIZE * 5;
	}
	else if (a == '～'){	//U+FF5E
		CText::uv[0] = 28 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 6;
		CText::uv[3] = CSIZE * 5;
	}
	else if (a >= L'←' && a <= L'↓'){	//U+2190 ~ U+2193
		a = a - L'←';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 7;
		CText::uv[3] = CSIZE * 6;
	}
	else if (a >= L'★' && a <= L'☆'){	//U+2605 ~ U+2606
		a = a - L'★';
		CText::uv[0] = 4 * CSIZE + a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 7;
		CText::uv[3] = CSIZE * 6;
	}
	else if (a == L'×'){				//U+00D7
		CText::uv[0] = 6 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 7;
		CText::uv[3] = CSIZE * 6;
	}
	else if (a >= L'Α' && a <= L'Ω'){	//U+0391 ~ U+03A9
		a = a - L'Α';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 9;
		CText::uv[3] = CSIZE * 8;
	}
	else if (a >= L'α' && a <= L'ω'){	//U+03B1 ~ U+03C9
		a = a - L'α';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 8;
		CText::uv[3] = CSIZE * 7;
	}
	else if (a >= L'１' && a <= L'９'){	//GamePad Key | U+FF11 ~ U+FF19
		a = a - L'１';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 10;
		CText::uv[3] = CSIZE * 9;
	}
	else if (a == L'０'){	//GamePad Key | U+FF10
		a = a - L'０';
		CText::uv[0] = CSIZE * 9;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 10;
		CText::uv[3] = CSIZE * 9;
	}
	else if (a >= L'Ａ' && a <= L'Ｚ'){	//GamePad Key | U+FF21 ~ U+FF3A
		a = a - L'Ａ';
		CText::uv[0] = CSIZE * 10 + a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 10;
		CText::uv[3] = CSIZE * 9;
	}
	else if (a >= 0xE000 && a <= 0xE099){	//U+E000 ~ U+E099	Nintendo フォント
		a = a - 0xE000;
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 1;
		CText::uv[3] = CSIZE * 0;
		mTexture02.DrawImageSetColor(left, right, bottom, top, CText::uv[0], CText::uv[1], CText::uv[2], CText::uv[3], r, g, b, alpha);
		return;
	}
	else if (a == L'中'){	//U+4E2D
		CText::uv[0] = 0 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'宝'){	//U+5B9D	アイテム フォント
		CText::uv[0] = 0 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 1;
		CText::uv[3] = CSIZE * 0;
		mTexture03.DrawImageSetColor(left, right, bottom, top, CText::uv[0], CText::uv[1], CText::uv[2], CText::uv[3], 1.0f, 1.0f, 1.0f, alpha);
		return;
	}
	else if (a == L'片'){	//U+77F3	アイテム フォント
		CText::uv[0] = 1 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 1;
		CText::uv[3] = CSIZE * 0;
		mTexture03.DrawImageSetColor(left, right, bottom, top, CText::uv[0], CText::uv[1], CText::uv[2], CText::uv[3], 1.0f, 1.0f, 1.0f, alpha);
		return;
	}
	else if (a == L'命'){	//U+547D	アイテム フォント
		CText::uv[0] = 2 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 1;
		CText::uv[3] = CSIZE * 0;
		mTexture03.DrawImageSetColor(left, right, bottom, top, CText::uv[0], CText::uv[1], CText::uv[2], CText::uv[3], 1.0f, 1.0f, 1.0f, alpha);
		return;
	}

	/*------ 人名など ------*/
	else if (a == L'前'){	//U+524D
		CText::uv[0] = 1 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'田'){	//U+7530
		CText::uv[0] = 2 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'拓'){	//U+62D3
		CText::uv[0] = 3 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'磨'){	//U+78E8
		CText::uv[0] = 4 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'長'){	//U+9577
		CText::uv[0] = 5 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'尾'){	//U+5C3E
		CText::uv[0] = 6 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'蓮'){	//U+84EE
		CText::uv[0] = 7 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'小'){	//U+5C0F
		CText::uv[0] = 8 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'見'){	//U+898B
		CText::uv[0] = 9 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'山'){	//U+5C71
		CText::uv[0] = 10 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'嶺'){	//U+5DBA
		CText::uv[0] = 11 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'治'){	//U+6CBB
		CText::uv[0] = 12 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'南'){	//U+5357
		CText::uv[0] = 13 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'木'){	//U+6728
		CText::uv[0] = 14 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'彩'){	//U+5F69
		CText::uv[0] = 15 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'希'){	//U+5E0C
		CText::uv[0] = 16 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'石'){	//U+77F3
		CText::uv[0] = 17 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'萌'){	//U+840C
		CText::uv[0] = 18 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'夏'){	//U+590F
		CText::uv[0] = 19 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'制'){	//U+5236
		CText::uv[0] = 20 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'作'){	//U+4F5C
		CText::uv[0] = 21 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'高' || a == 0x9AD9){	//U+9AD8	表示は、U+9AD9
		CText::uv[0] = 22 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'橋'){	//U+6A4B
		CText::uv[0] = 23 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'忍'){	//U+5FCD
		CText::uv[0] = 24 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'平'){	//U+5E73
		CText::uv[0] = 25 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'大'){	//U+5927
		CText::uv[0] = 26 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'井'){	//U+4E95
		CText::uv[0] = 27 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'上'){	//U+4E0A
		CText::uv[0] = 28 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'美'){	//U+7F8E
		CText::uv[0] = 29 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'先'){	//U+5148
		CText::uv[0] = 30 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'生'){	//U+751F
		CText::uv[0] = 31 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}

	else if (isupper(a)){	//U+0041 ~ U+005A
		a = a - L'A';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 2;
		CText::uv[3] = CSIZE * 1;
	}
	else if (islower(a)){	//U+0061 ~ U+007A
		a = a - L'a';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 1;
		CText::uv[3] = CSIZE * 0;
	}
	else if (a >= L' ' && a <= L'@'){	//U+0020 ~ U+0040
		a = a - L' ';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 3;
		CText::uv[3] = CSIZE * 2;
	}
	else if (a >= L'[' && a <= L'`'){	//U+005B ~ U+0060
		a = a - L'[';
		CText::uv[0] = 33 * CSIZE + a*CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 3;
		CText::uv[3] = CSIZE * 2;
	}
	else if (a >= L'{' && a <= L'~'){	//U+007B ~ U+007E
		a = a - L'{';
		CText::uv[0] = 39 * CSIZE + a*CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 3;
		CText::uv[3] = CSIZE * 2;
	}
	else if (a == L'\n'){	//U+000D, U+000A
		CText::uv[0] = CText::uv[1] = CText::uv[2] = CText::uv[3] = 0.0f;
#ifdef _DEBUG
		CText::uv[0] = 43 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 3;
		CText::uv[3] = CSIZE * 2;
#endif
	}
	else{
		CText::uv[0] = CSIZE * 0;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 6;
		CText::uv[3] = CSIZE * 5;
	}
	mTexture01.DrawImageSetColor(left, right, bottom, top, CText::uv[0], CText::uv[1], CText::uv[2], CText::uv[3], r, g, b, alpha);
}

void CText::SetDrawStringW(wchar_t s[], float left, float bottom, float size, float r, float g, float b, float alpha, int drawspeed){
	int j = 0;	//改行回数
	int k = 0;	//改行位置
	//文字列の長さを取得
	int DSMAX = 0;
	for (int i = 0; true; i++){
		if (s[i] == '\0'){
			DSMAX = drawspeed * i;
			break;
		}
	}

	for (int i = 0; s[i] != '\0'; i++){
		if (s[i - 1] == '\n'){
			k = i;
			j++;
		}
		if (drawspeed <= 0)
			CText::DrawTextW(s[i], left + (i - k)*size, left + (i - k)*size + size, bottom - (size * j), bottom + size - (size * j), r, g, b, alpha);
		else if (drawspeed > 0){
			if (ds >= drawspeed * (i + 1)){
				CText::DrawTextW(s[i], left + (i - k)*size, left + (i - k)*size + size, bottom - (size * j), bottom + size - (size * j), r, g, b, alpha);
				if (soundtime > drawspeed){
					CSE::mSoundText.Play();
					soundtime = 0;
				}
			}
			else if (ds < drawspeed){
				CText::DrawTextW(s[i], left + (i - k)*size, left + (i - k)*size + size, bottom - (size * j), bottom + size - (size * j), r, g, b, 0.0f);
			}
		}
		textlimit = true;
	}
	if (drawspeed > 0 && ds < DSMAX){
		ds++;
		soundtime++;
	}
}

void CText::DrawStringW(wchar_t s[], float left, float bottom, float size, float alpha, int drawspeed){
	CText::SetDrawStringW(s, left, bottom, size, 1.0f, 1.0f, 1.0f, alpha, drawspeed);
}

void CText::DrawStringWSetColor(wchar_t s[], float left, float bottom, float size, float r, float g, float b, float alpha, int drawspeed){
	CText::SetDrawStringW(s, left, bottom, size, r, g, b, alpha, drawspeed);
}

void CText::DrawSppedReset(){
	ds = 0;
}
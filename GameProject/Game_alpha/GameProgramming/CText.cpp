#include "CText.h"

#define CSIZE			64
#define CSIZE_ITEM		72
#define CSIZE_IMPACT	24

int CText::ds = 0;
float CText::uv[4];

CTexture CText::mTexture01;	//eLXg eNX`[ M+ 1m bold
CTexture CText::mTexture02;	//eLXg eNX`[ nintendoP Seurat
CTexture CText::mTexture03;	//eLXg eNX`[ ACe
CTexture CText::mTexture04;	//eLXg eNX`[ Impact Font
int CText::soundtime;		//¶\¦¹ Ôu
bool CText::textlimit;		//Ï ÁZÔ

void CText::Init(){
	mTexture01.Load(".\\Data\\Images\\Font\\Mplus_1m_bold-Unicode_064.tga");
	mTexture02.Load(".\\Data\\Images\\Font\\nintendoP_Seurat_064.tga");
	mTexture03.Load(".\\Data\\Images\\Font\\UI.tga");
	mTexture04.Load(".\\Data\\Images\\Font\\Impact.tga");
}

void CText::DrawText(char a, float left, float right, float bottom, float top, float r, float g, float b, float alpha){
	if (isupper(a)){						//U+0041 ~ U+005A
		a = a - 'A';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 2;
		CText::uv[3] = CSIZE * 1;
	}
	else if (islower(a)){					//U+0061 ~ U+007A
		a = a - 'a';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 1;
		CText::uv[3] = CSIZE * 0;
	}
	else if (a >= ' ' && a <= '@'){			//U+0020 ~ U+0040
		a = a - ' ';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 3;
		CText::uv[3] = CSIZE * 2;
	}
	else if (a >= '[' && a <= '`'){			//U+005B ~ U+0060
		a = a - '[';
		CText::uv[0] = 33 * CSIZE + a*CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 3;
		CText::uv[3] = CSIZE * 2;
	}
	else if (a >= '{' && a <= '~'){			//U+007B ~ U+007E
		a = a - '{';
		CText::uv[0] = 39 * CSIZE + a*CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 3;
		CText::uv[3] = CSIZE * 2;
	}
	else if (a == '\n'){					//U+000D, U+000A
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
	int j = 0;	//üsñ
	int k = 0;	//üsÊu
	//¶ñÌ·³ðæ¾
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

void CText::DrawTextW(wchar_t a, float left, float right, float bottom, float top,float r, float g, float b, float alpha, int font){
	/*Unicode*/
	if (a >= L'' && a <= 0x30A0){			//U+3041 ~ U+30A0
		a = a - L'';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 4;
		CText::uv[3] = CSIZE * 3;
	}
	else if (a >= L'@' && a <= 0x30FF){		//U+30A1 ~ U+30FF
		a = a - L'@';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 5;
		CText::uv[3] = CSIZE * 4;
	}
	else if (a >= L'@' && a <= 0x301B){		//U+3000 ~ U+301B
		a = a - L'@';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 6;
		CText::uv[3] = CSIZE * 5;
	}
	else if (a == '`'){						//U+FF5E
		CText::uv[0] = 28 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 6;
		CText::uv[3] = CSIZE * 5;
	}
	else if (a >= L'©' && a <= L'«'){		//U+2190 ~ U+2193
		a = a - L'©';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 7;
		CText::uv[3] = CSIZE * 6;
	}
	else if (a >= L'' && a <= L''){		//U+2605 ~ U+2606
		a = a - L'';
		CText::uv[0] = 4 * CSIZE + a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 7;
		CText::uv[3] = CSIZE * 6;
	}
	else if (a == L'~'){					//U+00D7
		if (font == 0){
			CText::uv[0] = 6 * CSIZE;
			CText::uv[1] = CText::uv[0] + CSIZE;
			CText::uv[2] = CSIZE * 7;
			CText::uv[3] = CSIZE * 6;
		}
		else if (font == 1){
			CText::uv[0] = 12 * CSIZE_IMPACT;
			CText::uv[1] = CText::uv[0] + CSIZE_IMPACT;
			CText::uv[2] = CSIZE_IMPACT * 1;
			CText::uv[3] = CSIZE_IMPACT * 0;
			mTexture04.DrawImageSetColor(left, right, bottom, top, CText::uv[0], CText::uv[1], CText::uv[2], CText::uv[3], 1.0f, 1.0f, 1.0f, alpha);
			return;
		}
	}
	else if (a >= L'£' && a <= L'¢'){		//U+25B2	ãü«, U+25B3	Eü«
		a = a - L'£';
		CText::uv[0] = 7 * CSIZE + a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 7;
		CText::uv[3] = CSIZE * 6;
	}
	else if (a >= L'¥' && a <= L'¤'){		//U+25BC	ºü«, U+25BD	¶ü«
		a = a - L'¥';
		CText::uv[0] = 9 * CSIZE + a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 7;
		CText::uv[3] = CSIZE * 6;
	}
	else if (a >= L'' && a <= L'¶'){		//U+0391 ~ U+03A9
		a = a - L'';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 9;
		CText::uv[3] = CSIZE * 8;
	}
	else if (a >= L'¿' && a <= L'Ö'){		//U+03B1 ~ U+03C9
		a = a - L'¿';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 8;
		CText::uv[3] = CSIZE * 7;
	}
	else if (a >= L'P' && a <= L'X'){		//GamePad Key | U+FF11 ~ U+FF19
		a = a - L'P';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 10;
		CText::uv[3] = CSIZE * 9;
	}
	else if (a == L'O'){					//GamePad Key | U+FF10
		a = a - L'O';
		CText::uv[0] = CSIZE * 9;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 10;
		CText::uv[3] = CSIZE * 9;
	}
	else if (a >= L'`' && a <= L'y'){		//GamePad Key | U+FF21 ~ U+FF3A
		a = a - L'`';
		CText::uv[0] = CSIZE * 10 + a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 10;
		CText::uv[3] = CSIZE * 9;
	}
	else if (a >= 0xE000 && a <= 0xE099){	//U+E000 ~ U+E099	Nintendo tHg
		a = a - 0xE000;
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 1;
		CText::uv[3] = CSIZE * 0;
		mTexture02.DrawImageSetColor(left, right, bottom, top, CText::uv[0], CText::uv[1], CText::uv[2], CText::uv[3], r, g, b, alpha);
		return;
	}
	else if (a == L''){					//U+4E2D
		CText::uv[0] = 0 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'I'){					//U+7D42
		CText::uv[0] = 1 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'¹'){					//U+4E86
		CText::uv[0] = 2 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'f'){					//U+7D20
		CText::uv[0] = 3 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'Þ'){					//U+6750
		CText::uv[0] = 4 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'Ø'){					//U+501F
		CText::uv[0] = 5 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'p'){					//U+7528
		CText::uv[0] = 6 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	/*------ ¤° ------*/
	else if (a == L''){					//U+9B54
		CText::uv[0] = 7 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'¤'){					//U+738B
		CText::uv[0] = 8 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L'°'){					//U+9B42
		CText::uv[0] = 9 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}

	/*------ í ------*/
	else if (a == L'í'){					//U+524A
		CText::uv[0] = 10 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}
	else if (a == L''){					//U+9664
		CText::uv[0] = 11 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}

	else if (a == L'S'){					//U+5168
		CText::uv[0] = 12 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 11;
		CText::uv[3] = CSIZE * 10;
	}

	else if (a == L'ó'){					//U+5B9D	ACe tHg
		CText::uv[0] = 0 * CSIZE_ITEM;
		CText::uv[1] = CText::uv[0] + CSIZE_ITEM;
		CText::uv[2] = CSIZE_ITEM * 1;
		CText::uv[3] = CSIZE_ITEM * 0;
		mTexture03.DrawImageSetColor(left, right, bottom, top, CText::uv[0], CText::uv[1], CText::uv[2], CText::uv[3], 1.0f, 1.0f, 1.0f, alpha);
		return;
	}
	else if (a == L'Ð'){					//U+7247	ACe tHg
		CText::uv[0] = 1 * CSIZE_ITEM;
		CText::uv[1] = CText::uv[0] + CSIZE_ITEM;
		CText::uv[2] = CSIZE_ITEM * 1;
		CText::uv[3] = CSIZE_ITEM * 0;
		mTexture03.DrawImageSetColor(left, right, bottom, top, CText::uv[0], CText::uv[1], CText::uv[2], CText::uv[3], 1.0f, 1.0f, 1.0f, alpha);
		return;
	}
	else if (a == L'½'){					//U+547D	ACe tHg
		CText::uv[0] = 2 * CSIZE_ITEM;
		CText::uv[1] = CText::uv[0] + CSIZE_ITEM;
		CText::uv[2] = CSIZE_ITEM * 1;
		CText::uv[3] = CSIZE_ITEM * 0;
		mTexture03.DrawImageSetColor(left, right, bottom, top, CText::uv[0], CText::uv[1], CText::uv[2], CText::uv[3], 1.0f, 1.0f, 1.0f, alpha);
		return;
	}

	/*------ l¼ÈÇ ------*/
	else if (a == L'O'){					//U+524D
		CText::uv[0] = 0 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'c'){					//U+7530
		CText::uv[0] = 1 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'ñ'){					//U+62D3
		CText::uv[0] = 2 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L''){					//U+78E8
		CText::uv[0] = 3 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'·'){					//U+9577
		CText::uv[0] = 4 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'ö'){					//U+5C3E
		CText::uv[0] = 5 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'@'){					//U+84EE
		CText::uv[0] = 6 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'¬'){					//U+5C0F
		CText::uv[0] = 7 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'©'){					//U+898B
		CText::uv[0] = 8 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'R'){					//U+5C71
		CText::uv[0] = 9 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'ä'){					//U+5DBA
		CText::uv[0] = 10 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'¡'){					//U+6CBB
		CText::uv[0] = 11 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'ì'){					//U+5357
		CText::uv[0] = 12 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'Ø'){					//U+6728
		CText::uv[0] = 13 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'Ê'){					//U+5F69
		CText::uv[0] = 14 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'ó'){					//U+5E0C
		CText::uv[0] = 15 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'Î'){					//U+77F3
		CText::uv[0] = 16 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'G'){					//U+840C
		CText::uv[0] = 17 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'Ä'){					//U+590F
		CText::uv[0] = 18 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'§'){					//U+5236
		CText::uv[0] = 19 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'ì'){					//U+4F5C
		CText::uv[0] = 20 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'' || a == 0x9AD9){		//U+9AD8	\¦ÍAU+9AD9
		CText::uv[0] = 21 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'´'){					//U+6A4B
		CText::uv[0] = 22 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'E'){					//U+5FCD
		CText::uv[0] = 23 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'½'){					//U+5E73
		CText::uv[0] = 24 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'å'){					//U+5927
		CText::uv[0] = 25 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'ä'){					//U+4E95
		CText::uv[0] = 26 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'ã'){					//U+4E0A
		CText::uv[0] = 27 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'ü'){					//U+7F8E
		CText::uv[0] = 28 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'³'){					//U+6559
		CText::uv[0] = 29 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}
	else if (a == L'õ'){					//U+54E1
		CText::uv[0] = 30 * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 12;
		CText::uv[3] = CSIZE * 11;
	}

	else if (isupper(a)){					//U+0041 ~ U+005A
		a = a - L'A';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 2;
		CText::uv[3] = CSIZE * 1;
	}
	else if (islower(a)){					//U+0061 ~ U+007A
		a = a - L'a';
		CText::uv[0] = a * CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 1;
		CText::uv[3] = CSIZE * 0;
	}
	else if (a >= L' ' && a <= L'@'){		//U+0020 ~ U+0040
		if (font == 0){
			a = a - L' ';
			CText::uv[0] = a * CSIZE;
			CText::uv[1] = CText::uv[0] + CSIZE;
			CText::uv[2] = CSIZE * 3;
			CText::uv[3] = CSIZE * 2;
		}
		else if (font == 1){
			if (a == L' '){
				CText::uv[0] = 0 * CSIZE;
				CText::uv[1] = CText::uv[0] + CSIZE;
				CText::uv[2] = CSIZE * 3;
				CText::uv[3] = CSIZE * 2;
			}
			else if (a == L'.'){
				CText::uv[0] = 0 * CSIZE_IMPACT;
				CText::uv[1] = CText::uv[0] + CSIZE_IMPACT;
				CText::uv[2] = CSIZE_IMPACT * 1;
				CText::uv[3] = CSIZE_IMPACT * 0;
				mTexture04.DrawImageSetColor(left, right, bottom, top, CText::uv[0], CText::uv[1], CText::uv[2], CText::uv[3], 1.0f, 1.0f, 1.0f, alpha);
				return;
			}
			else if (a >= L'0' && a <= L':'){
				a = a - L'0';
				CText::uv[0] = CSIZE_IMPACT * 1 + a * CSIZE_IMPACT;
				CText::uv[1] = CText::uv[0] + CSIZE_IMPACT;
				CText::uv[2] = CSIZE_IMPACT * 1;
				CText::uv[3] = CSIZE_IMPACT * 0;
				mTexture04.DrawImageSetColor(left, right, bottom, top, CText::uv[0], CText::uv[1], CText::uv[2], CText::uv[3], 1.0f, 1.0f, 1.0f, alpha);
				return;
			}
		}
	}
	else if (a >= L'[' && a <= L'`'){		//U+005B ~ U+0060
		a = a - L'[';
		CText::uv[0] = 33 * CSIZE + a*CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 3;
		CText::uv[3] = CSIZE * 2;
	}
	else if (a >= L'{' && a <= L'~'){		//U+007B ~ U+007E
		a = a - L'{';
		CText::uv[0] = 39 * CSIZE + a*CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = CSIZE * 3;
		CText::uv[3] = CSIZE * 2;
	}
	else if (a == L'\n'){					//U+000D, U+000A
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

void CText::SetDrawStringW(wchar_t s[], float left, float bottom, float size, float r, float g, float b, float alpha, int drawspeed, int font = 0){
	int j = 0;	//üsñ
	int k = 0;	//üsÊu
	//¶ñÌ·³ðæ¾
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
			CText::DrawTextW(s[i], left + (i - k)*size, left + (i - k)*size + size, bottom - (size * j), bottom + size - (size * j), r, g, b, alpha, font);
		else if (drawspeed > 0){
			if (ds >= drawspeed * (i + 1)){
				CText::DrawTextW(s[i], left + (i - k)*size, left + (i - k)*size + size, bottom - (size * j), bottom + size - (size * j), r, g, b, alpha, font);
				if (soundtime > drawspeed){
					CSE::mSoundText.Play();
					soundtime = 0;
				}
			}
			else if (ds < drawspeed){
				CText::DrawTextW(s[i], left + (i - k)*size, left + (i - k)*size + size, bottom - (size * j), bottom + size - (size * j), r, g, b, 0.0f, font);
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

void CText::DrawStringImpact(wchar_t s[], float left, float bottom, float size, float alpha, int drawspeed){
	CText::SetDrawStringW(s, left, bottom, size, 1.0f, 1.0f, 1.0f, alpha, drawspeed, 1);
}

void CText::DrawSppedReset(){
	ds = 0;
}
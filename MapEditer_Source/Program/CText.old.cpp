#include "CText.h"

#define CSIZE 8

int CText::ds = 0;
int dsmax;
float CText::uv[4];

CTexture CText::mTexture;	//テキスト テクスチャー

void CText::Init(){
	mTexture.Load(".\\Data\\Images\\PokeFont.tga");
}

void CText::DrawText(char a, float left, float right, float bottom, float top, float r, float g, float b, float alpha){
	if (isupper(a)){
		a = a - 'A';
		CText::uv[0] = a*CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 32;
		CText::uv[3] = 16;
	}
	else if (islower(a)){
		a = a - 'a';
		CText::uv[0] = a*CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 16;
		CText::uv[3] = 0;
	}
	else if (isdigit(a)){
		a = a - '0';
		CText::uv[0] = a*CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	else if (a == '('){	//半角 括弧 | 全角 括弧は 使用不可
		CText::uv[0] = 720;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 80;
		CText::uv[3] = 64;
	}
	else if (a == ')'){	//半角 括弧 | 全角 括弧は 使用不可
		CText::uv[0] = 728;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 80;
		CText::uv[3] = 64;
	}
	else if (a == '['){
		CText::uv[0] = 704;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 80;
		CText::uv[3] = 64;
	}
	else if (a == ']'){
		CText::uv[0] = 712;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 80;
		CText::uv[3] = 64;
	}
	else if (a == '!'){	//半角 感嘆符
		CText::uv[0] = 208;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 16;
		CText::uv[3] = 0;
	}
	else if (a == '?'){	//半角 疑問符
		CText::uv[0] = 216;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 16;
		CText::uv[3] = 0;
	}
	else if (a == '-'){	//ハイフン
		CText::uv[0] = 664;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 64;
		CText::uv[3] = 48;
	}
	else if (a == '.'){
		CText::uv[0] = 80;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	else if (a == ','){
		CText::uv[0] = 88;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	else if (a == '/'){	//スラッシュ
		CText::uv[0] = 96;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	else if (a == '\\'){	//バックスラッシュ
		CText::uv[0] = 104;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	else if (a == '+'){
		CText::uv[0] = 112;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	else if (a == '%'){
		CText::uv[0] = 728;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 64;
		CText::uv[3] = 48;
	}
	else if (a == '_'){
		CText::uv[0] = 736;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 64;
		CText::uv[3] = 48;
	}
	else if (a == ' '){	//半角 スペース | 全角 スペースは使用不可
		/*空白記号 表示*/
		//CText::uv[0] = 120;
		//CText::uv[1] = CText::uv[0] + CSIZE;
		//CText::uv[2] = 48;
		//CText::uv[3] = 32;
		/*空白記号 非表示*/
		CText::uv[0] = CText::uv[1] = CText::uv[2] = CText::uv[3] = 0;
	}
	else if (a == '\n'){	//改行
		/*空白記号 表示*/
		CText::uv[0] = 128;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
		/*改行記号 非表示*/
		//CText::uv[0] = CText::uv[1] = CText::uv[2] = CText::uv[3] = 0;
	}
	else{	//未収録文字
		CText::uv[0] = 136;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	mTexture.DrawImageSetColor(left, right, bottom, top, CText::uv[0], CText::uv[1], CText::uv[2], CText::uv[3], r, g, b, alpha);
}

void CText::SetDrawString(char s[], float left, float bottom, float size, float r, float g, float b, float alpha, int drawspeed){
	int j = 0;	//改行回数
	int k = 0;	//改行位置
	dsmax = 256 * drawspeed;
	for (int i = 0; s[i] != '\0'; i++){
		if (s[i - 1] == '\n'){
			k = i;
			j++;
		}
		if (drawspeed <= 0)
			CText::DrawText(s[i], left + (i - k)*size, left + (i - k)*size + size, bottom - (size * 2 * j), bottom + size * 2 - (size * 2 * j), r, g, b, alpha);
		else if (drawspeed > 0){
			if (ds >= drawspeed * (i + 1)){
				CText::DrawText(s[i], left + (i - k)*size, left + (i - k)*size + size, bottom - (size * 2 * j), bottom + size * 2 - (size * 2 * j), r, g, b, alpha);
			}
			else if (ds < drawspeed)
				CText::DrawText(s[i], left + (i - k)*size, left + (i - k)*size + size, bottom - (size * 2 * j), bottom + size * 2 - (size * 2 * j), r, g, b, 0.0f);
		}
	}
	if (drawspeed > 0 && ds < dsmax)
		ds++;
}

void CText::DrawString(char s[], float left, float bottom, float size, float alpha, int drawspeed){
	CText::SetDrawString(s, left, bottom, size, 1.0f, 1.0f, 1.0f, alpha, drawspeed);
}

void CText::DrawStringSetColor(char s[], float left, float bottom, float size, float r, float g, float b, float alpha, int drawspeed){
	CText::SetDrawString(s, left, bottom, size, r, g, b, alpha, drawspeed);
}

void CText::DrawTextW(wchar_t a, float left, float right, float bottom, float top,float r, float g, float b, float alpha){
	if (a >= L'ぁ' && a <= L'ん'){
		a = a - L'ぁ';
		CText::uv[0] = a*CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 64;
		CText::uv[3] = 48;
	}
	else if (a >= L'ァ' && a <= L'ヶ'){
		a = a - L'ァ';
		CText::uv[0] = a*CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 80;
		CText::uv[3] = 64;
	}
	else if (a == L'ー' || a == L'-'){	//長音記号, ハイフン
		CText::uv[0] = 664;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 64;
		CText::uv[3] = 48;
	}
	else if (a == L'。'){
		CText::uv[0] = 672;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 64;
		CText::uv[3] = 48;
	}
	else if (a == L'、'){
		CText::uv[0] = 680;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 64;
		CText::uv[3] = 48;
	}
	else if (a == L'「' || a == L'」'){
		a = a - L'「';
		CText::uv[0] = 688 + a*CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 80;
		CText::uv[3] = 64;
	}
	else if (a == L'！'){	//全角 感嘆符
		CText::uv[0] = 208;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 32;
		CText::uv[3] = 16;
	}
	else if (a == L'？'){	//全角 疑問符
		CText::uv[0] = 216;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 32;
		CText::uv[3] = 16;
	}
	else if (a == L'…'){	//3点リーダー
		CText::uv[0] = 688;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 64;
		CText::uv[3] = 48;
	}
	else if (a == L'→'){	//右 矢印
		CText::uv[0] = 144;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	else if (a == L'←'){	//左 矢印
		CText::uv[0] = 152;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	else if (a == L'↑'){	//上 矢印
		CText::uv[0] = 160;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	else if (a == L'↓'){	//下 矢印
		CText::uv[0] = 168;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	else if (a == L'円'){
		CText::uv[0] = 704;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 64;
		CText::uv[3] = 48;
	}
	else if (a == L'中'){
		CText::uv[0] = 64;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 96;
		CText::uv[3] = 80;
	}
	else if (a == L'銅'){
		CText::uv[0] = 0;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 96;
		CText::uv[3] = 80;
	}
	else if (a == L'銀'){
		CText::uv[0] = 8;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 96;
		CText::uv[3] = 80;
	}
	else if (a == L'金'){
		CText::uv[0] = 16;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 96;
		CText::uv[3] = 80;
	}
	else if (a == L'白'){
		CText::uv[0] = 24;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 96;
		CText::uv[3] = 80;
	}
	else if (a == L'北'){
		CText::uv[0] = 32;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 96;
		CText::uv[3] = 80;
	}
	else if (a == L'東'){
		CText::uv[0] = 40;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 96;
		CText::uv[3] = 80;
	}
	else if (a == L'南'){
		CText::uv[0] = 48;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 96;
		CText::uv[3] = 80;
	}
	else if (a == L'西'){
		CText::uv[0] = 56;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 96;
		CText::uv[3] = 80;
	}
	else if (a == L'入'){
		CText::uv[0] = 72;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 96;
		CText::uv[3] = 80;
	}
	else if (a == L'切'){
		CText::uv[0] = 80;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 96;
		CText::uv[3] = 80;
	}
	else if (a == L'○'){	//○ 全角 丸
		CText::uv[0] = 712;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 64;
		CText::uv[3] = 48;
	}
	else if (a == L'×'){	//× 全角 乗算記号
		CText::uv[0] = 720;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 64;
		CText::uv[3] = 48;
	}
	else if (isupper(a)){
		a = a - L'A';
		CText::uv[0] = a*CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 32;
		CText::uv[3] = 16;
	}
	else if (islower(a)){
		a = a - L'a';
		CText::uv[0] = a*CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 16;
		CText::uv[3] = 0;
	}
	else if (isdigit(a)){
		a = a - L'0';
		CText::uv[0] = a*CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	else if (a == L'('){	//半角 括弧 | 全角 括弧は 使用不可
		CText::uv[0] = 720;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 80;
		CText::uv[3] = 64;
	}
	else if (a == L')'){	//半角 括弧 | 全角 括弧は 使用不可
		CText::uv[0] = 728;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 80;
		CText::uv[3] = 64;
	}
	else if (a == L'['){
		CText::uv[0] = 704;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 80;
		CText::uv[3] = 64;
	}
	else if (a == L']'){
		CText::uv[0] = 712;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 80;
		CText::uv[3] = 64;
	}
	else if (a == L'!'){	//半角 感嘆符
		CText::uv[0] = 208;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 16;
		CText::uv[3] = 0;
	}
	else if (a == L'?'){	//半角 疑問符
		CText::uv[0] = 216;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 16;
		CText::uv[3] = 0;
	}
	else if (a == L'ー' || a == L'-'){	//長音記号, ハイフン
		CText::uv[0] = 664;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 64;
		CText::uv[3] = 48;
	}
	else if (a == L'.'){
		CText::uv[0] = 80;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	else if (a == L','){
		CText::uv[0] = 88;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	else if (a == L'/'){	//スラッシュ
		CText::uv[0] = 96;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	else if (a == L'\\'){	//バックスラッシュ
		CText::uv[0] = 104;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	else if (a == L'+'){
		CText::uv[0] = 112;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	else if (a == L'%'){
		CText::uv[0] = 728;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 64;
		CText::uv[3] = 48;
	}
	else if (a == L'_'){
		CText::uv[0] = 736;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 64;
		CText::uv[3] = 48;
	}
	else if (a == L' '){	//半角 スペース | 全角 スペースは使用不可 | 表示は 全角スペース
		/*空白記号 表示*/
		//CText::uv[0] = 120;
		//CText::uv[1] = CText::uv[0] + CSIZE;
		//CText::uv[2] = 48;
		//CText::uv[3] = 32;
		/*空白記号 非表示*/
		CText::uv[0] = CText::uv[1] = CText::uv[2] = CText::uv[3] = 0;
	}
	else if (a == L'\n'){	//改行
		/*改行記号 表示*/
		//CText::uv[0] = 128;
		//CText::uv[1] = CText::uv[0] + CSIZE;
		//CText::uv[2] = 48;
		//CText::uv[3] = 32;
		/*改行記号 非表示*/
		CText::uv[0] = CText::uv[1] = CText::uv[2] = CText::uv[3] = 0;
	}
	else{	//未収録文字
		CText::uv[0] = 136;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	mTexture.DrawImageSetColor(left, right, bottom, top, CText::uv[0], CText::uv[1], CText::uv[2], CText::uv[3], r, g, b, alpha);
}

void CText::SetDrawStringW(wchar_t s[], float left, float bottom, float size, float r, float g, float b, float alpha, int drawspeed){
	int j = 0;	//改行回数
	int k = 0;	//改行位置
	dsmax = 256 * drawspeed;
	for (int i = 0; s[i] != '\0'; i++){
		if (s[i - 1] == '\n'){
			k = i;
			j++;
		}
		if (drawspeed <= 0)
			CText::DrawTextW(s[i], left + (i - k)*size, left + (i - k)*size + size, bottom - (size * 2 * j), bottom + size * 2 - (size * 2 * j), r, g, b, alpha);
		else if (drawspeed > 0){
			if (ds >= drawspeed * (i + 1)){
				CText::DrawTextW(s[i], left + (i - k)*size, left + (i - k)*size + size, bottom - (size * 2 * j), bottom + size * 2 - (size * 2 * j), r, g, b, alpha);
			}
			else if (ds < drawspeed)
				CText::DrawTextW(s[i], left + (i - k)*size, left + (i - k)*size + size, bottom - (size * 2 * j), bottom + size * 2 - (size * 2 * j), r, g, b, 0.0f);
		}
	}
	if (drawspeed > 0 && ds < dsmax)
		ds++;
}

void CText::DrawStringW(wchar_t s[], float left, float bottom, float size, float alpha, int drawspeed){
	CText::SetDrawStringW(s, left, bottom, size, 1.0f, 1.0f, 1.0f, alpha, drawspeed);
}

void CText::DrawStringWSetColor(wchar_t s[], float left, float bottom, float size, float r, float g, float b, float alpha, int drawspeed){
	CText::SetDrawStringW(s, left, bottom, size, r, g, b, alpha, drawspeed);;
}
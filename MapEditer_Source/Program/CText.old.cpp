#include "CText.h"

#define CSIZE 8

int CText::ds = 0;
int dsmax;
float CText::uv[4];

CTexture CText::mTexture;	//�e�L�X�g �e�N�X�`���[

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
	else if (a == '('){	//���p ���� | �S�p ���ʂ� �g�p�s��
		CText::uv[0] = 720;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 80;
		CText::uv[3] = 64;
	}
	else if (a == ')'){	//���p ���� | �S�p ���ʂ� �g�p�s��
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
	else if (a == '!'){	//���p ���Q��
		CText::uv[0] = 208;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 16;
		CText::uv[3] = 0;
	}
	else if (a == '?'){	//���p �^�╄
		CText::uv[0] = 216;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 16;
		CText::uv[3] = 0;
	}
	else if (a == '-'){	//�n�C�t��
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
	else if (a == '/'){	//�X���b�V��
		CText::uv[0] = 96;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	else if (a == '\\'){	//�o�b�N�X���b�V��
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
	else if (a == ' '){	//���p �X�y�[�X | �S�p �X�y�[�X�͎g�p�s��
		/*�󔒋L�� �\��*/
		//CText::uv[0] = 120;
		//CText::uv[1] = CText::uv[0] + CSIZE;
		//CText::uv[2] = 48;
		//CText::uv[3] = 32;
		/*�󔒋L�� ��\��*/
		CText::uv[0] = CText::uv[1] = CText::uv[2] = CText::uv[3] = 0;
	}
	else if (a == '\n'){	//���s
		/*�󔒋L�� �\��*/
		CText::uv[0] = 128;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
		/*���s�L�� ��\��*/
		//CText::uv[0] = CText::uv[1] = CText::uv[2] = CText::uv[3] = 0;
	}
	else{	//�����^����
		CText::uv[0] = 136;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	mTexture.DrawImageSetColor(left, right, bottom, top, CText::uv[0], CText::uv[1], CText::uv[2], CText::uv[3], r, g, b, alpha);
}

void CText::SetDrawString(char s[], float left, float bottom, float size, float r, float g, float b, float alpha, int drawspeed){
	int j = 0;	//���s��
	int k = 0;	//���s�ʒu
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
	if (a >= L'��' && a <= L'��'){
		a = a - L'��';
		CText::uv[0] = a*CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 64;
		CText::uv[3] = 48;
	}
	else if (a >= L'�@' && a <= L'��'){
		a = a - L'�@';
		CText::uv[0] = a*CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 80;
		CText::uv[3] = 64;
	}
	else if (a == L'�[' || a == L'-'){	//�����L��, �n�C�t��
		CText::uv[0] = 664;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 64;
		CText::uv[3] = 48;
	}
	else if (a == L'�B'){
		CText::uv[0] = 672;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 64;
		CText::uv[3] = 48;
	}
	else if (a == L'�A'){
		CText::uv[0] = 680;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 64;
		CText::uv[3] = 48;
	}
	else if (a == L'�u' || a == L'�v'){
		a = a - L'�u';
		CText::uv[0] = 688 + a*CSIZE;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 80;
		CText::uv[3] = 64;
	}
	else if (a == L'�I'){	//�S�p ���Q��
		CText::uv[0] = 208;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 32;
		CText::uv[3] = 16;
	}
	else if (a == L'�H'){	//�S�p �^�╄
		CText::uv[0] = 216;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 32;
		CText::uv[3] = 16;
	}
	else if (a == L'�c'){	//3�_���[�_�[
		CText::uv[0] = 688;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 64;
		CText::uv[3] = 48;
	}
	else if (a == L'��'){	//�E ���
		CText::uv[0] = 144;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	else if (a == L'��'){	//�� ���
		CText::uv[0] = 152;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	else if (a == L'��'){	//�� ���
		CText::uv[0] = 160;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	else if (a == L'��'){	//�� ���
		CText::uv[0] = 168;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	else if (a == L'�~'){
		CText::uv[0] = 704;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 64;
		CText::uv[3] = 48;
	}
	else if (a == L'��'){
		CText::uv[0] = 64;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 96;
		CText::uv[3] = 80;
	}
	else if (a == L'��'){
		CText::uv[0] = 0;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 96;
		CText::uv[3] = 80;
	}
	else if (a == L'��'){
		CText::uv[0] = 8;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 96;
		CText::uv[3] = 80;
	}
	else if (a == L'��'){
		CText::uv[0] = 16;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 96;
		CText::uv[3] = 80;
	}
	else if (a == L'��'){
		CText::uv[0] = 24;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 96;
		CText::uv[3] = 80;
	}
	else if (a == L'�k'){
		CText::uv[0] = 32;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 96;
		CText::uv[3] = 80;
	}
	else if (a == L'��'){
		CText::uv[0] = 40;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 96;
		CText::uv[3] = 80;
	}
	else if (a == L'��'){
		CText::uv[0] = 48;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 96;
		CText::uv[3] = 80;
	}
	else if (a == L'��'){
		CText::uv[0] = 56;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 96;
		CText::uv[3] = 80;
	}
	else if (a == L'��'){
		CText::uv[0] = 72;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 96;
		CText::uv[3] = 80;
	}
	else if (a == L'��'){
		CText::uv[0] = 80;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 96;
		CText::uv[3] = 80;
	}
	else if (a == L'��'){	//�� �S�p ��
		CText::uv[0] = 712;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 64;
		CText::uv[3] = 48;
	}
	else if (a == L'�~'){	//�~ �S�p ��Z�L��
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
	else if (a == L'('){	//���p ���� | �S�p ���ʂ� �g�p�s��
		CText::uv[0] = 720;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 80;
		CText::uv[3] = 64;
	}
	else if (a == L')'){	//���p ���� | �S�p ���ʂ� �g�p�s��
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
	else if (a == L'!'){	//���p ���Q��
		CText::uv[0] = 208;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 16;
		CText::uv[3] = 0;
	}
	else if (a == L'?'){	//���p �^�╄
		CText::uv[0] = 216;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 16;
		CText::uv[3] = 0;
	}
	else if (a == L'�[' || a == L'-'){	//�����L��, �n�C�t��
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
	else if (a == L'/'){	//�X���b�V��
		CText::uv[0] = 96;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	else if (a == L'\\'){	//�o�b�N�X���b�V��
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
	else if (a == L' '){	//���p �X�y�[�X | �S�p �X�y�[�X�͎g�p�s�� | �\���� �S�p�X�y�[�X
		/*�󔒋L�� �\��*/
		//CText::uv[0] = 120;
		//CText::uv[1] = CText::uv[0] + CSIZE;
		//CText::uv[2] = 48;
		//CText::uv[3] = 32;
		/*�󔒋L�� ��\��*/
		CText::uv[0] = CText::uv[1] = CText::uv[2] = CText::uv[3] = 0;
	}
	else if (a == L'\n'){	//���s
		/*���s�L�� �\��*/
		//CText::uv[0] = 128;
		//CText::uv[1] = CText::uv[0] + CSIZE;
		//CText::uv[2] = 48;
		//CText::uv[3] = 32;
		/*���s�L�� ��\��*/
		CText::uv[0] = CText::uv[1] = CText::uv[2] = CText::uv[3] = 0;
	}
	else{	//�����^����
		CText::uv[0] = 136;
		CText::uv[1] = CText::uv[0] + CSIZE;
		CText::uv[2] = 48;
		CText::uv[3] = 32;
	}
	mTexture.DrawImageSetColor(left, right, bottom, top, CText::uv[0], CText::uv[1], CText::uv[2], CText::uv[3], r, g, b, alpha);
}

void CText::SetDrawStringW(wchar_t s[], float left, float bottom, float size, float r, float g, float b, float alpha, int drawspeed){
	int j = 0;	//���s��
	int k = 0;	//���s�ʒu
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
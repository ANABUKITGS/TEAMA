#include "CText.h"

//�e�N�X�`���̃|�C���^
CTexture CText::mFont;
/*29
DrawChar
������`�悷��
ch:�����f�[�^ x:X���W y:Y���W w:�� h:����
*/
void CText::DrawChar(char ch, int x, int y, int w, int h) {
	int u = ch % 16 * 16;
	int v = (ch - ' ') / 16 * 16;
	mFont.DrawImage(x - w, x + w, y - h, y + h, u, u + 15, v + 15, v);
}
//30
/*
DrawString
������`�悷��
s:������f�[�^ x:X���W y:Y���W w:�� h:����
*/
void CText::DrawString(char *s, int x, int y, int w, int h) {
	//1�������`�悵�܂�
	for (int i = 0; s[i] != '\0'; i++) {
		//������`�悷��
		DrawChar(s[i], x, y, w, h);
		//�E�ֈړ�
		x += w * 2;
	}
}

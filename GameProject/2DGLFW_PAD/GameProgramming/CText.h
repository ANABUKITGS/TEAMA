#include "CTexture.h"

/*
�����̕`��
*/
class CText {
public:
	//�e�N�X�`���̎w��
	static CTexture mFont;
	//29 �����̕`��
	static void DrawChar(char ch, int x, int y, int w, int h);
	//30
	static void DrawString(char *s, int x, int y, int w, int h);
};

#ifndef CTEXTURE_H
#define CTEXTURE_H
#include "glut.h"

#define TEX_FULLSCREEN -640, 640, -360, 360

/*
TGAファイルのヘッダフォーマット
*/
struct STgaheader {
	unsigned char	dummy1[12];
	unsigned short	width;	//幅
	unsigned short	height;	//高さ
	unsigned char	depth;	//ビットの深さ
	unsigned char	dummy2;
};
/*
テクスチャークラス
*/
class CTexture {
public:
	//テクスチャID
	GLuint id;
	//TGAファイルのヘッダ情報
	STgaheader header;
	/*
	デフォルトコンストラクタ
	*/
	CTexture() : id(0) {}
	/*
	デストラクタ（このインスタンスが破棄されるときに実行される）
	*/
	~CTexture() {
		//テクスチャデータがあれば削除する
		if (id != 0) {
			//テクスチャデータの削除
			glDeleteTextures(1, &id);
			id = 0;
		}
	}

	/*
	画像ファイルの読み込み（テクスチャファイルの読み込み）
	*/
	void Load(const char* filename);

	void SetDrawImage(int left, int right, int bottom, int top, float fLeft, float tRight, float tBottom, float tTop, float r, float g, float b, float alpha);

	void DrawImage(int left, int right, int bottom, int top, float fLeft, float tRight, float tBottom, float tTop, float alpha);

	void DrawImageSetColor(int left, int right, int bottom, int top, float fLeft, float tRight, float tBottom, float tTop, float r, float g, float b, float alpha);
};

#endif

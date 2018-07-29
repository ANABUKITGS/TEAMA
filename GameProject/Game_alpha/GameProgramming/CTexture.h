#ifndef CTEXTURE_H
#define CTEXTURE_H
#include "glut.h"

#define TEX_FULLSCREEN -640, 640, -360, 360

/*
TGA�t�@�C���̃w�b�_�t�H�[�}�b�g
*/
struct STgaheader {
	unsigned char	dummy1[12];
	unsigned short	width;	//��
	unsigned short	height;	//����
	unsigned char	depth;	//�r�b�g�̐[��
	unsigned char	dummy2;
};
/*
�e�N�X�`���[�N���X
*/
class CTexture {
public:
	//�e�N�X�`��ID
	GLuint id;
	//TGA�t�@�C���̃w�b�_���
	STgaheader header;
	/*
	�f�t�H���g�R���X�g���N�^
	*/
	CTexture() : id(0) {}
	/*
	�f�X�g���N�^�i���̃C���X�^���X���j�������Ƃ��Ɏ��s�����j
	*/
	~CTexture() {
		//�e�N�X�`���f�[�^������΍폜����
		if (id != 0) {
			//�e�N�X�`���f�[�^�̍폜
			glDeleteTextures(1, &id);
			id = 0;
		}
	}

	/*
	�摜�t�@�C���̓ǂݍ��݁i�e�N�X�`���t�@�C���̓ǂݍ��݁j
	*/
	void Load(const char* filename);

	void SetDrawImage(int left, int right, int bottom, int top, float fLeft, float tRight, float tBottom, float tTop, float r, float g, float b, float alpha);

	void DrawImage(int left, int right, int bottom, int top, float fLeft, float tRight, float tBottom, float tTop, float alpha);

	void DrawImageSetColor(int left, int right, int bottom, int top, float fLeft, float tRight, float tBottom, float tTop, float r, float g, float b, float alpha);
};

#endif

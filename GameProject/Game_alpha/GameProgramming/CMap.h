#ifndef CEDITER_H
#define CEDITER_H
#include <Windows.h>
#include "CKey.h"
#include "CRectangle.h"
#include "CText.h"
#include "CFileIO.h"
#include "CCharcter.h"

//class CRectangle;

#define CELLSIZE		64		//�}�X �T�C�Y
#define MAP_SIZEY		11		//�}�b�v ��� Y
#define MAP_SIZEX		256		//�}�b�v ��� X
#define CURSOR_NUM		-1		//�J�[�\��
#define SCROLL_SPEED	2.0f	//�X�N���[���X�s�[�h

#define WINDOW_SIZE_W 1280
#define WINDOW_SIZE_H 720

#define POS(Y,X) CVector2(X * CELLSIZE, Y * -CELLSIZE + WINDOW_SIZE_H)

#define EDT_RIGHT		0x01
#define EDT_LEFT		0x04
#define EDT_TOP			0x02
#define EDT_BOTTOM		0x08


class CPauseMenu{
private:
	enum EPAUSEMENU_NUM{
		EBACK = 1,
		ETITLE,
		ESIZE,
	};
	int cursor_num = EBACK;
	wchar_t cursor_buf[32];

public:
	bool pauseflag;									//�|�[�Y���j���[

	void Update();
	void Render();
};

class CEditer : public CPauseMenu{
private:
	int editmap_cursor[MAP_SIZEY][MAP_SIZEX];		//�}�b�v �J�[�\��
	int cursor_posX;								//�J�[�\�� �ꏊ X
	int cursor_posY;								//�J�[�\�� �ꏊ Y
	int setcell;									//�}�b�v �z�u���e
	unsigned int cursor_anime;						//�J�[�\�� �A�j���[�V����
	bool guideIO;									//�K�C�h ON OFF
	bool prtscrIO;									//�X�N���[���V���b�g�p? �J�[�\������\��
	CRectangle editmap_rect[MAP_SIZEY][MAP_SIZEX];	//�}�b�v �`��

public:
	int editmap[MAP_SIZEY][MAP_SIZEX];				//�}�b�v
	CTexture mTexUI;								//UI �e�N�X�`���[
	CTexture mTexSetCell;							//UI �I�u�W�F�N�g

	void Init();
	void Update();
	void Render();
	static void MakeTaskList(int *gamemap);
};

class CGame : public CEditer{
public:
	int gamemap[MAP_SIZEY][MAP_SIZEX];				//�}�b�v
	float mapscrollnum;								//�X�N���[��������, ���X�^�[�g�ʒu�܂ł̃X�N���[����
	bool mapsctoll_flag;							//�X�N���[�� �J�n
	CRectangle gamemap_rect[MAP_SIZEY][MAP_SIZEX];	//�}�b�v �`��

	void Init();
	void Update();
	void Scroll();
	void Render();
};
#endif
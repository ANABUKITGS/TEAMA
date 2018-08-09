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

#define EDT_RIGHT 0x01
#define EDT_LEFT 0x04
#define EDT_TOP 0x02
#define EDT_BOTTOM 0x08


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
	//�}�b�v �z�� ���g
	//enum ECELLNUM{
	//	/*------ �}�b�v �`�� �Ȃ� ------*/
	//	ENONE = 1,			//�� | 0�͎g�p�֎~
	//	EGROUND,			//�����
	//	EUNDER,				//�����甲���鑫��
	//	EBELT,				//�x���g�R���x�A
	//	EJEWELRY,			//���
	//	ECHIKUWA,			//������u���b�N
	//	ESWITCH_GROUND1,	//�X�C�b�`�� �؂�ւ�鑫�� 1
	//	ESWITCH_GROUND2,	//�X�C�b�`�� �؂�ւ�鑫�� 2
	//	ESWITCH,			//�X�C�b�`�� �؂�ւ�鑫��� �X�C�b�`
	//	ETORABASAMI,		//�g���o�T�~

	//	/*------ �L�����N�^�[ �Ȃ� ------*/
	//	ECHECKPOINT,		//�`�F�b�N�|�C���g
	//	EPLAYER,			//�v���C���[
	//	EENEMY1,			//�G1
	//	EENEMY2,			//�G2
	//	EENEMY3,			//�G3
	//	//EENEMY4,			//�G4
	//	EBOSS,				//�{�X
	//	ESIZE,				//ECELLNUM �T�C�Y
	//};

	int editmap[MAP_SIZEY][MAP_SIZEX];				//�}�b�v
	CTexture mTexBack;								//�w�i
	CTexture mTexUI;								//UI �e�N�X�`���[
	CTexture mTexObject;							//UI �I�u�W�F�N�g
	CTexture mTexCharacter;							//UI �L�����N�^�[

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
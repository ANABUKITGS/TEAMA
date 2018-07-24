#ifndef CEDITER_H
#define CEDITER_H
#include <Windows.h>
#include "CKey.h"
#include "CRectangle.h"
#include "CText.h"
#include "CFileIO.h"

class CEditer{
public:
#define CELLSIZE		64	//�}�X �T�C�Y
#define EDITMAP_SIZEY	11	//�}�b�v ��� Y
#define EDITMAP_SIZEX	256	//�}�b�v ��� X
#define CURSOR_NUM		2	//�J�[�\��
	//�}�b�v �z�� ���g
	enum ECELLNUM{
		/*------ �}�b�v �`�� �Ȃ� ------*/
		ENONE = 1,			//�� | 0�͎g�p�֎~
		EGROUND,			//�����
		EUNDER,				//�����甲���鑫��
		EBELT,				//�x���g�R���x�A
		EJEWELRY,			//���
		ECHIKUWA,			//������u���b�N
		ESWITCH_GROUND1,	//�X�C�b�`�� �؂�ւ�鑫�� 1
		ESWITCH_GROUND2,	//�X�C�b�`�� �؂�ւ�鑫�� 2
		ESWITCH,			//�X�C�b�`�� �؂�ւ�鑫��� �X�C�b�`
		ETORABASAMI,		//�g���o�T�~
		ECHECKPOINT,		//�`�F�b�N�|�C���g

		/*------ �L�����N�^�[ �Ȃ� ------*/
		EPLAYER,			//�v���C���[
		EENEMY1,			//�G1
		//EENEMY2,			//�G2
		//EENEMY3,			//�G3
		//EENEMY4,			//�G4
		//EBOSS,				//�{�X
		ESIZE,				//ECELLNUM �T�C�Y
	};
	int editmap[11][256];				//�}�b�v
	int editmap_cursor[11][256];		//�}�b�v �J�[�\��
	int cursor_posX;					//�J�[�\�� �ꏊ X
	int cursor_posY;					//�J�[�\�� �ꏊ Y
	int setcell;						//�}�b�v �z�u���e
	unsigned int cursor_anime;			//�J�[�\�� �A�j���[�V����
	bool guideIO;						//�K�C�h ON OFF
	bool prtscrIO;						//�X�N���[���V���b�g
	CRectangle editmap_rect[11][256];	//�}�b�v �`��
	CTexture mTexBack;					//�w�i
	CTexture mTexUI;					//UI �e�N�X�`���[
	CTexture mTexObject;				//UI �I�u�W�F�N�g
	CTexture mTexCharacter;				//UI �L�����N�^�[

	//�R���X�g���N�^
	CEditer(){

	}
	void Init();
	void Update();
	void Render();
};
#endif
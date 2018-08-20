#ifndef CGAME2_H
#define CGAME2_H

#include "CMap.h"
#include "CTaskManager.h"
#include "CCamera2D.h"
#include "CSound.h"

//#define WINDOW_SIZE_W 1280
//#define WINDOW_SIZE_H 720


#define TUTORIAL_MAP	".\\Data\\Map\\MAP0.BIN"	//�`���[�g���A���}�b�v �t�@�C���p�X
#define GAME_MAP		".\\Data\\Map\\MAP1.BIN"	//�Q�[���}�b�v �t�@�C���p�X
#define EDITER_MAP		".\\Data\\Map\\MAP2.BIN"	//�G�f�B�b�g�}�b�v �t�@�C���p�X


class CGame2 : public CEditer {
public:
	static CCamera2D mCamera;


	CTexture mTexBack;								//�w�i
	CTexture mTexUI;								//UI �e�N�X�`���[
	CTexture mTexObject;							//UI �I�u�W�F�N�g
	CTexture mTexCharacter;							//UI �L�����N�^�[
	CTexture mTexEnemy;								//�G

//	bool mapsctoll_flag;							//�X�N���[�� �J�n

	void Init();
	void Update();
	void Scroll();
	void Render();

	static void MakeTaskList(int *gamemap);
};

#endif

#ifndef CGAME2_H
#define CGAME2_H

#include "CMap.h"
#include "CTaskManager.h"
#include "CCamera2D.h"

#define TUTORIAL_MAP	".\\Data\\Map\\MAP0.BIN"	//�`���[�g���A���}�b�v �t�@�C���p�X
#define GAME_MAP		".\\Data\\Map\\MAP1.BIN"	//�Q�[���}�b�v �t�@�C���p�X
#define EDITER_MAP		".\\Data\\Map\\MAP2.BIN"	//�G�f�B�b�g�}�b�v �t�@�C���p�X


class CMapChip : public CRectangle {
public:
	CMapChip(const CVector2 &pos, const CVector2 &scale, CTexture *tex, float uv0, float uv1, float uv2, float uv3)
		: CRectangle(pos, scale, tex)
	{
		mUv[0] = uv0;
		mUv[1] = uv1;
		mUv[2] = uv2;
		mUv[3] = uv3;
		CTaskManager::Get()->Add(this);
	}
};


class CGame2 : public CEditer {
public:
	CCamera2D mCamera;

	CTexture mTexBack;								//�w�i
	CTexture mTexUI;								//UI �e�N�X�`���[
	CTexture mTexObject;							//UI �I�u�W�F�N�g
	CTexture mTexCharacter;							//UI �L�����N�^�[

//	bool mapsctoll_flag;							//�X�N���[�� �J�n

	void Init();
	void Update();
	void Scroll();
	void Render();
};

#endif

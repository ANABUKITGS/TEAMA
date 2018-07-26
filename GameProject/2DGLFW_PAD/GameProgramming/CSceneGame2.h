#ifndef CSCENEGAME2_H
#define CSCENEGAME2_H
//�V�[���N���X
#include "CScene.h"
//���I�z��
#include <vector>
//�L�����N�^�N���X
#include "CCharacter.h"

#include "CSound.h"

#include "CGamePad.h"


//�Q�[���N���X
class CSceneGame2 : public CScene {
	//vector ���I�z��
	std::vector<CCharacter*> mCharacters;
	//�g�p����e�N�X�`��
	CTexture mTexImage;
	//�J�����̐ݒ�
	void SetCamera();
public:
	//�T�E���h�̕ϐ�
	CSound mSound;
	void Init();
	void Update();
	EScene GetNextScene();
	//UI��ʂ̕\��
	void UI();

	static CGamePad mGamePad;

};

#endif

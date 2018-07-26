#include "CScene.h" //�V�[���N���X�̃C���N���[�h
#include "CText.h" //�e�L�X�g�N���X�̃C���N���[�h
#include "CKey.h" //�L�[�N���X�̃C���N���[�h
#include <Windows.h>
/*
�^�C�g���V�[��
*/
//CScene�N���X���p������
class CSceneTitle : public CScene {
public:
	//���̃V�[���̎擾
	EScene GetNextScene() {
		return mScene;
	}
	//�����������̃I�[�o�[���C�h
	void Init() {
		//�t�H���g�̐ݒ�
		//�e�N�X�`���t�@�C����ǂݍ���
		CText::mFont.Load("font.tga");
		mScene = ETITLE;
	}
	//�X�V�����̃I�[�o�[���C�h
	void Update() {
		//������̕`��
		CText::DrawString("TITLE", -200, 0, 50, 50);
		CText::DrawString("Push ENTER Key", -200, -100, 16, 16);
		if (CKey::Once(VK_RETURN)) {
			//���̃V�[���̓Q�[��
			mScene = EGAME;
		}
	}
};

//GetKeyState�֐��̃w�b�_�t�@�C��
#include <Windows.h>
#include "CScene.h" //�V�[���̃C���N���[�h
#include "CSceneTitle.h" //�V�[���^�C�g���̃C���N���[�h
#include "CSceneGame2.h"
#include "glut.h"

/*
�V�[���Ǘ��N���X
*/
class CSceneManager {
public:

	CScene::EScene mScene; //�V�[���̎���
	CScene *mpScene; //�V�[���ւ̃|�C���^

	//�f�t�H���g�R���X�g���N�^
	CSceneManager()
	: mpScene(0)
	{
	}
	//�f�X�g���N�^
	~CSceneManager() {
		//�V�[��������΍폜
		if (mpScene)
			//�V�[���̍폜
			delete mpScene;
		mpScene = 0;
	}
	/*
	����������
	*/
	void Init() {
		//�V�[���̎��ʂ�ݒ肷��
		mScene = CScene::ETITLE;
		//�V�[���𐶐����A�|�C���^��ݒ肷��
		//�ϐ��͐e�N���X�A�����͎q�N���X
		mpScene = new CSceneTitle();
		//���������N���X�̃��\�b�h���Ă΂��
		mpScene->Init();
	}
	/*
	�X�V����
	*/
	void Update() {
		//�|�C���^��Update���Ă�
		mpScene->Update();
		//���̃V�[�����擾���قȂ邩����
		if (mScene != mpScene->GetNextScene()) {
			mScene = mpScene->GetNextScene();
			delete mpScene;//���̃V�[���폜
			//�Y������V�[���𐶐�
			switch (mScene) {
			case CScene::EGAME:
				mpScene = new CSceneGame2();
				mpScene->Init();
				break;
			case CScene::ETITLE:
				mpScene = new CSceneTitle();
				mpScene->Init();
				break;
			}
		}
	}
};

//�V�[���}�l�[�W���̃C���X�^���X
CSceneManager SceneManager;

//Init�֐�
//�ŏ��Ɉ�x�����Ă΂��֐�
void Init() {
	//�V�[���}�l�[�W���̏�����
	SceneManager.Init();
}

//Update�֐�
//�v���O�����̎��s���A�J��Ԃ��Ă΂��֐�
void Update() {
	//�V�[���}�l�[�W���̍X�V
	SceneManager.Update();
}

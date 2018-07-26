#ifndef CSCENE_H //�C���N���[�h�K�[�h
#define CSCENE_H //�C���N���[�h�K�[�h

/*
�V�[���̊��N���X
*/
class CScene {
public:
	//�V�[���̎��ʎq
	enum EScene {
		EGAME,	//�Q�[��
		ETITLE, //�^�C�g��
	};
	//���̃V�[��
	EScene mScene;
	//virtual ���z�֐�
	//�|�����[�t�B�Y���̎���
	//=0 ����
	virtual void Init() = 0;	//�������z�֐� ����������
	virtual void Update() = 0; //�������z�֐� �X�V����
	//���̃V�[���̎擾
	virtual EScene GetNextScene() = 0;
};

#endif //�C���N���[�h�K�[�h

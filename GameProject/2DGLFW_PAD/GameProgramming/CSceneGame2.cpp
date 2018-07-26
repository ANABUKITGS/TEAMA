#include "CSceneGame2.h"
#include "CText.h"

CGamePad CSceneGame2::mGamePad;


//�z��̗v�f�������߂�
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
//�}�b�v�z��̉��̒���
#define MAPSIZE_V 10
//�`�b�v�T�C�Y
#define CHIPSIZE 16
//�摜�̃}�b�s���O ��,�E,��,��
//�u���b�N�n��
#define UVBLOCKG 48, 95, 191, 144
//�v���C���[
#define UVPLAYER 136, 156, 158, 130
//�G�̃e�N�X�`��
#define UVENEMY 136, 156, 190, 161

#define DISP_XS CHIPSIZE * 8 //��ʂ̊J�nX���Έʒu
#define DISP_W CHIPSIZE * 4 * 6 //��ʂ̕�
#define DISP_H CHIPSIZE * 3 * 6 //��ʂ̍���

//�����������̃I�[�o�[���C�h
void CSceneGame2::Init() {
	//�T�E���h�t�@�C���̃��[�h
	mSound.Load("bgm.mp3");
	//���s�[�g�Đ�
	mSound.Repeat();
	mScene = EGAME;
	mTexImage.Load("Image.tga");
	CText::mFont.Load("Font.tga");
	int map[] = {
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 2, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 3, 0, 0, 0, 0, 0, //�G�̒ǉ�
		1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 0, 0, 0, 0, 0, 0, 0, //�i�̒ǉ�
		1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
	};
	for (int i = 0; i < ARRAY_SIZE(map); i++) {
		int x = i / MAPSIZE_V; //�������̒l
		int y = i % MAPSIZE_V; //�c�����̒l
		CCharacter *c;
		switch (map[i]) {
		case 1:
			c = new CBlock(&mTexImage, x*CHIPSIZE * 2, y*CHIPSIZE * 2, CHIPSIZE, CHIPSIZE, UVBLOCKG);
			mCharacters.push_back(c);
			break;
		case 3: //�G�̐���
			c = new CEnemy2(&mTexImage, x*CHIPSIZE * 2, y*CHIPSIZE * 2, CHIPSIZE, CHIPSIZE, UVENEMY);
			mCharacters.push_back(c);
			break;
		}
	}
	for (int i = 0; i < ARRAY_SIZE(map); i++) {
		int x = i / MAPSIZE_V; //�������̒l
		int y = i % MAPSIZE_V; //�c�����̒l
		CCharacter *c;
		switch (map[i]) {
		case 2:
			c = new CPlayer2(&mTexImage, x*CHIPSIZE * 2, y*CHIPSIZE * 2, CHIPSIZE, CHIPSIZE, UVPLAYER);
			mCharacters.push_back(c);
			break;
		}
	}
}

//�X�V�����̃I�[�o�[���C�h
void CSceneGame2::Update() {
	mGamePad.Update();

	for (int i = 0; i < mCharacters.size(); i++) {
		mCharacters[i]->Update();
	}
	//�Փˏ���
	for (int i = 0; i < mCharacters.size() - 1; i++) {
		for (int j = i + 1; j < mCharacters.size(); j++) {
			mCharacters[i]->Collision(mCharacters[i], mCharacters[j]);
			mCharacters[j]->Collision(mCharacters[j], mCharacters[i]);
		}
	}
	//�J�����̐ݒ���s��
	SetCamera();
	for (int i = 0; i < mCharacters.size(); i++) {
		mCharacters[i]->Render();
	}
	//���[�U�[�C���^�t�F�[�X�̕`��
	UI();
}

//���̃V�[���̎擾
CScene::EScene CSceneGame2::GetNextScene() {
	return mScene;
}
/*
�J�����̐ݒ�
*/
void CSceneGame2::SetCamera() {
	glMatrixMode(GL_PROJECTION);	//�s����v���W�F�N�V�������[�h�֕ύX
	glLoadIdentity();				//�s���������
	//2D��ʕ\���̈��ݒ�
	//��ʂ̍����W�C��ʂ̉E���W�C��ʂ̉����W�C��ʂ̏���W
	gluOrtho2D(CPlayer2::spInstance->x - DISP_XS
		, CPlayer2::spInstance->x - DISP_XS + DISP_W
		, 0, DISP_H);	//2D�̉�ʂ�ݒ�
	glMatrixMode(GL_MODELVIEW);		//�s������f���r���[���[�h�֕ύX
}
/*
���[�U�[�C���^�t�F�[�X�̎���
*/
void CSceneGame2::UI() {
	//�s����v���W�F�N�V�������[�h�֕ύX
	glMatrixMode(GL_PROJECTION);
	//���݂̃v���W�F�N�V�����s���ޔ�
	glPushMatrix();
	//�s���������
	glLoadIdentity();
	//2D��ʕ\���̈��ݒ�
	//��ʂ̍����W�C��ʂ̉E���W�C��ʂ̉����W�C��ʂ̏���W
	gluOrtho2D( -400, 400, -300, 300);	//2D�̉�ʍ��W��ݒ�
	//������\��
	CText::DrawString("SCORE", -320, 240, 20, 20);
	//�ޔ������s��ɖ߂�
	glPopMatrix();
	//�s������f���r���[���[�h�֕ύX
	glMatrixMode(GL_MODELVIEW);
}

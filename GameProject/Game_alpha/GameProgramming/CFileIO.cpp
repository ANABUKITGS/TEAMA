#include "CFileIO.h"
extern CEditer mEditer;

char cdir[MAX_PATH];	//�f�B���N�g��
char filepath[MAX_PATH];	//�J�� / �ۑ����� �t�@�C���� �t���p�X

void CFileIO::Init(){

}

void CFileIO::Update(){
	
}

void CMapIO::MapLoad(char map){

}

void CMapIO::Load(){	//�ǂݍ���
	FILE *fp = fopen(filepath, "rb");	//�t�@�C�����J��(�ǂݍ���)
	if (fp == NULL) //NULL���Ԃ��Ă�����G���[
		printf("Load : fopen error!\n");

	else {
		for (int i = 0; i < EDITMAP_SIZEY; i++){
			for (int j = 0; j < EDITMAP_SIZEX; j++){
				fread(&mEditer.editmap[i][j], sizeof(int), 1, fp);
				if (mEditer.editmap[i][j] >= mEditer.ESIZE){
					MessageBox(NULL, "�}�b�v�f�[�^���j�����Ă��邩�A�Ⴄ�t�@�C���ł��B", "�G���[", 0x00040010L);
					for (int i = 0; i < EDITMAP_SIZEY; i++){
						for (int j = 0; j < EDITMAP_SIZEX; j++)
							mEditer.editmap[i][j] = mEditer.ENONE;
					}
					char loadmsg[MAX_PATH + 8];
					sprintf(loadmsg, "Load to %s\n", filepath);
					printf(loadmsg);
					fclose(fp);	//�t�@�C�������
					return;
				}
			}
		}
		char loadmsg[MAX_PATH + 8];
		sprintf(loadmsg, "Load to %s\n", filepath);
		printf(loadmsg);
		fclose(fp);	//�t�@�C�������
	}
}

void CMapIO::Save(){	//��������
	FILE *fp = fopen(filepath, "wb");	//�t�@�C�����J��(��������)
	if (fp == NULL) //NULL���Ԃ��Ă�����G���[����
		printf("Save : fopen error!\n");

	else {
		for (int i = 0; i < EDITMAP_SIZEY; i++){
			for (int j = 0; j < EDITMAP_SIZEX; j++)
				fwrite(&mEditer.editmap[i][j], sizeof(int), 1, fp);
		}
		char savemsg[MAX_PATH + 8];
		sprintf(savemsg, "Save to %s\n", filepath);
		printf(savemsg);
		fclose(fp);	//�t�@�C�������
	}
}

void CMapIO::LoadDialog(HWND hWnd){	//�J�� �_�C�A���O
	/*------ �J�����g�f�B���N�g�� �ړ� ------*/
	GetCurrentDirectory(MAX_PATH, cdir);	//�v���O������ �f�B���N�g���� �擾
	SetCurrentDirectory(cdir);	//�擾�����f�B���N�g���� �J�����g�f�B���N�g���� ����

	static OPENFILENAME ofn;
	static TCHAR szPath[MAX_PATH];
	static TCHAR szFile[MAX_PATH];

	if (szPath[0] == TEXT('\0')){
		GetCurrentDirectory(MAX_PATH, szPath);	//�v���O������ �f�B���N�g���� �擾
	}
	if (ofn.lStructSize == 0){
		ofn.lStructSize = sizeof(OPENFILENAME);	//�\���̂̒��� (�o�C�g�P��)
		ofn.hwndOwner = hWnd;	//�e�E�C���h�E�̃n���h�� | ���ɂȂ��ꍇ��NULL
		ofn.lpstrInitialDir = szPath;	//�����t�H���_�ʒu
		ofn.lpstrFile = szFile;	//�I���t�@�C���i�[
		ofn.nMaxFile = MAX_PATH;	//lpstrFile�̎w�� �o�b�t�@�̃T�C�Y
		ofn.lpstrDefExt = TEXT("bin");	//�t�@�C������ �g���q��t���Ȃ������ꍇ�ɕt���� �g���q�̎w��
		ofn.lpstrFilter = TEXT("�}�b�v�f�[�^(*.bin)\0*.bin\0");	//�t�@�C���̎�� �v���_�E�����j���[
		ofn.lpstrTitle = TEXT("�J��");	//�E�B���h�E �^�C�g��
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;	//�_�C�A���O�{�b�N�X�쐬�t���O (�����̃t�@�C�����������͂������Ȃ� | �ǂݍ��ݐ�p�`�F�b�N�{�b�N�X ��\��)
	}
	if (GetOpenFileName(&ofn)){	//�ۑ�����w�肵���ꍇ
		//MessageBox(hWnd, szFile, TEXT("�t�@�C�����J��"), MB_OK);
		sprintf(filepath, "%s", szFile);
		CMapIO::Load();
	}

	SetCurrentDirectory(cdir);	//�擾�����f�B���N�g���� �J�����g�f�B���N�g���� ����
}

void CMapIO::SaveDialog(HWND hWnd){	//�ۑ� �_�C�A���O
	/*------ �J�����g�f�B���N�g�� �ړ� ------*/
	GetCurrentDirectory(MAX_PATH, cdir);	//�v���O������ �f�B���N�g���� �擾
	SetCurrentDirectory(cdir);	//�擾�����f�B���N�g���� �J�����g�f�B���N�g���� ����

	static OPENFILENAME ofn;
	static TCHAR szPath[MAX_PATH];
	static TCHAR szFile[MAX_PATH];

	if (szPath[0] == TEXT('\0')){
		GetCurrentDirectory(MAX_PATH, szPath);	//�v���O������ �f�B���N�g���� �擾
	}
	if (ofn.lStructSize == 0){
		ofn.lStructSize = sizeof(OPENFILENAME);	//�\���̂̒���(�o�C�g�P��)
		ofn.hwndOwner = hWnd;	//�e�E�C���h�E�̃n���h�� | ���ɂȂ��ꍇ��NULL
		ofn.lpstrInitialDir = szPath;	//�����t�H���_�ʒu
		ofn.lpstrFile = szFile;	//�I���t�@�C���i�[
		ofn.nMaxFile = MAX_PATH;	//lpstrFile�̎w�� �o�b�t�@�̃T�C�Y
		ofn.lpstrDefExt = TEXT("bin");	//�t�@�C������ �g���q��t���Ȃ������ꍇ�ɕt���� �g���q�̎w��
		ofn.lpstrFilter = TEXT("�}�b�v�f�[�^(*.bin)\0*.bin\0");	//�t�@�C���̎�� �v���_�E�����j���[
		ofn.lpstrTitle = TEXT("���O�����ĕۑ�");	//�E�B���h�E �^�C�g��
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;	//�_�C�A���O�{�b�N�X�쐬�t���O (�L���ȃp�X�y�уt�@�C�����łȂ���Γ��͂������Ȃ� | �t�@�C���̏㏑���m�F)
	}
	if (GetSaveFileName(&ofn)){	//�ۑ�����w�肵���ꍇ
		sprintf(filepath, "%s", szFile);
		CMapIO::Save();
	}
	SetCurrentDirectory(cdir);	//�擾�����f�B���N�g���� �J�����g�f�B���N�g���� ����
}
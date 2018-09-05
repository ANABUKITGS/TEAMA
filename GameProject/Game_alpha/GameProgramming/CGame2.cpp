#include "CGame2.h"
#include "CFileIO.h"
#include "CMap.h"
#include "CCamera2D.h"
#include "CMapChip.h"
#include "CPlayerT.h"
#include "CScene.h"
#include "CScore.h"
#include "CTime.h"
#include "CBGM.h"
#include "CMapBackImage.h"
#include "CFade.h"
#include "CMapSwitchGround.h"
#include "CMapSign.h"
#include "CMapScroll.h"
#include "CBoss.h"

bool CGame2::mCheat[CHEAT_NUM::ESIZE];
int CGame2::mTime;
int CGame2::mTimeMin;
float CGame2::mTimeSec;
CMapBackImage *mBackImage[4];

CCamera2D CGame2::mCamera;

void CGame2::Init(const char *map) {
	CMapScroll::scroll_flg = false;
	mCamera.SetOrtho(WINDOW_SIZE_W / 2, WINDOW_SIZE_H / 2, WINDOW_SIZE_W / 2, WINDOW_SIZE_H / 2);
	MapLoad(map);
	//�w�i
	mBackImage[0] = new CMapBackImage(CVector2(mCamera.x, mCamera.y), CMapBackImage::ETEXTURE_LAYER::LAYER1);
	mBackImage[1] = new CMapBackImage(CVector2(mCamera.x + 1280, mCamera.y), CMapBackImage::ETEXTURE_LAYER::LAYER1);
	mBackImage[2] = new CMapBackImage(CVector2(mCamera.x, mCamera.y), CMapBackImage::ETEXTURE_LAYER::LAYER2);
	mBackImage[3] = new CMapBackImage(CVector2(mCamera.x + 1280, mCamera.y), CMapBackImage::ETEXTURE_LAYER::LAYER2);


	//�J������_
	CMapScroll::mpScroll = new CMapScroll();

	//�X�C�b�`���� �� �L����
	CMapSwitchGround::mNumber = ESWITCH_GROUND1;

	//�`�[�g������
	for (int i = CHEAT_NUM::EFLAG; i < CHEAT_NUM::ESIZE; i++)
		mCheat[i] = false;

	//�X�N���[�� ��~ ����
	CMapScroll::scroll_stop = false;
}

void CGame2::MapLoad(const char *map){
	char filepath[256];
	//	if (map == CMapIO::EGAMEMAP)
	//	sprintf(filepath, "%s", GAME_MAP);
	//else if (map == CMapIO::ETUTORIAL)
	sprintf(filepath, "%s", map);
	//else if (map == CMapIO::EEDITERMAP)
	//	sprintf(filepath, "%s", EDITER_MAP);
	//else{
	//	MessageBox(NULL, "�}�b�v�f�[�^�̎w�肪����Ă��܂���B", "�G���[", 0x00040010L);
	//	return;
	//}
	FILE *fp = fopen(filepath, "rb");	//�t�@�C�����J��(�ǂݍ���)
	if (fp == NULL){	//NULL���Ԃ��Ă�����G���[
		MessageBox(NULL, "�}�b�v�f�[�^�̓ǂݍ��݂Ɏ��s���܂����B", "�G���[", 0x00040010L);
		printf("Load : fopen error!\n");
	}
	else {
		fseek(fp, 0L, SEEK_END);
		int size = ftell(fp);
		int gamemap[MAP_SIZEY][MAP_SIZEX];
		//		char *buf = new char[size];	//�t�@�C���T�C�Y+1�o�C�g���̗̈���m��
		fseek(fp, 0L, SEEK_SET);
		size = sizeof(gamemap);
		fread(gamemap, size, 1, fp);	//�m�ۂ����̈�Ƀt�@�C���T�C�Y���f�[�^��ǂݍ���
		//		buf[size] = '\0';	//�Ō��\0��ݒ肷��i������̏I�[�j
		fclose(fp);	//�t�@�C�����N���[�Y����

		CEditer::MakeTaskList((int*)gamemap);

		char loadmsg[MAX_PATH + 8];
		sprintf(loadmsg, "Load to %s\n", filepath);
		printf(loadmsg);
		fclose(fp);	//�t�@�C�������
	}
}

void CGame2::Update() {
	//���C���[1
	if (CGame2::mCamera.x < mBackImage[0]->mPosition.x)
		mBackImage[1]->mPosition.x = mBackImage[0]->mPosition.x - 1280;

	if (CGame2::mCamera.x > mBackImage[0]->mPosition.x)
		mBackImage[1]->mPosition.x = mBackImage[0]->mPosition.x + 1280;

	if (CGame2::mCamera.x < mBackImage[1]->mPosition.x)
		mBackImage[0]->mPosition.x = mBackImage[1]->mPosition.x - 1280;

	if (CGame2::mCamera.x > mBackImage[1]->mPosition.x)
		mBackImage[0]->mPosition.x = mBackImage[1]->mPosition.x + 1280;

	//���C���[2
	if (CGame2::mCamera.x < mBackImage[2]->mPosition.x)
		mBackImage[3]->mPosition.x = mBackImage[2]->mPosition.x - 1280;

	if (CGame2::mCamera.x > mBackImage[2]->mPosition.x)
		mBackImage[3]->mPosition.x = mBackImage[2]->mPosition.x + 1280;

	if (CGame2::mCamera.x < mBackImage[3]->mPosition.x)
		mBackImage[2]->mPosition.x = mBackImage[3]->mPosition.x - 1280;

	if (CGame2::mCamera.x > mBackImage[3]->mPosition.x)
		mBackImage[2]->mPosition.x = mBackImage[3]->mPosition.x + 1280;

	if (CKey::Push('D')) {
		mCamera.x += 5;
	}
	if (CKey::Push('A')) {
		mCamera.x -= 5;
	}
#ifndef _DEBUG
	if (CKey::Push('P')) {
		mTimeMin = CTime::ElapsedTimeMin();
		mTimeSec = CTime::ElapsedTimeSec();
		CScore::GetScore();
		CSceneResult::mResultTag = CSceneResult::ESCORE;
		CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::ERESULT);
		
	}
#endif
	if (CGamePad::Once(PAD_10) || CKey::Once(VK_ESCAPE)){
		CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::ETITLE);
		//CSceneChange::changenum = CSceneChange::ECSCENECHANGE_NUM::ETITLE;
		//CBGM::ChangeMusic(CBGM::EMUSIC_NUM::ETITLE);
	}
	if (CGamePad::Once(PAD_9) || CKey::Once(VK_RETURN)){
		if (CFade::mMapfile != CFade::EGAMEMAP_NUM::EMAIN && CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::EGAME)){
			if (CFade::mMapfile == CFade::EGAMEMAP_NUM::ETUTORIAL){
				CFade::mMapfile = CFade::EGAMEMAP_NUM::EMAIN;
			}
		}
	}

#ifdef _DEBUG
	if (CGamePad::Push(PAD_11) || CKey::Push(LVKF_CONTROL)){
		if (CGamePad::Once(PAD_1) || CKey::Once('1')){	//���G
			if (!mCheat[CHEAT_NUM::EMUTEKI])
				mCheat[CHEAT_NUM::EMUTEKI] = true;
			else
				mCheat[CHEAT_NUM::EMUTEKI] = false;
		}
		if (CGamePad::Once(PAD_2) || CKey::Once('2')){	//�㉺�̃G���A���� ����
			if (!mCheat[CHEAT_NUM::EAREA])
				mCheat[CHEAT_NUM::EAREA] = true;
			else
				mCheat[CHEAT_NUM::EAREA] = false;
		}
		if (CGamePad::Once(PAD_3) || CKey::Once('3')){	//�����X�N���[�� ����
			if (!mCheat[CHEAT_NUM::ESCROLL])
				mCheat[CHEAT_NUM::ESCROLL] = true;
			else
				mCheat[CHEAT_NUM::ESCROLL] = false;
		}
	}
#endif
	CTaskManager::Get()->Update();
	CTaskManager::Get()->Remove();
}

void CGame2::Render() {
	if (CPlayerT::mpPlayer == NULL){
		CBGM::AllStop();
		CSE::AllStop();
		MessageBox(NULL, "�}�b�v�Ƀv���C���[���ݒu����Ă��܂���B", "�G���[", 0x00040010L);
		CSceneChange::changenum = CSceneChange::ECSCENECHANGE_NUM::ETITLE;
		CBGM::ChangeMusic(CBGM::EMUSIC_NUM::ETITLE);
		return;
	}
//	CCamera2D::Begin(0.0, WINDOW_SIZE_W, 0.0, WINDOW_SIZE_H);
	mCamera.x = CMapScroll::mpScroll->mPosition.x;
	mCamera.y = CMapScroll::mpScroll->mPosition.y;
	mCamera.Begin();
	CTaskManager::Get()->Render();
	CCamera2D::End();
#ifdef _DEBUG
	wchar_t jumptime_buf[256];
	swprintf(jumptime_buf, L"�v���C���[\nmVelocityX\n%6.2f\nmVelocityY\n%6.2f\nmPosition.x\n%.2f\nmPosition.y\n%.2f", CPlayerT::mpPlayer->mVelocityX, CPlayerT::mpPlayer->mVelocityY, CPlayerT::mpPlayer->mPosition.x, CPlayerT::mpPlayer->mPosition.y);
	CText::DrawStringW(jumptime_buf, 0, 0, 16, 1.0f, 0);
	CheatText();
#endif

	//�`���[�g���A�� ���b�Z�[�W
	if (CMapSign::mView && CMapTextView::mpTextView == NULL){
		CMapTextView::mpTextView = new CMapTextView();
		CText::DrawSppedReset();
	}

	//�o�ߎ���
	wchar_t time_buf[64];
	for (int i = 0; i < 16; i++)
		time_buf[i] = '\0';
	swprintf(time_buf, L"%03d", (int)(CTime::GetTime()));
	CText::DrawStringImpact(time_buf, -620, 300, 32, 1.0f, 0);

	//�_�C�������h
	swprintf(time_buf, L"��");
	CText::DrawStringImpact(time_buf, -620, 250, 40, 1.0f, 0);
	swprintf(time_buf, L" �~ %02d", CPlayerT::mpPlayer->mJewel);
	CText::DrawStringImpact(time_buf, -588, 258, 24, 1.0f, 0);

	//�~�j�_�C�������h
	swprintf(time_buf, L"��");
	CText::DrawStringImpact(time_buf, -612, 218, 24, 1.0f, 0);
	swprintf(time_buf, L" �~ %02d", CPlayerT::mpPlayer->mMiniJewel);
	CText::DrawStringImpact(time_buf, -588, 218, 24, 1.0f, 0);

	//�c�@
	swprintf(time_buf, L"���~%1d", CPlayerT::mpPlayer->mLife);
	CText::DrawStringImpact(time_buf, -620, -350, 48, 1.0f, 0);

	if (CFade::mMapfile == CFade::EGAMEMAP_NUM::ETUTORIAL){
		CText::DrawStringW(L"�`���[�g���A��", -111, 328, 32, 1.0f, 0);
		CText::DrawStringW(L"�X�� �X�L�b�v���邱�Ƃ� �ł��܂��B", -216, 304, 24, 1.0f, 0);
	}

	static float mTextAlpha = 0.0f;
	if (CPlayerT::mpPlayer->mLife < 1){
		mTextAlpha += 0.1f;
		CText::DrawStringW(L"�Q�[���I�[�o�[", -224, -32, 64, mTextAlpha, 0);
		CText::DrawStringW(L"�Q�� �^�C�g���� ���ǂ�", -192, -64, 24, mTextAlpha, 0);
	}
	else
		mTextAlpha = 0.0f;
}

void CGame2::CheatText(){
#ifdef _DEBUG
	for (int i = CHEAT_NUM::EMUTEKI; i < CHEAT_NUM::ESIZE; i++){
		if (mCheat[i])
			mCheat[CHEAT_NUM::EFLAG] = true;	//���̃Z�b�V�����Ń`�[�g���g������
	}

	if (mCheat[CHEAT_NUM::EFLAG]){
		wchar_t cheat_buf[13];
		swprintf(cheat_buf, L"�`�[�g���悤 �Z�b�V����");
		CText::DrawStringW(cheat_buf, -640, 328, 16, 1.0f, 0);

		if (mCheat[CHEAT_NUM::EMUTEKI]){
			wchar_t cheatname_buf[5];
			swprintf(cheatname_buf, L"�E�ނĂ�");
			CText::DrawStringW(cheatname_buf, -640, 312, 16, 1.0f, 0);
		}
		if (mCheat[CHEAT_NUM::EAREA]){
			wchar_t cheatname_buf[13];
			swprintf(cheatname_buf, L"\n�E�G���A�������� �Ȃ�");
			CText::DrawStringW(cheatname_buf, -640, 312, 16, 1.0f, 0);
		}
		if (mCheat[CHEAT_NUM::ESCROLL]){
			wchar_t cheatname_buf[17];
			swprintf(cheatname_buf, L"\n\n�E���傤�����X�N���[�� �Ȃ�");
			CText::DrawStringW(cheatname_buf, -640, 312, 16, 1.0f, 0);
		}
	}
#endif
}
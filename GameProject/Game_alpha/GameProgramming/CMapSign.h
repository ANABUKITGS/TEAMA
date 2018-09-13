#ifndef CMAPSIGN_H
#define CMAPSIGN_H
#include "CMapChip.h"
#include "CMap.h"
#include "CCamera2D.h"
#include "CGame2.h"

#define SIGN_UV				mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 0, 64, 64, 0
#define BOSSROOM_SIGN_UV	mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, 0, 64, mTexPosY + 128, mTexPosY
#define BOSSROOM_SIGN_UV2	mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, 0, 64, 256, 128
#define TEXTVIEW_UV			CGame2::mCamera.x - 256 - 8, CGame2::mCamera.x + 256 + 8, CGame2::mCamera.y - 128 - 8, CGame2::mCamera.y + 128 + 8, 0, 512, 512, 0
#define MSGBUTTON_UV		mPosition.x - 32, mPosition.x + 32, mPosition.y - 32, mPosition.y + 32, 0, 64, 64, 0

#define DRAWSTRING_UV	text_buf, -256, 192, 32, 3, 1.0f

#define MAX_SIGN		10

//�`���[�g���A�� �Ŕ�
class CMapSign : public CMapChip {
private:
	CTexture mTexSign;
	bool mOnceCol;

public:
	int mSignTag;
	static bool mView;
	static bool mCol;
	CMapSign(const CVector2& pos)
		//CMapChip�ŏ�����
		: CMapChip(pos, CVector2(CELLSIZE / 2, CELLSIZE / 2), NULL, NULL, NULL, NULL, NULL, ECELLNUM::ESIGN)
	{
		if (mTexSign.id == NULL)
			mTexSign.Load(".\\Data\\Images\\Map\\MapSign.tga");
		mRender = false;
		mTag = ECELLNUM::ESIGN;
		mSignTag = NULL;
		mView = false;
		mOnceCol = false;
	}
	void Update();
	bool Collision(CRectangle *r);	//�Փˎ��̏���
	void Render();
};

class CMapTextView : public CRectangle{
private:
	CTexture mTexTextView;
	struct SMapSign{
		bool flg;
		wchar_t text_buf[MAX_PATH];
	};
	static SMapSign mSignText[MAX_SIGN];
	static wchar_t view_text_buf[MAX_PATH];

public:
	static CMapTextView *mpTextView;
	CMapTextView::CMapTextView()
		: CRectangle(CVector2(CGame2::mCamera.x, CGame2::mCamera.y), CVector2(0, 0), NULL)
	{
		mPriority = -100;
		mRender = false;
		for (int i = 0; i < MAX_SIGN; i++){
			swprintf(mSignText[i].text_buf, L"Sign%02d", i + 1);
		}
		{
			//swprintf(mSignText[0].text_buf, L"[�v���C���[�� ���������߂�]\n�o ���ǂ�\n�P ���[���[ �Ȃ�\n�Q �W�����v\n�R �_�b�V��\n�X �`���[�g���A���� �X�L�b�v\n�O �^�C�g���� ���ǂ�");
			swprintf(mSignText[0].text_buf, L"[�_�C�������h�� ����]\n�_�C�������h�� �ӂ�邩\n���[���[�� ���Ă邱�Ƃ�\n�Ă� ����邱�Ƃ�\n�ł��܂��B\n�_�C�������h���Ȃ��Ȃ��\n�~�X�� �Ȃ�܂��B");
			swprintf(mSignText[1].text_buf, L"[�X�N���[���� ����]\n���߂� �Ђ���� ��������\n�łĂ��܂��� �~�X�� �Ȃ�܂��B\n�~�X�� �Ȃ�Ȃ��悤��\n�������܂��傤�B");
			swprintf(mSignText[2].text_buf, L"[�`�F�b�N�|�C���g�� ����]\n�`�F�b�N�|�C���g�� �ӂ���\n�~�X�� ���Ă�\n�`�F�b�N�|�C���g�� ���Ă񂩂�\n�ӂ����� ���邱�Ƃ� �ł��܂��B");
			swprintf(mSignText[3].text_buf, L"[�Ă��� ����]\n�Ă��� ���[���[�� ���Ă邩\n�R���e�i�� �Ă�����\n���[���[�� ���Ƃ���\n�Ă��� ���Ă邱�Ƃ�\n���������Ƃ� �ł��܂��B");
			swprintf(mSignText[4].text_buf, L"[������� �����΂� ����]\n������� �����΂�\n�ƂĂ����ׂ�₷���ł��B\n���܂��v���C���[��\n�R���g���[������\n�Ă��� ����������\n������Ȃ��悤�� ���܂��傤�B");
			swprintf(mSignText[5].text_buf, L"[�x���g�R���x�A�� ����]\n�x���g�R���x�A�� �̂��\n�₶�邵�� �ق�������\n�Ȃ������ ���܂��܂��B");
			swprintf(mSignText[6].text_buf, L"[�����邠���΂� ����]\n�����邠���΂� �̂��\n������ �����Ă��܂��܂��B\n���߂�� ���Ƃ� �������\n�~�X�� �Ȃ�̂�\n�������� �����݂܂��傤�B");
			swprintf(mSignText[7].text_buf, L"[���肩��� �����΂� ����]\n���[���[�� �X�C�b�`�� ���Ă��\n������ ������ �����΂�\n���肩���܂��B\n�͂�Ƃ��߂��� �����΂�\n����邱�Ƃ� �ł��܂���B\n���܂� �X�C�b�`�� ���肩����\n�����݂܂��傤�B");
			swprintf(mSignText[8].text_buf, L"�����ꂳ�܂ł����B\n�`���[�g���A���� �����\n�����܂��ł��B\n�݂��͂��� ����΂�� �ӂ���\n�ق�؂�� �X�e�[�W��\n�͂��܂�܂��B");
			swprintf(mSignText[9].text_buf, L"\n\n�`���[�g���A�� �ł�����");
		}
		CTaskManager::Get()->Add(this);
	}
	~CMapTextView(){
		mpTextView = 0;
	}
	void Update();
	void Render();
	void SignTag(int);
};

//�`���[�g���A���I�� �Ŕ�
class CMapEndSign : public CMapChip {
private:
	CTexture mTexEndSign;

public:
	static CMapEndSign *mpEndSign;
	CMapEndSign(const CVector2& pos)
		//CMapChip�ŏ�����
		: CMapChip(pos, CVector2(CELLSIZE / 2, CELLSIZE / 2), NULL, NULL, NULL, NULL, NULL, ECELLNUM::EENDSIGN)
	{
		if (mTexEndSign.id == NULL)
			mTexEndSign.Load(".\\Data\\Images\\Map\\MapSign.tga");
		mRender = false;
		mTag = ECELLNUM::EENDSIGN;
	}
	~CMapEndSign(){
		mpEndSign = 0;
	}
	void Update();
	bool Collision(CRectangle *r);	//�Փˎ��̏���
	void Render();
};

//�{�X�̕��� �Ŕ�
class CMapBossRoomSign : public CMapChip {
private:
	CTexture mTexBossRoomSign;
	int mTexPosY;

public:
	bool mColFlg;
	static CMapBossRoomSign *mpBossRoomSign;
	CMapBossRoomSign(const CVector2& pos)
		//CMapChip�ŏ�����
		: CMapChip(pos + CVector2(0.0f, CELLSIZE / 2), CVector2(CELLSIZE / 2, CELLSIZE), NULL, NULL, NULL, NULL, NULL, ECELLNUM::EBOSSROOM)
	{
		if (mTexBossRoomSign.id == NULL)
			mTexBossRoomSign.Load(".\\Data\\Images\\Map\\MapBossRoomSign.tga");
		mTexPosY = 0;
		mColFlg = false;
		mRender = false;
		mTag = ECELLNUM::EBOSSROOM;
	}
	~CMapBossRoomSign(){
		mpBossRoomSign = 0;
	}
	void Update();
	bool Collision(CRectangle *r);	//�Փˎ��̏���
	void Render();
};

class CMsgButton : public CRectangle{
private:
	CTexture mTexButton;

public:
	static CMsgButton *mpMsgButton;
	CMsgButton(CVector2 pos)
		:CRectangle(pos, CVector2(0.0f, 0.0f), NULL)
	{
		if (mTexButton.id == NULL)
			mTexButton.Load(".\\Data\\Images\\Player\\MsgButton.tga");

		mAlpha = 0.0f;
		mTag = ECELLNUM::ENONE;
		mRender = false;
		CTaskManager::Get()->Add(this);
	}
	~CMsgButton(){
		mpMsgButton = NULL;
	}

	void Update();
	void Render();
};
#endif
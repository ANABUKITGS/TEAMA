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

//チュートリアル 看板
class CMapSign : public CMapChip {
private:
	CTexture mTexSign;
	bool mOnceCol;

public:
	int mSignTag;
	static bool mView;
	static bool mCol;
	CMapSign(const CVector2& pos)
		//CMapChipで初期化
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
	bool Collision(CRectangle *r);	//衝突時の処理
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
			//swprintf(mSignText[0].text_buf, L"[プレイヤーの そうさせつめい]\nＰ いどう\n１ ヨーヨー なげ\n２ ジャンプ\n３ ダッシュ\n９ チュートリアルを スキップ\n０ タイトルに もどる");
			swprintf(mSignText[0].text_buf, L"[ダイヤモンドに ついて]\nダイヤモンドは ふれるか\nヨーヨーを あてることで\nてに いれることが\nできます。\nダイヤモンドがなくなると\nミスに なります。");
			swprintf(mSignText[1].text_buf, L"[スクロールに ついて]\nがめん ひだりや したから\nでてしまうと ミスに なります。\nミスに ならないように\nきをつけましょう。");
			swprintf(mSignText[2].text_buf, L"[チェックポイントに ついて]\nチェックポイントに ふれると\nミスを しても\nチェックポイントの ちてんから\nふっかつ することが できます。");
			swprintf(mSignText[3].text_buf, L"[てきに ついて]\nてきは ヨーヨーを あてるか\nコンテナや てっこつを\nヨーヨーで おとして\nてきに あてることで\nたおすことが できます。");
			swprintf(mSignText[4].text_buf, L"[こおりの あしばに ついて]\nこおりの あしばは\nとてもすべりやすいです。\nうまくプレイヤーを\nコントロールして\nてきの こうげきに\nあたらないように しましょう。");
			swprintf(mSignText[5].text_buf, L"[ベルトコンベアに ついて]\nベルトコンベアに のると\nやじるしの ほうこうに\nながされて しまいます。");
			swprintf(mSignText[6].text_buf, L"[おちるあしばに ついて]\nおちるあしばは のると\nしたに おちてしまいます。\nがめんの そとに おちると\nミスに なるので\nきをつけて すすみましょう。");
			swprintf(mSignText[7].text_buf, L"[きりかわる あしばに ついて]\nヨーヨーを スイッチに あてると\nあかと あおの あしばが\nきりかわります。\nはんとうめいな あしばは\nさわることが できません。\nうまく スイッチを きりかえて\nすすみましょう。");
			swprintf(mSignText[8].text_buf, L"おつかれさまでした。\nチュートリアルは これで\nおしまいです。\nみぎはしの かんばんに ふれると\nほんぺんの ステージが\nはじまります。");
			swprintf(mSignText[9].text_buf, L"\n\nチュートリアル でぐち→");
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

//チュートリアル終了 看板
class CMapEndSign : public CMapChip {
private:
	CTexture mTexEndSign;

public:
	static CMapEndSign *mpEndSign;
	CMapEndSign(const CVector2& pos)
		//CMapChipで初期化
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
	bool Collision(CRectangle *r);	//衝突時の処理
	void Render();
};

//ボスの部屋 看板
class CMapBossRoomSign : public CMapChip {
private:
	CTexture mTexBossRoomSign;
	int mTexPosY;

public:
	bool mColFlg;
	static CMapBossRoomSign *mpBossRoomSign;
	CMapBossRoomSign(const CVector2& pos)
		//CMapChipで初期化
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
	bool Collision(CRectangle *r);	//衝突時の処理
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
#ifndef CEDITER_H
#define CEDITER_H
#include <Windows.h>
#include "CKey.h"
#include "CRectangle.h"
#include "CText.h"
#include "CFileIO.h"
#include "CCharcter.h"

//class CRectangle;

#define CELLSIZE		64		//マス サイズ
#define MAP_SIZEY		11		//マップ 上限 Y
#define MAP_SIZEX		256		//マップ 上限 X
#define CURSOR_NUM		-1		//カーソル
#define SCROLL_SPEED	2.0f	//スクロールスピード

#define WINDOW_SIZE_W 1280
#define WINDOW_SIZE_H 720

#define POS(Y,X) CVector2(X * CELLSIZE, Y * -CELLSIZE + WINDOW_SIZE_H)

#define EDT_RIGHT 0x01
#define EDT_LEFT 0x04
#define EDT_TOP 0x02
#define EDT_BOTTOM 0x08


class CPauseMenu{
private:
	enum EPAUSEMENU_NUM{
		EBACK = 1,
		ETITLE,
		ESIZE,
	};
	int cursor_num = EBACK;
	wchar_t cursor_buf[32];

public:
	bool pauseflag;									//ポーズメニュー

	void Update();
	void Render();
};

class CEditer : public CPauseMenu{
private:
	int editmap_cursor[MAP_SIZEY][MAP_SIZEX];		//マップ カーソル
	int cursor_posX;								//カーソル 場所 X
	int cursor_posY;								//カーソル 場所 Y
	int setcell;									//マップ 配置内容
	unsigned int cursor_anime;						//カーソル アニメーション
	bool guideIO;									//ガイド ON OFF
	bool prtscrIO;									//スクリーンショット用? カーソル等非表示
	CRectangle editmap_rect[MAP_SIZEY][MAP_SIZEX];	//マップ 描画

public:
	//マップ 配列 中身
	//enum ECELLNUM{
	//	/*------ マップ 形状 など ------*/
	//	ENONE = 1,			//空白 | 0は使用禁止
	//	EGROUND,			//床や壁
	//	EUNDER,				//下から抜ける足場
	//	EBELT,				//ベルトコンベア
	//	EJEWELRY,			//宝石
	//	ECHIKUWA,			//ちくわブロック
	//	ESWITCH_GROUND1,	//スイッチで 切り替わる足場 1
	//	ESWITCH_GROUND2,	//スイッチで 切り替わる足場 2
	//	ESWITCH,			//スイッチで 切り替わる足場の スイッチ
	//	ETORABASAMI,		//トラバサミ

	//	/*------ キャラクター など ------*/
	//	ECHECKPOINT,		//チェックポイント
	//	EPLAYER,			//プレイヤー
	//	EENEMY1,			//敵1
	//	EENEMY2,			//敵2
	//	EENEMY3,			//敵3
	//	//EENEMY4,			//敵4
	//	EBOSS,				//ボス
	//	ESIZE,				//ECELLNUM サイズ
	//};

	int editmap[MAP_SIZEY][MAP_SIZEX];				//マップ
	CTexture mTexBack;								//背景
	CTexture mTexUI;								//UI テクスチャー
	CTexture mTexObject;							//UI オブジェクト
	CTexture mTexCharacter;							//UI キャラクター

	void Init();
	void Update();
	void Render();
	static void MakeTaskList(int *gamemap);
};

class CGame : public CEditer{
public:
	int gamemap[MAP_SIZEY][MAP_SIZEX];				//マップ
	float mapscrollnum;								//スクロールした量, リスタート位置までのスクロール量
	bool mapsctoll_flag;							//スクロール 開始
	CRectangle gamemap_rect[MAP_SIZEY][MAP_SIZEX];	//マップ 描画

	void Init();
	void Update();
	void Scroll();
	void Render();
};
#endif
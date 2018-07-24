#ifndef CEDITER_H
#define CEDITER_H
#include <Windows.h>
#include "CKey.h"
#include "CRectangle.h"
#include "CText.h"
#include "CFileIO.h"

class CEditer{
public:
#define CELLSIZE		64	//マス サイズ
#define EDITMAP_SIZEY	11	//マップ 上限 Y
#define EDITMAP_SIZEX	256	//マップ 上限 X
#define CURSOR_NUM		2	//カーソル
	//マップ 配列 中身
	enum ECELLNUM{
		/*------ マップ 形状 など ------*/
		ENONE = 1,			//空白 | 0は使用禁止
		EGROUND,			//床や壁
		EUNDER,				//下から抜ける足場
		EBELT,				//ベルトコンベア
		EJEWELRY,			//宝石
		ECHIKUWA,			//ちくわブロック
		ESWITCH_GROUND1,	//スイッチで 切り替わる足場 1
		ESWITCH_GROUND2,	//スイッチで 切り替わる足場 2
		ESWITCH,			//スイッチで 切り替わる足場の スイッチ
		ETORABASAMI,		//トラバサミ
		ECHECKPOINT,		//チェックポイント

		/*------ キャラクター など ------*/
		EPLAYER,			//プレイヤー
		EENEMY1,			//敵1
		//EENEMY2,			//敵2
		//EENEMY3,			//敵3
		//EENEMY4,			//敵4
		//EBOSS,				//ボス
		ESIZE,				//ECELLNUM サイズ
	};
	int editmap[11][256];				//マップ
	int editmap_cursor[11][256];		//マップ カーソル
	int cursor_posX;					//カーソル 場所 X
	int cursor_posY;					//カーソル 場所 Y
	int setcell;						//マップ 配置内容
	unsigned int cursor_anime;			//カーソル アニメーション
	bool guideIO;						//ガイド ON OFF
	bool prtscrIO;						//スクリーンショット
	CRectangle editmap_rect[11][256];	//マップ 描画
	CTexture mTexBack;					//背景
	CTexture mTexUI;					//UI テクスチャー
	CTexture mTexObject;				//UI オブジェクト
	CTexture mTexCharacter;				//UI キャラクター

	//コンストラクタ
	CEditer(){

	}
	void Init();
	void Update();
	void Render();
};
#endif
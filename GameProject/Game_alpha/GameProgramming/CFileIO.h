#ifndef CSAVEFILE_H
#define CSAVEFILE_H

#include <stdio.h>
#include <iostream>
#include <shobjidl.h>
#include <direct.h>
#include "CMap.h"

class CFileIO{
public:
	void Init();
	void Update();
};

class CMapIO : public CFileIO{
public:
	enum EGAMEMAP_FILENAME{
		ETUTORIAL = 1,	//チュートリアルマップ
		EGAMEMAP,		//ゲームマップ
		EEDITERMAP,		//エディットマップ
		ESIZE,			//サイズ
	};
	//マップの読み込み
	void GameMapLoad(int);

	//読み込み
	void Load();

	//書き込み
	void Save();

	//ファイル 開く ダイアログ
	void LoadDialog(HWND);

	//ファイル 名前をつけて保存 ダイアログ
	void SaveDialog(HWND);
};
#endif
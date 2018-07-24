#ifndef CSAVEFILE_H
#define CSAVEFILE_H

#include <stdio.h>
#include <iostream>
#include <shobjidl.h>
#include <direct.h>
#include "CEditer.h"

class CFileIO{
public:
	void Init();
	void Update();

	//読み込み
	void Load();

	//書き込み
	void Save();

	//ファイル 開く ダイアログ
	void LoadDialog(HWND hWnd);

	//ファイル 名前をつけて保存 ダイアログ
	void SaveDialog(HWND hWnd);
};
#endif
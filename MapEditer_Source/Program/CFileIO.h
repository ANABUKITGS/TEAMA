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

	//�ǂݍ���
	void Load();

	//��������
	void Save();

	//�t�@�C�� �J�� �_�C�A���O
	void LoadDialog(HWND hWnd);

	//�t�@�C�� ���O�����ĕۑ� �_�C�A���O
	void SaveDialog(HWND hWnd);
};
#endif
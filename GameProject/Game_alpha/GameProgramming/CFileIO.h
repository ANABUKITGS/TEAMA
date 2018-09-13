#ifndef CSAVEFILE_H
#define CSAVEFILE_H

#include <stdio.h>
#include <iostream>
#include <shobjidl.h>
#include <direct.h>
#include "CMap.h"
//#include "CScore.h"

class CMapIO{
public:
	enum EGAMEMAP_FILENAME{
		ETUTORIAL = 1,	//�`���[�g���A���}�b�v
		EGAMEMAP,		//�Q�[���}�b�v
		EEDITERMAP,		//�G�f�B�b�g�}�b�v
		ESIZE,			//�T�C�Y
	};
	//�}�b�v�̓ǂݍ���
	void GameMapLoad(int);

	//�ǂݍ���
	void Load();

	//��������
	void Save();

	//�t�@�C�� �J�� �_�C�A���O
	void LoadDialog(HWND);

	//�t�@�C�� ���O�����ĕۑ� �_�C�A���O
	void SaveDialog(HWND);
};

class CRankingIO{
public:
	void Load();

	void Save();

	void Remove();
};
#endif
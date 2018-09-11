#include "CKey.h"
#include <Windows.h>
#include "CFade.h"

#define ONCEPUSH_LIMIT 30

//�����R�[�h���̃t���O
//true�̂Ƃ���̃L�[�͉�����Ă���
bool CKey::flg[256];

unsigned int CKey::oncetimekey[256];
/*
 push
 k�L�[��������Ă����true
 ������Ă��Ȃ����false
 �g����
 W�L�[��������Ă��邩�H
 if(CKey::Push('W'))
*/
bool CKey::Push(char k) {
	if (CFade::mFade == CFade::EFADE_NUM::EFALSE)
		return GetKeyState(k) & 0x8000;
	return false;
}
/*
 once
 k�L�[�������ꂽ�ŏ���true
 �������܂܂��ƁA���̌��false
 �g����
 W�L�[��������Ă��邩�H
 if(CKey::Once('W'))
 */
bool CKey::Once(char k) {
	if (CFade::mFade == CFade::EFADE_NUM::EFALSE){
		//k�L�[��������Ă��邩�H
		if (GetKeyState(k) & 0x8000) {
			//���łɉ�����Ă��邩�H
			if (flg[k]) {
				//������Ă�����false
				return false;
			}
			else {
				//������Ă��Ȃ����
				//flg��true��ݒ�
				flg[k] = true;
				return true;
			}
		}
		else {
			//���̃L�[��������ĂȂ����
			//flg��false�ɐݒ�
			flg[k] = false;
		}
	}
	return false;
}

bool CKey::OncePush(char k){
	if (CFade::mFade == CFade::EFADE_NUM::EFALSE){
		//k�L�[��������Ă��邩�H
		if (GetKeyState(k) & 0x8000) {
			if (oncetimekey[k] < ONCEPUSH_LIMIT){
				oncetimekey[k]++;
				//���łɉ�����Ă��邩�H
				if (flg[k]) {
					//������Ă�����false
					return false;
				}
				else {
					//������Ă��Ȃ����
					//flg��true��ݒ�
					flg[k] = true;
					return true;
				}
			}
			else
				return GetKeyState(k) & 0x8000;
		}
		else {
			//���̃L�[��������ĂȂ����
			//flg��false�ɐݒ�
			flg[k] = false;
			oncetimekey[k] = 0;
		}
	}
	return false;
}
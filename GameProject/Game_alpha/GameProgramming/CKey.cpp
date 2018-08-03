#include "CKey.h"
#include <Windows.h>

#define ONCEPUSH_LIMIT 30

//文字コード分のフラグ
//trueのところのキーは押されている
bool CKey::flg[256];

unsigned int CKey::oncetimekey[256];
/*
 push
 kキーが押されていればtrue
 押されていなければfalse
 使い方
 Wキーが押されているか？
 if(CKey::Push('W'))
*/
bool CKey::Push(char k) {
	return GetKeyState(k) & 0x8000;
}
/*
 once
 kキーが押された最初はtrue
 押したままだと、その後はfalse
 使い方
 Wキーが押されているか？
 if(CKey::Once('W'))
 */
bool CKey::Once(char k) {
	//kキーが押されているか？
	if (GetKeyState(k) & 0x8000) {
		//すでに押されているか？
		if (flg[k]) {
			//押されていたらfalse
			return false;
		}
		else {
			//押されていなければ
			//flgにtrueを設定
			flg[k] = true;
			return true;
		}
	}
	else {
		//そのキーが押されてなければ
		//flgをfalseに設定
		flg[k] = false;
	}
	return false;
}

bool CKey::OncePush(char k){
	//kキーが押されているか？
	if (GetKeyState(k) & 0x8000) {
		if (oncetimekey[k] < ONCEPUSH_LIMIT){
			oncetimekey[k]++;
			//すでに押されているか？
			if (flg[k]) {
				//押されていたらfalse
				return false;
			}
			else {
				//押されていなければ
				//flgにtrueを設定
				flg[k] = true;
				return true;
			}
		}
		else
			return GetKeyState(k) & 0x8000;
	}
	else {
		//そのキーが押されてなければ
		//flgをfalseに設定
		flg[k] = false;
		oncetimekey[k] = 0;
	}
	return false;
}
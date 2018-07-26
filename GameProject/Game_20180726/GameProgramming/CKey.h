#ifndef CKEY_H
#define CKEY_H
/*
 キー入力クラス
*/
class CKey {
	//キーが押されているかのフラグ
	static bool flg[256];
public:
	//kキーが押されている間trueを返す
	static bool Push(char k);
	//kキーが押された時に一度だけtrueを返す
	static bool Once(char k);
};

#endif

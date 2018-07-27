#ifndef CVECTOR_H
#define CVECTOR_H

#include <math.h>

class CVector2{
public:
	float x;
	float y;

	CVector2()	//コンストラクタ
		:x(0.0f)
		, y(0.0f)
	{}

	CVector2(float x, float y)	//引数コンストラクタ
		:x(x), y(y)
	{}

	const CVector2 operator+(const CVector2 &v)const;
	const CVector2 operator-(const CVector2 &v)const;
	const CVector2 operator*(const CVector2 &v)const;
	const CVector2 operator/(const CVector2 &v)const;

	float Length();	//ベクトルの大きさを返す

};
#endif
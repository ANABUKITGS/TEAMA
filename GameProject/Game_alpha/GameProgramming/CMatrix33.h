#ifndef CMATRIX33_H
#define CMATRIX33_H
#include <string.h>
#include "CVector2.h"
class CMatrix33{
public:
	float m[3][3];
	CMatrix33(){
		memset(m, 0, sizeof(m));
	}
	void Identity();
	void Print();
	void SetRotation(float degree);
	void SetTranslate(float x,float y);
	void SetScale(float x, float y);
	const CVector2 MultiVector2(const CVector2 &v) const;

	const CMatrix33 MultiMatrix33(const CMatrix33 &v)const;
	const CMatrix33 operator+(const CMatrix33 &v) const;
	const CMatrix33 operator-(const CMatrix33 &v) const;
	const CMatrix33 operator*(const CMatrix33 &v) const;
	const CMatrix33 operator/(const CMatrix33 &v) const;

};
#endif
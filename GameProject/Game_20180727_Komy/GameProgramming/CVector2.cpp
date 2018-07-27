#include "CVector2.h"

const CVector2 CVector2::operator+(const CVector2 &v)const{
	return CVector2(x + v.x, y + v.y);
}

const CVector2 CVector2::operator-(const CVector2 &v)const{
	return CVector2(x - v.x, y + v.y);
}

const CVector2 CVector2::operator*(const CVector2 &v)const{
	return CVector2(x*v.x, y*v.y);
}

const CVector2 CVector2::operator/(const CVector2 &v)const{
	return CVector2(x / v.x, y / v.y);
}

float CVector2::Length(){
	return sqrtf((x*x)+(y*y));
}

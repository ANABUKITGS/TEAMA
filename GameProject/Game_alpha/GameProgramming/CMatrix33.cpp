#include "CMatrix33.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

void CMatrix33::Print(){
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			printf("%f ", m[i][j]);
		}
		printf("\n");
	}
}
//’PˆÊs—ñ
void CMatrix33::Identity(){
	/*[1][0][0]
	  [0][1][0]
	  [0][0][1]
	*/
	memset(m, 0, sizeof(m));
	for (int i = 0; i < 3; i++){
		m[i][i] = 1;
	}
}

void CMatrix33::SetTranslate(float x, float y){
	/*[1][0][x]
	  [0][1][y]
	  [0][0][1]*/
	Identity();
	m[0][2] = x;
	m[1][2] = y;
}
void CMatrix33::SetRotation(float degree){
	/*[cos][-sin][0]
	  [sin][ cos][0]
	  [0]  [0]   [1]
	*/
	float radian = degree * M_PI / 180.0f;
	float sin = sinf(radian);
	float cos = cosf(radian);
	Identity();
	m[0][0] = m[1][1] = cos;
	m[0][1] = -sin;
	m[1][0] = sin;
}
void CMatrix33::SetScale(float x, float y){
	/*[x][0][0]
	  [0][y][0]
	  [0][0][1]*/
	Identity();
	m[0][0] = x;
	m[1][1] = y;
}
const CVector2 CMatrix33::MultiVector2(const CVector2 &v) const
{
	CVector2 vector;
	vector.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2];
	vector.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2];
	return vector;
}

const CMatrix33 CMatrix33::MultiMatrix33(const CMatrix33 &v)const{
	/*
	[0][0][0]   [0][0][0]
	[0][0][0] * [0][0][0]
	[0][0][0]   [0][0][0]

	[0][0]=[0][0]*[0][0]+[0][1]*[1][0]+[0][2]*[2][0]
	*/

	CMatrix33 r;
	//[0]
	r.m[0][0] = m[0][0] * v.m[0][0] + m[0][1] * v.m[1][0] + m[0][2] * v.m[2][0];
	r.m[0][1] = m[0][0] * v.m[0][1] + m[0][1] * v.m[1][1] + m[0][2] * v.m[2][1];
	r.m[0][2] = m[0][0] * v.m[0][2] + m[0][1] * v.m[1][2] + m[0][2] * v.m[2][2];

	//[1]
	r.m[1][0] = m[1][0] * v.m[0][0] + m[1][1] * v.m[1][0] + m[1][2] * v.m[2][0];
	r.m[1][1] = m[1][0] * v.m[0][1] + m[1][1] * v.m[1][1] + m[1][2] * v.m[2][1];
	r.m[1][2] = m[1][0] * v.m[0][2] + m[1][1] * v.m[1][2] + m[1][2] * v.m[2][2];

	//[2]
	r.m[2][0] = m[2][0] * v.m[0][0] + m[2][1] * v.m[1][0] + m[2][2] * v.m[2][0];
	r.m[2][1] = m[2][0] * v.m[0][1] + m[2][1] * v.m[1][1] + m[2][2] * v.m[2][1];
	r.m[2][2] = m[2][0] * v.m[0][2] + m[2][1] * v.m[1][2] + m[2][2] * v.m[2][2];

	return r;
}

const CMatrix33 CMatrix33::operator+(const CMatrix33 &v) const{
	return MultiMatrix33(v);
}
const CMatrix33 CMatrix33::operator-(const CMatrix33 &v) const{
	return MultiMatrix33(v);
}
const CMatrix33 CMatrix33::operator*(const CMatrix33 &v) const{
	return MultiMatrix33(v);
}
const CMatrix33 CMatrix33::operator/(const CMatrix33 &v) const{
	return MultiMatrix33(v);
}

const CMatrix33 CMatrix33::transpose() const {
	CMatrix33 tmp;
	tmp.m[0][0] = m[0][0];
	tmp.m[0][1] = m[1][0];
	tmp.m[0][2] = m[2][0];
	tmp.m[1][0] = m[0][1];
	tmp.m[1][1] = m[1][1];
	tmp.m[1][2] = m[2][1];
	tmp.m[2][0] = m[0][2];
	tmp.m[2][1] = m[1][2];
	tmp.m[2][2] = m[2][2];
	return tmp;
}

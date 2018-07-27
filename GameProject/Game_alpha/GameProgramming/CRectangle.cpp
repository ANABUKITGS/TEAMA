#include "CRectangle.h"

CRectangle::CRectangle(const CVector2&position, const CVector2&scale, CTexture*texture)
:mPosition(position), mScale(scale)
{
	mPosition.x = position.x;
	mPosition.y = position.y;
};

void CRectangle::SetVertex(float mLeft, float mRight, float mBottom, float mTop){
	/*四角形を
	左上、左下、右下、右上の頂点順で作る
	*/
	mVector[0].x = mLeft;	mVector[0].y = mTop;
	mVector[1].x = mLeft;	mVector[1].y = mBottom;
	mVector[2].x = mRight;	mVector[2].y = mBottom;
	mVector[3].x = mRight;	mVector[3].y = mTop;
}
void CRectangle::Update(){
	//移動行列
	mMatrix.SetTranslate(mPosition.x, mPosition.y);
	//マトリクスクラスを回転、拡宿用行列
	CMatrix33 rot, sca;
	//回転行列
	rot.SetRotation(mRotation);
	//拡大縮小行列
	sca.SetScale(mScale.x, mScale.y);
}

void CRectangle::Render(){
	CVector2 mv[4];	//座標で四角形生成するためのインスタンス
	//合成行列を代入する
	mv[0] = mMatrix.MultiVector2(mVector[0]);
	mv[1] = mMatrix.MultiVector2(mVector[1]);
	mv[2] = mMatrix.MultiVector2(mVector[2]);
	mv[3] = mMatrix.MultiVector2(mVector[3]);
	if (!mEnabled)	//有効フラグが無効な時は戻り値を返す
		return;
	else{	//フラグが有効な時は四角形を生成する
		glBegin(GL_QUADS);
		glVertex2f(mv[0].x, mv[0].y);
		glVertex2f(mv[1].x, mv[1].y);
		glVertex2f(mv[2].x, mv[2].y);
		glVertex2f(mv[3].x, mv[3].y);
		glEnd();
	}
}
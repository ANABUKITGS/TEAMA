#ifndef CRECTANGLE_H
#define CRECTANGLE_H
//OpenGLライブラリ
#include "glut.h"
//テクスチャクラスのインクルード
#include "CTexture.h"

/*
CRectangleクラス
四角形に関するクラス
*/
class CRectangle {
public:
	//列挙型の定義
	enum ETag {
		EBLOCK,	//ブロック
		EPLAYERBULLET,	//プレイヤー弾
		EPLAYER,	//プレイヤー
	};
	ETag mTag;	//列挙型の変数
	//デフォルトコンストラクタ
	CRectangle()
		: mTag(EBLOCK)	//初期値ブロック
	{}
	int x;	//中心のX座標
	int y, w, h;	//中心のY座標,幅,高さ

	/*
	DrawTriangle
	三角形を描画する関数
	*/
	void DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2) {
		//三角形の描画
		glBegin(GL_TRIANGLES);	//三角形の描画開始
		glVertex2d(x0, y0);		//頂点１の座標を指定
		glVertex2d(x1, y1);		//頂点２の座標を指定
		glVertex2d(x2, y2);		//頂点３の座標を指定
		glEnd();	//描画終了
	}

	/*
	DrawRectangle
	四角形を描画する関数
	x0,y0:右上
	x1,y1:左上
	x2,y2:左下
	x3,y3:右下
	*/
	void DrawRectangle(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3) {
		DrawTriangle(x0, y0, x1, y1, x2, y2);
		DrawTriangle(x0, y0, x2, y2, x3, y3);
	}

	/*
	Draw
	四角形を描画する関数
	*/
	void Draw() {
		//クラスメンバの変数x,y,w,hを使用します
		DrawRectangle(x + w, y + h, x - w, y + h, x - w, y - h, x + w, y - h);
	}

	/*28
	テクスチャの描画
	*/
	void Draw(const CTexture &t, int left, int right, int bottom, int top) {
		t.DrawImage(x - w, x + w, y - h, y + h, left, right, bottom, top);
	}

	/*
	Collision
	四角形*prと衝突していればtrueを
	していなければfalseを返します。
	*/
	bool Collision(const CRectangle &r) {
		//X軸の重なりを判定
		//中心のX座標の距離を求める
		int lenX = x - r.x;
		//距離の絶対値を求める
		lenX = lenX < 0 ? -lenX : lenX;
		//距離が幅の合計より大きいとき、X軸は重なっていない
		if (lenX > w + r.w) {
			//重なってなければ、衝突していない
			//falseを返す
			return false;
		}
		//Y軸の重なり判定
		int lenY = y - r.y;
		lenY = lenY < 0 ? -lenY : lenY;
		if (lenY > h + r.h) {
			return false;
		}
		//X軸、Y軸ともに重なっているので、trueを返す
		return true;
	}
	/*
	Collision
	引数*prの四角形と衝突しているか検出し、
	衝突していればtrueを、していなければfalseを返す。
	また、衝突していた場合、*pxにX軸方向に重なった量を、
	*pyにY軸方向へ重なった量を設定する。
	*/
	bool Collision(CRectangle *pr, int *px, int *py) {
		//xとyを0に0を代入
		*px = 0;
		*py = 0;
		//X軸の重なりを判定
		//中心のX座標の距離を求める
		int lenX = x - pr->x;
		//距離の絶対値を求める
		lenX = lenX < 0 ? -lenX : lenX;
		//距離が幅の合計より小さいとき、X軸は重なっている
		if (lenX < w + pr->w) {
			//重なり具合を計算
			if (x < pr->x) {
				//相手が右の時は左へ移動
				*px = lenX - w - pr->w;
			}
			else {
				//相手が左の時は右へ移動
				*px = w + pr->w - lenX;
			}
		}
		else {
			//重なってなければ、衝突していない
			//falseを返す
			return false;
		}
		//Y軸の重なり判定
		int lenY = y - pr->y;
		lenY = lenY < 0 ? -lenY : lenY;
		if (lenY < h + pr->h) {
			if (y < pr->y) {
				*py = lenY - h - pr->h;
			}
			else {
				*py = h + pr->h - lenY;
			}
		}
		else {
			return false;
		}
		//X軸、Y軸ともに重なっているので、trueを返す
		return true;
	}
};


#endif

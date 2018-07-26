#ifndef CCHARACTER_H
#define CCHARACTER_H
//四角形クラスのインクルード
#include "CRectangle.h"
#include "CSound.h"
/*
キャラクタクラス
*/
class CCharacter : public CRectangle {
public:
	//キャラクタ識別子
	enum EChara {
		EBLOCK,
		EPLAYER,
		EENEMY, //敵追加
	};
	EChara mTag; //キャラクタ識別子
//43
	//状態識別子
	enum EState {
		ERUN, //移動中
		EJUMPUP, //ジャンプ上
		EJUMPDOWN, //ジャンプ下
		ECRY, //泣いている
	};
	EState mState; //状態
	CTexture *mpTexture; //テクスチャ
	int mU[2]; //マッピング横
	int mV[2]; //マッピング縦
	//コンストラクタ
	CCharacter(CTexture *t, int ax, int ay, int aw, int ah, int u0, int u1, int v0, int v1)
		: mpTexture(t)
		//43
		, mState(ERUN) //移動状態
	{
		x = ax; //X座標
		y = ay; //Y座標
		w = aw; //幅
		h = ah; //高さ
		mU[0] = u0; //UV左
		mU[1] = u1; //UV右
		mV[0] = v0; //UV下
		mV[1] = v1; //UV上
	}
	//仮想関数 描画処理
	virtual void Render() {
		//画像描画
		Draw(*mpTexture, mU[0], mU[1], mV[0], mV[1]);
	}
	//仮想関数 更新処理
	virtual void Update() {}
	//衝突処理
	virtual bool Collision(CCharacter *m, CCharacter *y) { return false; };
	//テクスチャマッピングの設定
	void SetUv(int u0, int u1, int v0, int v1);
};
/*
ブロッククラス
*/
class CBlock : public CCharacter {
public:
	CBlock(CTexture *t, int x, int y, int w, int h, int u0, int u1, int v0, int v1)
		: CCharacter(t, x, y, w, h, u0, u1, v0, v1)
	{
		mTag = CCharacter::EBLOCK;
	}
};
/*
プレイヤークラス
*/
class CPlayer2 : public CCharacter {
private:
	int mGravityV; //重力速度
	int mStartX; //スタートX座標
	CSound mSound;
public:
	static CPlayer2 *spInstance; //インスタンスのポインタ
	CPlayer2(CTexture *t, int x, int y, int w, int h, int u0, int u1, int v0, int v1)
		: CCharacter(t, x, y, w, h, u0, u1, v0, v1)
		, mGravityV(0)
		, mStartX(x)
	{
		mTag = CCharacter::EPLAYER;
		//インスタンスポインタに設定
		spInstance = this;
		//サウンドロード
		mSound.Load("jump.mp3");
	}
	//更新処理
	void Update();
	//衝突処理
	bool Collision(CCharacter *m, CCharacter *y);
};

/*
敵クラス
*/
class CEnemy2 : public CCharacter {
private:
	int mGravityV; //重力速度
	int mForward; //向き -1:左 1:右
public:
	CEnemy2(CTexture *t, int x, int y, int w, int h, int u0, int u1, int v0, int v1)
		: CCharacter(t, x, y, w, h, u0, u1, v0, v1)
		, mGravityV(0)
		, mForward(1) //右へ
	{
		mTag = CCharacter::EENEMY;
	}
	//更新処理
	void Update();
	//衝突処理
	bool Collision(CCharacter *m, CCharacter *y);
};

#endif

#include "CScene.h"
#include "CScore.h"
#include "CBGM.h"
#include "CGame2.h"

CCharcter player;
CEditer mEditer;
CGame mGame;
CGame2 mGame2;
CTitle mTitle;
CGetScore mScore;
CBGM mBGM;

int CSceneChange::changenum = ETITLE;

void CSceneChange::Init(){
	mEditer.Init();
	mGame.Init();
	mTitle.Init();
	mEditer.Init();
	mBGM.Init();
}

void CSceneChange::Update(){
	mBGM.Update();
	switch (changenum){
	default:
		break;

	case ETITLE:
		mTitle.Update();
		mTitle.Render();
		break;

	case EGAME:
		mGame2.Update();
		mGame2.Render();
		break;

	case ERANKING:
		break;

	case ESCORE:
		mScore.Update();
		break;

	case EEDITER:
		mEditer.Update();
		mEditer.Render();
		break;

	case EEXIT:
		break;
	}
}

void CSceneChange::Render(){

}
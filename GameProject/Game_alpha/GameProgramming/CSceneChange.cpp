#include "CScene.h"
CCharcter player;
CEditer mEditer;
CGame mGame;
CTitle mTitle;

int CSceneChange::changenum = ETITLE;

void CSceneChange::Init(){
	player.Init();
	mEditer.Init();
	mGame.Init();
	mTitle.Init();
	mEditer.Init();
}

void CSceneChange::Update(){
	switch (changenum){
	default:
		break;

	case ETITLE:
		mTitle.Update();
		mTitle.Render();
		break;

	case EGAME:
		mGame.Update();
		mGame.Render();
		break;

	case ERANKING:
		break;

	case EEDITER:
		mEditer.Update();
		mEditer.Render();
		break;

	case EHOGE1:
		break;
	}
}

void CSceneChange::Render(){

}
#include "CScene.h"
#include "CScore.h"
#include "CBGM.h"
#include "CGame2.h"
#include "CMapBackImage.h"

CCharcter player;
CEditer mEditer;
CGame mGame;
CGame2 mGame2;
CTitle mTitle;
CSceneResult mResult;
CScore mScore;
CRanking mRanking;
CName mName;
CBGM mBGM;

int CSceneChange::changenum = ETITLE;

void CSceneChange::Init(){
	mEditer.Init();
	mGame.Init();
	mTitle.Init();
	mEditer.Init();
	mResult.Init();
	mRanking.Init();
	mScore.Init();
	mName.Init();
	mBGM.Init();
}

void CSceneChange::Update(){
	mBGM.Update();
	switch (changenum){
	case ECSCENECHANGE_NUM::ETITLE:
		CTaskManager::Get()->Destroy();
		mTitle.Update();
		mTitle.Render();
		break;

	case ECSCENECHANGE_NUM::EGAME:
		mGame2.Update();
		mGame2.Render();
		break;

	case ECSCENECHANGE_NUM::ERANKING:
		CTaskManager::Get()->Destroy();
		CSceneResult::mResultTag = CSceneResult::ERANKING;
		mResult.Update();
		break;

	case ECSCENECHANGE_NUM::ERESULT:
		if (CSceneResult::mResultTag == CSceneResult::ESCORE)
			CSceneResult::mResultTag = CSceneResult::ESCORE;
		mResult.Update();
		break;

	case ECSCENECHANGE_NUM::EEDITER:
		mEditer.Update();
		mEditer.Render();
		break;

	case ECSCENECHANGE_NUM::EEXIT:
		CTaskManager::Get()->Destroy();
		_sleep(500);
		exit(0);
		break;

	default:
		break;
	}
	CMapBackImage::RenderFade();
}

void CSceneChange::Render(){

}
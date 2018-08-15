#ifndef CBGM_H
#define CBGM_H
#include <time.h>
#include "CSound.h"
#include "CScene.h"

#define SOUND_TITLE		0
#define SOUND_TUTORIAL	161 //2682
#define SOUND_MAIN		0
#define SOUND_BOSS		0
#define SOUND_RESULT	0

class CBGM {
private:
	int starttime;
	int musictime = SOUND_TUTORIAL;
	CSound mSoundTitle;								//タイトル用
	CSound mSoundTutorial;							//チュートリアル用
	CSound mSoundMain;							//本編用
	CSound mSoundBoss;								//ボス用
	CSound mSoundResult;							//リザルト用

public:
	void Init();
	void Update();
};

#endif
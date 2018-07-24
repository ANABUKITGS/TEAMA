#include "CTitle.h"

void CTitle::Init(){
	//mTexture.Load(".\\Data\\Images\\Title.tga");
}

void CTitle::Update(){

}

void CTitle::GameExit(){	//ゲーム終了 ダイアログ
	{
		int msg_button;
		msg_button = MessageBox(NULL, "ゲームを終了しますか?\n保存していないデータは失われます", "ゲームの終了", 0x00040031L);
		if (msg_button == IDYES || msg_button == IDOK){
			_sleep(500);
			exit(0);
		}
	}
}

void CTitle::Render(){

}
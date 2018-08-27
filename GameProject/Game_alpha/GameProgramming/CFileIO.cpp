#include "CFileIO.h"
#include "CScore.h"
#define TUTORIAL_MAP	".\\Data\\Map\\MAP0.BIN"	//チュートリアルマップ ファイルパス
#define GAME_MAP		".\\Data\\Map\\MAP1.BIN"	//ゲームマップ ファイルパス
#define EDITER_MAP		".\\Data\\Map\\MAP2.BIN"	//エディットマップ ファイルパス
#define RANKING_PATH	".\\Data\\RANKING.BIN"		//ランキングデータ ファイルパス

extern CEditer mEditer;
extern CGame mGame;
extern CRanking mRanking;

char cdir[MAX_PATH];	//ディレクトリ
char filepath[MAX_PATH];	//開く / 保存する ファイルの フルパス

void CMapIO::GameMapLoad(int map){
	if (map == EGAMEMAP)
		sprintf(filepath, "%s", GAME_MAP);
	else if (map == ETUTORIAL)
		sprintf(filepath, "%s", TUTORIAL_MAP);
	else if (map == EEDITERMAP)
		sprintf(filepath, "%s", EDITER_MAP);
	else{
		MessageBox(NULL, "マップデータの指定がされていません。", "エラー", 0x00040010L);
		return;
	}
	FILE *fp = fopen(filepath, "rb");	//ファイルを開く(読み込み)
	if (fp == NULL){	//NULLが返ってきたらエラー
		MessageBox(NULL, "マップデータの読み込みに失敗しました。", "エラー", 0x00040010L);
		printf("Load : fopen error!\n");
	}

	else {
		for (int i = 0; i < MAP_SIZEY; i++){
			for (int j = 0; j < MAP_SIZEX; j++){
				fread(&mGame.gamemap[i][j], sizeof(int), 1, fp);
				if (mGame.gamemap[i][j] >= ECELLNUM::ESIZE){
					MessageBox(NULL, "マップデータが破損しているか、違うファイルです。", "エラー", 0x00040010L);
					for (int i = 0; i < MAP_SIZEY; i++){
						for (int j = 0; j < MAP_SIZEX; j++)
							mGame.gamemap[i][j] = ECELLNUM::ENONE;
					}
					char loadmsg[MAX_PATH + 8];
					sprintf(loadmsg, "Load to %s\n", filepath);
					printf(loadmsg);
					fclose(fp);	//ファイルを閉じる
					return;
				}
			}
		}
		char loadmsg[MAX_PATH + 8];
		sprintf(loadmsg, "Load to %s\n", filepath);
		printf(loadmsg);
		fclose(fp);	//ファイルを閉じる
	}
}

void CMapIO::Load(){	//読み込み
	FILE *fp = fopen(filepath, "rb");	//ファイルを開く(読み込み)
	if (fp == NULL){	//NULLが返ってきたらエラー
		MessageBox(NULL, "マップデータの読み込みに失敗しました。", "エラー", 0x00040010L);
		printf("Load : fopen error!\n");
	}

	else {
		for (int i = 0; i < MAP_SIZEY; i++){
			for (int j = 0; j < MAP_SIZEX; j++){
				fread(&mEditer.editmap[i][j], sizeof(int), 1, fp);
				if (mEditer.editmap[i][j] >= ECELLNUM::ESIZE){
					MessageBox(NULL, "マップデータが破損しているか、違うファイルです。", "エラー", 0x00040010L);
					for (int i = 0; i < MAP_SIZEY; i++){
						for (int j = 0; j < MAP_SIZEX; j++)
							mEditer.editmap[i][j] = ECELLNUM::ENONE;
					}
					char loadmsg[MAX_PATH + 8];
					sprintf(loadmsg, "Load to %s\n", filepath);
					printf(loadmsg);
					fclose(fp);	//ファイルを閉じる
					return;
				}
			}
		}
		char loadmsg[MAX_PATH + 8];
		sprintf(loadmsg, "Load to %s\n", filepath);
		printf(loadmsg);
		fclose(fp);	//ファイルを閉じる
	}
}

void CMapIO::Save(){	//書き込み
	FILE *fp = fopen(filepath, "wb");	//ファイルを開く(書き込み)
	if (fp == NULL){	//NULLが返ってきたらエラー発生
		MessageBox(NULL, "マップデータの保存に失敗しました。", "エラー", 0x00040010L);
		printf("Save : fopen error!\n");
	}

	else {
		for (int i = 0; i < MAP_SIZEY; i++){
			for (int j = 0; j < MAP_SIZEX; j++)
				fwrite(&mEditer.editmap[i][j], sizeof(int), 1, fp);
		}
		char savemsg[MAX_PATH + 8];
		sprintf(savemsg, "Save to %s\n", filepath);
		printf(savemsg);
		fclose(fp);	//ファイルを閉じる
	}
}

void CMapIO::LoadDialog(HWND hWnd){	//開く ダイアログ
	/*------ カレントディレクトリ 移動 ------*/
	GetCurrentDirectory(MAX_PATH, cdir);	//プログラムの ディレクトリを 取得
	SetCurrentDirectory(cdir);	//取得したディレクトリを カレントディレクトリに する

	static OPENFILENAME ofn;
	static TCHAR szPath[MAX_PATH];
	static TCHAR szFile[MAX_PATH];

	if (szPath[0] == TEXT('\0')){
		GetCurrentDirectory(MAX_PATH, szPath);	//プログラムの ディレクトリを 取得
	}
	if (ofn.lStructSize == 0){
		ofn.lStructSize = sizeof(OPENFILENAME);	//構造体の長さ (バイト単位)
		ofn.hwndOwner = hWnd;	//親ウインドウのハンドル | 特にない場合はNULL
		ofn.lpstrInitialDir = szPath;	//初期フォルダ位置
		ofn.lpstrFile = szFile;	//選択ファイル格納
		ofn.nMaxFile = MAX_PATH;	//lpstrFileの指す バッファのサイズ
		ofn.lpstrDefExt = TEXT("bin");	//ファイル名に 拡張子を付けなかった場合に付ける 拡張子の指定
		ofn.lpstrFilter = TEXT("マップデータ(*.bin)\0*.bin\0");	//ファイルの種類 プルダウンメニュー
		ofn.lpstrTitle = TEXT("開く");	//ウィンドウ タイトル
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;	//ダイアログボックス作成フラグ (既存のファイル名しか入力を許さない | 読み込み専用チェックボックス 非表示)
	}
	if (GetOpenFileName(&ofn)){	//保存先を指定した場合
		//MessageBox(hWnd, szFile, TEXT("ファイルを開く"), MB_OK);
		sprintf(filepath, "%s", szFile);
		CMapIO::Load();
	}

	SetCurrentDirectory(cdir);	//取得したディレクトリを カレントディレクトリに する
}

void CMapIO::SaveDialog(HWND hWnd){	//保存 ダイアログ
	/*------ カレントディレクトリ 移動 ------*/
	GetCurrentDirectory(MAX_PATH, cdir);	//プログラムの ディレクトリを 取得
	SetCurrentDirectory(cdir);	//取得したディレクトリを カレントディレクトリに する

	static OPENFILENAME ofn;
	static TCHAR szPath[MAX_PATH];
	static TCHAR szFile[MAX_PATH];

	if (szPath[0] == TEXT('\0')){
		GetCurrentDirectory(MAX_PATH, szPath);	//プログラムの ディレクトリを 取得
	}
	if (ofn.lStructSize == 0){
		ofn.lStructSize = sizeof(OPENFILENAME);	//構造体の長さ(バイト単位)
		ofn.hwndOwner = hWnd;	//親ウインドウのハンドル | 特にない場合はNULL
		ofn.lpstrInitialDir = szPath;	//初期フォルダ位置
		ofn.lpstrFile = szFile;	//選択ファイル格納
		ofn.nMaxFile = MAX_PATH;	//lpstrFileの指す バッファのサイズ
		ofn.lpstrDefExt = TEXT("bin");	//ファイル名に 拡張子を付けなかった場合に付ける 拡張子の指定
		ofn.lpstrFilter = TEXT("マップデータ(*.bin)\0*.bin\0");	//ファイルの種類 プルダウンメニュー
		ofn.lpstrTitle = TEXT("名前をつけて保存");	//ウィンドウ タイトル
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;	//ダイアログボックス作成フラグ (有効なパス及びファイル名でなければ入力を許さない | ファイルの上書き確認)
	}
	if (GetSaveFileName(&ofn)){	//保存先を指定した場合
		sprintf(filepath, "%s", szFile);
		CMapIO::Save();
	}
	SetCurrentDirectory(cdir);	//取得したディレクトリを カレントディレクトリに する
}

void CRankingIO::Load(){
	FILE *fp = fopen(RANKING_PATH, "rb");	//ファイルを開く(書き込み)
	if (fp == NULL){	//ファイルがなければ、空のファイルを作成
		FILE *nfp = fopen(RANKING_PATH, "wb");	//ファイルを開く(書き込み)
		for (int i = 0; i < 3; i++){
			sprintf(mRanking.mRanking[i].n, "???");
			mRanking.mRanking[i].s = 0;
			fwrite(&mRanking.mRanking[i].n, sizeof(int), 1, nfp);
			fwrite(&mRanking.mRanking[i].s, sizeof(int), 1, nfp);
		}
		fclose(nfp);	//ファイルを閉じる
	}
	else {
		for (int i = 0; i < 3; i++){
			fread(&mRanking.mRanking[i].n, sizeof(int), 1, fp);
			fread(&mRanking.mRanking[i].s, sizeof(int), 1, fp);
		}
		char savemsg[MAX_PATH + 8];
		sprintf(savemsg, "Load to %s\n", RANKING_PATH);
		printf(savemsg);
		fclose(fp);	//ファイルを閉じる
	}
}

void CRankingIO::Save(){
	FILE *fp = fopen(RANKING_PATH, "wb");	//ファイルを開く(書き込み)
	if (fp == NULL){	//NULLが返ってきたらエラー発生
		MessageBox(NULL, "ランキングデータの保存に失敗しました。", "エラー", 0x00040010L);
		printf("Save : fopen error!\n");
	}

	else {
		for (int i = 0; i < 3; i++){
			fwrite(&mRanking.mRanking[i].n, sizeof(int), 1, fp);
			fwrite(&mRanking.mRanking[i].s, sizeof(int), 1, fp);
		}
		char savemsg[MAX_PATH + 8];
		sprintf(savemsg, "Save to %s\n", RANKING_PATH);
		printf(savemsg);
		fclose(fp);	//ファイルを閉じる
	}
}
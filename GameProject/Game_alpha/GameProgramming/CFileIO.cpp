#include "CFileIO.h"
extern CEditer mEditer;

char cdir[MAX_PATH];	//ディレクトリ
char filepath[MAX_PATH];	//開く / 保存する ファイルの フルパス

void CFileIO::Init(){

}

void CFileIO::Update(){
	
}

void CMapIO::MapLoad(char map){

}

void CMapIO::Load(){	//読み込み
	FILE *fp = fopen(filepath, "rb");	//ファイルを開く(読み込み)
	if (fp == NULL) //NULLが返ってきたらエラー
		printf("Load : fopen error!\n");

	else {
		for (int i = 0; i < EDITMAP_SIZEY; i++){
			for (int j = 0; j < EDITMAP_SIZEX; j++){
				fread(&mEditer.editmap[i][j], sizeof(int), 1, fp);
				if (mEditer.editmap[i][j] >= mEditer.ESIZE){
					MessageBox(NULL, "マップデータが破損しているか、違うファイルです。", "エラー", 0x00040010L);
					for (int i = 0; i < EDITMAP_SIZEY; i++){
						for (int j = 0; j < EDITMAP_SIZEX; j++)
							mEditer.editmap[i][j] = mEditer.ENONE;
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
	if (fp == NULL) //NULLが返ってきたらエラー発生
		printf("Save : fopen error!\n");

	else {
		for (int i = 0; i < EDITMAP_SIZEY; i++){
			for (int j = 0; j < EDITMAP_SIZEX; j++)
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
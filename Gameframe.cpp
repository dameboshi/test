#include "DxLib.h"
#include "map.h"
#include "gameframe.h"
#include "common.h"
#include "keyconfig.h"
#include "player.h"
#include "effect.h"
using namespace std;

//padコントローラー
//クラスの配列で宣言すればいいのでは？
PAD pad1;
PAD pad2;
PAD pad3;
PAD pad4;

void GameFrame::doMainLoop(int scmode){
	ChangeWindowMode(scmode);
	if (DxLib_Init() == -1)return;
	SetMainWindowText("Falling Fight ver1.0");
	SetDrawScreen(DX_SCREEN_BACK);
	setIdouHosei();

	//フォント作成
	largefont = CreateFontToHandle(0, 100, 9, DX_FONTTYPE_ANTIALIASING_EDGE);
	smallfont = CreateFontToHandle(0, 21, 9, DX_FONTTYPE_ANTIALIASING_EDGE);
	mfont = CreateFontToHandle(0, 46, 9, DX_FONTTYPE_ANTIALIASING_EDGE);

	try{
		loadfile();					//各ファイルの読み込み
	}
	catch (int errcode){
		MessageBox(NULL, "ファイル読み込みエラー", "メッセージ", MB_OK);
		return;
	}

	SetBackgroundColor(152, 251, 152);
	GetScreenState(&Sx, &Sy, &Cb);

	setGameState(GAME_TITLE);
	
	
	//メインループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		pad2.PadInput(DX_INPUT_PAD2);
		pad3.PadInput(DX_INPUT_PAD3);
		pad4.PadInput(DX_INPUT_PAD4);
		pad1.PadInput(DX_INPUT_KEY_PAD1);

		ClsDrawScreen();
		switch (gstate)
		{
		case GAME_TITLE:
			drawGameTitle();
			break;
		case GAME_SELECT:
			drawGameSelect();
			break;
		case GAME_MAIN:
			drawGameMain();
			break;
		case GAME_OVER:
			drawGameOver();
			break;
		case GAME_CLEAR:
			drawGameClear();
			break;
		default:
			break;
		}
		ScreenFlip();
		animcounter++;
	}

	DxLib_End();
}

//gstateをセットする（画面切り替え）
GAMESTATE GameFrame::setGameState(GAMESTATE state){
	if (gstate != state){
		gstate = state;
		starttime = GetNowCount();
		if (gstate == GAME_MAIN) Initstage();	//initStage関数の呼び出し
	}
	return gstate;
}

//タイトルの表示
void GameFrame::drawGameTitle(){
	int col = GetColor(255, 0, 255);

	if (pad1.PadGet(DOWN) == 1){
		starttime = GetNowCount();
	}

	int a = GetNowCount() - starttime;
	if (GetNowCount() - starttime < 255){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
		//int w = GetDrawStringWidthToHandle("PUSH BUTTON", 12, smallfont);
		//if(a % 840 > 420)
		DrawGraph(320 - sx1 / 2, 300, buttonhandle, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
	else{
		//int w = GetDrawStringWidthToHandle("PUSH BUTTON", 12, smallfont);
		//if (a % 840 > 420)
		DrawGraph(320 - sx1 / 2, 300, buttonhandle, TRUE);
	}

	//int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//if (key & PAD_INPUT_A) setGameState(GAME_MAIN);
}

void GameFrame::drawGameSelect(){

}

//ゲーム本体画面の表示
void GameFrame::drawGameMain(){
	for (int i = 0; i < EFFECT_MAX; i++){
		effect[i].Draw();
		effect[i].Move();
	}
	//if (pad1.PadGet(B_1) == 1)setGameState(GAME_TITLE);
}

int GameFrame::MainLogo(){

	if (logo_state == 0 && GetNowCount() - starttime < 1200){
		int w = GetDrawStringWidthToHandle("ROUND  ", 7, largefont);
		DrawFormatStringToHandle(220 - w / 2, 160, WHITE,largefont,"ROUND %d",nowround);
		DrawStringToHandle(65 - 15, 65 - PLAYER_SIZE, "1P", WHITE, smallfont);
		DrawStringToHandle(475 - 65 -15, 65 - PLAYER_SIZE, "2P", WHITE, smallfont);
		DrawStringToHandle(65 -15, (Sy - 65) - PLAYER_SIZE, "3P", WHITE, smallfont);
		DrawStringToHandle(475 - 65-15, (Sy - 65) - PLAYER_SIZE, "4P", WHITE, smallfont);
	}
	if (logo_state == 1 && GetNowCount() - starttime < 1200){
		int w = GetDrawStringWidthToHandle("GAME SET", 7, largefont);
		DrawFormatStringToHandle(220 - w / 2, 160, WHITE, largefont, "GAME SET", nowround);
	}

	if (GetNowCount() - starttime > 1200)return 1;
	else return 0;
}

//ゲームクリア画面の表示
void GameFrame::drawGameClear(){
	//int col = GetColor(0, 255, 255);
	//int w = GetDrawStringWidthToHandle("GAMECLEAR", 9, largefont);
	//DrawStringToHandle(320 - w / 2, 160, "GAMECLEAR", col, largefont);

	if (GetNowCount() - starttime > 5000){
		setGameState(GAME_TITLE);
	}
}
//ゲームオーバー画面の表示
void GameFrame::drawGameOver(){
	int col = GetColor(255, 0, 0);
	int w = GetDrawStringWidthToHandle("GAMEOVER", 8, largefont);
	DrawStringToHandle(320 - w / 2, 160, "GAMEOVER", col, largefont);

	if (GetNowCount() - starttime > 5000){
		setGameState(GAME_TITLE);
	}
}

unsigned int GameFrame::GetAnimCnt(){
	return animcounter;
}

//staticなので実体が必要
unsigned int GameFrame::animcounter = 0;

//補正移動量を求める
void GameFrame::setIdouHosei(){
	float frametime = 0;
	unsigned int s = GetNowCount();		//計測開始時間をsに代入
	for (int i = 0; i < 30; i++)
	{
		ScreenFlip();
		unsigned int e = GetNowCount();	//計測終了時間をeに代入
		frametime = frametime + e - s;
		s = e;
	}
	frametime = frametime / 30;	//30回採取した経過時間の平均を取る
	//移動量0～19の補正値を配列変数にセット
	for (int i = 1; i<20; i = i + 1){
		idouryou[i] = i / frametime * 16.67;
	}
}
//補正後の移動量を返す
float GameFrame::IdouHosei(int idou){
	if (idou<0){
		return(-idouryou[-idou]);
	}
	else {
		return(idouryou[idou]);
	}
}

//idouryouの実体
float GameFrame::idouryou[20];

void GameFrame::Initstage(){
}

void GameFrame::setState(GAMESTATE state){
	this->gstate = state;
}

int GameFrame::FadeOut(){
	return 0;
}
void GameFrame::MakeFrame(int x, int y,int height,int width){
	DrawGraph(x, y, framehandle[0], TRUE);
	for (int i = 1; i < width; i++)DrawGraph(x + i*32, y, framehandle[1], TRUE);
	DrawGraph(x + width * 32, y, framehandle[2], TRUE);
	for (int i = 1; i < height; i++)DrawGraph(x , y + i*32, framehandle[3], TRUE);
	DrawGraph(x, y + height * 32, framehandle[6], TRUE);
	for (int i = 1; i < width; i++)DrawGraph(x + i * 32, y + 32*height, framehandle[7], TRUE);
	for (int i = 1; i < height; i++)DrawGraph(x+width*32, y + i*32, framehandle[5], TRUE);
	DrawGraph(x + width * 32, y + height*32, framehandle[8], TRUE);
}


#include "DxLib.h"
#include "gameframe.h"
#include "animdraw.h"
#include "map.h"
#include "keyconfig.h"
#include "player.h"
#include "select.h"
#include "result.h"
#include "Item.h"

MAP map;
Bomb bakudan[10];
HoverItem hover[10];
HeavyItem heavy[10];
PortableBomb potablebakudan[10];
Select select1;
Pause pause;
Result *result1;
Player1 *player1;
Player2 *player2;
Player3 *player3;
Player4 *player4;

class Fight :public GameFrame{
	int timer;
	int mainend_flag;
	int continue_flag;//ゲームを継続させるフラグ
	void drawGameTitle();
	void drawGameSelect();
	void loadfile()throw(int);
	void drawGameMain();
	void drawGameClear();
	void InitStage();
	void MakeBomb(int,int);
	void MakeHeavy(int, int);
	void MakeHover(int, int);
	void MakePortaBomb(int, int);
	void ItemInit();
	void RandomItem(int);
};

void Fight::drawGameTitle(){
	
	GameFrame::drawGameTitle();
	
	DrawGraph(320 - sx / 2, 125, logohandle, TRUE);
	
	if (pad1.PadGet(B_1) == 1){
		player1 = new Player1(65, 65, DOWN);
		player2 = new Player2(330 - 65, 65, DOWN);
		player3 = new Player3(65, 330 - 65, UP);
		player4 = new Player4(330 - 65, 330 - 65, UP);
		pause.Init();
		InitStage();
		select1.Init();
		GameFrame::setGameState(GAME_SELECT);
		//setGameState(GAME_SELECT);
	}
}

void Fight::drawGameSelect(){
	/*
	for (int i = 0; i < 8; i++){
		DrawGraph(i*32, 0, Bomb::ghandle[i], TRUE);
	}
	*/
	GameFrame::drawGameSelect();
	select1.Calc();
	int t = GetNowCount() - starttime;
	if (GetNowCount() - starttime < 255){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, t);
		MakeFrame(32, 32, 9, 11);
		MakeFrame(416, 32, 9, 5);
		select1.Draw(t);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
	else{
		MakeFrame(32, 32, 9, 11);
		MakeFrame(416, 32, 9, 5);
		select1.Draw(t);
	}

	//ボタンを押した際の遷移
	if (pad1.PadGet(B_1) == 1){
		if (select1.GetState() == NEXT){
			InitStage();
			playernum = select1.GetPlayerNumber();
			nowround = 1;
			GameFrame::setGameState(GAME_MAIN);
		}
		else if (select1.GetState() == BACK){
			delete player1;
			delete player2;
			delete player3;
			delete player4;
			GameFrame::setGameState(GAME_TITLE);
		}
	}
}

void Fight::drawGameMain(){
	GameFrame::drawGameMain();
	if (GetNowCount() - starttime < 255){
		int t = GetNowCount() - starttime;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, t);
		map.Draw();
		player1->Draw();
		player2->Draw();
		player3->Draw();
		player4->Draw();
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
	else{
		map.Draw();
		player1->Draw();
		player2->Draw();
		player3->Draw();
		player4->Draw();
	}

	pause.Draw();
	pause.Move();


	if (pause.Start() == 0){
	RandomItem(450);

	for (int i = 0; i < 10; i++){
		if (bakudan[i].Getalive()){
			bakudan[i].Draw();
			bakudan[i].Move();
		}
		bakudan[i].BombExplosion();
		hover[i].Draw();
		hover[i].Move();
		heavy[i].Draw();
		heavy[i].Move();
		potablebakudan[i].Draw();
		potablebakudan[i].Move();
	}

		if (MainLogo() == 1){
			player1->Calc();
			player1->Operate(1);

			switch (select1.GetPlayerNumber())
			{
			case 2:
				player2->Calc();
				player2->Operate(2);
				break;
			case 3:
				player2->Calc();
				player2->Operate(2);
				player3->Calc();
				player3->Operate(3);
				break;
			case 4:
				player2->Calc();
				player2->Operate(2);
				player3->Calc();
				player3->Operate(3);
				player4->Calc();
				player4->Operate(4);
				break;
			default:
				break;
			}
			int direction1 = player1->GetDirection();
			int direction2 = player2->GetDirection();
			int direction3 = player3->GetDirection();
			int direction4 = player4->GetDirection();

			//プレイヤー同士の衝突
			player1->PlayerHitPlayer(player2->GetX(), player2->GetY(), player2->GetAlive(), direction2);
			player1->PlayerHitPlayer(player3->GetX(), player3->GetY(), player3->GetAlive(), direction3);
			player1->PlayerHitPlayer(player4->GetX(), player4->GetY(), player4->GetAlive(), direction4);
			player1->InitHitTimer();
			player2->PlayerHitPlayer(player1->GetX(), player1->GetY(), player1->GetAlive(), direction1);
			player2->PlayerHitPlayer(player3->GetX(), player3->GetY(), player3->GetAlive(), direction3);
			player2->PlayerHitPlayer(player4->GetX(), player4->GetY(), player4->GetAlive(), direction4);
			player2->InitHitTimer();
			player3->PlayerHitPlayer(player1->GetX(), player1->GetY(), player1->GetAlive(), direction1);
			player3->PlayerHitPlayer(player2->GetX(), player2->GetY(), player2->GetAlive(), direction2);
			player3->PlayerHitPlayer(player4->GetX(), player4->GetY(), player4->GetAlive(), direction4);
			player3->InitHitTimer();
			player4->PlayerHitPlayer(player1->GetX(), player1->GetY(), player1->GetAlive(), direction1);
			player4->PlayerHitPlayer(player3->GetX(), player3->GetY(), player3->GetAlive(), direction3);
			player4->PlayerHitPlayer(player2->GetX(), player2->GetY(), player2->GetAlive(), direction2);
			player4->InitHitTimer();

			//一人が生き残るまで続く
			if (mainend_flag == 0 && continue_flag == 0){
				if ((player1->GetAlive() + player2->GetAlive() + player3->GetAlive() + player4->GetAlive()) == 1){

					if (player1->GetAlive())player1->SetWinnum(1);
					else if (player2->GetAlive())player2->SetWinnum(1);
					else if (player3->GetAlive())player3->SetWinnum(1);
					else player4->SetWinnum(1);

					logo_state = 1;
					starttime = GetNowCount();
					timer = 0;
					continue_flag = 1;

					if (player1->GetWinnum() == select1.GetRoundNumber() || player2->GetWinnum() == select1.GetRoundNumber() || player3->GetWinnum() == select1.GetRoundNumber() || player4->GetWinnum() == select1.GetRoundNumber()){
						mainend_flag = 1;
						
					}
					else{
						mainend_flag = 2;
						logo_state = 1;
						starttime = GetNowCount();
						timer = 0;
						continue_flag = 1;
					}
				}
				else if (player1->GetAlive() + player2->GetAlive() + player3->GetAlive() + player4->GetAlive() == 0){
					logo_state = 1;
					starttime = GetNowCount();
					timer = 0;
					continue_flag = 1;
					mainend_flag = 3;
				}
			}


		}
		if (mainend_flag == 1 && timer > 60){
			InitStage();
			result1 = new Result(player1->GetWinnum(), player2->GetWinnum(), player3->GetWinnum(), player4->GetWinnum(), select1.GetRoundNumber());
			GameFrame::setGameState(GAME_CLEAR);
		}
		else if (mainend_flag == 2 && timer > 60){
			nowround++;
			InitStage();
			GameFrame::setGameState(GAME_MAIN);
		}
		else if (mainend_flag == 3 && timer > 60){
			nowround++;
			InitStage();
			GameFrame::setGameState(GAME_MAIN);
		}

		//Pause
		if (pad1.PadGet(B_2) == 1){
			pause.SetState(1);
		}
	}

	if (pause.GetState() == 2){
		InitStage();
		GameFrame::setGameState(GAME_TITLE);
	}

	timer++;
	itemtimer++;
}

void Fight::loadfile()throw(int){
	Bomb::Load();
	//WeightItem::Load();
	Fontload();
	logohandle = LoadGraph("media/logo1.png");
	LoadDivGraph("media/frame.png", 9, 3, 3, 32, 32, framehandle);
	GetGraphSize(logohandle, &sx, &sy);
	buttonhandle = LoadGraph("media/push.png");
	GetGraphSize(buttonhandle, &sx1, &sy1);
	map.Set(15, 15, select1.GetCountMax());
	map.Mapload(0);
}

void Fight::InitStage(){
	GameFrame::Initstage();
	ItemInit();
	starttime = GetNowCount();
	continue_flag = 0;
	logo_state = 0;
	timer = 0;
	itemtimer = 0;
	player1->Init(65, 65, DOWN);
	player2->Init(475 - 65, 65, DOWN);
	player3->Init(65, Sy - 65, UP);
	player4->Init(475 - 65, Sy - 65, UP);
	if (select1.GetPlayerNumber() <= 2){
		player3->SetAlive(FALSE);
		player4->SetAlive(FALSE);
	}
	else if (select1.GetPlayerNumber() == 3)player4->SetAlive(FALSE);

	mainend_flag = 0;
	map.Set(15, 15, select1.GetCountMax());
}

void Fight::drawGameClear(){
	GameFrame::drawGameClear();
	result1->Calc(player1->GetWinnum(), player2->GetWinnum(), player3->GetWinnum(), player4->GetWinnum());
	int w2 = GetDrawStringWidthToHandle("RESULT", 6, mfont);

	if (GetNowCount() - starttime < 255){
		int t = GetNowCount() - starttime;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, t);
		DrawFormatStringToHandle(320 - w2 / 2, 32, BLACK, mfont, "RESULT");
		result1->Draw(player1->GetWinnum(), player2->GetWinnum(), player3->GetWinnum(), player4->GetWinnum(), select1.GetPlayerNumber());
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
	else{
		DrawFormatStringToHandle(320 - w2 / 2, 32, BLACK, mfont, "RESULT");
		result1->Draw(player1->GetWinnum(), player2->GetWinnum(), player3->GetWinnum(), player4->GetWinnum(), select1.GetPlayerNumber());
	}
	
	timer++;

	if (pad1.PadGet(B_1) == 1 || GetNowCount() - starttime > 5000){
		delete player1;
		delete player2;
		delete player3;
		delete player4;
		delete result1;
		GameFrame::setGameState(GAME_TITLE);
	}
}

void Fight::MakeBomb(int x, int y){
	for (int i = 0; i < 10; i++){
		if (!bakudan[i].Getalive()){
			for (int k = 0; k < 4; k++){
				if (map.MapCountCheck(x*32, y*32) == 1){
					x++;
					y++;
				}
				else{
					break;
				}
			}
			bakudan[i].Init(x*32, y*32);
			break;
		}
	}
}
void Fight::MakeHeavy(int x, int y){
	for (int i = 0; i < 10; i++){
		if (heavy[i].GetState()==0){
			for (int k = 0; k < 4; k++){
				if (map.MapCountCheck(x * 32, y * 32) == 1){
					x++;
					y++;
				}
				else{
					break;
				}
			}
			heavy[i].Make(x * 32, y * 32);
			break;
		}
	}
}
void Fight::MakeHover(int x, int y){
	for (int i = 0; i < 10; i++){
		if (hover[i].GetState() == 0){
			for (int k = 0; k < 4; k++){
				if (map.MapCountCheck(x * 32-1, y * 32-1) == 1){
					x++;
					y++;
				}
				else{
					break;
				}
			}
			hover[i].Make(x * 32, y * 32);
			break;
		}
	}
}
void Fight::MakePortaBomb(int x, int y){
	for (int i = 0; i < 10; i++){
		if (potablebakudan[i].GetState() == 0){
			for (int k = 0; k < 4; k++){
				if (map.MapCountCheck((x * 32) - 1, (y * 32) - 1) == 1){
					x++;
					y++;
				}
				else{
					break;
				}
			}
			potablebakudan[i].Make(x * 32, y * 32);
			break;
		}
	}
}

void Fight::RandomItem(int max){
	if ((itemtimer % max) == max-1){
		switch (GetRand(7)){
		case 0:
			MakeBomb(GetRand(12)+1,GetRand(12)+1);
			MakePortaBomb(GetRand(12) + 1, GetRand(12) + 1);
			break;
		case 1:
			MakeHeavy(GetRand(12) + 1, GetRand(12) + 1);
			break;
		case 2:
			MakeHover(GetRand(12) + 1, GetRand(12) + 1);
			break;
		case 3:
			MakeHeavy(GetRand(12) + 1, GetRand(12) + 1);
			MakeBomb(GetRand(12) + 1, GetRand(12) + 1);
			break;
		case 4:
			MakeHeavy(GetRand(12) + 1, GetRand(12) + 1);
			MakeHover(GetRand(12) + 1, GetRand(12) + 1);
			break;
		case 5:
			MakePortaBomb(GetRand(12) + 1, GetRand(12) + 1);
			break;
		case 6:
			MakePortaBomb(GetRand(12) + 1, GetRand(12) + 1);
			MakeHeavy(GetRand(12) + 1, GetRand(12) + 1);
			break;
		default:
			MakeBomb(GetRand(12) + 1, GetRand(12) + 1);
			MakeHover(GetRand(12) + 1, GetRand(12) + 1);
			break;
		}
	}
}

void Fight::ItemInit(){
	for (int i = 0; i < 10; i++){
		bakudan[i].~Bomb();
		hover[i].Init();
		heavy[i].Init();
		potablebakudan[i].Init();
	}
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Fight *p = new Fight();
	p->doMainLoop(TRUE);
	delete p;
}
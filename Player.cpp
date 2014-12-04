#include "player.h"
#include "effect.h"
#include "gameframe.h"
#include "keyconfig.h"
#include "common.h"
#include "animdraw.h"
#include "map.h"
#include "Item.h"

void Player::Init(int x,int y,int direction){
	this->x = x;
	this->y = y;
	vx = vy = 0;
	this->direction = direction;
	timer = 0;
	nowitem = 0;
	alive = TRUE;
	wall_switch = TRUE;
	MoveFlag = TRUE;
	HitTimer = 0;
	itemstate = 0;
	speed = PLAYER_SPEED;
	bagucheck = 0;
}
void Player::InitWin(){
	this->winnum = 0;
}

void Player::Calc(){
	if (alive == TRUE){

		//-方向-//
		switch (direction)
		{
		case DOWN:
			vx = 0;
			vy = speed;
			break;
		case LEFT:
			vx = -speed;
			vy = 0;
			break;
		case RIGHT:
			vx = speed;
			vy = 0;
			break;
		case UP:
			vx = 0;
			vy = -speed;
			break;
		default:
			vx = vy = 0;
			break;
		}


		//---マップとのあたり判定---//
		//左
		if (bagucheck < 1 && wall_switch == TRUE){
			if ((MAP::MapCheck(x - PLAYER_SIZE / 2 + PLAYER_ZURE, y - PLAYER_SIZE / 2 + PLAYER_ZURE) == 1) ||//左上
				(MAP::MapCheck(x - PLAYER_SIZE / 2 + PLAYER_ZURE, y) == 1) ||//左真ん中
				(MAP::MapCheck(x - PLAYER_SIZE / 2 + PLAYER_ZURE, y + PLAYER_SIZE / 2 - PLAYER_ZURE) == 1))//左下
			{

				bagucheck++;
				//x = (x / 32) * 32;
				Effect::MakeExplosion(x, y);
				x -= (vx - 1);
				//vx = 0;
				direction = RIGHT;
				timer = 0;
				wall_switch = FALSE;
			}
			//右
			if ((MAP::MapCheck(x + PLAYER_SIZE / 2 - PLAYER_ZURE, y - PLAYER_SIZE / 2 + PLAYER_ZURE) == 1) ||//右上
				(MAP::MapCheck(x + PLAYER_SIZE / 2 - PLAYER_ZURE, y) == 1) ||//右真ん中
				(MAP::MapCheck(x + PLAYER_SIZE / 2 - PLAYER_ZURE, y + PLAYER_SIZE / 2 - PLAYER_ZURE) == 1))//右下
			{

				bagucheck++;
				//x = (x / 32) * 32;
				x -= (vx + 1);
				//vx = 0;
				direction = LEFT;
				timer = 0;
				wall_switch = FALSE;
			}

			//上
			if ((MAP::MapCheck(x + PLAYER_SIZE / 2 - PLAYER_ZURE, y - PLAYER_SIZE / 2 + PLAYER_ZURE) == 1) ||//上右
				(MAP::MapCheck(x, y - PLAYER_SIZE / 2 + PLAYER_ZURE) == 1) ||//上真ん中
				(MAP::MapCheck(x - PLAYER_SIZE / 2 + PLAYER_ZURE, y - PLAYER_SIZE / 2 + PLAYER_ZURE) == 1))//上左
			{

				bagucheck++;
				//y = (y / 32) * 32;
				y -= (vy - 1);
				//vy = 0;
				direction = DOWN;
				timer = 0;
				wall_switch = FALSE;
				
			}
			//下
			if ((MAP::MapCheck(x + PLAYER_SIZE / 2 - PLAYER_ZURE, y + PLAYER_SIZE / 2 - PLAYER_ZURE) == 1) ||//下右
				(MAP::MapCheck(x, y + PLAYER_SIZE / 2 - PLAYER_ZURE) == 1) ||//下真ん中
				(MAP::MapCheck(x - PLAYER_SIZE / 2 + PLAYER_ZURE, y + PLAYER_SIZE / 2 - PLAYER_ZURE) == 1))//下左
			{

				bagucheck++;
				//y = (y / 32) * 32;
				y -= (vy + 1);
				//vy = 0;
				direction = UP;
				timer = 0;
				wall_switch = FALSE;
				
			}
		}

		if (bagucheck >= 1)MAP::MapCountReduce(x, y);
		bagucheck = 0;

		//アイテムを取るあたりの処理
		for (int i = 0; i < 10; i++){
			if (hover[i].GetState() == 1 && hover[i].Catch(x, y)){
				itemstate = 1;
				nowitem = i;
			}
			if (heavy[i].GetState() == 1 && heavy[i].Catch(x, y)){
				itemstate = 2;
				nowitem = i;
			}
			if (potablebakudan[i].GetState() == 1 && potablebakudan[i].Catch(x, y) && bakudanstate == 0){
				bakudanstate = 1;
				nowitem = i;
			}

			if (potablebakudan[i].GetState() == 3){
				bakudanstate = 0;
			}

			if (itemstate != 0){
				if (hover[i].Catch(x, y) || heavy[i].Catch(x, y)){
					if (hover[nowitem].GetState() == 2){
						hover[nowitem].Init();
					}
					if (heavy[nowitem].GetState() == 2){
						heavy[nowitem].Init();
					}
				}
			}
		}
		if (hover[nowitem].GetState() == 3 && itemstate != 0){
			itemstate = 0;
		}
		if (heavy[nowitem].GetState() == 3 && itemstate != 0){
			itemstate = 0;
		}

		//パネルを踏むと数字が減る
		if (MAP::MapCheck(x, y) == 0 && panel_On == TRUE){

			switch (itemstate)
			{
			case 0:
				MAP::MapCountReduce(x, y);
				break;
			case 1:
				break;
			case 2:
				MAP::MapCountReduce(x, y, 2);
				break;
			default:
				MAP::MapCountReduce(x, y);
				break;
			}

			mapdata_p = (int)&mapdata1[x / MAPSIZE][y / MAPSIZE].data;
			panel_On = FALSE;
		}
		//別のパネルに移らないと数字減らないっすよ
		if (mapdata_p != (int)&mapdata1[x / MAPSIZE][y / MAPSIZE].data)panel_On = TRUE;

		//カウントが0になったら死にます
		if (itemstate != 1){
			if (MAP::MapCountCheck(x, y) == 0 && panel_On == TRUE){
				Effect::MakeExplosion(x, y);
				alive = FALSE;
				x = y = 1000;
				direction = 5;
			}
		}

	}

	if (MoveFlag == FALSE && HitTimer >= 15)MoveFlag = TRUE;

	//---速度を座標に加える---//
	x += vx;
	y += vy;

	timer++;
	HitTimer++;
}

void Player::Draw(int color){
	for (int i = 0; i < EFFECT_MAX; i++){
		effect[i].Draw();
		effect[i].Move();
	}
	//プレイヤーキャラの表示
	if (alive == TRUE){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
		DrawBox(x - PLAYER_SIZE / 2, y - PLAYER_SIZE / 2, x + PLAYER_SIZE / 2, y + PLAYER_SIZE / 2, color, 1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
	if (itemstate != 0){
		//DrawGraph(score_x + 80, score_y, Bomb::ghandle[4+(itemstate-1)], TRUE);
		DrawExtendGraph(score_x + 80, score_y, score_x + 80 + 16, score_y + 16, Bomb::ghandle[3+(itemstate)], TRUE);
	}
	if (bakudanstate != 0){
		//DrawGraph(score_x + 80, score_y, Bomb::ghandle[4+(itemstate-1)], TRUE);
		DrawExtendGraph(score_x + 100, score_y, score_x + 100 + 16, score_y + 16, Bomb::ghandle[6], TRUE);
	}
}

void Player1::Draw(){
	Player::Draw(RED);
	DrawFormatStringFToHandle(score_x + 30, score_y - 10, BLACK, Font3, "勝ち数");
	DrawFormatStringFToHandle(score_x + 70, score_y - 10, BLACK, Font3, "アイテム");
	DrawFormatStringFToHandle(score_x, score_y, BLACK, CountFont, "1P  %d",winnum);
}
void Player2::Draw(){
	Player::Draw(BLUE);
	DrawFormatStringFToHandle(score_x, score_y , BLACK, CountFont, "2P  %d",winnum);
}
void Player3::Draw(){
	Player::Draw(GREEN);
	if (playernum > 2){
		DrawFormatStringFToHandle(score_x, score_y , BLACK, CountFont, "3P  %d", winnum);
	}
}
void Player4::Draw(){
	Player::Draw(PURPLE);
	if (playernum > 3){
		DrawFormatStringFToHandle(score_x, score_y , BLACK, CountFont, "4P  %d", winnum);
	}
}

//プレイヤー同士の衝突
void Player::PlayerHitPlayer(int x1, int y1,bool alive1,int direction1){
	if (alive1 != FALSE && HitTimer1 < 1){
		if (HitBox(x-PLAYER_SIZE/2, y-PLAYER_SIZE/2, x + PLAYER_SIZE/2, y + PLAYER_SIZE/2,
			x1 - PLAYER_SIZE / 2, y1 - PLAYER_SIZE / 2, x1 + PLAYER_SIZE/2, y1 + PLAYER_SIZE/2) && HitTimer > 4){
			Effect::MakeExplosion2(x, y);
			switch (direction1)
			{
			case UP:
				//y -= 2;
				direction = UP;
				if (x + PLAYER_SIZE/2 < x1 - PLAYER_SIZE/2)direction = LEFT;
				if (x - PLAYER_SIZE / 2 > x1 + PLAYER_SIZE / 2)direction = RIGHT;
				break;
			case DOWN:
				//y += 2;
				direction = DOWN;
				if (y1 + PLAYER_SIZE / 2 > y)direction = Hanten(direction);
				if (x + PLAYER_SIZE / 2 < x1 - PLAYER_SIZE / 2)direction = LEFT;
				if (x - PLAYER_SIZE / 2 > x1 + PLAYER_SIZE / 2)direction = RIGHT;
				break;
			case RIGHT:
				//x += 2;
				direction = RIGHT;
				if (y + PLAYER_SIZE / 2 < y1 - PLAYER_SIZE / 2)direction = UP;
				if (y - PLAYER_SIZE / 2 > y1 + PLAYER_SIZE / 2)direction = DOWN;
				break;
			case LEFT:
				//x -= 2;
				direction = LEFT;
				if (y + PLAYER_SIZE / 2 < y1 - PLAYER_SIZE / 2)direction = UP;
				if (y - PLAYER_SIZE / 2 > y1 + PLAYER_SIZE / 2)direction = DOWN;
				break;
			default:
				break;
			}
			HitTimer1++;
			HitTimer = 0;
			MoveFlag = FALSE;
		}
	}
}

void Player::Operate(int num){
	//壁にぶつかったとき少し行動不能になるための処理
	if (MoveFlag == TRUE){
		if (wall_switch == TRUE){
			switch (num)
			{
				//衝突の際の処理
			case 1:
				if (pad1.PadGet(DOWN) == 1)direction = DOWN;
				if (pad1.PadGet(LEFT) == 1)direction = LEFT;
				if (pad1.PadGet(RIGHT) == 1)direction = RIGHT;
				if (pad1.PadGet(UP) == 1)direction = UP;

				if (bakudanstate == 1 && pad1.PadGet(B_1) == 1){
					MakeBomb1(x / 32, y / 32);
					bakudanstate = 0;
				}
				break;
			case 2:
				if (pad2.PadGet(DOWN) == 1)direction = DOWN;
				if (pad2.PadGet(LEFT) == 1)direction = LEFT;
				if (pad2.PadGet(RIGHT) == 1)direction = RIGHT;
				if (pad2.PadGet(UP) == 1)direction = UP;
				if (bakudanstate == 1 && pad2.PadGet(B_1) == 1){
					MakeBomb1(x / 32, y / 32);
					bakudanstate = 0;
				}
				break;
			case 3:
				if (pad3.PadGet(DOWN) == 1)direction = DOWN;
				if (pad3.PadGet(LEFT) == 1)direction = LEFT;
				if (pad3.PadGet(RIGHT) == 1)direction = RIGHT;
				if (pad3.PadGet(UP) == 1)direction = UP;
				if (bakudanstate == 1 && pad3.PadGet(B_1) == 1){
					MakeBomb1(x / 32, y / 32);
					bakudanstate = 0;
				}
				break;
			case 4:
				if (pad4.PadGet(DOWN) == 1)direction = DOWN;
				if (pad4.PadGet(LEFT) == 1)direction = LEFT;
				if (pad4.PadGet(RIGHT) == 1)direction = RIGHT;
				if (pad4.PadGet(UP) == 1)direction = UP;
				if (bakudanstate == 1 && pad4.PadGet(B_1) == 1){
					MakeBomb1(x / 32, y / 32);
					bakudanstate = 0;
				}
				break;
			default:
				break;
			}

		}
		else{
			if (timer >= 4)wall_switch = TRUE;
		}
	}
}
//---セッターとゲッター---///

int Player::GetX(){
	return x;
}
int Player::GetY(){
	return y;
}
int Player::GetVx(){
	return vx;
}
int Player::GetVy(){
	return vy;
}
int Player::GetAlive(){
	return alive;
}
int Player::GetDirection(){
	return direction;
}
int Player::GetWinnum(){
	return winnum;
}
void Player::SetVx(int vx){
	this->vx = vx;
}
void Player::SetVy(int vy){
	this->vy = vy;
}
void Player::SetAlive(bool alive){
	this->alive = alive;
}
void Player::SetWinnum(int num){
	winnum += num;
}

int Player::Hanten(int direction){
	switch (direction)
	{
	case DOWN:
		return UP;
	case LEFT:
		return RIGHT;
	case RIGHT:
		return LEFT;
	case UP:
		return DOWN;
	default:
		return 0;
		break;
	}
}

void Player::InitHitTimer(){
	HitTimer1 = 0;
}
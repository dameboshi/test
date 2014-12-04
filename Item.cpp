#include "Item.h"
#include "DxLib.h"
#include "effect.h"
#include "map.h"
#include "common.h"
#include "player.h"

Bomb::Bomb(int x, int y){
	this->x = x;
	this->y = y;
	alive = TRUE;
	timer = 0;
	state = 0;
	expro_flag = 0;
}

void Bomb::Init(int x, int y){
	//Bomb(x,y);
	this->x = x;
	this->y = y;
	alive = TRUE;
	timer = 0;
	state = 0;
	expro_flag = 0;
}

void Bomb::Move(){
	if (alive){
		//時間における状態変化
		if (timer < 180)state = 0;
		else if (timer >181 && timer < 240)state = 1;
		else if (timer > 241 && timer < 359)state = 2;
		else if (timer > 360&& timer < 420)state = 3;

		if (state == 3){
			expro_flag = 1;
			MAP::MapCountReduce(x, y, 20);
			MAP::MapCountReduce(x + 32, y, 20);
			MAP::MapCountReduce(x - 32, y, 20);
			MAP::MapCountReduce(x, y + 32, 20);
			MAP::MapCountReduce(x, y - 32, 20);
			starttime = timer;
			state = 4;
		}

		if (state == 4){
			alive = FALSE;
		}

	}
}

int Bomb::ghandle[8];

void Bomb::Draw(){
	if (alive){
		switch (state){
		case 0:
			if (timer % 120 < 60)DrawGraph(x, y, ghandle[0], TRUE);
			else DrawGraph(x, y, ghandle[1], TRUE);
			break;
		case 1:
			if (timer % 120 < 60)DrawGraph(x, y, ghandle[2], TRUE);
			else DrawGraph(x, y, ghandle[3], TRUE);
			break;
		case 2:
			if (timer % 60 < 30)DrawGraph(x, y, ghandle[2], TRUE);
			else DrawGraph(x, y, ghandle[3], TRUE);
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			break;
		}
	}
}

void Bomb::BombExplosion(){
	if (expro_flag == 1){
		for (int i = 0; i < EFFECT_MAX; i++){
			effect[i].Draw();
			effect[i].Move();
		}
		int t = timer - starttime;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, t % 255);
		DrawOval(x + 32 / 2, y + 32 / 2, 32, 32, RED, TRUE, 1);
		Effect::MakeExplosion2(x, y);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		if (t > 30){
			expro_flag = 0;
		}
	}
	timer++;
}

void Bomb::Load()throw(int){
	if (LoadDivGraph("media/item.png", 8, 4, 2, 32, 32, ghandle) == -1)throw(-1);
}

WeightItem::WeightItem()
{
	x = 0;
	y = 0;
	state = 0;
	timer = 0;
}

WeightItem::~WeightItem()
{
}

void WeightItem::Init(){
	state = 0;
	WeightItem();
}

void WeightItem::Make(int x,int y){
	timer = 0;
	state = 1;
	this->x = x;
	this->y = y;
}

void WeightItem::Draw(){
	
}

void HoverItem::Draw(){
	if (state == 1){
		if (timer > 480){
			if (timer % 60 > 30)DrawGraph(x, y, Bomb::ghandle[4], TRUE);
		}
		else DrawGraph(x, y, Bomb::ghandle[4], TRUE);
	}
}
void HeavyItem::Draw(){
	if (state == 1){
		if (timer > 480){
			if (timer % 60 > 30)DrawGraph(x, y, Bomb::ghandle[5], TRUE);
		}
		else DrawGraph(x, y, Bomb::ghandle[5], TRUE);
	}
}


void WeightItem::Move(){
	switch (state)
	{
	case 0://死
		break;
	case 1://マップ上に存在
		if (timer > 600)state = 0;
		break;
	case 2://プレイヤーに取られている状態
		if (timer > 360)state = 3;
		break;
	case 3:
		if(timer > 1)state = 0;
		break;
	default:
		break;
	}

	timer++;
}

void HeavyItem::Move(){
	switch (state)
	{
	case 0://死
		break;
	case 1://マップ上に存在
		if (timer > 600)state = 0;
		break;
	case 2://プレイヤーに取られている状態
		if (timer > 600)state = 3;
		break;
	case 3:
		if (timer > 1)state = 0;
		break;
	default:
		break;
	}

	timer++;
}

int WeightItem::Catch(int x1,int y1){
	if (state == 1){
		if (HitBox(x, y, x + ITEMSIZE, y + ITEMSIZE, x1 - PLAYER_SIZE / 2, y1 - PLAYER_SIZE / 2, x1 + PLAYER_SIZE/2, y1 + PLAYER_SIZE/2)){
			timer = 0;
			state = 2;
			return 1;
		}
	}
	return 0;
}
int WeightItem::GetState(){
	return state;
}

int WeightItem::ghandle[2];

void WeightItem::Load()throw(int){
	if (LoadDivGraph("media/item.png", 2, 2, 1, 32, 32, ghandle) == -1)throw(-1);
}

void PortableBomb::Draw(){
	if (state == 1){
		if (timer > 480){
			if (timer % 60 > 30)DrawGraph(x, y, Bomb::ghandle[6], TRUE);
		}
		else DrawGraph(x, y, Bomb::ghandle[6], TRUE);
	}
}

void PortableBomb::Move(){
	switch (state)
	{
	case 0://死
		break;
	case 1://マップ上に存在
		if (timer > 600)state = 0;
		break;
	case 2://プレイヤーに取られている状態
		if (timer > 1200)state = 3;
		break;
	case 3:
		if (timer > 1)state = 0;
		break;
	default:
		break;
	}

	timer++;
}
#include "common.h"
#include "gameframe.h"
#include "select.h"
#include "map.h"
#include "Item.h"
#include <math.h>

int Sx, Sy, Cb;
int logox, logoy;
int scrollx;
int Font1;
int Font2;
int Font3;
int playernum;

void Fontload(){
	CountFont = CreateFontToHandle(NULL, 20, 9, DX_FONTTYPE_ANTIALIASING);
	Font1 = CreateFontToHandle(NULL, 26, 1);
	Font2 = CreateFontToHandle(NULL, 30, 9, DX_FONTTYPE_ANTIALIASING);
	Font3 = CreateFontToHandle(NULL, 12, 3, DX_FONTTYPE_ANTIALIASING);
}

int HitBox(int left1, int up1, int right1, int bottom1, int left2, int up2, int right2, int bottom2)
{
	if (left1 < right2 && left2 < right1 && up1 < bottom2 && up2 < bottom1)
	{
		return 1;
	}
	return 0;
}

int TimeStop(int stop){
	int time = 0;
	while (time < stop)time++;

	return 1;
}

double Rad(int x){
	return (x * (PI / 180));
}

void MakeBomb1(int x, int y){
	for (int i = 0; i < 10; i++){
		if (!bakudan[i].Getalive()){
			for (int k = 0; k < 4; k++){
				if (map.MapCountCheck(x * 32, y * 32) == 1){
					x++;
					y++;
				}
				else{
					break;
				}
			}
			bakudan[i].Init(x * 32, y * 32);
			break;
		}
	}
}

Pause::Pause(){
	x = 250;
	y = 240;
	state = 0;
	select_state = 0;
}

Pause::~Pause(){
	x = 0;
	y = 0;
	state = 0;
}

int Pause::Start(){
	if (state == 1)return 1;
	return 0;
}
void Pause::SetState(int state){
	this->state = state;
}
void Pause::Init(){
	state = 0;
	Pause();
}

void Pause::Draw(){
	if (state == 1){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBox(0, 0, Sx, Sy, BLACK, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		int w = GetDrawStringWidthToHandle("PAUSE", 5, Font2);
		int w2 = GetDrawStringWidthToHandle("Ç¬Ç√ÇØÇÈ", 4, Font2);
		int w3 = GetDrawStringWidthToHandle("Ç‚ÇﬂÇÈ", 4, Font2);
		DrawFormatStringToHandle(320 - w / 2, 200, WHITE, Font2, "PAUSE");
		DrawFormatStringToHandle(320 - w2 / 2, 240, WHITE, CountFont, "Ç¬Ç√ÇØÇÈ");
		DrawFormatStringToHandle(320 - w3 / 2, 270, WHITE, CountFont, "Ç‚ÇﬂÇÈ");

		DrawBox(x - ICON_SIZE / 2 - 5, y - ICON_SIZE / 2 + 5 + inter*select_state, x + ICON_SIZE / 2 - 10 + 5, y + ICON_SIZE / 2 + 5 + inter*select_state, BLACK, TRUE);
		DrawBox(x - ICON_SIZE / 2 - 10, y - ICON_SIZE / 2 + inter*select_state, x + ICON_SIZE / 2 - 10, y + ICON_SIZE / 2 + inter*select_state, RED, TRUE);
	}
}

void Pause::Move(){
	if (state == 1){
		//â∫Ç…àÍå¬ìÆÇ≠ÇÊ
		if (pad1.PadGet(DOWN) == 1){
			select_state = (select_state + 1) % 2;

		}//è„Ç…àÍå¬ìÆÇ≠ÇÊ
		else if (pad1.PadGet(UP) == 1){
			select_state = (select_state + 1) % 2;
		}

		switch (select_state)
		{
		case 0:
			if (pad1.PadGet(B_1) == 1)state = 0;
			break;
		case 1:
			if (pad1.PadGet(B_1) == 1)state = 2;
			break;
		default:
			break;
		}
	}
}

int Pause::GetState(){
	return state;
}
#include "select.h"
#include "effect.h"

//int Font1;

void Select::Init(){
	x = SYOKI_X, y = SYOKI_Y;
	state = PLAYER_NUMBER;
	timer = 0;
	timer_switch = FALSE;
	player_n = 1;
	count_max = 10;
	round_n = 1;
}

void Select::Calc(){

	if (timer_switch == TRUE && timer < 60){
		timer++;
	}

	switch (state)
	{
	case PLAYER_NUMBER:
		if (pad1.PadGet(RIGHT) == 1)player_n++;
		if (pad1.PadGet(LEFT) == 1)player_n--;
		break;
	case COUNT_MAX:
		if (pad1.PadGet(RIGHT) == 1){
			if (count_max == 1) count_max -= 1;
			count_max += 5;
		}
		if (pad1.PadGet(LEFT) == 1)count_max -= 5;
		break;
	case ROUND:
		if (pad1.PadGet(RIGHT) == 1)round_n++;
		if (pad1.PadGet(LEFT) == 1)round_n--;
		break;
	case BACK:
		break;
	case NEXT:
		break;
	default:
		break;
	}

	//下に一個動くよ
	if (pad1.PadGet(DOWN) == 1){
		/*now_y = y;
		timer_switch = TRUE;
		*/
		state = (state + 1)%4;
	}//上に一個動くよ
	else if (pad1.PadGet(UP) == 1){
		state = (state + 3) % 4;
	}
	y = SYOKI_Y + SELECT_INTERVAL*(state);



	//y = now_y + SELECT_INTERVAL * sin(timer % 60);

	//if (timer == 60)timer = 0;

	player_n = player_n % 5;
	if (player_n <= 1)player_n = 2;
	round_n = round_n % 4;
	if (round_n <= 0)round_n = 1;
	if (count_max < 1)count_max = 1;
	if (count_max > 20)count_max = 20;

	

}

void Select::Draw(int t){
	if (pad1.PadGet(B_1) == 1){
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	//DrawBox(SYOKI_X - 40, 80 - 50, PLAYER_X + 60, SYOKI_Y + SELECT_INTERVAL * 4, BLACK, TRUE);
	DrawBox(0,0, Sx, Sy, BLACK, TRUE);
	//DrawBox(PLAYER_X - 40, 80 - 50, , 80 + SELECT_INTERVAL * 4, BLACK, TRUE);
	if (t > 255)t = 255;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, t);

	//セレクト画面の文字の描画
	int w = GetDrawStringWidthToHandle("GAME START", 10, Font2);
	DrawFormatStringFToHandle(SYOKI_X + 10, SYOKI_Y - 10, WHITE, Font2, "PLAYER： %d", player_n);
	DrawFormatStringFToHandle(SYOKI_X + 10, SYOKI_Y - 10 + SELECT_INTERVAL, WHITE, Font2, "COUNT： %d", count_max);
	DrawFormatStringFToHandle(SYOKI_X + 10, SYOKI_Y - 10 + SELECT_INTERVAL*2, WHITE, Font2, "ROUND： %d", round_n);
	DrawFormatStringFToHandle(320 - w /2, SYOKI_Y - 10 + SELECT_INTERVAL * 4 + 50, WHITE, Font2, "GAME START", round_n);
	//DrawFormatStringFToHandle(SYOKI_X + 180, SYOKI_Y - 10 + SELECT_INTERVAL * 4 + 50, WHITE, Font1, "BACK", round_n);

	switch (state)
	{
	case PLAYER_NUMBER:
		DrawBox(x - ICON_SIZE / 2 - 5, y - ICON_SIZE / 2 + 5, x + ICON_SIZE / 2 - 10 + 5, y + ICON_SIZE / 2 + 5, BLACK, TRUE);
		DrawBox(x - ICON_SIZE / 2 - 10, y - ICON_SIZE / 2, x + ICON_SIZE / 2 - 10, y + ICON_SIZE / 2, RED, TRUE);
		
		DrawFormatStringFToHandle(SETUMEI_X , SETUMEI_Y, WHITE, CountFont, "プレイヤー数を");
		DrawFormatStringFToHandle(SETUMEI_X, SETUMEI_Y + 32, WHITE, CountFont, "設定します。2");
		DrawFormatStringFToHandle(SETUMEI_X, SETUMEI_Y + 32*2, WHITE, CountFont, "～4人まで選ぶ");
		DrawFormatStringFToHandle(SETUMEI_X, SETUMEI_Y + 32*3, WHITE, CountFont, "ことができます");
		break;
	case COUNT_MAX:
		DrawBox(x - ICON_SIZE / 2 - 5, y - ICON_SIZE / 2 + 5, x + ICON_SIZE / 2 - 10 + 5, y + ICON_SIZE / 2 + 5, BLACK, TRUE);
		DrawBox(x - ICON_SIZE / 2 - 10, y - ICON_SIZE / 2, x + ICON_SIZE / 2 - 10, y + ICON_SIZE / 2, RED, TRUE);
		DrawFormatStringFToHandle(SETUMEI_X, SETUMEI_Y,          WHITE, CountFont, "パネルのカウン");
		DrawFormatStringFToHandle(SETUMEI_X, SETUMEI_Y + 32,     WHITE, CountFont, "ト数を設定しま");
		DrawFormatStringFToHandle(SETUMEI_X, SETUMEI_Y + 32 * 2, WHITE, CountFont, "す。値が小さい");
		DrawFormatStringFToHandle(SETUMEI_X, SETUMEI_Y + 32 * 3, WHITE, CountFont, "ほど短期決戦に");
		DrawFormatStringFToHandle(SETUMEI_X, SETUMEI_Y + 32 * 4, WHITE, CountFont, "なりやすくなり");
		DrawFormatStringFToHandle(SETUMEI_X, SETUMEI_Y + 32 * 5, WHITE, CountFont, "ます。");
		break;
	case ROUND:
		DrawBox(x - ICON_SIZE / 2 - 5, y - ICON_SIZE / 2 + 5  , x + ICON_SIZE / 2 - 10 + 5, y + ICON_SIZE / 2 + 5, BLACK, TRUE);
		DrawBox(x - ICON_SIZE / 2 -10, y - ICON_SIZE / 2 , x + ICON_SIZE / 2 -10, y + ICON_SIZE / 2, RED, TRUE);
		DrawFormatStringFToHandle(SETUMEI_X, SETUMEI_Y, WHITE, CountFont, "ラウンド数を設");
		DrawFormatStringFToHandle(SETUMEI_X, SETUMEI_Y + 32, WHITE, CountFont, "定します。値が");
		DrawFormatStringFToHandle(SETUMEI_X, SETUMEI_Y + 32 * 2, WHITE, CountFont, "小さいほどすぐ");
		DrawFormatStringFToHandle(SETUMEI_X, SETUMEI_Y + 32 * 3, WHITE, CountFont, "に終わります。");
		break;
	case NEXT:
		DrawFormatStringFToHandle(320 - w / 2 - 2, SYOKI_Y - 10 + SELECT_INTERVAL * 4 - 1 + 50, BLACK, Font2, "GAME START", round_n);
		DrawFormatStringFToHandle(SETUMEI_X, SETUMEI_Y, WHITE, CountFont, "ゲームを始めま");
		DrawFormatStringFToHandle(SETUMEI_X, SETUMEI_Y + 32, WHITE, CountFont, "す。ボタンを押");
		DrawFormatStringFToHandle(SETUMEI_X, SETUMEI_Y + 32 * 2, WHITE, CountFont, "してください。");
		break;
	case BACK:
		DrawFormatStringFToHandle(SYOKI_X + 180 - 2, SYOKI_Y - 10 + SELECT_INTERVAL * 4 - 1 + 50, BLACK, Font1, "BACK", round_n);
		break;
	default:
		break;
	}

	switch (player_n)
	{
	case 0:
	case 1:
		DrawFormatStringFToHandle(PLAYER_X - PLAYER_SIZE_SELECT / 2, PLAYER_Y - PLAYER_SIZE_SELECT * 2, WHITE, CountFont, "1P");
		DrawBox(PLAYER_X - PLAYER_SIZE_SELECT / 2, PLAYER_Y- PLAYER_SIZE_SELECT / 2, PLAYER_X+ PLAYER_SIZE_SELECT / 2, PLAYER_Y+ PLAYER_SIZE_SELECT / 2, RED, TRUE);
		break;
	case 2:
		DrawFormatStringFToHandle(PLAYER_X - PLAYER_SIZE_SELECT / 2, PLAYER_Y - PLAYER_SIZE_SELECT * 2, WHITE, CountFont, "1P");
		DrawBox(PLAYER_X - PLAYER_SIZE_SELECT / 2, PLAYER_Y - PLAYER_SIZE_SELECT / 2 , PLAYER_X + PLAYER_SIZE_SELECT / 2, PLAYER_Y + PLAYER_SIZE_SELECT / 2 , RED, TRUE);
		DrawFormatStringFToHandle(PLAYER_X - PLAYER_SIZE_SELECT / 2, PLAYER_Y - PLAYER_SIZE_SELECT * 2 + 60, WHITE, CountFont, "2P");
		DrawBox(PLAYER_X - PLAYER_SIZE_SELECT / 2, PLAYER_Y - PLAYER_SIZE_SELECT / 2 + 60, PLAYER_X + PLAYER_SIZE_SELECT / 2, PLAYER_Y + PLAYER_SIZE_SELECT / 2 + 60, BLUE, TRUE);
		break;
	case 3:
		DrawFormatStringFToHandle(PLAYER_X - PLAYER_SIZE_SELECT / 2, PLAYER_Y - PLAYER_SIZE_SELECT * 2, WHITE, CountFont, "1P");
		DrawBox(PLAYER_X - PLAYER_SIZE_SELECT / 2, PLAYER_Y - PLAYER_SIZE_SELECT / 2, PLAYER_X + PLAYER_SIZE_SELECT / 2, PLAYER_Y + PLAYER_SIZE_SELECT / 2, RED, TRUE);
		DrawFormatStringFToHandle(PLAYER_X - PLAYER_SIZE_SELECT / 2, PLAYER_Y - PLAYER_SIZE_SELECT * 2 + 60, WHITE, CountFont, "2P");
		DrawBox(PLAYER_X - PLAYER_SIZE_SELECT / 2, PLAYER_Y - PLAYER_SIZE_SELECT / 2 + 60, PLAYER_X + PLAYER_SIZE_SELECT / 2, PLAYER_Y + PLAYER_SIZE_SELECT / 2 + 60, BLUE, TRUE);
		DrawFormatStringFToHandle(PLAYER_X - PLAYER_SIZE_SELECT / 2, PLAYER_Y - PLAYER_SIZE_SELECT * 2 + 60 * 2, WHITE, CountFont, "3P");
		DrawBox(PLAYER_X - PLAYER_SIZE_SELECT / 2, PLAYER_Y - PLAYER_SIZE_SELECT / 2 + 60 * 2, PLAYER_X + PLAYER_SIZE_SELECT / 2, PLAYER_Y + PLAYER_SIZE_SELECT / 2 + 60 * 2, GREEN, TRUE);
		break;
	case 4:
		DrawFormatStringFToHandle(PLAYER_X - PLAYER_SIZE_SELECT / 2, PLAYER_Y - PLAYER_SIZE_SELECT * 2, WHITE, CountFont, "1P");
		DrawBox(PLAYER_X - PLAYER_SIZE_SELECT / 2, PLAYER_Y - PLAYER_SIZE_SELECT / 2, PLAYER_X + PLAYER_SIZE_SELECT / 2, PLAYER_Y + PLAYER_SIZE_SELECT / 2, RED, TRUE);
		DrawFormatStringFToHandle(PLAYER_X - PLAYER_SIZE_SELECT / 2, PLAYER_Y - PLAYER_SIZE_SELECT * 2 + 60, WHITE, CountFont, "2P");
		DrawBox(PLAYER_X - PLAYER_SIZE_SELECT / 2, PLAYER_Y - PLAYER_SIZE_SELECT / 2 + 60, PLAYER_X + PLAYER_SIZE_SELECT / 2, PLAYER_Y + PLAYER_SIZE_SELECT / 2 + 60, BLUE, TRUE);
		DrawFormatStringFToHandle(PLAYER_X - PLAYER_SIZE_SELECT / 2, PLAYER_Y - PLAYER_SIZE_SELECT * 2 + 60 * 2, WHITE, CountFont, "3P");
		DrawBox(PLAYER_X - PLAYER_SIZE_SELECT / 2, PLAYER_Y - PLAYER_SIZE_SELECT / 2 + 60 * 2, PLAYER_X + PLAYER_SIZE_SELECT / 2, PLAYER_Y + PLAYER_SIZE_SELECT / 2 + 60 * 2, GREEN, TRUE);
		DrawFormatStringFToHandle(PLAYER_X - PLAYER_SIZE_SELECT / 2, PLAYER_Y - PLAYER_SIZE_SELECT * 2 + 60 * 3, WHITE, CountFont, "4P");
		DrawBox(PLAYER_X- PLAYER_SIZE_SELECT / 2, PLAYER_Y- PLAYER_SIZE_SELECT / 2 + 60 * 3, PLAYER_X+ PLAYER_SIZE_SELECT / 2, PLAYER_Y+ PLAYER_SIZE_SELECT / 2 + 60 * 3, PURPLE, TRUE);
		break;
	default:
		break;
	}
}

int Select::GetState(){
	return state;
}

int Select::GetPlayerNumber(){
	return player_n;
}
int Select::GetCountMax(){
	return count_max;
}
int Select::GetRoundNumber(){
	return round_n;
}
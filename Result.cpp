#include "result.h"
#include "keyconfig.h"
#include "player.h"
#include "common.h"
#include "select.h"

Result::Result(int p1,int p2,int p3,int p4,int round){
	x = RESULT_X;
	y = RESULT_Y;
	timer = 0;
	int player_num[4] = { p1, p2, p3, p4 };

	for (int i = 0; i < 4; i++){
		int count = 0;
		while (player_num[i] > 0){
			player_num[i]--;
			count++;
		}
		if (count == round)player_rank[i] = 1;
		else if (count == (round - 1))player_rank[i] = 2;
		else if (count == (round - 2))player_rank[i] = 3;
		else if (count == (round - 3))player_rank[i] = 4;
	}

}

void Result::Init(){
	x = RESULT_X;
	y = RESULT_Y;
	timer = 0;

}

void Result::Calc(int win1,int win2,int win3,int win4){
	

	timer++;
}

void Result::Draw(int win1, int win2, int win3, int win4,int pnum){
	int w = GetDrawStringWidthToHandle("PLAYER1 : 1 位", 13, Font2);
	DrawFormatStringFToHandle(RESULT_X -w/2, RESULT_Y, BLACK, Font2, "PLAYER1 : %d　位", player_rank[0]);
	
	switch (pnum){
	case 2:
		DrawFormatStringFToHandle(RESULT_X-w/2, RESULT_Y + RESULT_Y_I, BLACK, Font2, "PLAYER2 : %d　位", player_rank[1]);
		break;
	case 3:
		DrawFormatStringFToHandle(RESULT_X-w/2, RESULT_Y + RESULT_Y_I, BLACK, Font2, "PLAYER2 : %d　位", player_rank[1]);
		DrawFormatStringFToHandle(RESULT_X-w/2, RESULT_Y + RESULT_Y_I * 2, BLACK, Font2, "PLAYER3 : %d　位", player_rank[2]);
		break;
	case 4:
		DrawFormatStringFToHandle(RESULT_X-w/2, RESULT_Y + RESULT_Y_I, BLACK, Font2, "PLAYER2 : %d　位", player_rank[1]);
		DrawFormatStringFToHandle(RESULT_X-w/2, RESULT_Y + RESULT_Y_I * 2, BLACK, Font2, "PLAYER3 : %d　位", player_rank[2]);
		DrawFormatStringFToHandle(RESULT_X-w/2, RESULT_Y + RESULT_Y_I * 3, BLACK, Font2, "PLAYER4 : %d　位", player_rank[3]);
		break;
	default:
		break;
	}

}

void Result::Hikaku4(int win1, int win2, int win3, int win4){
	int num[4] = {win1,win2,win3,win4};
	int rank = 1;

	for (int i = 0; i < 4; i++){
		for (int t = 0; t > 3; t++){
			if (num[i] > num[i + 1]){
				player_rank[i] = rank;
			}
		}
		rank++;
	}
}
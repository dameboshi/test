#include "map.h"
#include "gameframe.h"
#include "common.h"
#include "keyconfig.h"
#include <string>
#include "common.h"
#include "effect.h"

int CountFont;

mapdata mapdata1[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];

int CountFontSize1;
int CountFontSize2;

int MAP::height = 0;
int MAP::width = 0;


void MAP::Init(){
	height = 0;
	width = 0;
	CountFontSize1 = GetDrawStringWidthToHandle("0", 1, CountFont);
	CountFontSize2 = GetDrawStringWidthToHandle("10", 2, CountFont);

}

void MAP::Set(int h, int w,int count){
	height = h;
	width = w;

	//カウントの初期化
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++){
			mapdata1[j][i].count = count;
		}
	}
}

void MAP::Mapload(int num)throw(int){

	if (LoadDivGraph("media\\mapchip.png", MAPKIND, 5, 1, MAPSIZE, MAPSIZE, ghandle) == -1)throw(-1);

	char buf[MAP_WIDTH_MAX];
	int filehandle;

	if (num != -1){
		filehandle = FileRead_open("media\\map1.txt");
		if (filehandle == 0)throw(-1);
	}

	//マップの高さ広さを決める
	for (int i = 0; i < height; i++)
	{
		FileRead_gets(buf, MAP_WIDTH_MAX, filehandle);
		for (int j = 0; j < width; j++){
			mapdata1[j][i].data = buf[j] - '0';
		}
	}
	FileRead_close(filehandle);


}

void MAP::Draw(){

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++){
			//DrawGraph(j * MAPSIZE , i*MAPSIZE, ghandle[mapdata[j][i]], 1);
			if (mapdata1[j][i].data == 0){
				//DrawBox(j * MAPSIZE, i* MAPSIZE, j * MAPSIZE + MAPSIZE, i * MAPSIZE + MAPSIZE, WHITE, FALSE);
				if (mapdata1[j][i].count == 0){
					DrawGraph(j * MAPSIZE, i* MAPSIZE, ghandle[4], FALSE);
					DrawFormatStringFToHandle(j * MAPSIZE + CountFontSize1 / 2 + 10, i * MAPSIZE + 10, WHITE, CountFont, "%d", mapdata1[j][i].count);
				}
				else if (mapdata1[j][i].count > 0 && mapdata1[j][i].count < 2){
					DrawGraph(j * MAPSIZE, i* MAPSIZE, ghandle[3], FALSE);
					DrawFormatStringFToHandle(j * MAPSIZE + CountFontSize1 / 2 + 10, i * MAPSIZE + 10, WHITE, CountFont, "%d", mapdata1[j][i].count);
				}
				else if (mapdata1[j][i].count >= 2 && mapdata1[j][i].count < 4){
					DrawGraph(j * MAPSIZE, i* MAPSIZE, ghandle[2], FALSE);
					DrawFormatStringFToHandle(j * MAPSIZE + CountFontSize1 / 2 + 10, i * MAPSIZE + 10, WHITE, CountFont, "%d", mapdata1[j][i].count);
				}
				else{
					DrawGraph(j * MAPSIZE, i* MAPSIZE, ghandle[1], FALSE);
					DrawFormatStringFToHandle(j * MAPSIZE + CountFontSize1 / 2 + 10, i * MAPSIZE + 10, WHITE, CountFont, "%d", mapdata1[j][i].count);
				}
				
			}else{
				//DrawBox(j * MAPSIZE, i* MAPSIZE, j * MAPSIZE + MAPSIZE, i * MAPSIZE + MAPSIZE, BLACK, TRUE);
				DrawGraph(j * MAPSIZE, i* MAPSIZE, ghandle[0],FALSE);
			}

			if (mapdata1[j][i].count < 0)mapdata1[j][i].count = 0;
		}
	}

	//-----そのた処理もここ-----//

}

//マップデータの番号を返す
int MAP::MapCheck(double x, double y){
    return mapdata1[(int)x / MAPSIZE][(int)y / MAPSIZE].data;
	//return 0;
}

//マップデータのカウントを返す
int MAP::MapCountCheck(double x, double y){
	return mapdata1[(int)x / MAPSIZE][(int)y / MAPSIZE].count;
}
/*
void MAP::MakeBomb(int x, int y){
	//bakudan[0].Init(x, y);
	printfDx("%d \n", bakudan[0].Getalive());
	for (int i = 0; i < 10; i++){
		if (!bakudan[i].Getalive()){
			bakudan[i].Init(x, y);
			break;
		}
	}
}
*/

void MAP::MapCountReduce(int x, int y){
	mapdata1[x / MAPSIZE][y / MAPSIZE].count--;
}

void MAP::MapCountReduce(int x, int y,int n){
	mapdata1[x / MAPSIZE][y / MAPSIZE].count -= n;
	if (mapdata1[x / MAPSIZE][y / MAPSIZE].count < 0){
		mapdata1[x / MAPSIZE][y / MAPSIZE].count = 0;
	}
}


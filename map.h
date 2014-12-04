#ifndef _MAP_H_
#define _MAP_H_

#include <vector>
#include "DxLib.h"
//using namespace std;

#define MAPKIND 15 //�}�b�v�`�b�v�̎�ނ̐�
#define MAP_HEIGHT_MAX 30
#define MAP_WIDTH_MAX 30
#define MAPSIZE 32//�}�b�v1�}�X�̑傫��

enum MAP_K{
	SPACE,
	WALL
};

typedef struct _MAP{
	int data;
	int count;
}mapdata;

extern mapdata mapdata1[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];

class MAP{
	int ghandle[MAPKIND];
public:
	MAP(){};
	void Init();
	void Set(int height, int width,int count);
	void Mapload(int)throw(int);
	//static void MakeBomb(int,int);
	void Draw();
	static int height;//�}�X�̐��i�����j
	static int width;//�}�X�̐��i���j
	static int MapCheck(double, double);
	static int MapCountCheck(double, double);
	static void MapCountReduce(int, int);
	static void MapCountReduce(int, int,int);
};

extern MAP map;

#endif
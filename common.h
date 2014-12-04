#ifndef _COMMON_H_
#define _COMMON_H_

#include "DxLib.h"

const int WHITE = GetColor(255, 255, 255);
const int BLACK = GetColor(0, 0, 0);
const int RED = GetColor(255, 0, 0);
const int BLUE = GetColor(0, 0, 255);
const int GREEN = GetColor(0, 255, 0);
const int PURPLE = GetColor(255, 0, 255);
const int YELLOW = GetColor(0, 255, 255);

const double PI = 3.14159265358;

extern int CountFont;
extern int Font1;
extern int Font2;
extern int Font3;

void Fontload();
int HitBox(int, int, int, int, int, int, int, int);
int TimeStop(int);
double Rad(int);
void Hikaku4(int, int, int, int);
void MakeBomb1(int, int);

extern int Sx, Sy, Cb;//スクリーンのサイズ
extern int logox, logoy;
extern int playernum;

extern int scrollx; //x方向のスクロール
extern void scrollx_lim();

const int inter = 30;

class Pause{
private:
	int x, y;
	int state;
	int select_state;
public:
	Pause();
	~Pause();
	int Start();
	void Init();
	void Move();
	void Draw();
	void SetState(int state);
	int GetState();
};

extern Pause pause;

#endif
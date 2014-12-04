#ifndef _PLAYER_H_
#define _PLAYER_H_


#include "DxLib.h"
#define PLAYER_SIZE 31
#define PLAYER_ZURE 3
#define PLAYER_SPEED 2
#define PLAYER_HYOZI 520
#define SCORE_INT 30
#define SCORE_SYOKI_Y 80

class Player{
protected:
	int bagucheck;
	int playerhit;
	int x, y;
	int vx, vy;
	int score_x, score_y;
	int direction;
	int rank;
	int speed;
	bool alive;
	unsigned int timer;
	int mapdata_p;//“¥‚ñ‚Å‚¢‚éƒ}ƒbƒv‚ð•Û‘¶‚·‚é
	bool panel_On;
	bool wall_switch;
	int winnum;
	int itemstate;
	int bakudanstate;
	int nowitem;
public:
	/*
	Player(int x,int y,int direction):x(x),y(y),direction(direction){
		vx = vy = 0;
		timer = 0;
		alive = 1;
		wall_switch = 1;
		MoveFlag = 1;
		HitTimer = 0;
	}
	*/
	int HitTimer;
	int HitTimer1;
	bool MoveFlag;

	void Init(int,int,int);
	void InitWin();
	void InitHitTimer();
	void Operate(int);
	void Calc();
	void Draw(int);
	int Hanten(int);
	int GetX();
	int GetY();
	int GetVx();
	int GetVy();
	int GetAlive();
	int GetDirection();
	int GetWinnum();
	void SetVx(int);
	void SetVy(int);
	void SetAlive(bool);
	void SetWinnum(int);
	void PlayerHitPlayer(int,int,bool,int);
};

class Player1 :public Player{
public:
	
	Player1::Player1(int x, int y, int direction){
		this->x = x;
		this->y = y;
		this->direction = direction;
		bakudanstate = 0;
		nowitem = 0;
		score_x = PLAYER_HYOZI;
		score_y = SCORE_SYOKI_Y;
		vx = vy = 0;
		timer = 0;
		alive = TRUE;
		wall_switch = TRUE;
		MoveFlag = TRUE;
		HitTimer = 0;
		winnum = 0;
		speed = PLAYER_SPEED;
		itemstate = 0;
	}
	
	void Draw();
};

class Player2 :public Player{
public:
	Player2(int x, int y, int direction){
		this->x = x;
		this->y = y;
		this->direction = direction;
		bakudanstate = 0;
		nowitem = 0;
		score_x = PLAYER_HYOZI;
		score_y = SCORE_SYOKI_Y + SCORE_INT;
		vx = vy = 0;
		timer = 0;
		alive = TRUE;
		wall_switch = TRUE;
		MoveFlag = TRUE;
		HitTimer = 0;
		winnum = 0;
		speed = PLAYER_SPEED;
		itemstate = 0;
	}
	void Draw();
};

class Player3 :public Player{
public:
	Player3(int x, int y, int direction){
		this->x = x;
		this->y = y;
		this->direction = direction;
		bakudanstate = 0;
		nowitem = 0;
		score_x = PLAYER_HYOZI;
		score_y = SCORE_SYOKI_Y + SCORE_INT*2;
		vx = vy = 0;
		timer = 0;
		alive = TRUE;
		wall_switch = TRUE;
		MoveFlag = TRUE;
		HitTimer = 0;
		winnum = 0;
		itemstate = 0;
		speed = PLAYER_SPEED;
	}
	void Draw();
}; 

class Player4 :public Player{
public:
	Player4(int x, int y, int direction){
		this->x = x;
		this->y = y;
		this->direction = direction;
		bakudanstate = 0;
		nowitem = 0;
		score_x = PLAYER_HYOZI;
		score_y = SCORE_SYOKI_Y + SCORE_INT*3;
		vx = vy = 0;
		timer = 0;
		alive = TRUE;
		wall_switch = TRUE;
		MoveFlag = TRUE;
		HitTimer = 0;
		winnum = 0;
		itemstate = 0;
		speed = PLAYER_SPEED;
	}
	void Draw();
};

extern Player1 *player1;
extern Player2 *player2;
extern Player3 *player3;
extern Player4 *player4;

#endif
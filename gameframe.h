#ifndef _GAMEFRAME_H_
#define _GAMEFRAME_H_

#include "keyconfig.h"

enum GAMESTATE{
	GAME_TITLE,
	GAME_SELECT,
	GAME_MAIN,
	GAME_OVER,
	GAME_CLEAR,
};

class GameFrame{
	virtual void loadfile()throw(int){};
	GAMESTATE gstate;
	static unsigned int animcounter;
	static float idouryou[20];
	void setIdouHosei();
	char Keyboard[256];
protected:
	int starttime;
	int nowround;
	virtual void drawGameTitle();
	virtual void drawGameSelect();
	virtual void drawGameMain();
	virtual void drawGameClear();
	virtual void drawGameOver();
	virtual void Initstage();
	void MakeFrame(int, int,int,int);
	int MainLogo();
	int logo_state;
	GAMESTATE setGameState(GAMESTATE state);
	int largefont, smallfont,mfont;
	int logohandle;
	int framehandle[9];
	int buttonhandle;
	int sx, sy;
	int sx1, sy1;
	int itemtimer;
public:
	virtual ~GameFrame(){};
	void doMainLoop(int);
	static unsigned int GetAnimCnt();
	static float IdouHosei(int);
	static int FadeOut();
	void setState(GAMESTATE);
};

#endif
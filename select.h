#include "animdraw.h"
#include "common.h"
#include "gameframe.h"
#include "keyconfig.h"
#include <math.h>

const int ICON_SIZE = 16;
const int SELECT_INTERVAL = 60;
const int SYOKI_X = 65;
const int SYOKI_Y = 120;
const int PLAYER_X = 320;
const int PLAYER_Y = 100;
const int SETUMEI_X = 436;
const int SETUMEI_Y = 52;
const int P_X = 380;
const int PLAYER_SIZE_SELECT = 20;

enum{
	PLAYER_NUMBER,
	COUNT_MAX,
	ROUND,
	NEXT,
	BACK
};

class Select{
	double x, y;
	double now_y;
	double vx, vy;
	int state;
	int timer;
	bool timer_switch;//˜A‘±‚µ‚Ä“®‚©‚È‚¢‚æ‚¤‚É
	int player_n;
	int count_max;
	int round_n;
public:
	void Init();
	void Calc();
	void Draw(int t);
	int GetState();
	int GetPlayerNumber();
	int GetCountMax();
	int GetRoundNumber();
};
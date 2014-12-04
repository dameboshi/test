#ifndef _ANIMDRAW_H_
#define _ANIMDRAW_H_

#include <vector>
#include "DxLib.h"
#include "gameframe.h"
using namespace std;

class AnimDraw{
	struct animpat{
		vector<int> glist;
		int anigap;
		animpat(){ anigap = 1; };//anipatのコンストラクタ
	};
	vector<animpat> aplist;
public:
	AnimDraw(){
		aplist.push_back(animpat()); //ひとつ目のanimpatをセット
	}

	int setImage(int apid, int ghandle); //グラフィックハンドルのセット
	int setGap(int apid, int gap); //表示間隔(anigap)をセット

	void draw(int apid, int x, int y);
	void draw(int apid, int x, int y, double rad);
};

class SoundBox{
	static vector<int> sounds;
	static int bgm;
public:
	static int set(int shandle);
	static void play(int snum);
	static void stop(int snum);
	static void playbgm(int snum);
};

#endif

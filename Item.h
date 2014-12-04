#ifndef _ITEM_H_
#define _ITEM_H_

#define ITEMSIZE 32

class Bomb{
private:
	int x, y;
	bool alive;
	int timer;
	int starttime;
	int state;
	int expro_flag;
public:
	static int ghandle[8];
	Bomb(){};
	Bomb(int, int);
	~Bomb(){ alive = 0; };
	void Init(int, int);
	void Move();
	void Draw();
	void BombExplosion();
	static void Load()throw(int);
	void Sethandle();
	int Getalive(){ return alive; };
	int GetX(){ return x; };
	int GetY(){ return y; };
};


class WeightItem{
protected:
	int x, y;
	int state;
	int timer;
public:
	static int ghandle[2];
	WeightItem();
	~WeightItem();
	static void Load();
	int Catch(int,int);
	int GetState();
	void Init();
	void Make(int,int);
	void Draw();
	void Move();
};

class HoverItem :public WeightItem{
public:
	void Draw();
};

class HeavyItem :public WeightItem{
public:
	void Draw();
	void Move();
};

class PortableBomb :public WeightItem{
public:
	void Draw();
	void Move();
};

extern Bomb bakudan[10];
extern HoverItem hover[10];
extern HeavyItem heavy[10];
extern PortableBomb potablebakudan[10];

#endif
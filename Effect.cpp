#include "DxLib.h"
#include "effect.h"
#include "common.h"
#include <math.h>

Effect effect[EFFECT_MAX];

void Effect::Init(bool alive){
	this->alive = alive;
	time = 0;
	alpha = 0;
}

void Effect::Make(int x, int y, int kind){

	Init(1);
	this->x = x;
	this->y = y;
	this->kind = kind;
	switch (kind)
	{
	case EXPLOSION:
		v = 3.0;
		alpha = 255;
		vector = Rad(GetRand(359));
		color = GetColor(127 + GetRand(128), 127 + GetRand(128), 127 + GetRand(128));
		break;
	case EXPLOSTON_2:
		v = 4.0;
		alpha = 255;
		vector = Rad(GetRand(359));
		color = RED;
		break;
	case BIRIBIRI:
		v = 3.0;
		alpha = 255;
		vector = Rad(GetRand(359));
		color = RED;
		break;
	case SPARK:
		v = 3.0;
		alpha = 255;
		vector = Rad(GetRand(359));
		color = BLACK;//GetColor(250 + GetRand(5), GetRand(25), 128);
		color2 = RED;//GetColor(225 + GetRand(20), 0, 50 + GetRand(60));

		break;
	}


}



void Effect::Move(){
	x += v * cos(vector);
	y += v * sin(vector);

	switch (kind)
	{
	case EXPLOSION:
		v -= 0.1;
		alpha -= 10;
		break;
	case EXPLOSTON_2:
		v -= 0.2;
		alpha -= 12;
		break;
	case BIRIBIRI:
		v -= 0.1;
		alpha -= 5;
		break;
	case SPARK:
		v -= 0.2;
		alpha -= 20;
		break;
	}


	if (v < 0){
		alive = false;
	}
	if (add < 0){
		add = 0;
	}

	time++;
}

void Effect::Draw(){
	if (alive == true){
		switch (kind)
		{
		case EXPLOSION:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			DrawCircle(x, y, 10, color, 1);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			break;
		case EXPLOSTON_2:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			DrawCircle(x, y, 8, color, 1);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			break;
		case BIRIBIRI:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			DrawTriangle(x, y, x + GetRand(20), y + GetRand(20), x - GetRand(20), y - GetRand(20), YELLOW, 1);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			break;
		case SPARK:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			//SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
			DrawBox(x, y, x + 4, y + 4, (time % 2 == 0) ? color : color2, 1);
			//SetDrawBlendMode(DX_BLENDMODE_ADD, 0);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
	}

}

void Effect::MakeExplosion(int x, int y){
	for (int n = 0; n < 20; ++n){
		for (int i = 0; i < EFFECT_MAX; ++i){
			if (!effect[i].alive){
				effect[i].Make(x, y, EXPLOSION);
				break;
			}
		}
	}
}


void Effect::MakeExplosion2(int x, int y){
	for (int n = 0; n < 20; ++n){
		for (int i = 0; i < EFFECT_MAX; ++i){
			if (!effect[i].alive){
				effect[i].Make(x, y, EXPLOSTON_2);
				break;
			}
		}
	}
}


void Effect::MakeBIRIBIRI(int x, int y){
	for (int n = 0; n < 8; ++n){
		for (int i = 0; i < EFFECT_MAX; ++i){
			if (!effect[i].alive){
				effect[i].Make(x, y, BIRIBIRI);
				break;
			}
		}
	}
}

void Effect::MakeSPARK(int x, int y){
	for (int n = 0; n < 8; ++n){
		for (int i = 0; i < EFFECT_MAX; ++i){
			if (!effect[i].alive){
				effect[i].Make(x, y, SPARK);
				break;
			}
		}
	}
}
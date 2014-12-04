
class Effect{
	double x, y;
	double v, vector;
	bool alive;
	int time;
	int alpha;
	int add;
	int color;
	int color2;
	//ここintで
	int kind;

public:
	enum{
		EXPLOSION,
		EXPLOSTON_2,
		BIRIBIRI,
		SPARK,
	};
	void Init(bool alive);
	void Make(int x, int y, int kind);
	void Move();
	void Draw();

	//staticはインスタンスが無くても呼べる
	static void MakeExplosion(int x, int y);
	static void MakeExplosion2(int x, int y);
	static void MakeBIRIBIRI(int x, int y);
	static void MakeSPARK(int x, int y);

	Effect(){
		alive = 0;
	}
};
const int EFFECT_MAX = 100;
extern Effect effect[EFFECT_MAX];

#define RESULT_X 320
#define RESULT_Y 100
#define RESULT_Y_I 110

//extern int player_rank;

class Result{
private:
	int x, y;
	unsigned int timer;
	int Font;
	int player_rank[4];
public:
	Result(int,int,int,int,int);
	void Init();
	void Calc(int,int,int,int);
	void Draw(int,int,int,int,int);
	void Hikaku4(int, int, int, int);
};
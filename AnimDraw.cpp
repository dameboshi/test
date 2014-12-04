#include "animdraw.h"

int AnimDraw::setImage(int apid, int ghandle){
	if (apid >= aplist.size()){
		aplist.push_back(animpat());//新しいアニメパターンを追加
		//apidが追加したアニメパターンを指す
		apid = aplist.size() - 1;
	}
	aplist.at(apid).glist.push_back(ghandle);
	return(apid);
}

int AnimDraw::setGap(int apid, int gap){
	if (apid >= aplist.size()){
		aplist.push_back(animpat());//新しいアニメパターンを追加
		//apidが追加したアニメパターンを指す
		apid = aplist.size() - 1;
	}
	aplist.at(apid).anigap = gap;
	return (apid);
}

//アニメーション描画
void AnimDraw::draw(int apid, int x, int y){
	if (aplist.at(apid).glist.size() > 1){
		int curpat = GameFrame::GetAnimCnt() / aplist.at(apid).anigap % aplist.at(apid).glist.size();
		DrawGraph(x, y, aplist.at(apid).glist.at(curpat), true);
	}
	else{
		DrawGraph(x, y, aplist.at(apid).glist.at(0), true);
	}
}

//アニメーション回転描画
void AnimDraw::draw(int apid, int x, int y, double rad){
	if (aplist.at(apid).glist.size() > 1){
		int curpat = GameFrame::GetAnimCnt() / aplist.at(apid).anigap % aplist.at(apid).glist.size();
		DrawRotaGraph(x, y, 1.0, rad, aplist.at(apid).glist.at(curpat), true, false);
	}
	else{
		DrawRotaGraph(x, y, 1.0, rad, aplist.at(apid).glist.at(0), true, false);
	}
}

//SoundBoxクラスメンバ変数の実体
vector<int> SoundBox::sounds;
int SoundBox::bgm = -1;

//サウンドハンドルの登録
int SoundBox::set(int shandle){
	sounds.push_back(shandle);
	return(sounds.size() - 1);
}

//サウンドのさいせい
void SoundBox::play(int snum){
	PlaySoundMem(sounds.at(snum), DX_PLAYTYPE_BACK);
}
//サウンドの停止
void SoundBox::stop(int snum){
	StopSoundMem(sounds.at(snum));
}
//BGMの再生
void SoundBox::playbgm(int snum){
	int newbgm = sounds.at(snum);
	if (bgm == newbgm) return;
	StopSoundMem(bgm);
	bgm = newbgm;
	PlaySoundMem(bgm, DX_PLAYTYPE_BACK);
}


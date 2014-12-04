#include "animdraw.h"

int AnimDraw::setImage(int apid, int ghandle){
	if (apid >= aplist.size()){
		aplist.push_back(animpat());//�V�����A�j���p�^�[����ǉ�
		//apid���ǉ������A�j���p�^�[�����w��
		apid = aplist.size() - 1;
	}
	aplist.at(apid).glist.push_back(ghandle);
	return(apid);
}

int AnimDraw::setGap(int apid, int gap){
	if (apid >= aplist.size()){
		aplist.push_back(animpat());//�V�����A�j���p�^�[����ǉ�
		//apid���ǉ������A�j���p�^�[�����w��
		apid = aplist.size() - 1;
	}
	aplist.at(apid).anigap = gap;
	return (apid);
}

//�A�j���[�V�����`��
void AnimDraw::draw(int apid, int x, int y){
	if (aplist.at(apid).glist.size() > 1){
		int curpat = GameFrame::GetAnimCnt() / aplist.at(apid).anigap % aplist.at(apid).glist.size();
		DrawGraph(x, y, aplist.at(apid).glist.at(curpat), true);
	}
	else{
		DrawGraph(x, y, aplist.at(apid).glist.at(0), true);
	}
}

//�A�j���[�V������]�`��
void AnimDraw::draw(int apid, int x, int y, double rad){
	if (aplist.at(apid).glist.size() > 1){
		int curpat = GameFrame::GetAnimCnt() / aplist.at(apid).anigap % aplist.at(apid).glist.size();
		DrawRotaGraph(x, y, 1.0, rad, aplist.at(apid).glist.at(curpat), true, false);
	}
	else{
		DrawRotaGraph(x, y, 1.0, rad, aplist.at(apid).glist.at(0), true, false);
	}
}

//SoundBox�N���X�����o�ϐ��̎���
vector<int> SoundBox::sounds;
int SoundBox::bgm = -1;

//�T�E���h�n���h���̓o�^
int SoundBox::set(int shandle){
	sounds.push_back(shandle);
	return(sounds.size() - 1);
}

//�T�E���h�̂�������
void SoundBox::play(int snum){
	PlaySoundMem(sounds.at(snum), DX_PLAYTYPE_BACK);
}
//�T�E���h�̒�~
void SoundBox::stop(int snum){
	StopSoundMem(sounds.at(snum));
}
//BGM�̍Đ�
void SoundBox::playbgm(int snum){
	int newbgm = sounds.at(snum);
	if (bgm == newbgm) return;
	StopSoundMem(bgm);
	bgm = newbgm;
	PlaySoundMem(bgm, DX_PLAYTYPE_BACK);
}


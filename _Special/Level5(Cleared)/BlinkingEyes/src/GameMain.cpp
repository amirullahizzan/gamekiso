#include "WinMain.h"

int eyes_Handle[3]; //you have to put it in init cannot be on global scope... this works.
int face_Handle;
int mouth_Handle[3];


int i_eyes = 0;
int i_mouth = 0;

void GameInit()
{
eyes_Handle[0] = LoadGraph("data/eye1.png", 0);
eyes_Handle[1] = LoadGraph("data/eye2.png", 0);
eyes_Handle[2] = LoadGraph("data/eye3.png", 0);

face_Handle = LoadGraph("data/face.png", 0);
mouth_Handle[0] = LoadGraph("data/mouce3.png", 0);
mouth_Handle[1] = LoadGraph("data/mouce2.png", 0);
mouth_Handle[2] = LoadGraph("data/mouce1.png", 0);

}


int eyestick;
int dialoguetimer;

void BlinkAnimManager()
{
	if (eyestick > 265)
	{
		i_eyes = 1;
	}
	if (eyestick > 270)
	{
		i_eyes = 2;

	}
	if (eyestick > 285)
	{
		i_eyes = 0;
		eyestick = 0;
	}


}

int mouthtimer = 0;
int times = 0;
void MouthAnimManager(int count)
{
	//already looping itself with the update for
	if (times < count)
	{
			mouthtimer++;
		if (mouthtimer > 20)
		{
			i_mouth = 1;
		}
		if (mouthtimer > 25)
		{
			i_mouth = 2;
		}
		if (mouthtimer > 35)
		{
			i_mouth = 0;
			times++;
			mouthtimer = 0;

		}
		
	}
}


struct TimeManager
{
	int timermilisec = 0;
	int timerseconds = 0;
	void GameTimer()
	{
		timermilisec++;
		if (timermilisec > 60)
		{
			timerseconds++;
			timermilisec = 0;
		}

	}
};

TimeManager timemanager;

void GameUpdate()
{
	timemanager.GameTimer();
	eyestick++;
	BlinkAnimManager();


}


struct Dialogue {

	void DrawDialogue(const char* Name, const char* Dialogue, int Timer, int MouthCount)
	{
		if (timemanager.timerseconds > Timer)
		{

		int x1 = 0+50;
		int y1 = 460;
		int x2 = WINDOW_W - 50;
		int y2 = 560;
		int dboxoffset = 12;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(x1-3, y1-3, x2+3, y2+3,WHITE,1);
		DrawBox(x1, y1, x2, y2,BLACK,1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawString(x1+dboxoffset, y1+dboxoffset, Name, YELLOW, 0);
		DrawString(x1+dboxoffset, y1+dboxoffset+22, Dialogue, WHITE, 0);
		dialoguetimer++;
		MouthAnimManager(MouthCount);

		}
	};
};

int alpha = 255;
void FadeIn()
{
	if (alpha > 0)
	{
		alpha--;

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBox(0, 0, WINDOW_W, WINDOW_H, BLACK, TRUE);

		
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void GameDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawGraph(0, 0, face_Handle, 1);
	DrawGraph(0, 0, eyes_Handle[i_eyes], 1);
	DrawGraph(0, 0, mouth_Handle[i_mouth], 1);
	FadeIn();
	Dialogue dialogue;
	dialogue.DrawDialogue("•P—l", "‚©‚í‚¢‚¢‚Å‚·‚í!!", 3,5);


//	DrawString(0, 0, "‚¨‚Í‚æ‚¤‚²‚´‚¢‚Ü‚·", WHITE, 0);

}

void GameExit()
{


}

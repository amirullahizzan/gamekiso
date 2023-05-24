#include "Main.h"
#include "Game.h"
int gauge_x2;
int gaugeborder_x1;
int gaugeborder_x2;
int movinggauge_x1;
int movinggaugeborder_x1;
int movinggauge_x2;
int movinggaugeborder_x2;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	gauge_x2 = 100;
	gaugeborder_x1 = 100;
	gaugeborder_x2 = 300;

	movinggauge_x2 = 100;
	movinggaugeborder_x2 = 200;

	movinggauge_x1 = 100;
	movinggaugeborder_x1 = 100;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------



class GaugeBar
{
public:
	void GaugeOverTime()
	{
		if (gauge_x2 < gaugeborder_x2)
		{
			gauge_x2++;
		}
	}
	void ResetGauge()
	{
		//Resets Gauge to Gaugeborder
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			gauge_x2 = gaugeborder_x1;
		}
	}
	void Draw()
	{
		DrawBox(100, 120, gauge_x2, 140, GREEN, 1);
		DrawLineBox(gaugeborder_x1, 120, gaugeborder_x2, 140, GetColor(255, 255, 255));
		DrawString(100, 60, "カウント１　：常に増え続ける（２００まで）", GetColor(255, 255, 255));
		DrawString(100, 80, "スペースキー：０に戻る", GetColor(255, 255, 255));
	}
	
private:

};



class MovingGaugeBar
{
public :
	void MoveGaugeBar()
	{
		if (CheckHitKey(KEY_INPUT_LEFT) && movinggauge_x2 > movinggaugeborder_x1)
		{
			movinggauge_x2--;
		}
		else if (CheckHitKey(KEY_INPUT_RIGHT) && movinggauge_x2 < movinggaugeborder_x2)
		{
			movinggauge_x2++;
		}
	}

	void Draw()
	{
		DrawString(100, 180, "カウント２　：左右キーで値の増減（０～１００）", GetColor(255, 255, 255));
		DrawBox(movinggauge_x1, 200, movinggauge_x2, 220, BLUE, 1);
		DrawLineBox(movinggaugeborder_x1, 200, movinggaugeborder_x2, 220, GetColor(255, 255, 255));

	}
};

void GameUpdate()
{
	GaugeBar().GaugeOverTime();
	GaugeBar().ResetGauge();
	MovingGaugeBar().MoveGaugeBar();
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	GaugeBar().Draw();
	MovingGaugeBar().Draw();
	
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
}

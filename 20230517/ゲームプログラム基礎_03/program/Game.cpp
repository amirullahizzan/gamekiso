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
//	����������
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
//	�X�V����
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
		DrawString(100, 60, "�J�E���g�P�@�F��ɑ���������i�Q�O�O�܂Łj", GetColor(255, 255, 255));
		DrawString(100, 80, "�X�y�[�X�L�[�F�O�ɖ߂�", GetColor(255, 255, 255));
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
		DrawString(100, 180, "�J�E���g�Q�@�F���E�L�[�Œl�̑����i�O�`�P�O�O�j", GetColor(255, 255, 255));
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
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	GaugeBar().Draw();
	MovingGaugeBar().Draw();
	
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
}

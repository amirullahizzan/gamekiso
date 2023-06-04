#include "WinMain.h"

// =====================================================
//	グローバル変数
//	複数の関数で共通して使いたい変数はここに書く
// =====================================================


int bg_Handle[3];
int enemy_Handle[3];

int scenecount = 0;
// =====================================================
//		初期化
//	ゲーム開始直後に最初に1回だけ実行される関数
//	最初の値を変数に入れたいときに使う
// =====================================================
void GameInit()
{
	bg_Handle[0] = LoadGraph("data/BG/pipo-battlebg001.jpg",0 );
	enemy_Handle[0] = LoadGraph("data/zakoB.png",0 );


}
bool isGame = false;


struct TimeManager
{
	int miliseconds = 0;
	int seconds = 0;

	void TimeUpdate()
	{
		if (isGame == true)
		{
			miliseconds++;

			if (miliseconds > 60)
			{
				seconds++;
				miliseconds = 0;
			}
		}

	}

	bool istimeReset = false;
	void ResetTime()
	{
		if (!istimeReset)
		{
			miliseconds = 0;
			seconds = 0;
			istimeReset = true;
		}
	}

};

TimeManager timemanager;

int enemyhp = 100;

struct Player
{
	int playerhp = 100;
	int playerdmg = 0;
	void DealDamage()
	{
		enemyhp -= playerdmg;
	}
};

struct Enemy
{
};

Player player;
Enemy enemy;

struct RythmManager
{
	int x = 200;
	int x2 = 200;
	int yfix = 280;
	int yfix2 = 380;

	int center_x = WINDOW_W/2;
	int center_y = WINDOW_H/2;

	void DrawTurnDisplay()
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 220);
		DrawBox(WINDOW_W / 2 - 50 - 3, WINDOW_H / 2 + 10 - 3, WINDOW_W / 2 + 55 + 3, WINDOW_H / 2 + 40 + 3, WHITE, 1);
		DrawBox(WINDOW_W / 2 - 50, WINDOW_H / 2 + 10, WINDOW_W / 2 + 55, WINDOW_H / 2 + 40, BLACK, 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawString(WINDOW_W / 2 - 40, WINDOW_H / 2 + 15, "攻撃ターン", YELLOW, 0);
	}


	

	int BoxGreenx1 = center_x - 40;
	int BoxGreenx2 = BoxGreenx1 + 40;
	int BoxBluex1 = center_x - 90;
	int BoxBluex2 = BoxBluex1 + 160;

	int triggerdelayseconds = 3;
	
	int xTrigger = 0;

	bool isOnGreen = false;
	bool isOnBlue = false;

	int DefWhitex1 = center_x - 120;
	int DefWhitex2 = DefWhitex1 + 20;

	bool isAttackMode = true;
	bool isDefenseMode = false;

	bool isOnWhite = true;


	void DrawTrigger()
	{
	
		DrawBox(10 + xTrigger, yfix - 10, 20+xTrigger, yfix2 + 10, RED, 1);
		if (timemanager.seconds > displaydelay+triggerdelayseconds &&isAttackMode)
		{
			xTrigger+=2;
		
			if (xTrigger > BoxGreenx1 && xTrigger < BoxGreenx2)
			{
			isOnGreen = true;
			}
			if (xTrigger > BoxBluex1 && xTrigger < BoxBluex2)
			{
			isOnBlue = true;
			}
		}

		if (timemanager.seconds > displaydelay + triggerdelayseconds && isDefenseMode)
		{
			xTrigger += 2;

			if (xTrigger > DefWhitex1 && xTrigger < DefWhitex2)
			{
				isOnWhite = true;
			}
		}
	}


	void DrawBackgroundBox()
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
		DrawBox(20, yfix, WINDOW_W - 20, yfix2, BLACK, 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}


	int playerhpx1 = 10;
	int playerhpy1 = 400;
	int playerhpx2 = playerhpx1+200;
	int playerhpy2 = playerhpy1+30;

	void DrawPlayerHP()
	{
		DrawBox(playerhpx1-2, playerhpy1-2, playerhpx2+2, playerhpy2+2,WHITE,1);
		DrawBox(playerhpx1, playerhpy1, playerhpx2, playerhpy2,BLACK,1);
		DrawBox(playerhpx1+2, playerhpy1+2, playerhpx2-2, playerhpy2-2,GREEN,1);
	}

	int enemyhpx1 = 10;
	int enemyhpy1 = 10;
	int enemyhpx2 = enemyhpx1 + 300;
	int enemyhpy2 = enemyhpy1 + 30;

	void DrawEnemyHP()
	{
		DrawBox(enemyhpx1 - 2, enemyhpy1 - 2, enemyhpx2 + 2, enemyhpy2 + 2, WHITE, 1);
		DrawBox(enemyhpx1, enemyhpy1, enemyhpx2, enemyhpy2, BLACK, 1);
		DrawBox(enemyhpx1 + 2, enemyhpy1 + 2, ((enemyhpx2/100) * enemyhp), enemyhpy2 - 2, RED, 1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
		DrawBox(10, 42, 10+50, 42+20, BLACK, 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawString(15, 45, "Tree", YELLOW, 0);
	}


	bool isGaugeOn = false;

	void DrawAttackPattern()
	{
		if (isAttackMode && isGaugeOn)
		{
		DrawBox(BoxBluex1, yfix, BoxBluex2, yfix2, BLUE, 1);
		DrawBox(BoxGreenx1, yfix, BoxGreenx2, yfix2, GREEN, 1);
		}
	}

	void DrawDefensePattern()
	{
		if (isDefenseMode && isGaugeOn)
		{
		DrawBox(DefWhitex1, yfix, DefWhitex2, yfix2, WHITE, 1);
		}
		
	}

	

	int displaydelay = 1;

	bool isdamageDealt = false;

	void DrawUI()
	{
		if (isGame)
		{
			
			DrawPlayerHP();
			DrawEnemyHP();
		}
	}

	void DrawRythmBar()
	{
		if (isGame && scenecount == 1 && timemanager.seconds > displaydelay)
		{
			isGaugeOn = true;
			DrawTurnDisplay();
			DrawBackgroundBox();
			DrawAttackPattern();
			DrawDefensePattern();
			
			DrawTrigger();
			
		}
		else
		{
			timemanager.ResetTime();
			isGaugeOn = false;
		}
	}


};
RythmManager rythmmanager;



struct SceneManager
{
	int getscenecount;
	void DebugGrid()
	{
		DrawLine(WINDOW_W / 2, 0 , WINDOW_W / 2, WINDOW_H,YELLOW,1);
		DrawLine(0, WINDOW_H/2, WINDOW_W, WINDOW_H/2,YELLOW,1);
	}

	void LoadMenu()
	{
		DrawBox(0,0,WINDOW_W, WINDOW_H,BLACK,1);
		DrawString(WINDOW_W/2-50, WINDOW_H/2-100,"PEPE SOULS", YELLOW, 0);
		DrawString(WINDOW_W/2-92, WINDOW_H/2+150,"Press Space to Start", YELLOW, 0);
	}

	void LoadStage1()
	{
		//BG on top
		DrawGraph(0, 0, bg_Handle[0], 0);
		DrawGraph((WINDOW_W / 2) - 120, 0, enemy_Handle[0], 1);
		rythmmanager.DrawRythmBar();

	}

	void SetStage(int Count)
	{
		getscenecount = Count; //updates
		if (Count == 0)
		{
			LoadMenu();
			
		}
		if(Count == 1)
		{
			isGame = true;
			LoadStage1();
			
		}
	}


};

SceneManager scenemanager;


void PlayerControl()
{
	if (!isGame && IsKeyOn(KEY_INPUT_SPACE))
	{
		//MAINMENU
		scenecount=1;
	}

	if (isGame && rythmmanager.isGaugeOn)
	{
		if (IsKeyOn(KEY_INPUT_SPACE) && rythmmanager.isAttackMode)
		{
			if (rythmmanager.isOnBlue)
			{
				player.playerdmg += 10;
			}
		
			if (rythmmanager.isOnGreen)
			{
				player.playerdmg += 20;
			
			}
			else
			{
			//MISS HIT DISPLAY
			}
			timemanager.ResetTime();
			player.DealDamage();
			rythmmanager.xTrigger = 0;
			rythmmanager.isDefenseMode = true;

			rythmmanager.isAttackMode = false;
		}

		if (IsKeyOn(KEY_INPUT_SPACE) && rythmmanager.isDefenseMode)
		{
			if (!rythmmanager.isOnWhite)
			{
				player.playerhp -= 20;
			}
			rythmmanager.xTrigger = 0;
			rythmmanager.isDefenseMode = false;
			rythmmanager.isAttackMode = true;

		}

	}
}

void GameUpdate()
{
	timemanager.TimeUpdate();
	PlayerControl();
}



void GameDraw()
{
	scenemanager.SetStage(scenecount);
	rythmmanager.DrawUI();
	scenemanager.DebugGrid();


}

void GameExit()
{


}

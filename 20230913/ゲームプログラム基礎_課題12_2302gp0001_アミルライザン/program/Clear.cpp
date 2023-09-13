#include "Main.h"
#include "Game.h"
#include "Clear.h"

int gameclearbg_handler = -1;

int bg_x;
int bg_y;

void GameClearLoad()
{
	gameclearbg_handler =  LoadGraph("data/clear_bg.bmp");
}

void GameClearInit()
{
	bg_x = 0;
	bg_y = 0;
}

void GameClearUpdate()
{
	if (PushHitKey(KEY_INPUT_SPACE))
	{
	scene_next = SCENE_TITLE;
	}
}

void GameClearRender()
{


	DrawGraph(bg_x, bg_y, gameclearbg_handler, 1);
	DrawString(SCREEN_W /2, 250, "おめでとうございます！", GetColor(0,0,0));
	DrawFormatString(20, 100, GetColor(0, 255, 255), "クリアまでにかかった時間：%d", stage_frame);
}
#include "Main.h"
#include "Game.h"

#define PLAYER_SPEED	3.0f

int player_image;
float player_x;
float player_y;
const int MAXTIMER = 300;

int timecounter_ms = 0;
int timecounter_sec = 0;
bool isInControl = true;


float record_x[MAXTIMER] = {};
float record_y[MAXTIMER] = {};

enum GameMode
{
	WAITMODE, RECORDMODE, REPLAYMODE
};

int gameMode;

void GameTimer(int nextMode)
{
		timecounter_ms++;
	if (timecounter_ms >= MAXTIMER)
	{
		gameMode = nextMode;
		timecounter_ms = 0;
	}
}

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	player_image = LoadGraph( "data/player.bmp" );

	player_x = 100.0f;
	player_y = 200.0f;
	gameMode = WAITMODE;
}

void PlayerControl()
{
	if (isInControl)
	{
		
			if (CheckHitKey(KEY_INPUT_RIGHT)) {
				player_x += PLAYER_SPEED;
			}
			if (CheckHitKey(KEY_INPUT_LEFT)) {
				player_x -= PLAYER_SPEED;
			}
			if (CheckHitKey(KEY_INPUT_DOWN)) {
				player_y += PLAYER_SPEED;
			}
			if (CheckHitKey(KEY_INPUT_UP)) {
				player_y -= PLAYER_SPEED;
			}
		
	}

}

void RecordControl()
{
	record_x[timecounter_ms] = player_x;
	record_y[timecounter_ms] = player_y;

}

void ReplayControl()
{
	player_x = record_x[timecounter_ms];
	player_y = record_y[timecounter_ms];
}

void GameUpdate()
{
	PlayerControl();

	switch (gameMode)
	{

	case WAITMODE :
		if (CheckHitKeyAll())
		{
			gameMode = RECORDMODE;
		}
		isInControl = true;
		break;

	case RECORDMODE:
		GameTimer(REPLAYMODE);
		RecordControl();
		break;

	case REPLAYMODE:
		GameTimer(WAITMODE);
		isInControl = false;
		ReplayControl();
		break;
	}
}

void GameRender()
{
	DrawGraphF( player_x, player_y, player_image, TRUE );

	switch (gameMode)
	{

	case REPLAYMODE:
			DrawString(20, 20, "十字キー：プレイヤー移動", GetColor(160, 160, 160));
		break;
	default :
		DrawString(20, 20, "十字キー：プレイヤー移動", GetColor(255, 255, 255));
		break;
	}

	if (gameMode == RECORDMODE)
	{
		DrawFormatString(20, 60, GetColor(255, 255, 20), "Time Counter : %d / %d", timecounter_ms, MAXTIMER);
	}
	if (gameMode == REPLAYMODE)
	{
		DrawFormatString(20, 60, GetColor(200, 200, 255), "Time Counter : %d / %d", timecounter_ms, MAXTIMER);
	}
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
}

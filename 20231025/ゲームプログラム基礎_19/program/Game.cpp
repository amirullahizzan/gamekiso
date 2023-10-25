#include "Main.h"
#include "Game.h"
#include "Float2.h"
#include "Hit.h"

#define PLAYER_SPEED	5.0f

int player_image;
Float2 player_pos;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	player_image = LoadGraph( "data/player.bmp" );

	player_pos.x = SCREEN_W / 2.0f;
	player_pos.y = SCREEN_H / 2.0f;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	int joypadnum = GetJoypadNum();

	if (joypadnum > 0)
	{
		//gamejoypad number, input code
		//if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT || GetJoypadInputState(DX_INPUT_PAD1)& PAD_INPUT_B)
		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT)
		{
			player_pos.x += PLAYER_SPEED;
		}
		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT)	
		{
			player_pos.x -= PLAYER_SPEED;
		}
		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN)
		{
			player_pos.y += PLAYER_SPEED;
		}
		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP)
		{
			player_pos.y -= PLAYER_SPEED;
		}

		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2)
		{
			player_pos.x += PLAYER_SPEED;
		}
		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3)
		{
			player_pos.x -= PLAYER_SPEED;
		}
		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1)
		{
			player_pos.y += PLAYER_SPEED;
		}
		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_4)
		{
			player_pos.y -= PLAYER_SPEED;
		}
		
	}
	else
	{
		if (CheckHitKey(KEY_INPUT_RIGHT))	player_pos.x += PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_LEFT))	player_pos.x -= PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_DOWN))	player_pos.y += PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_UP))		player_pos.y -= PLAYER_SPEED;
	}

	DINPUT_JOYSTATE joystick = {};
	
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	DrawRotaGraphF( player_pos.x, player_pos.y, 1.0f, TO_RADIAN( 0.0f ), player_image, TRUE );

	DrawString( 16, 16, "コントローラー十字キー：プレイヤー移動（左スティックやＡＢＸＹでも）", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
}

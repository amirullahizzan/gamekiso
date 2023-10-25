#include "Main.h"
#include "Game.h"
#include "Float2.h"
#include "Hit.h"

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	int joypadnum = GetJoypadNum();

	if (joypadnum == 0)
	{
		return;
	}
	if( PushHitKey( KEY_INPUT_SPACE ) )
	{
		//Pad inputs
		//0~1000
		//-1~ Milisec
		//-1~1 Vibration Modes
		StartJoypadVibration(DX_INPUT_PAD1,500,-1,1);
	}
	
	if (PushHitKey(KEY_INPUT_A))
	{
		//end effect
	StopJoypadVibration(DX_INPUT_PAD1,1);
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	DrawString( 16, 16, "スペースキー：コントローラー振動", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
}

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

XINPUT_STATE input;
void GameUpdate()
{
	if (input.Buttons[0] == 1)
	{
		exit(0);
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	DrawString( 16, 16, "コントローラー情報（ XInput ）", GetColor( 255, 255, 255 ) );

	//take data
	//XINPUT_STATE input;
	GetJoypadXInputState( DX_INPUT_PAD1, &input );

	//doesnt go to 0 by itself
	DrawFormatString( 16, 48, GetColor( 255, 255, 255 ), "STICK L %6d %6d", input.ThumbLX, input.ThumbLY );

	DrawFormatString( 16, 64, GetColor( 255, 255, 255 ), "STICK R %6d %6d", input.ThumbRX, input.ThumbRY );

	DrawFormatString( 16, 96, GetColor( 255, 255, 255 ), "TRIGGER %3d %3d", input.LeftTrigger, input.RightTrigger );

	for( int i = 0; i < 16; i++ ){
		DrawFormatString( 16, 128 + 16 * i, GetColor( 255, 255, 255 ), "BUTTON[%2d] : %d", i, input.Buttons[i] );
	}
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
}

#include "Main.h"
#include "Game.h"
#include "Float2.h"
#include "Hit.h"

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
}
//---------------------------------------------------------------------------------
//	�X�V����
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
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	DrawString( 16, 16, "�R���g���[���[���i XInput �j", GetColor( 255, 255, 255 ) );

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
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
}

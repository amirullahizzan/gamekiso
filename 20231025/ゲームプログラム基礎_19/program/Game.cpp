#include "Main.h"
#include "Game.h"
#include "Float2.h"
#include "Hit.h"

#define PLAYER_SPEED	5.0f

int player_image;
Float2 player_pos;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	player_image = LoadGraph( "data/player.bmp" );

	player_pos.x = SCREEN_W / 2.0f;
	player_pos.y = SCREEN_H / 2.0f;
}
//---------------------------------------------------------------------------------
//	�X�V����
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
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	DrawRotaGraphF( player_pos.x, player_pos.y, 1.0f, TO_RADIAN( 0.0f ), player_image, TRUE );

	DrawString( 16, 16, "�R���g���[���[�\���L�[�F�v���C���[�ړ��i���X�e�B�b�N��`�a�w�x�ł��j", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
}

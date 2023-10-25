#include "Main.h"
#include "Game.h"
#include "Float2.h"
#include "Hit.h"

int player_image;
Float2 player_pos;

int stick_x;
int stick_y;
float player_rot;
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

	if (joypadnum == 0)
	{
		return;
	}
	else 
	{
		//���� 
		GetJoypadAnalogInput(&stick_x, &stick_y, DX_INPUT_PAD1);
		//�E 
		//GetJoypadAnalogInputRight(&stick_x, &stick_y, DX_INPUT_PAD1);
		if (stick_x != 0 || stick_y != 0)
		{

		player_pos.x += stick_x * 0.01f;
		player_pos.y += stick_y * 0.01f;
		//if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT)
		player_rot = TO_DEGREE(GetRadian_LengthYX(stick_y, stick_x));
		player_rot = 180.0f / 3.14159265f * atan2f(stick_y, stick_x);
		}
	}
	
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	DrawRotaGraphF( player_pos.x, player_pos.y, 1.0f, TO_RADIAN( player_rot ), player_image, TRUE );
	clsDx();
	printfDx("analog input X : %5d\n", stick_x);
	printfDx("analog input Y : %5d\n", stick_y);
	DrawString( 16, 16, "�Q�[���p�b�h���X�e�B�b�N�ňړ�", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
}

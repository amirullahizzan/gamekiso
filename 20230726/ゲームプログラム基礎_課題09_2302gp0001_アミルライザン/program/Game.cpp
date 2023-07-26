#include "Main.h"
#include "Game.h"

//	�r�d�f�[�^�p�̕ϐ�
int se_walk;	//	����
int se_door;	//	�h�A���J���鉹
int se_rain;	//	�J�̉�

//	�v���C���[�ϐ�
//	�v���C���[�摜
int player_image;
int field_image;
int room_image;
//	�v���C���[�w���W
float player_x;

#define RAIN_AMOUNT 80

int rain_x[RAIN_AMOUNT];
int rain_y[RAIN_AMOUNT];
int rain_speed[RAIN_AMOUNT];
int getRainDuration() { return GetRand(100)+20; }
int rain_duration[RAIN_AMOUNT];

enum SceneEnum
{
	isInRoom = 0, isInField = 1
}; 

//int puddle_x[RAIN_AMOUNT];
//int puddle_y[RAIN_AMOUNT];
//int puddle_rad[RAIN_AMOUNT];
//int puddle_duration[RAIN_AMOUNT];
//
//void DrawPuddle()
//{
//	for (int i = 0; i < RAIN_AMOUNT; i++)
//	{
//		if (rain_duration[i] > getRainDuration())
//		{
//			puddle_x[i] = rain_x[i];
//			puddle_y[i] = rain_y[i];
//			DrawCircle(puddle_x[i], puddle_y[i], puddle_rad[i], GetColor(200, 200, 255), 0, 1);
//			puddle_rad[i]++;
//		}
//		
//	}
//}


void DrawRain()
{
	for (int i = 0; i < RAIN_AMOUNT; i++)
	{
		rain_duration[i]++;
		rain_speed[i] = GetRand(3) + 10;
		rain_x[i] += rain_speed[i];
		rain_y[i] += rain_speed[i];
		DrawLine(rain_x[i], rain_y[i], rain_x[i] + 5, rain_y[i] + 20, GetColor(200, 200, 255), 1);
		if (rain_duration[i] > getRainDuration())
		{
			rain_x[i] = GetRand(SCREEN_W)-200;
			rain_y[i] = GetRand(SCREEN_H / 2)-200;
			rain_duration[i] = 0;
		}
	}
	
}

void InitRain()
{
	for (int i = 0; i < RAIN_AMOUNT; i++)
	{
		rain_speed[i] = GetRand(3)+10;
		rain_x[i] = GetRand(SCREEN_W) - 200;
		rain_y[i] = GetRand(SCREEN_H) - 200;
	}

}

void GameInit()
{
	//	�e�r�d�f�[�^�̓ǂݍ���
	se_walk = LoadSoundMem( "data/se_walk.mp3" );	//	����
	se_door = LoadSoundMem( "data/se_door.mp3" );	//	�h�A���J���鉹
	se_rain = LoadSoundMem( "data/se_rain.mp3" );	//	�J�̉�

	//	�v���C���[�摜�̓ǂݍ���
	player_image = LoadGraph( "data/player.bmp" );
	field_image = LoadGraph( "data/image_field.bmp" );
	room_image = LoadGraph( "data/image_room.bmp" );
	//	�v���C���[�������W�ݒ�
	player_x = 100.0f;

	InitRain();
	
}

SceneEnum sceneenum;

int scenenumber = 0;

void GameUpdate()
{
	//	�E�L�[�Ńv���C���[�ړ�
	if( CheckHitKey( KEY_INPUT_RIGHT )  )
	{
		player_x += 5.0f;
		if (!CheckSoundMem(se_walk))
		{
			PlaySoundMem(se_walk, 2);
		}

		if (scenenumber >= isInField )
		{
			if (!CheckSoundMem(se_rain))
			{
				PlaySoundMem(se_rain, 3);
			}
		}
	}

	

	//	��ʉE�܂ōs������
	if( player_x > SCREEN_W-1 )
	{
		//	���ɂ���
		scenenumber++;
		player_x = -50.0f;
		PlaySoundMem(se_door,2);
	}

	if (scenenumber == isInRoom)
	{
		StopSoundMem(se_rain);
	}
	if (scenenumber >= 2)
	{
		scenenumber = 0;
	}

}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	
	if (scenenumber == isInRoom)
	{
		DrawGraph(0, 0, room_image, 0);
	}
	else if (scenenumber >= isInField)
	{
		DrawGraph(0, 0, field_image, 0);
	}
	//	�v���C���[�摜�̕`��
	DrawGraphF( player_x, 200.0f, player_image, TRUE );

	if (scenenumber >= isInField)
	{
		DrawRain();
		//DrawPuddle();
	}


	DrawString( 20,  20, "�E�L�[�F�v���C���[�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 20,  40, "���@�ړ����� se_walk �Đ�", GetColor( 255, 255, 0 ) );
	DrawString( 20,  60, "���@��ʉE�܂ōs�����獶����o�Ă���", GetColor( 255, 255, 255 ) );
	DrawString( 20,  80, "���@���̂��тɔw�i��ύX����i�؂�ւ��Ƃ��̃h�A�� se_door �j", GetColor( 255, 255, 0 ) );
	DrawString( 20, 100, "���@�t�B�[���h�̎��͉J�̕`��Ɖ��i se_rain �j", GetColor( 255, 255, 0 ) );
	

}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	InitSoundMem();
}

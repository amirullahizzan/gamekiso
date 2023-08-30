#include "Main.h"
#include "Game.h"

//	�v���C���[�̈ړ��X�s�[�h
#define PLAYER_SPEED	3.0f
//	�v���C���[�摜
int player_image;
int npc_image;
//	�v���C���[���W
float player_x;
float player_y;
float npc_x;
float npc_y;

//	�Q�[�����[�h
enum {
	MODE_WAIT,		//	�O�F�����L�[���������܂ő҂��Ă��郂�[�h
	MODE_MOVE,		//	�P�F�\���L�[�ňړ����郂�[�h�i���W�̋L�^���j
	MODE_REPLAY,	//	�Q�F���v���C���Đ����郂�[�h
};

//	���������[�h���p�̕ϐ��i�O�F�҂��@�P�F����@�Q�F���v���C�j
int game_mode;

//	�L�^����ꏊ�̐�
#define RECORD_MAX	300
//	�v���C���[�̍��W���L�^����p�̕ϐ�
float record_x[RECORD_MAX];
float record_y[RECORD_MAX];
//	�������t���[���ڂ��𐔂���p�̕ϐ�
int frame_count;
int frame_countmult = 1;


//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�摜�̓ǂݍ���
	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );
	//	�������W�̐ݒ�
	player_x = 100.0f;
	player_y = 200.0f;
	npc_x = -50;
	npc_y = -50;

	//	�ŏ��͑҂���Ԃ���J�n���܂�
	game_mode = MODE_WAIT;
	//	�O�t���[���ڂ���J�n
	frame_count = 0;
	//	�L�^���W���O������
	for( int i = 0; i < RECORD_MAX; i++ ){
		record_x[i] = 0.0f;
		record_y[i] = 0.0f;
	}
}


void GameUpdate()
{
	//	���[�h�ɂ���ď����𕪂��܂�
	switch (game_mode) {
	case MODE_WAIT:		//	�҂���Ԃ̂Ƃ�
		//	�����L�[����������
		if (CheckHitKeyAll()) {
			//	�v���C���[�𓮂������[�h�ɂ��܂�
			game_mode = MODE_MOVE;
			//	�O�t���[���ڂ���L�^���J�n
			frame_count = 0;
		}
		break;

	case MODE_MOVE:		//	�ړ���Ԃ̂Ƃ�
		//	�\���L�[�Ńv���C���[���W�̍X�V
		if (CheckHitKey(KEY_INPUT_RIGHT))	player_x += PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_LEFT))	player_x -= PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_DOWN))	player_y += PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_UP))		player_y -= PLAYER_SPEED;
		//	�v���C���[�̍��W�̒l���L�^�p�̂Ƃ���ɓ���܂�
		record_x[frame_count] = player_x;
		record_y[frame_count] = player_y;

		//	�J�E���g�̒l�𑝂₷
		frame_count++;

		//	�Ō�܂ŋL�^�o������
		if (frame_count >= RECORD_MAX) {
			//	���v���C�J�n
			game_mode = MODE_REPLAY;
			//	���v���C�Ŏg�����Ԃ��ŏ�����
			frame_count = 0;
		}
		break;

	case MODE_REPLAY:	//	���v���C��Ԃ̂Ƃ�
		//	���v���C�Đ��i�L�^�������W record_x �����ԂɃv���C���[���W player_x �ɓ���Ă����j
		npc_x = record_x[frame_count];
		npc_y = record_y[frame_count];

		//	�J�E���g�̒l�𑝂₷
		if (frame_count>=0)
		{
			frame_count += frame_countmult;
			if (frame_count<0)
			{
				frame_count = 0;
			}
		}

		//	�Ō�܂ōĐ�������
		if (frame_count >= RECORD_MAX) {
			//	�҂����[�h�ɂ���
			game_mode = MODE_WAIT;
			//	���̋L�^�̂��߂Ƀt���[�������Z�b�g
			frame_count = 0;
		}
		break;
	}
}

void PlaybackControl()
{
	if (PushHitKey(KEY_INPUT_F1))
	{
		frame_countmult--;
	}
	if (PushHitKey(KEY_INPUT_F2))
	{
		frame_countmult = 0;
	}
	if (PushHitKey(KEY_INPUT_F3))
	{
		frame_countmult++;
	}
	if (PushHitKey(KEY_INPUT_F4))
	{
		frame_count = 0;
	}
}

int flickertimer = 0;

void PlaylistBar(int frame)
{
	int barposition = 220;
	DrawBox(220 - 5, 400 - 5, 520 + 5, 420 + 5, GetColor(0, 0, 0), 1);
	DrawBox(barposition,400, barposition+frame,420,GetColor(255,255,255),1);
}

void GameRender()
{
	//	��ʂɃv���C���[�摜�̕`��

	//	���[�h���Ƃɕ`�悷�镶�����ς��܂�
	switch( game_mode ){
	case MODE_WAIT:		//	�҂���Ԃ̎�
		DrawString( 20, 20, "�\���L�[�F�v���C���[�ړ��i�Ƌ��ɋL�^���J�n���܂��j", GetColor( 255, 255, 255 ) );
		DrawString( 20, 40, "���v���C�Đ����͕ʃL�����𓮂���", GetColor( 255, 255, 0 ) );
		frame_countmult = 1;
		break;

	case MODE_MOVE:		//	�ړ���Ԃ̎�
		DrawString( 20, 20, "�\���L�[�F�v���C���[�ړ�", GetColor( 255, 255, 255 ) );
		DrawString( 20, 40, "���v���C�Đ����͕ʃL�����𓮂���", GetColor( 255, 255, 0 ) );
		DrawFormatString( 20, 80, GetColor( 255, 255, 0 ), "�v���C���[���W�L�^���F%3d/%d", frame_count, RECORD_MAX );
		break;

	case MODE_REPLAY:	//	���v���C�̎�
		DrawGraphF(npc_x, npc_y, npc_image, TRUE);

		DrawString( 20, 20, "�\���L�[�F�v���C���[�ړ�", GetColor( 128, 128, 128 ) );
		DrawString( 20, 40, "���v���C�Đ����͕ʃL�����𓮂���", GetColor( 255, 255, 0 ) );
		DrawString( 20, 60, "���@�Ƃ����킯�Ń��v���C�ňړ�����̂͂m�o�b�i npc.bmp �j", GetColor( 0, 255, 0 ) );
		DrawFormatString( 20, 80, GetColor( 0, 255, 255 ), "���v���C�Đ����@�@�@�F%3d/%d", frame_count, RECORD_MAX );
		//DrawFormatString( 20, 100, GetColor( 0, 255, 255 ), "flicker�@�@�@�F%3d", flickertimer );

		DrawString(20, 300, "f1 : Reverse/Slowdown", GetColor(0, 255, 0));
		DrawString(20, 320, "f2 : Pause", GetColor(0, 255, 0));
		DrawString(20, 340, "f3 : Resume/Fast Forward", GetColor(0, 255, 0));
		DrawString(20, 360, "f4 : Restart Replay", GetColor(0, 255, 0));
		DrawFormatString(20, 100, GetColor(0, 255, 255), "�Đ��X�s�[�h�@�@�F%d", frame_countmult);
		DrawFormatString(20, 220, GetColor(0, 255, 255), "frame % 100 : %d", frame_count % 100);


		PlaylistBar(frame_count);
		PlaybackControl();
		flickertimer++;
		//	���̕������_�ł����܂�
		if ((frame_count % 100 )< 70)
		{
			DrawString(200, 200, "�u���v���C���i���̕������_�ł����܂��j�v", GetColor(255, 255, 0));
		}
		
		break;
	}
	DrawGraphF(player_x, player_y, player_image, TRUE);

}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
}

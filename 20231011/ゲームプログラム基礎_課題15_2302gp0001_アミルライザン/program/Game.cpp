#include "Main.h"
#include "Game.h"
#include "Hit.h"
//	Float2 �\���̂��g�������̂�
#include "Float2.h"

//	�v���C���[�̈ړ��X�s�[�h�i���ʂ́j
#define PLAYER_NORMAL_SPEED	1.0f
//	�����X�s�[�h
#define PLAYER_FAST_SPEED	20.0f
//	�{�^���摜�̑傫��
#define BUTTON_SIZE		100.0f

//	�{�^���摜�p�̕ϐ�
int button_image;
//	�e�摜�p�̕ϐ�
int shadow_image;
//	�v���C���[�摜�p�̕ϐ�
int player_image;

bool isPressed = false;
int button_onpush_offset[2];

//	�v���C���[���W
Float2 player_pos;
//	�v���C���[�̌����i�x�j
float player_rot;
//	�v���C���[�X�s�[�h
float player_speed;

//	�{�^���̃T�C�Y
Float2 button_size;
//	�����ύX�{�^���̍��W
Float2 rot_button_pos;
//	�X�s�[�h�ύX�{�^��
Float2 speed_button_pos;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�{�^���摜�̓ǂݍ���
	button_image = LoadGraph( "data/button.bmp" );
	//	�e�摜�̓ǂݍ���
	shadow_image = LoadGraph( "data/shadow.bmp" );
	//	�v���C���[�摜�̓ǂݍ���
	player_image = LoadGraph( "data/player.bmp" );

	//	�v���C���[�̏������W�ݒ�
	player_pos.x = 100.0f;		//	player_pos �̒��ɂ��� x �� 100.0f �����܂�
	player_pos.y = 200.0f;		//	player_pos �̒��ɂ��� y �� 200.0f �����܂�
	//	�����͂O�x�ŊJ�n
	player_rot = 0.0f;
	//	���ʂ̃X�s�[�h�ŊJ�n
	player_speed = PLAYER_NORMAL_SPEED;

	//	�{�^���T�C�Y�̐ݒ�
	button_size.x = BUTTON_SIZE;
	button_size.y = BUTTON_SIZE;

	//	�����ύX�{�^���̍��W�ݒ�
	rot_button_pos.x = 200.0f;
	rot_button_pos.y = 300.0f;

	//	�X�s�[�h�{�^���̍��W
	speed_button_pos.x = 500.0f;
	speed_button_pos.y = 300.0f;
}

float player_speedmult = 1;

void GameUpdate()
{
	//	�}�E�X���W�̎擾
	Float2 mouse;
	mouse.x = GetMouseX();
	mouse.y = GetMouseY();

	//	�}�E�X�{�^�����������u�ԁi�{�^���摜���������������ς������j
	if( PushMouseInput() ){
		//	�}�E�X���W�������ύX�{�^���̎l�p�̒��ɂ�������i���W���傫���� Float2 �Ȃ̂� Float2 �œ����蔻�肷��֐����g���܂��j
		if( CheckPointBoxHit( mouse, rot_button_pos, button_size ) ){
			//	�v���C���[�̌����������_���ɕύX���܂�
			int player_rot_index = GetRand( 3 );
			switch (player_rot_index)
			{
			case 0: player_rot = 0;
				break;
			case 1: player_rot = 90;
				break;
			case 2: player_rot = 180;
				break;
			case 3: player_rot = 270;
				break;
			}
		}
	}

	if (CheckMouseInput())
	{
		if (CheckPointBoxHit(mouse, rot_button_pos, button_size))
		{
			button_onpush_offset[1] = 5;
		}
	}
	else
	{
		button_onpush_offset[1] = 0;
	}


	//	�܂��̓X�s�[�h�𕁒ʂɂ��Ă�����
	player_speed = PLAYER_NORMAL_SPEED;

	//	�}�E�X�{�^���������Ă���Ƃ��i�{�^���摜����������X�s�[�h�𑬂��������j
	if( CheckMouseInput() )
	{
		//	�}�E�X���W���X�s�[�h�{�^���̂Ƃ���ɂ�������
		if( CheckPointBoxHit( mouse, speed_button_pos, button_size ) ){
			//	�X�s�[�h�𑬂�����
			isPressed = true;
		}
		else
		{
			isPressed = false;
		}
		
		
	}
	

	if (isPressed)
	{
		if (player_speedmult < PLAYER_FAST_SPEED)
		{
			player_speedmult += 0.2;
		}
		button_onpush_offset[0] = 5;
	}
	else
	{
		button_onpush_offset[0] = 0;
		if (player_speedmult > 0.2)
		{
			player_speedmult -= 0.2;
		}

	}


	//	�v���C���[�̍��W�ړ��i�����Ă�������Ɂj�i����ɕω�����X�s�[�h�̒l���g���āj
	player_pos.x += player_speedmult * player_speed * GetLength_RotSotte( TO_RADIAN( player_rot ) );
	player_pos.y += player_speedmult * player_speed * GetLength_RotMukai( TO_RADIAN( player_rot ) );

	//	�v���C���[����ʂ̒[�܂ōs�����甽�΂���o�Ă���
	if( player_pos.x < 0.0f )		player_pos.x = SCREEN_W;
	if( player_pos.x > SCREEN_W )	player_pos.x = 0.0f;
	if( player_pos.y < 0.0f )		player_pos.y = SCREEN_H;
	if( player_pos.y > SCREEN_H )	player_pos.y = 0.0f;
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�v���C���[�̍��W�i player_pos �j�ƌ����i player_rot �j���g���ăv���C���[�摜�i player_image �j�̕`��
	DrawRotaGraphF( player_pos.x, player_pos.y, 1.0f, TO_RADIAN( player_rot ), player_image, TRUE );
	//	�����ύX�{�^���摜�̕`��
	DrawGraphF(rot_button_pos.x+15 , rot_button_pos.y + 15, shadow_image, TRUE);
	DrawGraphF( rot_button_pos.x+ button_onpush_offset[1], rot_button_pos.y + button_onpush_offset[1], button_image, TRUE );
	//	�X�s�[�h�{�^���摜�̕`��
	DrawGraphF( speed_button_pos.x+15, speed_button_pos.y+ 15, shadow_image, TRUE );
	DrawGraphF( speed_button_pos.x+ button_onpush_offset[0], speed_button_pos.y + button_onpush_offset[0], button_image, TRUE);

	DrawString( 16, 16, "���̎l�p���N���b�N�@�@�F�v���C���[�����������_���ɕύX", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "���@�����������u�E�v�u���v�u���v�u��v�̂S�̃����_����", GetColor( 255, 255, 0 ) );
	DrawString( 16, 48, "�E�̎l�p�������Ă���ԁF�v���C���[�̃X�s�[�h�A�b�v", GetColor( 255, 255, 255 ) );
	DrawString( 16, 64, "���@�����Ă���ԏ��X�ɃX�s�[�h�A�b�v�i�����ĂȂ������珙�X�ɃX�s�[�h�_�E���j", GetColor( 255, 255, 0 ) );
	DrawString( 16, 96, "���{�^���炵�������邽�߂ɉe�̕`��", GetColor( 255, 255, 0 ) );

	clsDx();
	//printfDx("%d",isPressed);
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( button_image );
	DeleteGraph( shadow_image );
	DeleteGraph( player_image );
}

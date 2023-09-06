#include "Main.h"
#include "Game.h"

//	�v���C���[�̈ړ��X�s�[�h
#define PLAYER_SPEED	3.0f

//	�v���C���[�p�̕ϐ�
int player_image;	//	�摜
float player_x;		//	�w���W
float player_y;		//	�x���W

//	�ꉞ�I�v�V�����̐��p�̒萔
#define OPTION_MAX		4

//	�I�v�V�����p�̕ϐ�
int option_image;	//	�摜
float option_x;		//	�w���W
float option_y;		//	�x���W

//	�P�F���W���L�^����ꏊ��p��
//	�L�^�ł��鐔
#define RECORD_MAX	100
//	�v���C���[�̍��W���L�^���Ă����p�̕ϐ�
float record_x[RECORD_MAX];
float record_y[RECORD_MAX];


enum
{
	Right = 0,
	Down = 90,
	Left = 180,
	Up = 270
};

int record_facing[RECORD_MAX] = {};
int player_facing = 0;
int option_facing = 0;

struct Option
{
	int x_ = 0;
	int y_ = 0;
	int facing_ = 0;
	int delay = 20;

	static int num_instances;

	Option()
	{
		num_instances++;
	}

	void FollowAI(int delaymult)
	{
		//	�R�F�I�v�V�����͋L�^�����l�����W�ɐݒ肷��
		//	�Q�O�t���[���O�̃v���C���[���W���I�v�V�����̍��W�ɂ��悤�Ǝv���܂�
		x_ = record_x[delay * delaymult];
		y_ = record_y[delay * delaymult ];
		facing_ = record_facing[15 * delaymult];
	}

	void DrawOption()
	{
		DrawRotaGraphF(x_, y_, 1.0f, TO_RADIAN(facing_), option_image, TRUE);
	}
};
int Option::num_instances = 0;

Option option1;
Option option2;
Option option3;
Option option4;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	���ꂼ��̉摜�̓ǂݍ���
	player_image	= LoadGraph( "data/player.bmp" );
	option_image	= LoadGraph( "data/option.bmp" );
	//	�v���C���[�̏������W�ݒ�
	player_x = 100.0f;
	player_y = 200.0f;
	//	�I�v�V�����̏������W�i��X�v���C���[�̍��W�ɂ��Ă����̂łƂ肠�����j
	option_x = 100.0f;
	option_y = 200.0f;

	//	�L�^�̈�̏����ݒ�
	for( int i = 0; i < RECORD_MAX; i++ ){
		//	�S���Ƀv���C���[���W�����Ă����܂�
		record_x[i] = player_x;
		record_y[i] = player_y;
	}
}




void GameUpdate()
{

	//	�\���L�[�Ńv���C���[���W�̍X�V
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		player_x += PLAYER_SPEED;
		player_facing = Right;
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		player_x -= PLAYER_SPEED;
		player_facing = Left;
	}
	if( CheckHitKey( KEY_INPUT_DOWN ) ){
		player_y += PLAYER_SPEED;
		player_facing = Down;
	}
	if( CheckHitKey( KEY_INPUT_UP ) ){
		player_y -= PLAYER_SPEED;
		player_facing = Up;
	}

	//	�Q�F�v���C���[���W�̋L�^
	//	�Q�|�P�F�v���C���[���W��z��̐擪�ɓ����O�ɍ��L�^����Ă���z��̒��g���P���炵�܂�
	for( int i = RECORD_MAX - 1; i > 0; i-- ){
		record_x[i] = record_x[i - 1];
		record_y[i] = record_y[i - 1];
		record_facing[i] = record_facing[i-1];
	}

	//	�Q�|�Q�F�z��̐擪�ɍ��̃v���C���[���W�����܂�
	record_x[0] = player_x;
	record_y[0] = player_y;
	record_facing[0] = player_facing;

	////	�R�F�I�v�V�����͋L�^�����l�����W�ɐݒ肷��
	////	�Q�O�t���[���O�̃v���C���[���W���I�v�V�����̍��W�ɂ��悤�Ǝv���܂�
	//option_x = record_x[20];
	//option_y = record_y[20];
	//option_facing = record_facing[20];


	option1.FollowAI(1);
	option2.FollowAI(2);
	option3.FollowAI(3);
	option4.FollowAI(4);

}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�I�v�V�����̕`��
	option1.DrawOption();
	option2.DrawOption();
	option3.DrawOption();
	option4.DrawOption();
	//	�v���C���[�̕`��
	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( player_facing ), player_image, TRUE );

	DrawString( 20, 20, "�\���L�[�F�v���C���[�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "�I�v�V�������v���C���[�ɂ��Ă���", GetColor( 255, 255, 255 ) );
	DrawString( 20, 60, "���@�I�v�V�����𕡐��ɂ��Ă݂�", GetColor( 255, 255, 0 ) );
	DrawString( 20, 80, "number of option spawned : ", GetColor( 255, 255, 0 ) );
	DrawFormatString(20, 80, GetColor(255, 255, 0), "number of option spawned : %d", Option::num_instances);
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( option_image );
}

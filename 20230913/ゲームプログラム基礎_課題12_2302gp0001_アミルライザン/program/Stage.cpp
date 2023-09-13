#include "Main.h"
#include "Game.h"
#include "Stage.h"

#include "Hit.h"

//=================================================================================
//	�X�e�[�W�̏���
//=================================================================================

//	�v���C���[�̃X�s�[�h
#define PLAYER_SPEED	5.0f
//	�m�o�b�̃X�s�[�h
#define NPC_SPEED		3.0f
//	�����蔻��p�̔��a
#define RADIUS			25.0f

//	���ꂼ��̉摜�p�̕ϐ�
int stage_image;
int player_image;
int npc_image;
//	�v���C���[�̕ϐ�
float player_x;
float player_y;
float player_rot;
//	�m�o�b
float npc_x;
float npc_y;
float npc_rot;

int stage_frame;
//---------------------------------------------------------------------------------
//	�f�[�^�̓ǂݍ���
//---------------------------------------------------------------------------------
void StageLoad()
{
	//	�摜�̓ǂݍ���
	stage_image = LoadGraph( "data/stage_bg.bmp" );
	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );
}
//---------------------------------------------------------------------------------
//	������
//---------------------------------------------------------------------------------
void StageInit()
{
	//	�v���C���[�ϐ��̏����ݒ�
	player_x = SCREEN_W / 2.0f;
	player_y = 400.0f;
	player_rot = -90.0f;
	//	�m�o�b��
	npc_x = (float)GetRand( SCREEN_W );
	npc_y = 0.0f;
	npc_rot = 90.0f;
	stage_frame = 0;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void StageUpdate()
{
	//	�\���L�[�Ńv���C���[�̍��W�̍X�V
	if( CheckHitKey( KEY_INPUT_RIGHT ) )	player_x += PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_LEFT ) )		player_x -= PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_DOWN ) )		player_y += PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_UP ) )		player_y -= PLAYER_SPEED;
	//	�m�o�b�̍X�V�����i��ʂ̉��Ɉړ��j
	npc_y += NPC_SPEED;
	if( npc_y > SCREEN_H ){
		npc_x = (float)GetRand( SCREEN_W );
		npc_y = 0.0f;
	}
	//	�v���C���[�Ƃm�o�b�̓����蔻��
	if( CheckCircleHit( player_x, player_y, RADIUS, npc_x, npc_y, RADIUS ) ){
		//	����������^�C�g���ɖ߂�̂Ŏ��ɍs�������V�[�����^�C�g����
		scene_next = SCENE_CLEAR;
	}
	stage_frame++;

}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void StageRender()
{
	//	���ꂼ��̉摜�̕`��
	DrawGraph( 0, 0, stage_image, TRUE );

	DrawRotaGraphF( npc_x, npc_y, 1.0f, TO_RADIAN( npc_rot ), npc_image, TRUE );

	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( player_rot ), player_image, TRUE );

	DrawString( 20, 20, "�y�X�e�[�W��ʁz", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "�\���L�[�F�v���C���[�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 20, 60, "�m�o�b�Ɠ���������u�N���A��ʁv��", GetColor( 255, 255, 0 ) );
	

	DrawFormatString( 20, 80, GetColor(255, 255, 0) , "�o�������� :  %d", stage_frame);
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void StageExit()
{
	DeleteGraph( stage_image );

	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}

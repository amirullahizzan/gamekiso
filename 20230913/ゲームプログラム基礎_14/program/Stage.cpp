#include "Main.h"
#include "Game.h"
#include "Stage.h"

#include "Hit.h"

//=================================================================================
//	�X�e�[�W�̏���
//=================================================================================

#define PLAYER_SPEED	5.0f
#define NPC_SPEED		3.0f
#define RADIUS			25.0f

int stage_image;
int player_image;
int npc_image;

float player_x;
float player_y;
float player_rot;

float npc_x;
float npc_y;
float npc_rot;

//---------------------------------------------------------------------------------
//	�f�[�^�̓ǂݍ���
//---------------------------------------------------------------------------------
void StageLoad()
{
	stage_image = LoadGraph( "data/stage_bg.bmp" );

	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );
}
//---------------------------------------------------------------------------------
//	������
//---------------------------------------------------------------------------------
void StageInit()
{
	player_x = SCREEN_W / 2.0f;
	player_y = 400.0f;
	player_rot = -90.0f;

	npc_x = (float)GetRand( SCREEN_W );
	npc_y = 0.0f;
	npc_rot = 90.0f;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void StageUpdate()
{
	if( CheckHitKey( KEY_INPUT_RIGHT ) )	player_x += PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_LEFT ) )		player_x -= PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_DOWN ) )		player_y += PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_UP ) )		player_y -= PLAYER_SPEED;

	npc_y += NPC_SPEED;
	if( npc_y > SCREEN_H ){
		npc_x = (float)GetRand( SCREEN_W );
		npc_y = 0.0f;
	}

	if( CheckCircleHit( player_x, player_y, RADIUS, npc_x, npc_y, RADIUS ) ){
		scene_next = SCENE_TITLE;
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void StageRender()
{
	DrawGraph( 0, 0, stage_image, TRUE );

	DrawRotaGraphF( npc_x, npc_y, 1.0f, TO_RADIAN( npc_rot ), npc_image, TRUE );

	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( player_rot ), player_image, TRUE );

	DrawString( 20, 20, "�y�X�e�[�W��ʁz", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "�\���L�[�F�v���C���[�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 20, 60, "�m�o�b�Ɠ���������^�C�g����", GetColor( 255, 255, 255 ) );
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

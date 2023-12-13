#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"

//	�v���C���[�̈ړ��X�s�[�h
#define PLAYER_SPEED	3.0f
//	�m�o�b�̐�
#define NPC_MAX			4

//	�v���C���[�摜
int player_image;
//	�v���C���[���W
Float2 player_pos;

//	�m�o�b�摜
int npc_image;
//	�m�o�b���W
Float2 npc_pos[NPC_MAX];
float npc_rotation_degree[NPC_MAX];

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�摜�̓ǂݍ���
	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );
	//	�������W�̐ݒ�
	player_pos.clear();
	//	�m�o�b�͂Ƃ肠���������_����
	for( int i = 0; i < NPC_MAX; i++ ){
		npc_pos[i].x = GetRandomF( SCREEN_W );
		npc_pos[i].y = GetRandomF( SCREEN_H );
	}

	FILE* readFile = fopen("data/start.txt","r");

	char text[256];
	float x, y, rotation;
	if (readFile)
	{
		fgets(text,sizeof(text),readFile);
		sscanf_s(text,"%f,%f",&x,&y);
		player_pos.set(x,y);

		for (int i = 0 ; i < NPC_MAX;i++)
		{
			fgets(text, sizeof(text), readFile);
			sscanf_s(text, "%f,%f,%f", &x, &y,&rotation);
			npc_pos[i].set(x, y);
			npc_rotation_degree[i] = rotation;
		}

		fclose(readFile);
	}

}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	�\���L�[�Ńv���C���[���W�̍X�V
	if( CheckHitKey( KEY_INPUT_RIGHT ) )	player_pos.x += PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_LEFT ) )		player_pos.x -= PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_DOWN ) )		player_pos.y += PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_UP ) )		player_pos.y -= PLAYER_SPEED;
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	for( int i = 0; i < NPC_MAX; i++ ){
		DrawRotaGraphF( npc_pos[i].x, npc_pos[i].y, 1.0f, TO_RADIAN(npc_rotation_degree[i]), npc_image, TRUE);
	}

	DrawRotaGraphF( player_pos.x, player_pos.y, 1.0f, TO_RADIAN( 0.0f ), player_image, TRUE );

	DrawString( 16, 16, "�\���L�[�F�v���C���[�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "����̉ۑ�ł̓e�L�X�g�t�@�C���ւ̏������݂͂���܂���", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "�������� start.txt ��ǂݍ���ňȉ��̏���ݒ肷��", GetColor( 255, 255, 0 ) );
	DrawString( 16, 64, "�e�L�X�g�P�s�ځi�v���C���[���j�F�w���W�@�x���W", GetColor( 255, 255, 0 ) );
	DrawString( 16, 80, "�e�L�X�g�Q�`�T�s�ځi�m�o�b���j�F�w���W�@�x���W�@����", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}

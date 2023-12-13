#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Hit.h"

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

	FILE* player_fp = fopen("data/player.txt", "r");
	
	char text[256];
	int x, y;
	//4 steps 
	if (player_fp)
	{
	//fgets(text,256,player_fp);
	fgets(text, sizeof(text), player_fp);
	sscanf_s(text,"%d,%d", &x, &y); //other than format specifiers needs to be read
	//Float2 newpos = {x,y };
	player_pos.set(x,y);
	//player_pos.x = x;
	//player_pos.y = y;
	fclose(player_fp);
	player_fp = nullptr;
	}

	FILE* npc_fp = fopen("data/npc.txt","r");

	if (npc_fp)
	{
		//char text[256];
		//int x, y;
		for (int i = 0; i <NPC_MAX;i++)
		{
		fgets(text,sizeof(text),npc_fp); //read per line, when executed again will go to the next line
		sscanf_s(text,"%d,%d",&x,&y); //takes the value address
		npc_pos[i].set(x,y);
		}
		fclose(npc_fp);
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
		DrawRotaGraphF( npc_pos[i].x, npc_pos[i].y, 1.0f, TO_RADIAN( 180.0f ), npc_image, TRUE );
	}

	DrawRotaGraphF( player_pos.x, player_pos.y, 1.0f, TO_RADIAN( 0.0f ), player_image, TRUE );

	DrawString( 16, 16, "�\���L�[�F�v���C���[�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "data �t�H���_�� player.txt �� npc.txt ������܂�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "�N�����ɂ��ꂼ��̃e�L�X�g���琔�l���擾���č��W�̏����ݒ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 64, "�I�����ɍ��̃v���C���[���W���uplayer.txt�v�ɏ�������", GetColor( 255, 255, 255 ) );
	DrawString( 16, 80, "���@�Ȃ̂Ŏ��ɋN������ƃv���C���[�͑O��I���������W����n�܂�܂�", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	//Saving player position on exit game

	FILE* saveFile = fopen("data/player.txt", "w");

	char text[256];
	if (saveFile)
	{
		int x = player_pos.x;
		int y = player_pos.y;
		sprintf(text,"%d,%d",x,y);
		//fwrite(text,sizeof(text),2, saveFile);
		fputs(text,saveFile);
		//if want to go to the next line
		fputs("\n", saveFile);

		fclose(saveFile);
	}

	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}

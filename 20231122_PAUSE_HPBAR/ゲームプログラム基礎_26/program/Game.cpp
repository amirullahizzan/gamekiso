#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"

#include "Player.h"
#include "Npc.h"

int player_image;
int npc_image;

Player player;

#define NPC_MAX	5
Npc npc[NPC_MAX];

bool isGamePaused = false;


//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );

	player.Init( player_image );
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Init( npc_image );
	}
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	
	if (PushHitKey(KEY_INPUT_SPACE)	) 
	{ 
		isGamePaused = !isGamePaused; 
	}

	/*if (isGamePaused)
	{
		return;
	}*/
	if (!isGamePaused)
	{
		player.Update();
		for (int i = 0; i < NPC_MAX; i++) {
			npc[i].Update();
		}
	}
	else
	{
		if (CheckHitKey(KEY_INPUT_LEFT)) { player.AddSpeed(-0.1f); }
		if (CheckHitKey(KEY_INPUT_RIGHT)) { player.AddSpeed(0.1f); }
	}


}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Render();
	}
	player.Render();

	if (isGamePaused)
	{

	//	�|�[�Y���j���[�i�Ƃ肠�����R�����g�ɂ��Ă��܂��F��Ŏg���܂��j
	DrawFillBox( 150, 100, 650, 350, GetColor( 0, 0, 0 ) );
	DrawLineBox( 150, 100, 650, 350, GetColor( 255, 255, 255 ) );
	DrawString( 200, 130, "�����L�[�F�v���C���[�X�s�[�h�ύX", GetColor( 255, 255, 255 ) );
	DrawString( 200, 300, "�X�y�[�X�F�|�[�Y����", GetColor( 255, 255, 255 ) );
	DrawFormatString(200,150, GetColor(255, 255, 255),"Speed : %f",player.GetSpeed());

	}


	DrawString( 16, 16, "�\���L�[�F�v���C���[�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "�X�y�[�X�F�|�[�Y���j���[", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	player.Exit();
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Exit();
	}

	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}

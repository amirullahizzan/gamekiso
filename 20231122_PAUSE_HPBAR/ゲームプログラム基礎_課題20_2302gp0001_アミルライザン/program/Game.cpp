#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"

#include "Player.h"
#include "Npc.h"

//	�摜�f�[�^�p�̕ϐ��i Game.cpp �̍ŏ��ɓǂݍ���ŃN���X�ɓn���j
int player_image;
int npc_image;

//	�v���C���[�N���X�i�P�錾�j
Player player;
//	�m�o�b�̐��i�T�j
#define NPC_MAX	5
//	�m�o�b�̐錾
Npc npc[NPC_MAX];

//	�Q�[�����[�h�̎��
enum {
	MODE_PLAY,		//	�O�F�v���C��
	MODE_PAUSE,		//	�P�F�|�[�Y��
};
//	���̃Q�[�����[�h
int game_mode;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	���ꂼ��̉摜�̓ǂݍ���
	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );

	//	��œǂݍ��񂾉摜�ԍ���n���ăN���X�̏�����
	//	�v���C���[�̏�����
	player.Init( player_image );
	//	�m�o�b�̏�����
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Init( npc_image );
	}

	//	�ŏ��͑���ł����Ԃ���J�n
	game_mode = MODE_PLAY;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	�Q�[�����[�h�ɂ���ď����𕪂��܂�
	switch( game_mode ){
	case MODE_PLAY:		//	�Q�[���v���C��

		//	�X�y�[�X�L�[����������
		if( PushHitKey( KEY_INPUT_SPACE ) ){
			//	���[�h���|�[�Y�ɐ؂�ւ���i�|�[�Y���j���[���J���j
			game_mode = MODE_PAUSE;
		}

		//	�Q�[���v���C���̂݌ĂԂ悤�ɂ��܂�
		//	�v���C���[�̍X�V�����i�\���L�[�ňړ��j
		player.Update();
		//	�m�o�b�̍X�V�����i��ʍ��Ɉړ��j
		for( int i = 0; i < NPC_MAX; i++ ){
			npc[i].Update();
		}

		break;

	case MODE_PAUSE:	//	�|�[�Y��

		//	�X�y�[�X�L�[����������
		if( PushHitKey( KEY_INPUT_SPACE ) ){
			//	���[�h���v���C���ɐ؂�ւ���
			game_mode = MODE_PLAY;
		}

		//	���E�L�[�Ńv���C���[�̃X�s�[�h�̕ύX
		if( CheckHitKey( KEY_INPUT_RIGHT ) ){
			player.m_speed += 0.1f;
			//	�v���C���[�X�s�[�h�̍ő�� 10.0f
			if( player.m_speed > 10.0f ){
				player.m_speed = 10.0f;
			}
		}
		if( CheckHitKey( KEY_INPUT_LEFT ) ){
			player.m_speed -= 0.1f;
			//	�v���C���[�X�s�[�h�̍ŏ��� 1.0f
			if( player.m_speed < 1.0f ){
				player.m_speed = 1.0f;
			}
		}
		if (CheckHitKey(KEY_INPUT_UP)) {
			player.m_speed = 10.0f;
		}
		if (CheckHitKey(KEY_INPUT_DOWN)) {
			player.m_speed = 1.0f;
		}



		break;
	}

}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�v���C���[��m�o�b�̓��[�h�ɂ�����炸�`�悵�Ƃ��܂�
	//	�m�o�b�̕`��
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Render();
	}
	//	�v���C���[�̕`��
	player.Render();

	//	�|�[�Y���̎��̂ݕ`�悵�܂�
	if( game_mode == MODE_PAUSE ){
		//	�|�[�Y���j���[
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawFillBox( 150, 100, 650, 350, GetColor( 0, 0, 0 ) );
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawLineBox( 150, 100, 650, 350, GetColor( 255, 255, 255 ) );

		//	�����p�̕�����
		DrawString( 200, 130, "�����L�[�F�v���C���[�X�s�[�h�ύX", GetColor( 255, 255, 255 ) );
		DrawString( 200, 150, "���L�[�@�F�X�s�[�h���ő�i 10.0f �j�ɐݒ�", GetColor( 255, 255, 0 ) );
		DrawString( 200, 170, "���L�[�@�F�X�s�[�h���ŏ��i  1.0f �j�ɐݒ�", GetColor( 255, 255, 0 ) );
		//	�v���C���[�̃X�s�[�h�𕶎���ŕ`��
		DrawFormatString( 200, 200, GetColor( 255, 255, 255 ), "�v���C���[�X�s�[�h�F%4.1f", player.m_speed );
		//	�|�[�Y���j���[���������p�̕�����
		static int flickertick = 0;
		static bool isDisplayed = true;
		flickertick++;
		if (flickertick > 60)
		{
			isDisplayed = false;
		}
		if (flickertick > 80 )
		{
			isDisplayed = true;
			flickertick = 0;
		}

		if(isDisplayed)
		{
		DrawString( 200, 300, "�X�y�[�X�F�|�[�Y����", GetColor( 255, 255, 255 ) );
		}

		





		DrawFillBox(200, 240, 200 + (30* (player.m_speed)), 260, GetColor(0, 255, 0));
		DrawLineBox(200, 240, 500, 260, GetColor(255, 255, 255)	);
	}

	DrawString( 16, 16, "�\���L�[�F�v���C���[�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "�X�y�[�X�F�|�[�Y���j���[", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "�|�[�Y���j���[�̔w�i�摜�̕`��𔼓�����", GetColor( 255, 255, 0 ) );
	DrawString( 16, 64, "�v���C���[�X�s�[�h���o�[���g���ĕ\��", GetColor( 255, 255, 0 ) );
	
	DrawString( 16, 80, "�u�X�y�[�X�F�|�[�Y����v��_�ł�����", GetColor( 255, 255, 0 ) );
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

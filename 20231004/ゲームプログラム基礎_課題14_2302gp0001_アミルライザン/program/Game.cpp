#include "Main.h"
#include "Game.h"
#include "Hit.h"

//	�v���C���[�p�̕ϐ�
int player_image;	//	�摜
float player_x;		//	�w���W
float player_y;		//	�x���W

//	�m�o�b�p�̕ϐ�
int npc_image;		//	�摜
float npc_x;		//	�w���W
float npc_y;		//	�x���W

int npc_alpha;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�v���C���[�̏����ݒ�
	player_image = LoadGraph( "data/player.bmp" );
	player_x = 100.0f;
	player_y = 200.0f;

	//	�m�o�b�̏����ݒ�
	npc_image = LoadGraph( "data/npc.bmp" );
	npc_x = 350.0f;
	npc_y = 200.0f;
	npc_alpha = 256;
}
int alphaMode = 1;
void GameUpdate()
{
	//	�}�E�X���W���v���C���[�̍��W�ɂ��܂�
	player_x = GetMouseX();
	player_y = GetMouseY();

	switch (alphaMode)
	{
	case 0:
		npc_alpha += 2;
		if (npc_alpha >= 256)
		{
			alphaMode = 1;
		}
		break;
	case 1:
		npc_alpha -= 2;
		if (npc_alpha <= 0)
		{
			npc_x = GetRand(SCREEN_W);
			npc_y = GetRand(SCREEN_H);
			alphaMode = 0;
		}
		break;
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�v���C���[�̕`��
	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( 0.0f ), player_image, TRUE );

	//	�m�o�b�𔼓����ɂ��ĕ`�悵����
	//	�P�F������`�悷����́i�m�o�b�j�̓����x��ݒ�
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, npc_alpha );
	//	�Q�F�����̕`��
	//	�m�o�b�̕`��
	DrawRotaGraphF( npc_x, npc_y, 1.0f, TO_RADIAN( 0.0f ), npc_image, TRUE );
	//	���̕`��̂��߂ɓ����x�ݒ�����ɖ߂��܂�
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );

	//WHITE
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256/2);
	DrawFillBox(SCREEN_W / 2 - 280,SCREEN_H - 160, SCREEN_W / 2 + 280, SCREEN_H -50,GetColor(0,0,0));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawLineBox(SCREEN_W / 2 - 280, SCREEN_H - 160, SCREEN_W / 2 + 280, SCREEN_H - 50, GetColor(255, 255, 255));

	DrawString( SCREEN_W/2 - 220, SCREEN_H - 145, "�}�E�X���W�̏��Ƀv���C���[�摜�̕`��", GetColor( 255, 255, 255 ) );
	DrawString(SCREEN_W / 2 - 220, SCREEN_H - 145 + 18, "�m�o�b�͏o�������������J��Ԃ�", GetColor( 255, 255, 0 ) );
	DrawString(SCREEN_W / 2 - 220, SCREEN_H - 145 + 18*2, "���@�o�Ă���Ƃ��͍��W�������_����", GetColor( 255, 255, 0 ) );
	DrawString(SCREEN_W / 2 - 220, SCREEN_H - 145 + 18*3, "���̕���������b�Z�[�W�\���݂����ɂ��Ă݂�", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}

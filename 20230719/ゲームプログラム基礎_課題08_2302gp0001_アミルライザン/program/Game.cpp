#include "Main.h"
#include "Game.h"

//	�v���C���[�摜
int player_image;
//	�v���C���[�w���W�i����͉��ɂ����ړ����Ȃ��̂łw���W�����j
float player_x;


int bg_image[3];
int bg_imageIndex;
int bgm[3];
int bgmIndex;

void GameInit()
{
	//	�v���C���[�摜�̓ǂݍ���
	player_image = LoadGraph( "data/player.bmp" );

	bg_image[0] = LoadGraph("data/image_town.bmp");
	bg_image[1] = LoadGraph("data/image_field.bmp");
	bg_image[2] = LoadGraph("data/image_battle.bmp");

	bg_imageIndex = 0;
	bgmIndex = 0;

	//	�������W�ݒ�
	player_x = 100.0f;

	//	�Ƃ肠�����ŏ��ɂa�f�l�̍Đ������Ă��܂�
	PlayMusic("data/bgm_town.mp3", DX_PLAYTYPE_LOOP);
}

void ChangeMusic()
{
	StopMusic();
	if (bg_imageIndex == 0)
	{
		PlayMusic("data/bgm_town.mp3", DX_PLAYTYPE_LOOP);
	}
	if (bg_imageIndex == 1)
	{
		PlayMusic("data/atmosphere.wav", DX_PLAYTYPE_LOOP);
	}
	if (bg_imageIndex == 2)
	{
		PlayMusic("data/castle.wav", DX_PLAYTYPE_LOOP);
	}
}

void GameUpdate()
{
	//	�E�L�[�Ńv���C���[�ړ�
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		player_x += 15.0f;
	}
	//	��ʉE�܂ōs�����獶�ɂ���
	if( player_x > SCREEN_W ){
		player_x = -50.0f;
		bg_imageIndex++;
		if (bg_imageIndex > 2)
		{
			bg_imageIndex = 0;
		}
		ChangeMusic();

	}

}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	DrawGraph(0, 0, bg_image[bg_imageIndex], 0);

	//	�v���C���[�摜�̕`��
	DrawGraphF( player_x, 200.0f, player_image, TRUE );

	DrawString( 20, 20, "�E�L�[�F�v���C���[�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "���@��ʉE�܂ōs�����獶����o�Ă���", GetColor( 255, 255, 255 ) );
	DrawString( 20, 60, "���@���̂��тɔw�i�Ƃa�f�l��ύX����", GetColor( 255, 255, 0 ) );

}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );

}

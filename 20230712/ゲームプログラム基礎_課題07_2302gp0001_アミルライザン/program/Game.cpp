#include "Main.h"
#include "Game.h"

//	���ɕ��ׂ鐔�i��ʑS���ɕ��ׂ�ꍇ�͂P�U�F����͏������������Ă��܂��j
#define MAP_W		10
//	�c�ɕ��ׂ鐔�i��ʑS���ɕ��ׂ�ꍇ�͂X�F����͏������������Ă��܂��j
#define	MAP_H		 7
//	�u���b�N�P�̑傫��
#define BLOCK_SIZE	50

//	�X�N���[���X�s�[�h�i�ꉞ�}�b�v�̈ړ��X�s�[�h�ŗp�ӂ��Ă��܂��j
#define SCROLL_SPEED	3

//	���ꂼ��̃|�C���g�̔ԍ�������p�̂Q�����z��
//	�}�b�v�O
int map0[MAP_H][MAP_W] =
{
	{ 4,4,4,4,4,4,4,4,4,4 },
	{ 4,0,2,2,0,0,0,0,0,4 },
	{ 4,2,0,0,2,0,0,0,0,4 },
	{ 4,2,0,0,2,0,3,3,3,4 },
	{ 4,2,0,0,2,0,3,3,3,4 },
	{ 4,0,2,2,0,0,3,3,3,4 },
	{ 4,4,4,4,4,4,4,4,4,4 },
};
//	�}�b�v�P
int map1[MAP_H][MAP_W] =
{
	{ 2,1,2,2,2,2,2,2,2,2 },
	{ 2,1,4,4,2,1,1,1,1,2 },
	{ 2,4,4,4,2,2,2,2,2,2 },
	{ 2,2,4,4,2,1,2,1,2,1 },
	{ 2,1,4,4,2,1,2,1,2,1 },
	{ 2,4,4,4,4,1,2,1,2,1 },
	{ 2,2,2,2,2,2,2,1,2,2 },
};

//	�}�b�v�Ŏg���摜�p�̕ϐ��i���̂P�̉摜����K�v�ȕ������g���ĕ`��j
int map_image;

int x;
int y;
int offset_x;
int offset_y;

void GameInit()
{
	//	�摜�̓ǂݍ��݁i����}�b�v�Ŏg���̂͂���P�������j
	map_image = LoadGraph( "data/map.bmp" );

}

int z = 0;

void GameUpdate()
{
	//	�\���L�[�Ń}�b�v�̈ړ��i�}�b�v�̊�ƂȂ���W�ϐ��̒l���X�V�j
	if( CheckHitKey( KEY_INPUT_RIGHT ) && x < SCREEN_W - 50 )
	{
		offset_x++;

	}
	if( CheckHitKey( KEY_INPUT_LEFT )&& offset_x > 0)
	{
		offset_x--;
	}
	if( CheckHitKey( KEY_INPUT_DOWN ) && y < SCREEN_H -50)
	{
		offset_y++;
	}
	if( CheckHitKey( KEY_INPUT_UP )&& offset_y > 0)
	{
		offset_y--;
	}

	if (PushHitKey(KEY_INPUT_SPACE))
	{
		if (z == 0)
		{
			z++;
		}
		else
		{
			z--;
		}
		
	}
	
}



void GameRender()
{
	//	�}�b�v�ԍ��ɍ��킹���摜�̒��̊J�n�ʒu���f�[�^�Ƃ��ėp��
	int image_xy_data[5][2] = 
	{
		{   0,  0 },	//	�O�Ԃ̏ꏊ
		{ 100,  0 },	//	�P�Ԃ̏ꏊ
		{ 150,  0 },	//	�Q��
		{ 100, 50 },	//	�R��
		{   0, 50 },	//	�S��
	};


	if (z == 0)
	{
		for (int h = 0; h < MAP_H; h++) {
			for (int w = 0; w < MAP_W; w++) {
				//	���̏ꏊ�̃}�b�v�̔ԍ����擾�i�Ƃ肠���� map0 ���g���Ă��܂��j
				int num = map0[h][w];
				//	��ʂ̂ǂ��ɕ`�悷��̂��̍��W�i�Q�����z��̏ꏊ����u���b�N�T�C�Y�����炵���Ƃ���j
				x = (w * BLOCK_SIZE) + offset_x;
				y = (h * BLOCK_SIZE) + offset_y;
				//	���̔ԍ��̊G�� map.bmp �̂ǂ�����n�܂邩
				int image_x = image_xy_data[num][0];
				int image_y = image_xy_data[num][1];
				//	��ʂ̍��W�i x y �j�̏ꏊ�ɉ摜�i map_image �j�̂����̏ꏊ�i image_x image_y �j����`��
				DrawRectGraph(x, y, image_x, image_y, BLOCK_SIZE, BLOCK_SIZE, map_image, TRUE);
			}
		}
	}
	else if (z == 1)
	{
		for (int h = 0; h < MAP_H; h++) {
			for (int w = 0; w < MAP_W; w++) {
				//	���̏ꏊ�̃}�b�v�̔ԍ����擾�i�Ƃ肠���� map0 ���g���Ă��܂��j
				int num = map1[h][w];
				//	��ʂ̂ǂ��ɕ`�悷��̂��̍��W�i�Q�����z��̏ꏊ����u���b�N�T�C�Y�����炵���Ƃ���j
				x = (w * BLOCK_SIZE) + offset_x;
				y = (h * BLOCK_SIZE) + offset_y;
				//	���̔ԍ��̊G�� map.bmp �̂ǂ�����n�܂邩
				int image_x = image_xy_data[num][0];
				int image_y = image_xy_data[num][1];
				//	��ʂ̍��W�i x y �j�̏ꏊ�ɉ摜�i map_image �j�̂����̏ꏊ�i image_x image_y �j����`��
				DrawRectGraph(x, y, image_x, image_y, BLOCK_SIZE, BLOCK_SIZE, map_image, TRUE);
			}
		}
	}
	//	�}�b�v�̕`��
	

	DrawString( 20, 20, "�}�b�v�̑傫����ς��Ă܂��i�g�p�摜�� map.bmp �̂܂܂ł��j", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "�\���L�[�F�}�b�v�ړ��i��ʂ̊O�ɍs���Ȃ��悤�Ɂj", GetColor( 255, 255, 0 ) );
	DrawString( 20, 60, "�X�y�[�X�F�}�b�v�̐؂�ւ�", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( map_image );
}

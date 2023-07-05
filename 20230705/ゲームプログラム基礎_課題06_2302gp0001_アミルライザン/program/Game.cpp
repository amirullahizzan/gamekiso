#include "Main.h"
#include "Game.h"

//	�u���b�N�̑傫��
#define BLOCK_SIZE	50
//	�l�p����ׂ鐔
#define MAP_W		16		//	��
#define	MAP_H		 9		//	�c

//	�}�b�v�p�̕ϐ��i�Q�����z��Łj�F�錾�������łɌ��܂������l��ݒ肵�܂�
int map[MAP_H][MAP_W] =
{
	{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,1,1,1,0,1,1,1,0,2 },
	{ 2,0,0,0,0,0,0,1,0,0,0,0,0,1,0,2 },
	{ 2,0,0,0,0,0,0,1,0,0,0,0,0,1,0,2 },
	{ 2,0,0,0,0,0,0,1,1,1,1,1,1,1,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
};
//	�u���b�N�摜�p�̕ϐ��i�O�F�΁@�P�F�D�F�@�Q�F���F�j
int block_image[3];

int num;
int player_state = map[2][2];



//	�v���C���[�摜
int player_image;
int enemy_image;
//	�v���C���[���i�Q�����z��I�Ɂj���Ԗڂ̂Ƃ���ɂ���̂��i���W�ł͂Ȃ��ł��j
int player_w;	//	���̉��Ԗ�
int player_h;	//	�c�̉��Ԗ�

int enemy_w;
int enemy_h;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�u���b�N�摜�̓ǂݍ���
	block_image[0] = LoadGraph( "data/block0.bmp" );
	block_image[1] = LoadGraph( "data/block1.bmp" );
	block_image[2] = LoadGraph( "data/block2.bmp" );

	//	�v���C���[�摜�̓ǂݍ���
	player_image = LoadGraph( "data/player.bmp" );
	enemy_image = LoadGraph( "data/npc.bmp" );
	//	�ǂ��̏ꏊ����J�n���邩�i���W�ł͂Ȃ����āA��ʂ��T�O��؂�ɂ������̉��Ԗڂ̂Ƃ��납�j
	player_w = 2;
	player_h = 2;

	enemy_w = 5;
	enemy_h = 6;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
int frame = 0;
int enemyrandomizer = 0;

void GameUpdate()
{
	//	�E�L�[��������v���C���[���P�}�X�E�Ɉړ�������

	if (PushHitKey(KEY_INPUT_RIGHT)) 
	{
		//	���ɍs�������Ƃ��낪�}�b�v�̒���������i�z��̐���菬����������j
		if (player_w + 1 <= MAP_W - 1 && map[player_h][player_w+1] == 0)
		{
			player_w++;
		}
	}
	//	���L�[
	if( PushHitKey( KEY_INPUT_LEFT ) )
	{
		//	���ɍs�������Ƃ���i�P�}�X���j���}�b�v�̒���������i�z��͈͓̔���������j
		if( player_w - 1 >= 0 && map[player_h][player_w - 1] == 0){
			//	���ɂP�}�X�i�߂�i�z��I�ɂP�}�C�i�X�j
			player_w--;
		}
	}
	//	�㉺�L�[��
	if( PushHitKey( KEY_INPUT_DOWN ) && map[player_h+1][player_w] == 0){
		if( player_h + 1 <= MAP_H - 1 ){
			player_h++;
		}
	}
	if( PushHitKey( KEY_INPUT_UP ) && map[player_h - 1][player_w] == 0){
		if( player_h - 1 >= 0 ){
			player_h--;
		}
	}

	frame++;
	
	if (frame == 50)
	{
		enemyrandomizer += GetRand(4);

		if (enemyrandomizer == 1 && map[enemy_h][enemy_w + 1] == 0)
		{
			enemy_w += 1;
		}
		else if (enemyrandomizer == 2 && map[enemy_h][enemy_w-1] == 0)
		{
			enemy_w -= 1;
		}
		else if (enemyrandomizer == 3 && map[enemy_h + 1][enemy_w] == 0)
		{
			enemy_h += 1;
		}
		else if (enemyrandomizer == 4 && map[enemy_h - 1][enemy_w] == 0)
		{
			enemy_h -= 1;
		}

		enemyrandomizer = 0;
		frame = 0;
	}

	
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�}�b�v�̕`��i�Q�����z��̔ԍ����P�����Ă����āA���̔ԍ��̉摜��`�悵�܂��j
	for( int h = 0; h < MAP_H; h++ ){
		for( int w = 0; w < MAP_W; w++ ){
			//	���̏ꏊ�̃}�b�v�̔ԍ����擾
			num = map[h][w];
			//	��ʂ̂ǂ��ɕ`�悷�邩�̍��W�i�u���b�N�̑傫�������炵�āj
			int x = w * BLOCK_SIZE;
			int y = h * BLOCK_SIZE;
			//	���̍��W�ɂ��̔ԍ��̉摜��`��
			DrawGraph( x, y, block_image[num], TRUE );
		}
	}

	//	�v���C���[�̕`��i��ʂ̂ǂ��ɕ`�悷�邩���߂�j
	//	���@���̃v���C���[�̃|�C���g�i player_w player_h �j����ʓI�ɂǂ��̍��W�ɂȂ邩
	int px = player_w * BLOCK_SIZE;
	int py = player_h * BLOCK_SIZE;
	//	�����̍��W�Ƀv���C���[�摜��`��
	DrawGraph( px, py, player_image, TRUE );

	int ex = enemy_w * BLOCK_SIZE;
	int ey = enemy_h * BLOCK_SIZE;
	DrawGraph(ex, ey, enemy_image, TRUE);


	DrawString( 20, 20, "�\���L�[�F�v���C���[�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "�D�F�i�P�F�ǂ��ۂ��j��i�Q�F�����ۂ��j�̂Ƃ���͐i�߂Ȃ�", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( block_image[0] );
	DeleteGraph( block_image[1] );
	DeleteGraph( block_image[2] );

	DeleteGraph( player_image );
}

#include "Main.h"
#include "Game.h"

//	�u���b�N�摜�p�̕ϐ��i block0.bmp �` block3.bmp �̂S�g���̂Łj
int block_image[4];

//	��ʏ�̊e�u���b�N��u���ꏊ�����ԂȂ̂�������p�̕ϐ�
int stage[5][8];

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�u���b�N�摜�̓ǂݍ���
	block_image[0] = LoadGraph( "data/block0.bmp" );	//	�O�F�������Ƃ���̉摜
	block_image[1] = LoadGraph( "data/block1.bmp" );	//	�P�`�R�F�ŏ��Ƀ����_���ɕ��ׂ�
	block_image[2] = LoadGraph( "data/block2.bmp" );
	block_image[3] = LoadGraph( "data/block3.bmp" );

	//	�z��̂��ׂĂ̏ꏊ�Ƀ����_���łP�`�R�̐��l�����Ă����܂�

	for( int h = 0; h < 5; h++ ){
		//	���̏c�P�P�ɂ��A�����[�v���W��
		for( int w = 0; w < 8; w++ ){
			//	���� [h][w] �Ԗڂ̂Ƃ���Ƀ����_���Ȓl��ݒ肵�܂�
			stage[h][w] = GetRand( 2 ) + 1;
		}
	}
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
int mouse_x = 0;
int mouse_y = 0;

void Looper();

int click_w = 0;
int click_h = 0;

void GameUpdate()
{
	
	//	�}�E�X���N���b�N�����炻�̏ꏊ�������i�O�ԉ摜�ɂ���j
	if( PushMouseInput() ){
		//	�}�E�X���W���擾�i��ʍ��W�j
		mouse_x = GetMouseX();
		mouse_y = GetMouseY();
		//	���̃}�E�X���W���Q�����z��I�ɉ��Ԗڂ̂Ƃ���ɂȂ�̂����擾
		click_w = mouse_x / 100;
		click_h = mouse_y / 100;
		//	�����̃X�e�[�W�ԍ��̒l���O�ɂ���i�O�ԉ摜���g���̂�

		if (stage[click_h][click_w] == 0)
		{
			return;
		}

		Looper();
		

		int check_num = stage[click_h][click_w];
		int count = 0;

		for (int w = 0;w<8;w++)
		{
			if (check_num == stage[click_h][w] )
			{
				count++;
			}
		}
				
		if (count == 8)
		{
			for(int w = 0; w<8; w++)
			{
				stage[click_h][w] = 0;
			}
		}
		
		
	}

	
	/*if ((stage[0][0] & stage[0][1] & stage[0][2] & stage[0][3] & stage[0][4] & stage[0][5] & stage[0][6] & stage[0][7]) == stage[0][0])
	{
		stage[0][0] = 0;
		stage[0][1] = 0;
		stage[0][2] = 0;
		stage[0][3] = 0;
		stage[0][4] = 0;
		stage[0][5] = 0;
		stage[0][6] = 0;
		stage[0][7] = 0;
	}*/
	

	
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�u���b�N�̕`��
	//	stage[5][8] �Ɋ���U��ꂽ�ԍ���S�����Ă����Ă��̔ԍ��̉摜��`��
	for( int h = 0; h < 5; h++ ){
		for( int w = 0; w < 8; w++ ){
			//	�X�e�[�W�ϐ��̒�̏ꏊ�̔ԍ����擾�i�摜�ԍ��j
			int num = stage[h][w];
			//	���̔ԍ��̉摜����ʂ̂ǂ��ɕ\�����邩�̍��W
			int x = w * 100;
			int y = h * 100;
			//	���̔ԍ��̉摜��`��
			DrawGraph( x, y, block_image[num], TRUE );
		}
	}

	DrawString( 16, 16, "�N���b�N�Ŏl�p�̐F��ύX����", GetColor( 255, 255, 0 ) );
	DrawString( 16, 32, "�@[1:��] �� [2:��] �� [3:��] �� [1:��] �� [2:��] �� [3:��] �� �E�E�E�j", GetColor( 255, 255, 0 ) );
	DrawString( 16, 48, "����s�����F�������炻�̍s�͑S��������i�O�F�D�F�j", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	for( int i = 0; i < 4; i++ ){
		DeleteGraph( block_image[i] );
	}
}

void Looper()
{
	if (stage[click_h][click_w] != 3)
	{
		stage[click_h][click_w]++;

	}
	else
	{
		stage[click_h][click_w] = 1;
	}
}
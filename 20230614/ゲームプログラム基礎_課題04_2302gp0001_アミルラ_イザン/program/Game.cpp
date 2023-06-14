#include "Main.h"
#include "Game.h"


struct Player
{
	//	�v���C���[�摜
	int image;
	//	�v���C���[���W�i��ʂ̂ǂ��Ɂj
	int posx;
	int posy;
	//	�v���C���[�摜�̂ǂ�����g���̂��̉摜���W
	int imgx;
	int imgy;

	//	��莞�Ԃ𐔂���p�̕ϐ�
	int frame;

	void Draw()
	{
		DrawRectGraph(posx, posy, imgx, imgy, 50, 50, image, TRUE);
	}

	void Init()
	{
		//	�v���C���[�摜�̓ǂݍ���
		image = LoadGraph("data/player.bmp");
		//	�������W�̐ݒ�
		posx = 100;
		posy = 200;
		//	�摜�̂ǂ����炩�̏����ݒ�
		imgx = 0;
		frame = 0;
	}

	void Control()
	{
		if (CheckHitKey(KEY_INPUT_RIGHT)) {
			posx += 2;
			imgy = 100;
		}
		if (CheckHitKey(KEY_INPUT_LEFT)) {
			posx -= 2;
			imgy = 50;
		}
		if (CheckHitKey(KEY_INPUT_DOWN)) {
			posy += 2;
			imgy = 0;

		}
		if (CheckHitKey(KEY_INPUT_UP)) {
			posy -= 2;
			imgy = 150;
		}
	}

	void Anim()
	{
		//	�v���C���[�p�̃J�E���g�𑝂₷
		frame++;
		//	�J�E���g�̒l���R�O�ȏ�ɂȂ�����
		if (frame >= 30)
		{
			//	���ɂR�O�𐔂��邽�߂ɂO�ɂ��܂�
			frame = 0;
			//	�v���C���[�摜�̂ǂ�����g���̂��̒l��ύX���܂�
			//	�T�O���₵�Ď��̃R�}�ɂ��܂�
			imgx += 50;
			//	�Q�R�}�����Ȃ��̂łP�O�O�P�O�O�ȏ�ɂȂ�����
			if (imgx >= 100)
			{
				//	�O�ɂ��܂�
				imgx = 0;
			}
		}
	}

};

struct NPC
{
	//	�m�o�b�摜
	int image;
	//	�m�o�b���W
	int x[5];
	int y[5];

	void Init()
	{
		for (int i = 0;i<5;i++)
		{

		image = LoadGraph("data/npc.bmp");
		x[i] = GetRand(SCREEN_W);
		y[i] = GetRand(SCREEN_H);

		}
	}

	void Draw()
	{
		//	�m�o�b�̕`��
		for (int i = 0;i<5;i++)
		{
		DrawGraph(x[i], y[i], image, TRUE);
		}
	}

	void Move()
	{
		for (int i = 0; i < 5; i++)
		{
			x[i] -= 5;
			if (x[i] < -100)
			{
				x[i] = SCREEN_W;
				y[i] = GetRand(400);
			}
		}
	}

};

NPC npc;

struct Effect 
{
	//	�G�t�F�N�g�摜
	int image;
	//	�G�t�F�N�g���W�i��ʂ̂ǂ��Ɂj
	int posx;
	int posy;
	//	�G�t�F�N�g�摜�̂ǂ�����ɂ���̂�
	int imgx;
	//	�G�t�F�N�g�p�̈�莞�Ԑ�����ϐ�
	int frame;

	void Init()
	{
		for (int i = 0; i < 5; i++)
		{
			image = LoadGraph("data/effect.bmp");
			posx = 300;
			posy = 100;
			imgx = 0;
			frame = 0;
		}
	}

	void Anim()
	{
		//	�G�t�F�N�g�p�J�E���^�[��i�߂�
		frame++;
		//	��莞�Ԃ�������
		if (frame >= 10) {
			//	���̈�莞�Ԃ𐔂��邽�߂Ƀ��Z�b�g
			frame = 0;
			//	���̃^�C�~���O�ŉ摜�̂ǂ����g������؂�ւ���
			imgx += 50;
			//	�W�R�}���T�O�̑傫���𒴂�����
			if (imgx >= 400)
			{
				//	�P�R�}�ڂ̏ꏊ����
				imgx = 0;

				//	�G�t�F�N�g�̉�ʍ��W�������_����
				//	����͍��W�̃����_���͎g���܂���
	//			effect_posx = GetRand( 750 );
	//			effect_posy = GetRand( 400 );
			}
		}
	}

	void Draw()
	{
		for(int i = 0;i<5;i++)
		{
	posx = npc.x[i] + 50;
	posy = npc.y[i];
	DrawRectGraph(posx, posy, imgx, 0, 50, 50, image, TRUE);
		}
	}

};



Player player;
Effect effect;


void GameInit()
{
	player.Init();

	effect.Init();
	
	npc.Init();
	//	�m�o�b�摜�̓ǂݍ��݂ƍ��W�̏����ݒ�

}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	�\���L�[�Ńv���C���[���W�̍X�V
	player.Control();
	player.Anim();
	
	npc.Move();
	
	effect.Anim();


}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�v���C���[�摜�̈ꕔ�����v���C���[���W�̏ꏊ�ɕ`�悵�܂�
	player.Draw();

	//for()


	//	�G�t�F�N�g�摜�̈ꕔ�����g�����`��
	npc.Draw();
	effect.Draw();
	

	DrawString( 20, 20, "�\���L�[�F�v���C���[�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "���@�ړ��ɍ��킹�Č�����ς���", GetColor( 255, 255, 0 ) );
	DrawString( 20, 60, "�m�o�b�͉�ʍ��Ɉړ��i���܂ōs������E����o�Ă���E�x���W�̓����_���Ɂj", GetColor( 255, 255, 0 ) );
	DrawString( 20, 80, "���@�m�o�b�̍��W�ɍ��킹�ăG�t�F�N�g", GetColor( 255, 255, 0 ) );

	DrawString( 20, 120, "���@�m�o�b�𕡐��\��", GetColor( 50, 190, 200 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player.image );
	DeleteGraph( npc.image );
	DeleteGraph( effect.image );
}

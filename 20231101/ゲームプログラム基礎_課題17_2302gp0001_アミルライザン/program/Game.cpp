#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Float2.h"
//	�����_���֌W�̊֐����g����悤�ɃC���N���[�h
#include "Random.h"

//	�m�C�Y�摜�p�̕ϐ�
int noise_image;
//	�m�C�Y�摜��`�悷�邩�ǂ����i true�F�`�悵�܂��@false�F�`�悵�܂���j
bool noise_draw;
//	�m�C�Y�摜�̕`����W
Float2 noise_pos;

//	�m�o�b�̐�
#define NPC_MAX		10
//	�m�o�b���a
#define NPC_RADIUS	25.0f

int npc_image;
//	�m�o�b���W
Float2 npc_pos[NPC_MAX];
float npc_rot[NPC_MAX];

void EnemiesOOBHandler(int i)
{
	while (npc_pos[i].x <= 100.0f + NPC_RADIUS)
	{
		npc_pos[i].x = GetRandomF(SCREEN_W);
	}
}

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�m�o�b�摜�̓ǂݍ���
	npc_image = LoadGraph( "data/npc.bmp" );
	//	�m�C�Y�摜�̓ǂݍ���
	noise_image = LoadGraph( "data/noise.bmp" );

	//	�m�o�b�̏����ݒ�
	for( int i = 0; i < NPC_MAX; i++ ){
		//	�w���W�͍��̐��i�w���W�F100.0f�j���E�Ƀ����_���ɍ��W�ݒ�
		npc_pos[i].x = GetRandomF( SCREEN_W );
		npc_pos[i].y = GetRandomF( SCREEN_H );
		npc_rot[i] = GetRandomF( 360.0f );
		EnemiesOOBHandler(i);
	}

	noise_draw = false;
	noise_pos.x = 0.0f;
	noise_pos.y = 0.0f;

}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
static int noise_timer = 0;
static int noise_randomcd = GetRandomI(5, 7);

void GameUpdate()
{
	//	�m�o�b�̍��W������̃����_���X�V
	if (noise_draw)
	{
		for (int i = 0; i < NPC_MAX; i++)
		{
			npc_pos[i].x = GetRandomF(SCREEN_W);
			npc_pos[i].y = GetRandomF(SCREEN_H);
			npc_rot[i] = GetRandomF(360.0f);

			EnemiesOOBHandler(i);
		}
	}

	

	for( int i = 0; i < NPC_MAX; i++ )
	{
		//	����͓��ɉ������Ă��܂���
		npc_pos[i].x += GetRandomI(-1.0f, 1.0f);
		npc_pos[i].y += GetRandomI(-1.0f, 1.0f);
		npc_rot[i] += GetRandomI(-3.0f, 3.0f);

	}

	//	�}�E�X���W
	Float2 mouse;
	mouse.x = static_cast<float>(GetMouseX());
	mouse.y = static_cast<float>(GetMouseY());
	//	�}�E�X�N���b�N
	if( PushMouseInput() ){
		for( int i = 0; i < NPC_MAX; i++ ){
			//	�m�o�b���N���b�N������
			if( CheckPointCircleHit( mouse, npc_pos[i], NPC_RADIUS ) ){
				//	�m�o�b����ʍ��ɂ���
				npc_pos[i].x = 50.0f;
			}
		}
	}

	//	����̓X�y�[�X�L�[�ŕ\�����Ă��܂����A�����_�����Ԃŕ\���E��\����؂�ւ��܂��̂�
	//	�ȉ��̏����̓R�����g�ɂ��ĐV���ɏ����̎����������Ȃ��܂�
	//if( CheckHitKey( KEY_INPUT_SPACE ) ){
	//	//	�m�C�Y�摜��`�悵����
	//	noise_draw = true;
	//}else{
	//	//	�`�悵�Ȃ�
	//	noise_draw = false;
	//}

	//	�m�C�Y�摜�̍��W�������_���ɂ��Ă݂܂�
	//	�w���W�i -200.0f �` 0.0f �j
	noise_pos.x = GetRandomF( -200.0f, 0.0f );
	//	�x���W�i -550.0f �` 0.0f �j
	noise_pos.y = GetRandomF( -550.0f, 0.0f );

	noise_timer++;
	if (noise_timer % (60*noise_randomcd) == 0)
	{
		noise_draw = true;
	}

	if (noise_timer % (60 * (noise_randomcd + 1)) == 0 && noise_draw)
	{
		noise_randomcd = GetRandomI(5, 7);
		noise_timer = 0;
		noise_draw = false;
	}

	

}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	clsDx();
	//printfDx("timer : %d", noise_timer);
	{
		static int timeremaining = 0;
		if (!noise_draw)
		{
			timeremaining = 60 * noise_randomcd - noise_timer;
		}
		else
		{
			timeremaining = 60 * (noise_randomcd+1) - noise_timer;
		}

		DrawFormatString(20, 100, GetColor(255, 255, 255), "Time left : %d", timeremaining);
	}

	//	��ʍ��̐��̕`��
	DrawLineAA( 100.0f, 0.0f, 100.0f, SCREEN_H, GetColor( 255, 255, 255 ) );

	//	�m�C�Y�摜��`�悷��̂ł����
	if( noise_draw ){
		//	�m�C�Y�摜�𔼓����ɂ��܂�
		SetDrawBlendMode( DX_BLENDMODE_ALPHA, 100 );
		//	�m�C�Y�摜��`��
		DrawGraphF( noise_pos.x, noise_pos.y, noise_image, TRUE );
		//	�������ݒ�����ɖ߂�
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
	}
	else
	{
		//	�m�o�b�̕`��
		for (int i = 0; i < NPC_MAX; i++) {
			DrawRotaGraphF(npc_pos[i].x, npc_pos[i].y, 1.0f, TO_RADIAN(npc_rot[i]), npc_image, TRUE);
		}
	}

	DrawString( 16, 16, "�m�o�b�͍��̐��i�w���W�F100.0f�j���E�Ƀ����_���ɍ��W�ݒ�", GetColor( 255, 255, 0 ) );
	DrawString( 16, 32, "�m�o�b�̓����_���ɍ��W�ړ��i -1.0f �` 1.0f �j���]�i -3.0f �` 3.0f �j����", GetColor( 255, 255, 0 ) );
	DrawString( 16, 48, "�}�E�X�łm�o�b���N���b�N �� �m�o�b����ʍ���", GetColor( 255, 255, 0 ) );
	DrawString( 16, 64, "�m�C�Y���o�F�\���P�b�Ɣ�\���T�`�V�b���J��Ԃ�", GetColor( 0, 255, 255 ) );
	DrawString( 16, 80, "���@�m�C�Y�\�����͂m�o�b��\���E�m�C�Y�������ɂm�o�b���W���Z�b�g", GetColor( 0, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( npc_image );
	DeleteGraph( noise_image );
}

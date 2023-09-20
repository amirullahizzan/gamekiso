#include "Main.h"
#include "Game.h"
#include "Hit.h"

//	����͔��a���^�C�v���Ƃɕς��̂ł��̒萔�͎g���܂���
#define NPC_RADIUS	25.0f

//	����̓X�s�[�h���^�C�v���Ƃɕς��̂ł��̒萔�͎g���܂���
#define NPC_SPEED	3.0f

//	�m�o�b�̃^�C�v���͉摜�ɍ��킹�ăT�C�Y�������閼�O�ɂ��Ă��܂�
enum {
	TYPE_NORMAL,	//	�O�F�����̑傫��
	TYPE_LARGE,		//	�P�F�傫���摜
	TYPE_SMALL,		//	�Q�F�������摜

	TYPE_MAX		//	�R�F�S���łR�̃^�C�v������܂�
};

//	�g���摜��ǂݍ���Ŕԍ������Ă����p�̕ϐ�
int load_image[TYPE_MAX];

//	�m�o�b�p�̕ϐ�
int npc_type;		//	�^�C�v
int npc_image;		//	�摜
float npc_x;		//	�w���W
float npc_y;		//	�x���W
float npc_rot;		//	�����i�x�j
int npc_frame;		//	��莞�Ԃ𐔂���p�̕ϐ��i���炵�Ă������Ǝv���Ă��܂��j
int npc_speed;		//	��莞�Ԃ𐔂���p�̕ϐ��i���炵�Ă������Ǝv���Ă��܂��j
int npc_radius;		//	��莞�Ԃ𐔂���p�̕ϐ��i���炵�Ă������Ǝv���Ă��܂��j

//	�^�C�v���Ƃ̓o�ꎞ�ԗp�̃f�[�^
int npc_frame_data[TYPE_MAX] = {
	120,	//	TYPE_NORMAL	�F�Q�b
	 60,	//	TYPE_ORANGE	�F�P�b
	180,	//	TYPE_RED	�F�R�b
};

int npc_radius_data[TYPE_MAX] = {
	25,	//	TYPE_NORMAL	�F�Q�b
	 40,	//	TYPE_ORANGE	�F�P�b
	15,	//	TYPE_RED	�F�R�b
};

float npc_speed_data[TYPE_MAX] =
{
	3,2,8
};

//---------------------------------------------------------------------------------
//	�m�o�b�̃^�C�v����W�Ƃ���ύX����֐�
//---------------------------------------------------------------------------------
void ResetNPC()
{
	//	�^�C�v�̕ύX�O�̒l���Ƃ��Ă����܂�
	int old_type = npc_type;

	//	�V�����^�C�v�ƌÂ��^�C�v�������������炭��Ԃ�
	while( npc_type == old_type ){
		//	�m�o�b�̃^�C�v��ύX
		npc_type = rand() % TYPE_MAX;
	}

	//	�^�C�v�ɍ��킹���摜�̐ݒ�
	npc_image = load_image[npc_type];
	//	���W�������_����
	if (GetMouseX() > SCREEN_W/2) { npc_x = GetRand(SCREEN_W / 2); }
	else { npc_x = GetRand(SCREEN_W - SCREEN_W / 2) + SCREEN_W / 2; }

	npc_y = GetRand( SCREEN_H );
	//	�^�C�v�ɍ��킹���o�ꎞ�Ԃ̐ݒ�
	npc_frame = npc_frame_data[npc_type];
	npc_speed = npc_speed_data[npc_type];
	npc_radius = npc_radius_data[npc_type];
}

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	for( int i = 0; i < TYPE_MAX; i++ ){
		//	�����������p�̕ϐ��i char�F������^�j�Q�T�U������
		char text[256];
		//	"data/npc0.bmp" �Ƃ���������� text �ɓ���܂�
		sprintf( text, "data/npc%d.bmp", i );
		//	���̕�������g���ĉ摜�̓ǂݍ��݊֐����Ăт܂�
		load_image[i] = LoadGraph( text );
	}

	//	�ŏ��̃^�C�v��ݒ�
	npc_type = TYPE_NORMAL;

	//	�^�C�v�ɍ��킹���摜�ԍ���ݒ肵�܂�
	npc_image = load_image[npc_type];

	//	�������W������̐ݒ�
	npc_x = SCREEN_W / 2;
	npc_y = SCREEN_H / 2;
	npc_rot = 0.0f;
	//	�^�C�v�ɍ��킹���o�ꎞ�Ԃ̐ݒ�
	npc_frame = npc_frame_data[npc_type];
	npc_speed = npc_speed_data[npc_type];
	npc_radius = npc_radius_data[npc_type];
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	��ɉ�]����
	npc_rot += npc_speed;

	//	���Ԃ����炵�Ă���
	npc_frame--;
	//	���Ԃ��O�ɂȂ�����
	if( npc_frame <= 0 ){
		//	�m�o�b�Đݒ�
		ResetNPC();
	}

	//	�}�E�X�N���b�N��
	if( PushMouseInput() ){
		//	�}�E�X�̍��W���擾
		int mouse_x = GetMouseX();
		int mouse_y = GetMouseY();
		//	�}�E�X���W�i�_�j�Ƃm�o�b�i�~�j�œ����蔻��
		if( CheckPointCircleHit( mouse_x, mouse_y, npc_x, npc_y, npc_radius ) ){
			//	�m�o�b�̍Đݒ�
			ResetNPC();
		}
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�}�E�X���W�Ƃm�o�b�̓o����W�̖ڈ��ŉ�ʂ̐^�񒆂ɐ���`�悵�Ă��܂�
	DrawLine( SCREEN_W / 2, 0, SCREEN_W / 2, SCREEN_H, GetColor( 50, 50, 50 ) );

	//	�m�o�b�̕`��
	DrawRotaGraphF( npc_x, npc_y, 1.0f, TO_RADIAN( npc_rot ), npc_image, TRUE );
	//	�m�o�b�̍��W�Ɣ��a���g���ĉ~��`��
	DrawCircleAA( npc_x, npc_y, npc_radius, 100, GetColor( 255, 255, 0 ), FALSE );

	DrawString( 20,  20, "�m�o�b�N���b�N�F�ʃ^�C�v�̂m�o�b�������_���ȏꏊ��", GetColor( 255, 255, 255 ) );
	DrawString( 20,  40, "���@�m�o�b�̓o��ꏊ�́A�}�E�X����ʍ��̎��͉�ʉE�ɁA�}�E�X����ʉE�̎��͉�ʍ���", GetColor( 255, 255, 0 ) );
	DrawString( 20,  60, "�m�o�b�͈�莞�Ԃ���������N���b�N���ꂽ���Ɠ��l�ɕʃ^�C�v�ɕύX", GetColor( 255, 255, 255 ) );
	DrawString( 20,  80, "���@�o�ꂵ�Ă��鎞�Ԃ̓^�C�v�ɂ���ĈႤ", GetColor( 255, 255, 255 ) );
	DrawString( 20, 100, "���@���a���]�X�s�[�h���^�C�v�ɂ���ĈႤ", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	for( int i = 0; i < TYPE_MAX; i++ ){
		DeleteGraph( load_image[i] );
	}
}

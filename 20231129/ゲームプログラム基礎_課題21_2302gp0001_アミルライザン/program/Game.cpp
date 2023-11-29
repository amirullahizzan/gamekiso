#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Hit.h"

#include "Player.h"
#include "Npc.h"

//	�摜�p�̕ϐ�
int player_image;
int npc_image;
//	�v���C���[�̐錾
Player	player;
//	�m�o�b�̐�
#define NPC_MAX	5
//	�m�o�b�̐錾
Npc		npc[NPC_MAX];

//	�~�j�}�b�v�w�i�摜
int mini_map_image;
//	�~�j�}�b�v�̃v���C���[�摜
int mini_player_image;
//	�~�j�}�b�v�̂m�o�b�摜
int mini_npc_image;

//	�~�j�}�b�v�̊�̍��W
#define MAP_X	25
#define MAP_Y	200.0f

//	�t���[���J�E���g�𐔂���p�̕ϐ�
int frame_count;

class MiniMap
{
public:
	Float2 pos = { 0,0 };
	Float2 scale = { 0,0 };
	Float2 size = { 0,0 };
	void SetPos(float _x, float _y)
	{
		pos.x = _x;
		pos.y = _y;
	}
	void SetSize(float _x, float _y)
	{
		size.x = _x;
		size.y = _y;
	}
	void SetScale(float original_screen_size_x, float original_screen_size_y)
	{
		scale.x = original_screen_size_x / size.x;
		scale.y = original_screen_size_y / size.y;
	}

	void ScaleToMinimap(Float2& minimapEntityPos, const Float2& originalEntityPos)
	{
		minimapEntityPos = { MAP_X + (originalEntityPos.x / scale.x),
							 MAP_Y + (originalEntityPos.y / scale.y) };
	}

private:
};

MiniMap minimap;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�摜�̓ǂݍ���
	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );
	//	�摜�ԍ���n���Ċe�N���X�̏�����
	player.Init( player_image );
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Init( npc_image );
	}
	//	�~�j�}�b�v�p�摜�̓ǂݍ���
	mini_map_image = LoadGraph( "data/mini_map.bmp" );
	mini_player_image = LoadGraph( "data/mini_player.bmp" );
	mini_npc_image = LoadGraph( "data/mini_npc.bmp" );
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	�v���C���[�̍X�V�����i�\���L�[�ŉ�]�E�ړ��j
	player.Update();
	//	�m�o�b�̍X�V�����i��]���Ă��邾���j
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Update();
	}
	//	�t���[���J�E���g�𑝂₷
	frame_count++;
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�m�o�b�̕`��
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Render();
	}
	//	�v���C���[�̕`��
	player.Render();

	//	��ʉE���̏��\��������ꏊ��������悤�Ɏl�p��`��
	DrawFillBox( 0, 0, STAGE_LEFT, SCREEN_H, GetColor( 0, 0, 0 ) );

	//	�~�j�}�b�v�w�i�̕`��
	DrawGraphF( MAP_X, MAP_Y, mini_map_image, TRUE );

	//	�~�j�m�o�b�̕`��
	for( int i = 0; i < NPC_MAX; i++ ){
		//	�~�j�m�o�b�̍��W�̐ݒ�
		float nx = MAP_X - STAGE_LEFT / 2 + npc[i].m_pos.x / 2.0f;
		float ny = MAP_Y + npc[i].m_pos.y / 2.0f;
		//	�����͒ʏ�̂m�o�b�Ɠ���
		float nrot = npc[i].m_rot;
		//	�~�j�m�o�b�̕`��
		DrawRotaGraphF( nx, ny, 1.0f, TO_RADIAN( nrot ), mini_npc_image, TRUE );
	}

	//	�~�j�v���C���[�̕`��
	//	�v���C���[�̍��W���~�j�v���C���[�p�ɂ��܂��i����̃~�j�}�b�v�͈͎̔͂��ۂ̃X�e�[�W�̔����j
	//	MAP_X MAP_Y �̂Ƃ��납��v���C���[���W�̔����������炷
	float px = MAP_X - STAGE_LEFT/2 + player.m_pos.x / 2.0f;
	float py = MAP_Y + player.m_pos.y / 2.0f;
	//	������
	float prot = player.m_rot;
	//	���̍��W�ƌ������g���ă~�j�v���C���[�摜��`��
	DrawRotaGraphF( px, py, 1.0f, TO_RADIAN( prot ), mini_player_image, TRUE );

	//	������̕`����E���ɂ��炵�܂�
	DrawString(  20, 20, "���E�L�[�F�v���C���[�̉�]", GetColor( 255, 255, 255 ) );
	DrawString(  20, 40, "��L�[�@�F�����Ă�������Ɉړ�", GetColor( 255, 255, 255 ) );

	DrawString( 20,  70, "�~�j�}�b�v�╶����Ȃǂ�", GetColor( 255, 255, 0 ) );
	DrawString( 20,  90, "���̕`�����ʍ���", GetColor( 255, 255, 0 ) );
	DrawString( 20, 110, "�v���C���[��m�o�b�͉�ʉE��", GetColor( 255, 255, 0 ) );

	//	�t���[���J�E���g�̕�����̕`��
	DrawFormatString( 20, 140, GetColor( 255, 255, 255 ), "�Q�[���J�n����@%05d", frame_count );
	static int frame_second = 0;
	static int frame_minute = 0;
	if (frame_count % 60 == 0) 
	{
		frame_second += 1;
		frame_count = 0;
		if (frame_second % 60 == 0)
		{
			frame_minute += 1;
			frame_second = 0;
		}
	}
	DrawFormatString( 20, 160, GetColor( 255, 255, 0), "�Q�[���J�n����@%02d:%02d:%02d", frame_minute, frame_second, frame_count);

	DrawString( 20, 180, "�~�j�}�b�v�̕\��", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	//	�~�j�}�b�v�֌W�̉摜�̏I������
	DeleteGraph( mini_map_image );
	DeleteGraph( mini_player_image );
	DeleteGraph( mini_npc_image );

	player.Exit();
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Exit();
	}

	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}

#include "Main.h"
#include "Game.h"
#include "Random.h"

//	Player.h �̒��ŗp�ӂ����v���C���[�N���X�̊֐��͒��łǂ�ȏ���������̂��� cpp �ŏ����܂�
//	���̂��߂Ƀv���C���[�N���X���ǂ��������̂������悤��
#include "Player.h"

//	�ړ��X�s�[�h
#define PLAYER_SPEED	5.0f

//---------------------------------------------------------------------------------
//	�v���C���[�N���X�̏������֐�
//---------------------------------------------------------------------------------
void Player::Init()
{
	//	�v���C���[�摜�i player.bmp �j��ǂݍ���Ŕԍ�������p�̕ϐ��i m_image �j�ɔԍ�������
	m_image = LoadGraph( "data/player.bmp" );
	//	�������W�̐ݒ�
	m_pos.x = 100.0f;
	m_pos.y = 200.0f;
}
//---------------------------------------------------------------------------------
//	�v���C���[�N���X�̍X�V�����i�\���L�[�ō��W�ړ��j
//---------------------------------------------------------------------------------
void Player::Update()
{
	//	�\���L�[�ō��W�̍X�V
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		m_pos.x += PLAYER_SPEED;
		rotation = 0;
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		m_pos.x -= PLAYER_SPEED;
		rotation = 180;

	}
	if( CheckHitKey( KEY_INPUT_DOWN ) ){
		m_pos.y += PLAYER_SPEED;
		rotation = 90;

	}
	if( CheckHitKey( KEY_INPUT_UP ) ){
		m_pos.y -= PLAYER_SPEED;
		rotation = 270;

	}
}
//---------------------------------------------------------------------------------
//	�v���C���[�N���X�̕`�揈��
//---------------------------------------------------------------------------------
void Player::Render()
{
	//	�X�V�����œ������������o�[�ϐ��̍��W�i m_pos �j�̏ꏊ�ɉ摜�i m_image �j�̕`��
	DrawRotaGraphF( m_pos.x, m_pos.y, 1.0f, TO_RADIAN( rotation ), m_image, TRUE );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Player::Exit()
{
	//	�ǂݍ��񂾉摜�i m_image �j�̏I������
	DeleteGraph( m_image );
}

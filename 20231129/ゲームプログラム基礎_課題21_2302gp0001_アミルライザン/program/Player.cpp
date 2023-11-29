#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Player.h"

//	�ړ��X�s�[�h
#define PLAYER_MOV_SPEED	5.0f
//	��]�X�s�[�h
#define PLAYER_ROT_SPEED	3.0f

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Player::Init( int image )
{
	//	�󂯎�����摜��ݒ�
	m_image = image;
	//	���a�̐ݒ�i����̓v���C���[�Ƃm�o�b�Ŕ��a���Ⴄ�̂ł��ꂼ��ŕϐ��������Ă��܂��j
	m_radius = 30.0f;
	//	���W������̐ݒ�
	m_pos.x = 250.0f;
	m_pos.y = 250.0f;
	m_rot = 0.0f;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Player::Update()
{
	//	���E�L�[�Ō����̕ύX
	if( CheckHitKey( KEY_INPUT_RIGHT ) )	m_rot += PLAYER_ROT_SPEED;
	if( CheckHitKey( KEY_INPUT_LEFT ) )		m_rot -= PLAYER_ROT_SPEED;
	//	��L�[��
	if( CheckHitKey( KEY_INPUT_UP ) ){
		//	�����Ă�������Ɉړ�
		m_pos.x += PLAYER_MOV_SPEED * cosf( TO_RADIAN( m_rot ) );
		m_pos.y += PLAYER_MOV_SPEED * sinf( TO_RADIAN( m_rot ) );
	}
	//	�X�e�[�W�͈̔͂���o�Ȃ��悤�ɂ���
	if( m_pos.x < STAGE_LEFT+m_radius )			m_pos.x = STAGE_LEFT + m_radius;
	if( m_pos.x > SCREEN_W - m_radius )	m_pos.x = SCREEN_W - m_radius;
	if( m_pos.y < m_radius )			m_pos.y = m_radius;
	if( m_pos.y > STAGE_H - m_radius )	m_pos.y = STAGE_H - m_radius;
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void Player::Render()
{
	DrawRotaGraphF( m_pos.x, m_pos.y, 1.0f, TO_RADIAN( m_rot ), m_image, TRUE );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Player::Exit()
{
}

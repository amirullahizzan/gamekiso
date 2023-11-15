#pragma once

#include "Float2.h"

//	�m�o�b�̏�Ԃ�\���萔
enum {
	TYPE_NONE,	//	�O�F�������Ȃ�
	TYPE_LEFT,	//	�P�F���Ɉړ�
	TYPE_RIGHT,	//	2
};

//---------------------------------------------------------------------------------
//	�m�o�b�N���X
//---------------------------------------------------------------------------------
class Npc
{
public:
	int		m_image;	//	�摜�p
	Float2	m_pos;		//	���W
	float	m_rot;		//	����

	int		m_type;		//	�ǂ�ȏ�ԂȂ̂��i�O�F�����Ă���@�P�F���Ɉړ��j

	void Init( int image );		//	�����������i�摜�ԍ����󂯎���悤�Ɂj
	void Update();		//	�X�V����
	void Render();		//	�`�揈��
	void Exit();		//	�I������
};

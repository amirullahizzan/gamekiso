#pragma once

//	Base �N���X���p�����邽�߂�
#include "Base.h"

//---------------------------------------------------------------------------------
//	�v���C���[�N���X�i Base �N���X���p�����܂��j
//---------------------------------------------------------------------------------
class Player : public Base
{
public:

	//	����͂��̕ϐ������� Base �̂��g���̂ŃR�����g�ɂ��܂�
//	int		m_image;
//	Float2	m_pos;
//	float	m_rot;

	//	�ړ��X�s�[�h�i�|�[�Y���j���[�ŕύX����̂ŕϐ��ɂ��܂��j
	float	m_speed;

	void Init( int image );		//	����������
	void Update();		//	�X�V����
	void Render();		//	�`�揈��
	void Exit();		//	�I������
};

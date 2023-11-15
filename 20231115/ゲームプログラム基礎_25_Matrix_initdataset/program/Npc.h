#pragma once

#include "Float2.h"

enum 
{
	TYPE_NONE, TYPE_LEFT
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
	int m_type; // 0 disappear, 1 move to left

	void Init(int image);		//	����������
	void Update();		//	�X�V����
	void Render();		//	�`�揈��
	void Exit(int image);		//	�I������
};

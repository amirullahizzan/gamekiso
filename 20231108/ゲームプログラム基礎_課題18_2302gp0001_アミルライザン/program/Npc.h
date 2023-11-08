#pragma once

//	���W�ŕK�v�Ȃ̂�
#include "Float2.h"

//---------------------------------------------------------------------------------
//	�m�o�b�N���X
//---------------------------------------------------------------------------------
class Npc
{
private :
	int rotation = 0;
public:
	//	�摜�p�̕ϐ�
	int		m_image;
	//	���W�p�̕ϐ�
	Float2	m_pos;

	void Init();	//	����������
	void Update();	//	�X�V����
	void Render();	//	�`�揈��
	void Exit();	//	�I������

	void SetRandom();	//	���W�������_���ɐݒ肷��֐�
};

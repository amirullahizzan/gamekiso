#pragma once

#include "Base.h"
#include "Float2.h"

//---------------------------------------------------------------------------------
//	�m�o�b�N���X
//---------------------------------------------------------------------------------
class Npc : public Base
{
public:

	void Init( int image );		//	����������
	void Update() override;		//	�X�V����
	void Render();		//	�`�揈��
	void Exit();		//	�I������
};

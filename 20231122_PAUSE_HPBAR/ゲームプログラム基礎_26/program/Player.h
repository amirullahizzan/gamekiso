#pragma once

#include "Base.h"
#include "Float2.h"

//---------------------------------------------------------------------------------
//	�v���C���[�N���X
//---------------------------------------------------------------------------------
class Player : public Base
{
private:
	float m_speed = 1.0f;
	const float MAX_SPEED = 10.0f;
	const float MIN_SPEED = 1.0f;
public:

	void Init( int image );		//	����������
	void Update();		//	�X�V����
	void Render();		//	�`�揈��
	void Exit();		//	�I������

	void AddSpeed(float add_value)
	{
		m_speed += add_value;
		if (m_speed + add_value > MAX_SPEED) { m_speed = 10.0f; }
		if (m_speed + add_value < MIN_SPEED) { m_speed = 1.0f; }
	}

	float GetSpeed()
	{
		return m_speed;
	}
};

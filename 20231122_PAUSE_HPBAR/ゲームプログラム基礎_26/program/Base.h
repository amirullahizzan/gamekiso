#pragma once

#include "Float2.h"

//---------------------------------------------------------------------------------
//	��{�N���X
//---------------------------------------------------------------------------------
extern bool isGamePaused;

class Base
{
public:
	int		m_image;

	Float2	m_pos;
	float	m_rot;

	virtual void Update()
	{
		if (isGamePaused)
		{
			//return;
		}
	}
};

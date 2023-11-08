#pragma once

#include "Float2.h"

//---------------------------------------------------------------------------------
//	‚m‚o‚bƒNƒ‰ƒX
//---------------------------------------------------------------------------------
class Npc
{
private :
	/*void SetSize()
	{
		static const int _size_x = 50;
		static const int _size_y = 50;
		size.x = m_pos.x + _size_x;
		size.y = m_pos.y + _size_y;
	}*/
public:

	int		m_image;
	int radius = 25;

	Float2	m_pos;
	//Float2	size;

	void Init();	//	‰Šú‰»ˆ—
	void Update();	//	XVˆ—
	void Render();	//	•`‰æˆ—
	void Exit();	//	I—¹ˆ—
	void Randomize();
};

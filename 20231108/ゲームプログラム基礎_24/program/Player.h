#pragma once
#include "Float2.h"

class Player
{
private :
	const int speed = 5;
	int imagehandler = -1;

	/*void SetSize()
	{
		static const int _size_x = 50;
		static const int _size_y = 50;
		size.x = pos.x + _size_x;
		size.y = pos.y + _size_y;
	}*/

public :
	Float2 pos;
	//Float2 size;
	int radius = 25;

	void Init();
	void Update();
	void Render();
	void Exit();

};
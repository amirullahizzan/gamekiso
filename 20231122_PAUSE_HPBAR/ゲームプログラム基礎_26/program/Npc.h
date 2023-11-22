#pragma once

#include "Base.h"
#include "Float2.h"

//---------------------------------------------------------------------------------
//	‚m‚o‚bƒNƒ‰ƒX
//---------------------------------------------------------------------------------
class Npc : public Base
{
public:

	void Init( int image );		//	‰Šú‰»ˆ—
	void Update() override;		//	XVˆ—
	void Render();		//	•`‰æˆ—
	void Exit();		//	I—¹ˆ—
};

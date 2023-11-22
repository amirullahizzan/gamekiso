#pragma once

#include "Base.h"
#include "Float2.h"

//---------------------------------------------------------------------------------
//	プレイヤークラス
//---------------------------------------------------------------------------------
class Player : public Base
{
private:
	float m_speed = 1.0f;
	const float MAX_SPEED = 10.0f;
	const float MIN_SPEED = 1.0f;
public:

	void Init( int image );		//	初期化処理
	void Update();		//	更新処理
	void Render();		//	描画処理
	void Exit();		//	終了処理

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

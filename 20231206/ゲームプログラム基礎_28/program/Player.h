#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	プレイヤークラス
//---------------------------------------------------------------------------------
class Player : public Base
{
public:
	Float2 m_mov;

	void Init( int image );		//	初期化処理
	void Update();		//	更新処理
//	void Render();		//	描画処理
	void Exit();		//	終了処理
};

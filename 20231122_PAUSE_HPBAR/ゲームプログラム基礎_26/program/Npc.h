#pragma once

#include "Base.h"
#include "Float2.h"

//---------------------------------------------------------------------------------
//	ＮＰＣクラス
//---------------------------------------------------------------------------------
class Npc : public Base
{
public:

	void Init( int image );		//	初期化処理
	void Update() override;		//	更新処理
	void Render();		//	描画処理
	void Exit();		//	終了処理
};

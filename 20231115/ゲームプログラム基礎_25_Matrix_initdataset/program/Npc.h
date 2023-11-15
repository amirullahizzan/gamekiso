#pragma once

#include "Float2.h"

enum 
{
	TYPE_NONE, TYPE_LEFT
};

//---------------------------------------------------------------------------------
//	ＮＰＣクラス
//---------------------------------------------------------------------------------
class Npc
{
public:
	int		m_image;	//	画像用
	Float2	m_pos;		//	座標
	float	m_rot;		//	向き
	int m_type; // 0 disappear, 1 move to left

	void Init(int image);		//	初期化処理
	void Update();		//	更新処理
	void Render();		//	描画処理
	void Exit(int image);		//	終了処理
};

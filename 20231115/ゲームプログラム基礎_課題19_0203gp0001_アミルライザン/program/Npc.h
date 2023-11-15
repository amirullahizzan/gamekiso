#pragma once

#include "Float2.h"

//	ＮＰＣの状態を表す定数
enum {
	TYPE_NONE,	//	０：何もしない
	TYPE_LEFT,	//	１：左に移動
	TYPE_RIGHT,	//	2
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

	int		m_type;		//	どんな状態なのか（０：消えている　１：左に移動）

	void Init( int image );		//	初期化処理（画像番号を受け取れるように）
	void Update();		//	更新処理
	void Render();		//	描画処理
	void Exit();		//	終了処理
};

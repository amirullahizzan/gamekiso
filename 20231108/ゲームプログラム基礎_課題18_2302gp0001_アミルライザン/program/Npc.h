#pragma once

//	座標で必要なので
#include "Float2.h"

//---------------------------------------------------------------------------------
//	ＮＰＣクラス
//---------------------------------------------------------------------------------
class Npc
{
private :
	int rotation = 0;
public:
	//	画像用の変数
	int		m_image;
	//	座標用の変数
	Float2	m_pos;

	void Init();	//	初期化処理
	void Update();	//	更新処理
	void Render();	//	描画処理
	void Exit();	//	終了処理

	void SetRandom();	//	座標をランダムに設定する関数
};

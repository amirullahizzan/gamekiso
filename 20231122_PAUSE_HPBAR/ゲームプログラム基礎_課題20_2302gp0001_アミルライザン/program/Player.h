#pragma once

//	Base クラスを継承するために
#include "Base.h"

//---------------------------------------------------------------------------------
//	プレイヤークラス（ Base クラスを継承します）
//---------------------------------------------------------------------------------
class Player : public Base
{
public:

	//	今回はこの変数たちは Base のを使うのでコメントにします
//	int		m_image;
//	Float2	m_pos;
//	float	m_rot;

	//	移動スピード（ポーズメニューで変更するので変数にします）
	float	m_speed;

	void Init( int image );		//	初期化処理
	void Update();		//	更新処理
	void Render();		//	描画処理
	void Exit();		//	終了処理
};

#include "Main.h"
#include "Base.h"

//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
Base::Base()
{
	m_image = -1;
	m_pos.clear();
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Base::Render( float offset_x )
{
	//	座標の値をそのまま描画として使っています
//	DrawGraphF( m_pos.x, m_pos.y, m_image, TRUE );

	//	ゲーム内座標からのずれ分を引いて画面座標を求めます
	float screen_x = m_pos.x - offset_x;
	//	その座標（画面座標）を使って描画
	DrawGraphF( screen_x, m_pos.y, m_image, TRUE );
}

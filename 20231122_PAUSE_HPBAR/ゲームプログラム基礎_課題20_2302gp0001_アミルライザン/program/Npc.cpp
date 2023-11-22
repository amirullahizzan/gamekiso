#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Npc.h"

#define NPC_SPEED	3.0f

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Npc::Init( int image )
{
	//	画像の設定
	m_image = image;
	//	ランダムに初期座標の設定
	m_pos.x = GetRandomF( SCREEN_W );
	m_pos.y = GetRandomF( SCREEN_H );
	//	左向きで開始
	m_rot = 180.0f;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Npc::Update()
{
	//	画面左に移動
	m_pos.x -= NPC_SPEED;
	//	画面左まで行ったら
	if( m_pos.x < 0.0f ){
		//	右にする
		m_pos.x = SCREEN_W;
		m_pos.y = GetRandomF( SCREEN_H );
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Npc::Render()
{
	DrawRotaGraphF( m_pos.x, m_pos.y, 1.0f, TO_RADIAN( m_rot ), m_image, TRUE );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Npc::Exit()
{
}

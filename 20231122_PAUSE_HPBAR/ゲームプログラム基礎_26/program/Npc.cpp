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
	m_image = image;

	m_pos.x = GetRandomF( SCREEN_W );
	m_pos.y = GetRandomF( SCREEN_H );
	m_rot = 180.0f;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Npc::Update()
{
	Base::Update();
	m_pos.x -= NPC_SPEED;
	if( m_pos.x < 0.0f ){
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

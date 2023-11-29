#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Player.h"

//	移動スピード
#define PLAYER_MOV_SPEED	5.0f
//	回転スピード
#define PLAYER_ROT_SPEED	3.0f

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Player::Init( int image )
{
	//	受け取った画像を設定
	m_image = image;
	//	半径の設定（今回はプレイヤーとＮＰＣで半径が違うのでそれぞれで変数を持っています）
	m_radius = 30.0f;
	//	座標や向きの設定
	m_pos.x = 250.0f;
	m_pos.y = 250.0f;
	m_rot = 0.0f;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Player::Update()
{
	//	左右キーで向きの変更
	if( CheckHitKey( KEY_INPUT_RIGHT ) )	m_rot += PLAYER_ROT_SPEED;
	if( CheckHitKey( KEY_INPUT_LEFT ) )		m_rot -= PLAYER_ROT_SPEED;
	//	上キーで
	if( CheckHitKey( KEY_INPUT_UP ) ){
		//	向いている方向に移動
		m_pos.x += PLAYER_MOV_SPEED * cosf( TO_RADIAN( m_rot ) );
		m_pos.y += PLAYER_MOV_SPEED * sinf( TO_RADIAN( m_rot ) );
	}
	//	ステージの範囲から出ないようにする
	if( m_pos.x < STAGE_LEFT+m_radius )			m_pos.x = STAGE_LEFT + m_radius;
	if( m_pos.x > SCREEN_W - m_radius )	m_pos.x = SCREEN_W - m_radius;
	if( m_pos.y < m_radius )			m_pos.y = m_radius;
	if( m_pos.y > STAGE_H - m_radius )	m_pos.y = STAGE_H - m_radius;
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Player::Render()
{
	DrawRotaGraphF( m_pos.x, m_pos.y, 1.0f, TO_RADIAN( m_rot ), m_image, TRUE );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Player::Exit()
{
}

#include "Main.h"
#include "Game.h"
#include "Random.h"

//	Player.h の中で用意したプレイヤークラスの関数は中でどんな処理をするのかを cpp で書きます
//	そのためにプレイヤークラスがどういうものか見れるように
#include "Player.h"

//	移動スピード
#define PLAYER_SPEED	5.0f

//---------------------------------------------------------------------------------
//	プレイヤークラスの初期化関数
//---------------------------------------------------------------------------------
void Player::Init()
{
	//	プレイヤー画像（ player.bmp ）を読み込んで番号を入れる用の変数（ m_image ）に番号を入れる
	m_image = LoadGraph( "data/player.bmp" );
	//	初期座標の設定
	m_pos.x = 100.0f;
	m_pos.y = 200.0f;
}
//---------------------------------------------------------------------------------
//	プレイヤークラスの更新処理（十字キーで座標移動）
//---------------------------------------------------------------------------------
void Player::Update()
{
	//	十字キーで座標の更新
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		m_pos.x += PLAYER_SPEED;
		rotation = 0;
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		m_pos.x -= PLAYER_SPEED;
		rotation = 180;

	}
	if( CheckHitKey( KEY_INPUT_DOWN ) ){
		m_pos.y += PLAYER_SPEED;
		rotation = 90;

	}
	if( CheckHitKey( KEY_INPUT_UP ) ){
		m_pos.y -= PLAYER_SPEED;
		rotation = 270;

	}
}
//---------------------------------------------------------------------------------
//	プレイヤークラスの描画処理
//---------------------------------------------------------------------------------
void Player::Render()
{
	//	更新処理で動かしたメンバー変数の座標（ m_pos ）の場所に画像（ m_image ）の描画
	DrawRotaGraphF( m_pos.x, m_pos.y, 1.0f, TO_RADIAN( rotation ), m_image, TRUE );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Player::Exit()
{
	//	読み込んだ画像（ m_image ）の終了処理
	DeleteGraph( m_image );
}

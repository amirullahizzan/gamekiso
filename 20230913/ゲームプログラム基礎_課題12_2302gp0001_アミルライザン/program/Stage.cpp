#include "Main.h"
#include "Game.h"
#include "Stage.h"

#include "Hit.h"

//=================================================================================
//	ステージの処理
//=================================================================================

//	プレイヤーのスピード
#define PLAYER_SPEED	5.0f
//	ＮＰＣのスピード
#define NPC_SPEED		3.0f
//	当たり判定用の半径
#define RADIUS			25.0f

//	それぞれの画像用の変数
int stage_image;
int player_image;
int npc_image;
//	プレイヤーの変数
float player_x;
float player_y;
float player_rot;
//	ＮＰＣ
float npc_x;
float npc_y;
float npc_rot;

int stage_frame;
//---------------------------------------------------------------------------------
//	データの読み込み
//---------------------------------------------------------------------------------
void StageLoad()
{
	//	画像の読み込み
	stage_image = LoadGraph( "data/stage_bg.bmp" );
	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );
}
//---------------------------------------------------------------------------------
//	初期化
//---------------------------------------------------------------------------------
void StageInit()
{
	//	プレイヤー変数の初期設定
	player_x = SCREEN_W / 2.0f;
	player_y = 400.0f;
	player_rot = -90.0f;
	//	ＮＰＣも
	npc_x = (float)GetRand( SCREEN_W );
	npc_y = 0.0f;
	npc_rot = 90.0f;
	stage_frame = 0;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void StageUpdate()
{
	//	十字キーでプレイヤーの座標の更新
	if( CheckHitKey( KEY_INPUT_RIGHT ) )	player_x += PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_LEFT ) )		player_x -= PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_DOWN ) )		player_y += PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_UP ) )		player_y -= PLAYER_SPEED;
	//	ＮＰＣの更新処理（画面の下に移動）
	npc_y += NPC_SPEED;
	if( npc_y > SCREEN_H ){
		npc_x = (float)GetRand( SCREEN_W );
		npc_y = 0.0f;
	}
	//	プレイヤーとＮＰＣの当たり判定
	if( CheckCircleHit( player_x, player_y, RADIUS, npc_x, npc_y, RADIUS ) ){
		//	当たったらタイトルに戻るので次に行きたいシーンをタイトルに
		scene_next = SCENE_CLEAR;
	}
	stage_frame++;

}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void StageRender()
{
	//	それぞれの画像の描画
	DrawGraph( 0, 0, stage_image, TRUE );

	DrawRotaGraphF( npc_x, npc_y, 1.0f, TO_RADIAN( npc_rot ), npc_image, TRUE );

	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( player_rot ), player_image, TRUE );

	DrawString( 20, 20, "【ステージ画面】", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "十字キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
	DrawString( 20, 60, "ＮＰＣと当たったら「クリア画面」へ", GetColor( 255, 255, 0 ) );
	

	DrawFormatString( 20, 80, GetColor(255, 255, 0) , "経った時間 :  %d", stage_frame);
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void StageExit()
{
	DeleteGraph( stage_image );

	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}

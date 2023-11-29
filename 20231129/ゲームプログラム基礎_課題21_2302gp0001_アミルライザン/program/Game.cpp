#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Hit.h"

#include "Player.h"
#include "Npc.h"

//	画像用の変数
int player_image;
int npc_image;
//	プレイヤーの宣言
Player	player;
//	ＮＰＣの数
#define NPC_MAX	5
//	ＮＰＣの宣言
Npc		npc[NPC_MAX];

//	ミニマップ背景画像
int mini_map_image;
//	ミニマップのプレイヤー画像
int mini_player_image;
//	ミニマップのＮＰＣ画像
int mini_npc_image;

//	ミニマップの基準の座標
#define MAP_X	25
#define MAP_Y	200.0f

//	フレームカウントを数える用の変数
int frame_count;

class MiniMap
{
public:
	Float2 pos = { 0,0 };
	Float2 scale = { 0,0 };
	Float2 size = { 0,0 };
	void SetPos(float _x, float _y)
	{
		pos.x = _x;
		pos.y = _y;
	}
	void SetSize(float _x, float _y)
	{
		size.x = _x;
		size.y = _y;
	}
	void SetScale(float original_screen_size_x, float original_screen_size_y)
	{
		scale.x = original_screen_size_x / size.x;
		scale.y = original_screen_size_y / size.y;
	}

	void ScaleToMinimap(Float2& minimapEntityPos, const Float2& originalEntityPos)
	{
		minimapEntityPos = { MAP_X + (originalEntityPos.x / scale.x),
							 MAP_Y + (originalEntityPos.y / scale.y) };
	}

private:
};

MiniMap minimap;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	画像の読み込み
	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );
	//	画像番号を渡して各クラスの初期化
	player.Init( player_image );
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Init( npc_image );
	}
	//	ミニマップ用画像の読み込み
	mini_map_image = LoadGraph( "data/mini_map.bmp" );
	mini_player_image = LoadGraph( "data/mini_player.bmp" );
	mini_npc_image = LoadGraph( "data/mini_npc.bmp" );
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	プレイヤーの更新処理（十字キーで回転・移動）
	player.Update();
	//	ＮＰＣの更新処理（回転しているだけ）
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Update();
	}
	//	フレームカウントを増やす
	frame_count++;
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	ＮＰＣの描画
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Render();
	}
	//	プレイヤーの描画
	player.Render();

	//	画面右側の情報表示をする場所が分かるように四角を描画
	DrawFillBox( 0, 0, STAGE_LEFT, SCREEN_H, GetColor( 0, 0, 0 ) );

	//	ミニマップ背景の描画
	DrawGraphF( MAP_X, MAP_Y, mini_map_image, TRUE );

	//	ミニＮＰＣの描画
	for( int i = 0; i < NPC_MAX; i++ ){
		//	ミニＮＰＣの座標の設定
		float nx = MAP_X - STAGE_LEFT / 2 + npc[i].m_pos.x / 2.0f;
		float ny = MAP_Y + npc[i].m_pos.y / 2.0f;
		//	向きは通常のＮＰＣと同じ
		float nrot = npc[i].m_rot;
		//	ミニＮＰＣの描画
		DrawRotaGraphF( nx, ny, 1.0f, TO_RADIAN( nrot ), mini_npc_image, TRUE );
	}

	//	ミニプレイヤーの描画
	//	プレイヤーの座標をミニプレイヤー用にします（今回のミニマップの範囲は実際のステージの半分）
	//	MAP_X MAP_Y のところからプレイヤー座標の半分だけずらす
	float px = MAP_X - STAGE_LEFT/2 + player.m_pos.x / 2.0f;
	float py = MAP_Y + player.m_pos.y / 2.0f;
	//	向きも
	float prot = player.m_rot;
	//	この座標と向きを使ってミニプレイヤー画像を描画
	DrawRotaGraphF( px, py, 1.0f, TO_RADIAN( prot ), mini_player_image, TRUE );

	//	文字列の描画も右側にずらします
	DrawString(  20, 20, "左右キー：プレイヤーの回転", GetColor( 255, 255, 255 ) );
	DrawString(  20, 40, "上キー　：向いている方向に移動", GetColor( 255, 255, 255 ) );

	DrawString( 20,  70, "ミニマップや文字列などの", GetColor( 255, 255, 0 ) );
	DrawString( 20,  90, "情報の描画を画面左に", GetColor( 255, 255, 0 ) );
	DrawString( 20, 110, "プレイヤーやＮＰＣは画面右に", GetColor( 255, 255, 0 ) );

	//	フレームカウントの文字列の描画
	DrawFormatString( 20, 140, GetColor( 255, 255, 255 ), "ゲーム開始から　%05d", frame_count );
	static int frame_second = 0;
	static int frame_minute = 0;
	if (frame_count % 60 == 0) 
	{
		frame_second += 1;
		frame_count = 0;
		if (frame_second % 60 == 0)
		{
			frame_minute += 1;
			frame_second = 0;
		}
	}
	DrawFormatString( 20, 160, GetColor( 255, 255, 0), "ゲーム開始から　%02d:%02d:%02d", frame_minute, frame_second, frame_count);

	DrawString( 20, 180, "ミニマップの表示", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	//	ミニマップ関係の画像の終了処理
	DeleteGraph( mini_map_image );
	DeleteGraph( mini_player_image );
	DeleteGraph( mini_npc_image );

	player.Exit();
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Exit();
	}

	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}

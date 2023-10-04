#include "Main.h"
#include "Game.h"
#include "Hit.h"

#define PLAYER_RADIUS		50.0f
#define CIRCLE_RADIUS		100.0f

int player_image;
float player_x;
float player_y;

int npc_image;
float npc_x;
float npc_y;

float circle_x;
float circle_y;

int circleAlpha = 256;
int blackboxAlpha = 0;


//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	player_image = LoadGraph( "data/player.bmp" );
	player_x = 100.0f;
	player_y = 200.0f;

	npc_image = LoadGraph( "data/npc.bmp" );
	npc_x = 350.0f;
	npc_y = 200.0f;

	circle_x = 200.0f;
	circle_y = 300.0f;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	player_x = GetMouseX();
	player_y = GetMouseY();

	if( CheckHitKey( KEY_INPUT_UP ) )
	{
		if (blackboxAlpha < 256){		blackboxAlpha+=4;		}
	}
	if( CheckHitKey( KEY_INPUT_DOWN ) )
	{
		if (blackboxAlpha > 0){		blackboxAlpha-=4;		}
	}

	if( CheckCircleHit( player_x, player_y, PLAYER_RADIUS, circle_x, circle_y, CIRCLE_RADIUS ) )
	{
		circleAlpha = 128;
	}
	else
	{
		circleAlpha = 256;
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------

void GameRender()
{
	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( 0.0f ), player_image, TRUE );
	DrawCircleAA( player_x, player_y, PLAYER_RADIUS, 100, GetColor( 255, 255, 0 ), FALSE );
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawRotaGraphF( npc_x, npc_y, 1.0f, TO_RADIAN( 0.0f ), npc_image, TRUE );
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, circleAlpha);
	DrawCircleAA( circle_x, circle_y, CIRCLE_RADIUS, 100, GetColor( 255, 255, 255 ) );
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blackboxAlpha);
	DrawFillBox(0,0,SCREEN_W,SCREEN_H,GetColor(0,0,0));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawString( 16, 16, "マウス座標の所にプレイヤー画像の描画", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "プレイヤー円と白い円が重なると白い円が半透明に", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "上下キー：フェード", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}

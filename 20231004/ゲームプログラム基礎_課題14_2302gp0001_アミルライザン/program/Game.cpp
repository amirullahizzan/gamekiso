#include "Main.h"
#include "Game.h"
#include "Hit.h"

//	プレイヤー用の変数
int player_image;	//	画像
float player_x;		//	Ｘ座標
float player_y;		//	Ｙ座標

//	ＮＰＣ用の変数
int npc_image;		//	画像
float npc_x;		//	Ｘ座標
float npc_y;		//	Ｙ座標

int npc_alpha;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	プレイヤーの初期設定
	player_image = LoadGraph( "data/player.bmp" );
	player_x = 100.0f;
	player_y = 200.0f;

	//	ＮＰＣの初期設定
	npc_image = LoadGraph( "data/npc.bmp" );
	npc_x = 350.0f;
	npc_y = 200.0f;
	npc_alpha = 256;
}
int alphaMode = 1;
void GameUpdate()
{
	//	マウス座標をプレイヤーの座標にします
	player_x = GetMouseX();
	player_y = GetMouseY();

	switch (alphaMode)
	{
	case 0:
		npc_alpha += 2;
		if (npc_alpha >= 256)
		{
			alphaMode = 1;
		}
		break;
	case 1:
		npc_alpha -= 2;
		if (npc_alpha <= 0)
		{
			npc_x = GetRand(SCREEN_W);
			npc_y = GetRand(SCREEN_H);
			alphaMode = 0;
		}
		break;
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	プレイヤーの描画
	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( 0.0f ), player_image, TRUE );

	//	ＮＰＣを半透明にして描画したい
	//	１：今から描画するもの（ＮＰＣ）の透明度を設定
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, npc_alpha );
	//	２：いつもの描画
	//	ＮＰＣの描画
	DrawRotaGraphF( npc_x, npc_y, 1.0f, TO_RADIAN( 0.0f ), npc_image, TRUE );
	//	次の描画のために透明度設定を元に戻します
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );

	//WHITE
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256/2);
	DrawFillBox(SCREEN_W / 2 - 280,SCREEN_H - 160, SCREEN_W / 2 + 280, SCREEN_H -50,GetColor(0,0,0));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawLineBox(SCREEN_W / 2 - 280, SCREEN_H - 160, SCREEN_W / 2 + 280, SCREEN_H - 50, GetColor(255, 255, 255));

	DrawString( SCREEN_W/2 - 220, SCREEN_H - 145, "マウス座標の所にプレイヤー画像の描画", GetColor( 255, 255, 255 ) );
	DrawString(SCREEN_W / 2 - 220, SCREEN_H - 145 + 18, "ＮＰＣは出たり消えたりを繰り返す", GetColor( 255, 255, 0 ) );
	DrawString(SCREEN_W / 2 - 220, SCREEN_H - 145 + 18*2, "→　出てくるときは座標をランダムに", GetColor( 255, 255, 0 ) );
	DrawString(SCREEN_W / 2 - 220, SCREEN_H - 145 + 18*3, "この文字列をメッセージ表示みたいにしてみる", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}

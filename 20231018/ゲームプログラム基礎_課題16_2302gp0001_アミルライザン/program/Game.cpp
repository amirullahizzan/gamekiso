#include "Main.h"
#include "Game.h"
#include "Float2.h"
#include "Hit.h"

//	選択項目に使う文字列は３個
#define TEXT_MAX	3

//	選択文字列３つ
const char *sample_text[TEXT_MAX] = {
	"はじめから",
	"続きから",
	"ゲームの設定",
};
//	その文字列の座標３つ
Float2 pos[TEXT_MAX];

Float2 text_size[TEXT_MAX];
int text_color[TEXT_MAX];
int pos_offset[TEXT_MAX];

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//ChangeFont("UD デジタル 教科書体 NK-B");

	for( int i = 0; i < TEXT_MAX; i++ ){
		//	とりあえず初期Ｘ座標を画面の真ん中にします
		pos_offset[i] = GetDrawStringWidth(sample_text[i], -1, 0);

		pos[i].x = SCREEN_W / 2 - pos_offset[i] / 2;
		//	Ｙ座標は 300 から 30 ずつずらしています
		pos[i].y = 300.0f + 30.0f * i;
		text_size[i].x = GetDrawStringWidth(sample_text[i], -1, 0);
		text_size[i].y = GetFontSize();
	}
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	マウス座標を取得
	Float2 mouse;

	mouse.x = GetMouseX();
	mouse.y = GetMouseY();

	for (int i = 0;i<TEXT_MAX;i++)
	{
		text_color[i] = GetColor(255, 255, 255);

	if (CheckPointBoxHit(mouse,pos[i],text_size[i] ) )
	{
		text_color[i] = GetColor(255,255,0);
	}

	}

}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
int text_flicker = 255;
int text_flickerMode = 0;

void GameRender()
{
	//	画面の真ん中に基準の線の描画
	DrawLine( SCREEN_W / 2, 0, SCREEN_W / 2, SCREEN_H, GetColor( 255, 255, 255 ) );

	//	メニュー項目用の文字列を描画
	for( int i = 0; i < TEXT_MAX; i++ ){
		DrawStringF( pos[i].x +2, pos[i].y, sample_text[i], GetColor(0,0,0));
		DrawStringF( pos[i].x, pos[i].y, sample_text[i], text_color[i]);
		//DrawCircle(pos[i].x, pos[i].y,25,1,1);
	}

	//	「マウスで選択」文字列を半透明で描画
	switch (text_flickerMode)
	{
	case 1: 
		text_flicker+=5;
		if (text_flicker >= 255)
		{
			text_flickerMode = 0;
		}
		break;
	default:
		text_flicker-= 5;
		if (text_flicker <= 0)
		{
		text_flickerMode = 1;
		}
		break;
	}


	SetDrawBlendMode( DX_BLENDMODE_ALPHA, text_flicker );
	DrawString( 100+2, 400, "マウスで選択", GetColor( 0, 0, 0 ) );
	DrawString( 100, 400, "マウスで選択", GetColor( 255, 255, 255 ) );
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );

	DrawString( 16, 16, "sample_tex を中央表示で", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "→　マウスがある文字列の色を変更", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "「マウスで選択」文字列を透明度を変更して点滅", GetColor( 255, 255, 255 ) );
	DrawString( 16, 64, "それぞれの文字列に影をつけてみる", GetColor( 255, 255, 255 ) );

}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
}

#include "Main.h"
#include "Game.h"
#include "Float2.h"
#include "Hit.h"

int count;
int defaultfontsize = 0;
const char* defaultfontname = nullptr;
const char* newtext = "DrawStringで文字列描画 hahaha...λ";
//const char* newtext = { "DrawStringで文字列描画", };

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	count = 0;
	defaultfontsize = GetFontSize();
	if (defaultfontname == nullptr)
	{
	defaultfontname = GetFontName();
	}
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	GetStringLength(newtext);

	

	if( PushHitKey( KEY_INPUT_F1 ) )
	{
		SetFontSize(defaultfontsize);
	}
	if( PushHitKey( KEY_INPUT_F2 ) )
	{
		SetFontSize(25);
	}
	if( PushHitKey( KEY_INPUT_F3 ) )
	{
		//ChangeFont(defaultfontname);
		ChangeFont("ＭＳ ゴシック");
	}
	if( PushHitKey( KEY_INPUT_F4 ) )
	{
		//ChangeFontType(3);
		//ChangeFont("ＭＳ 明朝");
		ChangeFont("UD デジタル 教科書体 NK-B");
	}
	if( PushHitKey( KEY_INPUT_F5 ) )
	{
		ChangeFontType(2);
	}
	if( PushHitKey( KEY_INPUT_F6 ) )
	{
		ChangeFontType(3);
	}
	if( PushHitKey( KEY_INPUT_F6 ) )
	{
		//SetDefaultFontState(newtext,25,1,1);
	}

	count++;
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	DrawString( 20,  20, "文字列表示いろいろ", GetColor( 255, 255, 255 ) );

	DrawString( 20, 100, "Ｆ１キー：いつもの大きさ", GetColor( 255, 255, 255 ) );
	DrawString( 20, 150, "Ｆ２キー：サイズを大きく変更", GetColor( 255, 255, 255 ) );

	DrawString( 20, 200, "Ｆ３キー：いつものフォント", GetColor( 255, 255, 255 ) );
	DrawString( 20, 250, "Ｆ４キー：別のフォントに変更 ADASDASD", GetColor( 255, 255, 255 ) );

	DrawFormatString( 20, 300, GetColor( 255, 255, 255 ), "COUNT:%d", count );

	//int stringwidth = GetDrawStringWidth(newtext, strlen("DrawStringで文字列描画 hahaha...λ"), 0);
	int stringwidth = GetDrawStringWidth(newtext, strlen(newtext), 0);
	//or 
	//int stringwidth = GetDrawStringWidth(newtext, -1, 0);

	DrawFormatString( 20, 320, GetColor( 255, 255, 255 ), "Stringlength (amount of moji) :%d", GetStringLength(newtext));
	DrawFormatString( 20, 340, GetColor( 255, 255, 255 ), "Stringwidth (size length of moji) :%d", stringwidth);

	DrawString( 160, 360, newtext ,GetColor( 255, 255, 0 ));
	DrawLine(160,360+GetFontSize(), 160 + stringwidth, 360 + GetFontSize(), GetColor(255, 255, 0));
	//DrawFormatStringToHandle(160,380,GetColor(255,255,0),GetDefaultFontHandle(),"%s%s", newtext, defaultfontname); //combining two strings
	DrawString( 160, 400, defaultfontname ,GetColor( 255, 255, 0 ));
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
}

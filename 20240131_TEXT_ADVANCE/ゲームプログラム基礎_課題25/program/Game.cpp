#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Hit.h"

//	基準の文字列
const char *base_text = {
	"文字は自動で増えます。スペースキーを押している時は早くなります。",
};

//	１：描画用の文字列入れ
char draw_text[256]; //storage

//	何文字目の文字列を入れるのかを数える用の変数
int draw_count;

//	基準の文字列の長さを入れておく用の変数
int base_length;

int autoTextAdvanceTimer;


//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	描画用の文字列の初期化
	//	とりあえず全部に０を入れときます
	for( int i = 0; i < 256; i++ ){
		draw_text[i] = 0;
	}
	//	０文字目から開始
	draw_count = 0;
	//	基準の文字列の長さを取得
	base_length = (int)strlen( base_text );
}

void DisplayLetter()
{
	//	２：描画用文字列入れに１文字入れる（まだ最後まで行っていない時）
	if (draw_count < base_length) {

		//	全角文字の場合は同じ処理を２回おこなう
		//	そのために今の場所の文字列が全角の１個目かどうか調べる
		if (IsDBCSLeadByte(base_text[draw_count])) {
			//	全角文字だったらこの処理をする
			draw_text[draw_count] = base_text[draw_count];
			draw_count++;
		}

		//	base_text の draw_count 番目の値を draw_text に入れる
		draw_text[draw_count] = base_text[draw_count];
		//	次の場所に進める
		draw_count++;
	}
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
		autoTextAdvanceTimer++;
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		if (autoTextAdvanceTimer % 3 == 0) { DisplayLetter(); }
	}
	else
	{
		if (autoTextAdvanceTimer % 10 == 0) { DisplayLetter(); }
	}

	//	右キーを押したとき
	//	（現状は右キーで１文字増やしていますが自動で増えますのでこの判定は変わります）
	if( PushHitKey( KEY_INPUT_RIGHT ) ){

		DisplayLetter();
	}

	//	左キーを押したとき
	if( PushHitKey( KEY_INPUT_LEFT ) ){
		//	最初から文字列の描画をします
		draw_count = 0;
		//	描画用文字列入れも全部０にします
		for( int i = 0; i < 256; i++ ){
			draw_text[i] = 0;
		}
	}
}

//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	clsDx();

	//	基準の文字列をそのまま描画
	DrawString( 100, 100, base_text, GetColor( 255, 255, 0 ) );

	//	フォントの高さ
	int h = GetFontSize();
	//	基準の文字列を描画したときの長さ
	int base_w = GetDrawStringWidth( base_text, -1 );
	//	基準の文字列の下に線を引く
	DrawLine( 100, 100 + h, 100 + base_w, 100 + h, GetColor( 255, 255, 0 ) );


	//	１文字ずつの方
	//	３：描画用文字列入れの方の文字列の描画
	//	水色の文字列の描画
	DrawString( 100, 200, draw_text, GetColor( 0, 255, 255 ) ); // BLUE
	//	基準の文字列を描画したときの長さ
	base_w = GetDrawStringWidth(base_text, draw_count);
	//	基準の文字列の下に線を引く
	DrawLine(100, 200 + h, 100 + base_w, 200 + h, GetColor(0, 255, 255));

	DrawString( 20, 20, "メッセージの描画（自動で文字を増やしていきます）", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "スペースキー：増やすスピードを速く", GetColor( 255, 255, 255 ) );

	DrawString( 100, 180, "文字列の長さに合わせて下線を引く", GetColor( 255, 255, 255 ) );
	DrawString( 100, 280, "文字列が右から左に来るように", GetColor( 255, 255, 255 ) );

	//GREEN
	//	基準の文字列を描画したときの長さ
	base_w = GetDrawStringWidth(base_text, -1); //get the full provided sentence
	int draw_w = GetDrawStringWidth(draw_text, -1); //get the current storage instead of the full provided sentence.
	//printfDx("string width %d ", base_w2);
	//	緑色の文字列の描画（現状は水色の文字列と同じ処理をしています）
	
	DrawString( 
		100+base_w -(draw_w),
		300, draw_text, GetColor(0, 255, 0)
	); //GREEN

	//	目安の縦線（基準の文字列の最後から縦に線の描画）
	DrawLine( 100 + base_w, 0, 100 + base_w, SCREEN_H, GetColor( 150, 150, 150 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
}

#include "Main.h"
#include "Game.h"

//	ブロック画像用の変数（ block0.bmp ～ block3.bmp の４つ使うので）
int block_image[4];

//	画面上の各ブロックを置く場所が何番なのかを入れる用の変数
int stage[5][8];

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	ブロック画像の読み込み
	block_image[0] = LoadGraph( "data/block0.bmp" );	//	０：消えたところの画像
	block_image[1] = LoadGraph( "data/block1.bmp" );	//	１～３：最初にランダムに並べる
	block_image[2] = LoadGraph( "data/block2.bmp" );
	block_image[3] = LoadGraph( "data/block3.bmp" );

	//	配列のすべての場所にランダムで１～３の数値を入れていきます

	for( int h = 0; h < 5; h++ ){
		//	その縦１個１個につき、横ループを８回
		for( int w = 0; w < 8; w++ ){
			//	その [h][w] 番目のところにランダムな値を設定します
			stage[h][w] = GetRand( 2 ) + 1;
		}
	}
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
int mouse_x = 0;
int mouse_y = 0;

void Looper();

int click_w = 0;
int click_h = 0;

void GameUpdate()
{
	
	//	マウスをクリックしたらその場所を消す（０番画像にする）
	if( PushMouseInput() ){
		//	マウス座標を取得（画面座標）
		mouse_x = GetMouseX();
		mouse_y = GetMouseY();
		//	このマウス座標が２次元配列的に何番目のところになるのかを取得
		click_w = mouse_x / 100;
		click_h = mouse_y / 100;
		//	そこのステージ番号の値を０にする（０番画像を使うので

		if (stage[click_h][click_w] == 0)
		{
			return;
		}

		Looper();
		

		int check_num = stage[click_h][click_w];
		int count = 0;

		for (int w = 0;w<8;w++)
		{
			if (check_num == stage[click_h][w] )
			{
				count++;
			}
		}
				
		if (count == 8)
		{
			for(int w = 0; w<8; w++)
			{
				stage[click_h][w] = 0;
			}
		}
		
		
	}

	
	/*if ((stage[0][0] & stage[0][1] & stage[0][2] & stage[0][3] & stage[0][4] & stage[0][5] & stage[0][6] & stage[0][7]) == stage[0][0])
	{
		stage[0][0] = 0;
		stage[0][1] = 0;
		stage[0][2] = 0;
		stage[0][3] = 0;
		stage[0][4] = 0;
		stage[0][5] = 0;
		stage[0][6] = 0;
		stage[0][7] = 0;
	}*/
	

	
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	ブロックの描画
	//	stage[5][8] に割り振られた番号を全部見ていってその番号の画像を描画
	for( int h = 0; h < 5; h++ ){
		for( int w = 0; w < 8; w++ ){
			//	ステージ変数の底の場所の番号を取得（画像番号）
			int num = stage[h][w];
			//	その番号の画像を画面のどこに表示するかの座標
			int x = w * 100;
			int y = h * 100;
			//	その番号の画像を描画
			DrawGraph( x, y, block_image[num], TRUE );
		}
	}

	DrawString( 16, 16, "クリックで四角の色を変更する", GetColor( 255, 255, 0 ) );
	DrawString( 16, 32, "　[1:赤] → [2:緑] → [3:青] → [1:赤] → [2:緑] → [3:青] → ・・・）", GetColor( 255, 255, 0 ) );
	DrawString( 16, 48, "横一行同じ色だったらその行は全部消える（０：灰色）", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	for( int i = 0; i < 4; i++ ){
		DeleteGraph( block_image[i] );
	}
}

void Looper()
{
	if (stage[click_h][click_w] != 3)
	{
		stage[click_h][click_w]++;

	}
	else
	{
		stage[click_h][click_w] = 1;
	}
}
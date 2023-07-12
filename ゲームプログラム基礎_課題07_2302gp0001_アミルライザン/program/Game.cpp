#include "Main.h"
#include "Game.h"

//	横に並べる数（画面全部に並べる場合は１６個：今回は少し小さくしています）
#define MAP_W		10
//	縦に並べる数（画面全部に並べる場合は９個：今回は少し小さくしています）
#define	MAP_H		 7
//	ブロック１個の大きさ
#define BLOCK_SIZE	50

//	スクロールスピード（一応マップの移動スピードで用意しています）
#define SCROLL_SPEED	3

//	それぞれのポイントの番号を入れる用の２次元配列
//	マップ０
int map0[MAP_H][MAP_W] =
{
	{ 4,4,4,4,4,4,4,4,4,4 },
	{ 4,0,2,2,0,0,0,0,0,4 },
	{ 4,2,0,0,2,0,0,0,0,4 },
	{ 4,2,0,0,2,0,3,3,3,4 },
	{ 4,2,0,0,2,0,3,3,3,4 },
	{ 4,0,2,2,0,0,3,3,3,4 },
	{ 4,4,4,4,4,4,4,4,4,4 },
};
//	マップ１
int map1[MAP_H][MAP_W] =
{
	{ 2,1,2,2,2,2,2,2,2,2 },
	{ 2,1,4,4,2,1,1,1,1,2 },
	{ 2,4,4,4,2,2,2,2,2,2 },
	{ 2,2,4,4,2,1,2,1,2,1 },
	{ 2,1,4,4,2,1,2,1,2,1 },
	{ 2,4,4,4,4,1,2,1,2,1 },
	{ 2,2,2,2,2,2,2,1,2,2 },
};

//	マップで使う画像用の変数（この１個の画像から必要な部分を使って描画）
int map_image;

int x;
int y;
int offset_x;
int offset_y;

void GameInit()
{
	//	画像の読み込み（今回マップで使うのはこれ１枚だけ）
	map_image = LoadGraph( "data/map.bmp" );

}

int z = 0;

void GameUpdate()
{
	//	十字キーでマップの移動（マップの基準となる座標変数の値を更新）
	if( CheckHitKey( KEY_INPUT_RIGHT ) && x < SCREEN_W - 50 )
	{
		offset_x++;

	}
	if( CheckHitKey( KEY_INPUT_LEFT )&& offset_x > 0)
	{
		offset_x--;
	}
	if( CheckHitKey( KEY_INPUT_DOWN ) && y < SCREEN_H -50)
	{
		offset_y++;
	}
	if( CheckHitKey( KEY_INPUT_UP )&& offset_y > 0)
	{
		offset_y--;
	}

	if (PushHitKey(KEY_INPUT_SPACE))
	{
		if (z == 0)
		{
			z++;
		}
		else
		{
			z--;
		}
		
	}
	
}



void GameRender()
{
	//	マップ番号に合わせた画像の中の開始位置をデータとして用意
	int image_xy_data[5][2] = 
	{
		{   0,  0 },	//	０番の場所
		{ 100,  0 },	//	１番の場所
		{ 150,  0 },	//	２番
		{ 100, 50 },	//	３番
		{   0, 50 },	//	４番
	};


	if (z == 0)
	{
		for (int h = 0; h < MAP_H; h++) {
			for (int w = 0; w < MAP_W; w++) {
				//	その場所のマップの番号を取得（とりあえず map0 を使っています）
				int num = map0[h][w];
				//	画面のどこに描画するのかの座標（２次元配列の場所からブロックサイズ分ずらしたところ）
				x = (w * BLOCK_SIZE) + offset_x;
				y = (h * BLOCK_SIZE) + offset_y;
				//	その番号の絵は map.bmp のどこから始まるか
				int image_x = image_xy_data[num][0];
				int image_y = image_xy_data[num][1];
				//	画面の座標（ x y ）の場所に画像（ map_image ）のここの場所（ image_x image_y ）から描画
				DrawRectGraph(x, y, image_x, image_y, BLOCK_SIZE, BLOCK_SIZE, map_image, TRUE);
			}
		}
	}
	else if (z == 1)
	{
		for (int h = 0; h < MAP_H; h++) {
			for (int w = 0; w < MAP_W; w++) {
				//	その場所のマップの番号を取得（とりあえず map0 を使っています）
				int num = map1[h][w];
				//	画面のどこに描画するのかの座標（２次元配列の場所からブロックサイズ分ずらしたところ）
				x = (w * BLOCK_SIZE) + offset_x;
				y = (h * BLOCK_SIZE) + offset_y;
				//	その番号の絵は map.bmp のどこから始まるか
				int image_x = image_xy_data[num][0];
				int image_y = image_xy_data[num][1];
				//	画面の座標（ x y ）の場所に画像（ map_image ）のここの場所（ image_x image_y ）から描画
				DrawRectGraph(x, y, image_x, image_y, BLOCK_SIZE, BLOCK_SIZE, map_image, TRUE);
			}
		}
	}
	//	マップの描画
	

	DrawString( 20, 20, "マップの大きさを変えてます（使用画像は map.bmp のままです）", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "十字キー：マップ移動（画面の外に行かないように）", GetColor( 255, 255, 0 ) );
	DrawString( 20, 60, "スペース：マップの切り替え", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( map_image );
}

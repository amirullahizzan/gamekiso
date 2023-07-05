#include "Main.h"
#include "Game.h"

#define BLOCK_SIZE	50
#define MAP_W		16
#define	MAP_H		 9



//2 次元. to load the images
int map[MAP_H][MAP_W] =
{
	{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,1,1,1,0,1,1,1,0,2 },
	{ 2,0,0,0,0,0,0,1,0,0,0,0,0,1,0,2 },
	{ 2,0,0,0,0,0,0,1,0,0,0,0,0,1,0,2 },
	{ 2,0,0,0,0,0,0,1,1,1,1,1,1,1,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
};

int block_image[3];

int player_image;

struct Player
{
public:
	int h = 2;
	int w = 2;
	
	void DrawPlayer()
	{
		int x = w * BLOCK_SIZE;
		int y = h * BLOCK_SIZE;
		DrawGraph(x, y, player_image, 1);
	}
};

Player player;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//block_image[0] = LoadGraph( "data/block0.bmp" );
	//block_image[1] = LoadGraph( "data/block1.bmp" );
	//block_image[2] = LoadGraph( "data/block2.bmp" );
	for (int i = 0; i < 3; i++)
	{
		char filename[100];
		sprintf(filename, "data/block%d.bmp", i);
		block_image[i] = LoadGraph(filename);
	}

	player_image = LoadGraph( "data/player.bmp" );

	//test


}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	if( PushHitKey( KEY_INPUT_RIGHT ) )
	{
		if (player.w < MAP_W-1)
		{
		player.w++;
		}
	}
	if( PushHitKey( KEY_INPUT_LEFT ) )
	{
		if (player.w+1 > 0+1)
		{
			player.w--;
		}

	}
	if( PushHitKey( KEY_INPUT_DOWN ) ){
		if (player.h < MAP_H - 1)
		{
			player.h++;
		}

	}
	if( PushHitKey( KEY_INPUT_UP ) ){
		if (player.h + 1 > 0 + 1)
		{
			player.h--;
		}
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------


void GameRender()
{
	for( int h = 0; h < MAP_H; h++ ){
		for( int w = 0; w < MAP_W; w++ ){
			int num = map[h][w];

			int x = w * BLOCK_SIZE;
			int y = h * BLOCK_SIZE;
			DrawGraph(x,y,block_image[num], 1);
		}
	}

	player.DrawPlayer();

	DrawString( 20, 20, "十字キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( block_image[0] );
	DeleteGraph( block_image[1] );
	DeleteGraph( block_image[2] );

	DeleteGraph( player_image );
}


#include "Main.h"
#include "Game.h"

int block_image[4];
int blocks[5][8]; //y,x. double array indicator

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	block_image[0] = LoadGraph( "data/block0.bmp" );
	block_image[1] = LoadGraph( "data/block1.bmp" );
	block_image[2] = LoadGraph( "data/block2.bmp" );
	block_image[3] = LoadGraph( "data/block3.bmp" );

	blocks[1][5] = 3; // put block_image 3 inside blocks y1x5

	for (int h = 0;h<5;h++)
	{
		for (int w = 0; w<8;w++)
		{
			blocks[h][w] = GetRand(2)+1;
		}
	}
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
int mouse_x = 0;
int mouse_y = 0;

void GameUpdate()
{

	if (PushMouseInput(0x0001) == 1)
	{
		GetMousePoint(&mouse_x, &mouse_y);
		
		int click_w = mouse_x / 100;
		int click_h = mouse_y / 100;
		
		blocks[click_h][click_w] = 0;
	}

}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------

int grey_x = 0;
int grey_y = 0;
int gap = 100;

void DrawGreyBackground();
void DrawGrid();


void GameRender()
{

	DrawString( 16, 16, "クリックで四角を消す", GetColor( 255, 255, 255 ) );
	
	//DrawGreyBackground();
	//DrawGraph();

	for (int h = 0; h < 5; h++)
	{
		for (int w = 0; w < 8; w++)
		{
			int num = blocks[h][w];

			int x = w * 100;
			int y = h * 100;

			DrawGraph( x,y,block_image[num], 0);
		}
	}

	DrawGrid();

	
}


void GameExit()
{
	for( int i = 0; i < 4; i++ ){
		DeleteGraph( block_image[i] );
	}
}

void DrawGreyBackground()
{
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			DrawGraph(grey_x + (gap * i), grey_y, block_image[0], 0);
		}
		grey_y = (100 * j);
	}
}

void DrawGrid()
{
	{
		for (int j = 0; j < 5; j++)
		{
			for (int i = 0; i < 9; i++)
			{
				DrawLine(100 * i, 0, 100 * i, SCREEN_H, GetColor(50, 50, 50), 4);
				DrawLine(0, 100 * i, SCREEN_W, 100 * i, GetColor(50, 50, 50), 4);
			}
			grey_y = (100 * j);
		}
	}
}

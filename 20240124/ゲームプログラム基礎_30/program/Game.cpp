#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Hit.h"

#define MAP_W	16
#define MAP_H	9
int map[MAP_H][MAP_W];

#define PANEL_SIZE	50
#define PANEL_KIND	4 //Variety
int panel_image[PANEL_KIND];

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	
	panel_image[0] = LoadGraph( "data/panel0.bmp" );
	panel_image[1] = LoadGraph( "data/panel1.bmp" );
	panel_image[2] = LoadGraph( "data/panel2.bmp" );
	panel_image[3] = LoadGraph( "data/panel3.bmp" );

	for( int h = 0; h < MAP_H; h++ ){
		for( int w = 0; w < MAP_W; w++ ){
			map[h][w] = 0;
		}
	}

	FILE* fp = fopen("data/map.txt", "r");

	if (fp)
	{
		char text[256];


		for (int h = 0; h < MAP_H; h++)
		{
			//1行取得
			fgets(text,256,fp);

			//1行取得できましたので、[,]で分けています
			char* pstr;
			pstr = strtok(text,",");
			for (int w = 0; w < MAP_W; w++)
			{
				//とってきた1文字を数値にする(文字列の「2」をintにする)
				int num = atoi(pstr);
				map[h][w] = num;

				//次の「、」の横の文字の所に進める
				pstr = strtok(NULL,",");
			}
		}


		//
		fclose(fp);
	}

}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	for( int h = 0; h < MAP_H; h++ ){
		for( int w = 0; w < MAP_W; w++ ){

			int x = w * PANEL_SIZE;
			int y = h * PANEL_SIZE;
			int num = map[h][w];

			DrawGraph( x, y, panel_image[num], TRUE );
		}
	}

	DrawString( 16, 16, "読み込んだテキストの番号に合わせて画像を並べる", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	for( int i = 0; i < PANEL_KIND; i++ ){
		DeleteGraph( panel_image[i] );
	}
}

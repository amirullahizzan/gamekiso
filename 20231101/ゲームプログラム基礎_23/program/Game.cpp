#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Float2.h"
#include "Random.h"

int noise_image;
float noise_rota = 0.0f;
bool isdisplaynoise = false;
bool isnoise_flip = false;

#define CIRCLE_MAX	30

#define RADIUS		5.0f

Float2 pos[CIRCLE_MAX];

float speed[CIRCLE_MAX];

int red[CIRCLE_MAX];
int green[CIRCLE_MAX];
int blue[CIRCLE_MAX];

Float2 noise_pos = {0,0};

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	noise_image = LoadGraph( "data/noise.bmp" );

	for( int i = 0; i < CIRCLE_MAX; i++ ){
		pos[i].x = GetRandomF(SCREEN_W);
		//pos[i].y = GetRand( SCREEN_H );
		pos[i].y = GetRandomF(150.0f, 350.0f);
		//pos[i].y =  (float)rand() / RAND_MAX * 255;

		speed[i] = GetRandomF(1.0f,3.0f);

		//red[i] = GetRand( 255 );
		//green[i] = GetRand( 255 );
		//blue[i] = GetRand( 255 );

		red[i] = GetRandomI(128,255);
		green[i] = GetRandomI(128, 255);
		blue[i] = GetRandomI(128, 255);
	}
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	for( int i = 0; i < CIRCLE_MAX; i++ ){
		pos[i].x -= speed[i];
		if( pos[i].x < 0.0f ){
			pos[i].x = SCREEN_W;
		}
	}

	if( CheckHitKey( KEY_INPUT_SPACE ) )
	{
		isdisplaynoise = true;
	}
	else
	{
		isdisplaynoise = false;
	}

	if (isdisplaynoise)
	{
		static int frame = 0;
		frame++;
		if (frame % 1 == 0 && frame != 0)
		{
			//noise_rota = GetRandomF(3.13f);
			constexpr float widthgap = SCREEN_W - 1000;
			constexpr float heightgap = SCREEN_H - 1000;
			noise_pos.x = GetRandomF(widthgap , 0);
			noise_pos.y = GetRandomF(heightgap, 0);
		}
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{

	DrawLine( 0, 150, SCREEN_W, 150, GetColor( 255, 255, 255 ) );
	DrawLine( 0, 350, SCREEN_W, 350, GetColor( 255, 255, 255 ) );

	for( int i = 0; i < CIRCLE_MAX; i++ ){
		DrawCircleAA( pos[i].x, pos[i].y, RADIUS, 100, GetColor( red[i], green[i], blue[i] ) );
	}

	if (isdisplaynoise)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,100);
		//DrawRotaGraph(noise_pos.x, noise_pos.y,1,noise_rota,noise_image,1,0, 0);
		DrawGraphF(noise_pos.x, noise_pos.y,noise_image,1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	DrawString( 16, 16, "色々とランダム設定", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "円の色　　　　　：128   ～ 255", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "円のＹ座標　　　：150.0 ～ 350.0", GetColor( 255, 255, 255 ) );
	DrawString( 16, 64, "円の移動スピード：  1.0 ～   3.0", GetColor( 255, 255, 255 ) );
	DrawString( 16, 80, "スペースキー　　：ノイズのような表現（ノイズ画像「 noise.bmp 」の描画座標をランダムに）", GetColor( 255, 255, 255 ) );

	clsDx();
	printfDx("Rota : %f", noise_rota);
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( noise_image );
}

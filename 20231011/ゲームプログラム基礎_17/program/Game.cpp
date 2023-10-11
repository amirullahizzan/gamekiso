#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Float2.h"

#define PLAYER_NORMAL_SPEED	1.0f
#define PLAYER_FAST_SPEED	20.0f

#define BUTTON_SIZE		100.0f

int button_image;
int player_image;

float player_rot;
float player_speed;

Float2 mousepoint = {0,0};
Float2 button1_pos = {0,0 };
Float2 button1_size = {0,0 };
Float2 button2_pos = {0,0 };
Float2 button2_size = {0,0 };

Float2 player_pos;
Float2 player_size;

	
	struct Button
	{
		//Button(Float2 thispos)
		//{
		//	//exit(0);
		//}

		bool MouseHit(Float2 box_pos, Float2 box_size)
		{
			return CheckPointBoxHit(mousepoint, box_pos, box_size);
		}

	};

	Button button1;
	Button button2;



void GameInit()
{
	button_image = LoadGraph( "data/button.bmp" );
	player_image = LoadGraph( "data/player.bmp" );


	player_pos = { 50,50 };
	button1_pos = { 200,300};
	button2_pos = { 500,300 };
	button1_size = { BUTTON_SIZE,BUTTON_SIZE };
	button2_size = { BUTTON_SIZE,BUTTON_SIZE };

}


void GameUpdate()
{
mousepoint.x = GetMouseX();
mousepoint.y = GetMouseY();

	if( PushMouseInput() )
	{
		if (button1.MouseHit(button1_pos, button1_size))
		{
			player_rot = GetRand(360);
		}
	
		
	}
	player_speed = PLAYER_NORMAL_SPEED;

	if( CheckMouseInput() )
	{
		if (button2.MouseHit(button2_pos, button2_size))
		{
			player_speed = PLAYER_FAST_SPEED;
		}
	}
		player_pos.x += player_speed * GetLength_RotSotte(TO_RADIAN(player_rot));
		player_pos.y += player_speed * GetLength_RotMukai(TO_RADIAN(player_rot));

		if (player_pos.x < 0.0f)  player_pos.x = SCREEN_W ;
		if (player_pos.x > SCREEN_W) player_pos.x = 0.0f ;
		if (player_pos.y < 0.0f)  player_pos.y = SCREEN_H ;
		if (player_pos.y > SCREEN_H) player_pos.y = 0.0f ;
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	clsDx();
	DrawRotaGraphF(player_pos.x, player_pos.y,1.0f, TO_RADIAN(player_rot),player_image,1,0,0);

	DrawGraphF(button1_pos.x, button1_pos.y, button_image,1);
	DrawGraphF(button2_pos.x, button2_pos.y, button_image,1);
	printfDx("%f, %f, ", mousepoint.x,mousepoint.y);
	//printfDx("%f, %f, ", button1_pos.x, button1_pos.y);

	DrawString( 16, 16, "左の四角をクリック　　：プレイヤー向きをランダムに変更", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "右の四角を押している間：プレイヤーのスピードアップ", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( button_image );
	DeleteGraph( player_image );
}

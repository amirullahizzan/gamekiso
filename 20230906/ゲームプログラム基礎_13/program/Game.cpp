#include "Main.h"
#include "Game.h"

#define PLAYER_SPEED	3.0f
#define RECORDMAX 999

int player_image;
float player_x;
float player_y;

int option_image;
float option_x;
float option_y;

float option_x2;
float option_y2;

float option_x3;
float option_y3;

int frame_count = 0;
int record_x[999] = {};
int record_y[999] = {};

int option_delay = 15;

struct Pos2
{
	int x_ = 100.0f;
	int y_ = 200.0f;
};
Pos2 option1;
Pos2 option2;
Pos2 option3;

void FollowerAI(Pos2& pos, int followernumber)
{
	if (frame_count > option_delay*followernumber)
	{
		pos.x_ = record_x[frame_count - option_delay*followernumber];
		pos.y_ = record_y[frame_count - option_delay * followernumber];
	}
}

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	player_image	= LoadGraph( "data/player.bmp" );
	option_image	= LoadGraph( "data/option.bmp" );

	player_x = 100.0f;
	player_y = 200.0f;

	option_x = 100.0f;
	option_y = 200.0f;
}
bool isMoving = false;

void FollowerAIHandler()
{
	frame_count++;
	FollowerAI(option1, 1);
	FollowerAI(option2, 2);
	FollowerAI(option3, 3);
	isMoving = false;
}


void GameUpdate()
{
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		player_x += PLAYER_SPEED;
		isMoving = true;
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		player_x -= PLAYER_SPEED;
		isMoving = true;
	}
	if( CheckHitKey( KEY_INPUT_DOWN ) ){
		player_y += PLAYER_SPEED;
		isMoving = true;
	}
	if( CheckHitKey( KEY_INPUT_UP ) ){
		player_y -= PLAYER_SPEED;
		isMoving = true;
	}

	record_x[frame_count] = player_x;
	record_y[frame_count] = player_y;

	if (isMoving)
	{
		FollowerAIHandler();
	}

	/*for (int i = 999-1; i>0 ;i--)
	{
		record_x[i] = record_x[i-1];
		record_y[i] = record_y[i-1];
	}

	record_x[0] = player_x;
	record_y[0] = player_y;

	option_x = record_x[20];
	option_y = record_y[20];*/
}

void DrawOption(const Pos2& pos)
{
	DrawRotaGraphF(pos.x_, pos.y_, 1.0f, TO_RADIAN(0.0f), option_image, TRUE);
}

void GameRender()
{
	/*DrawRotaGraphF(option_x, option_y, 1.0f, TO_RADIAN(0.0f), option_image, TRUE);*/


	DrawOption(option1);
	DrawOption(option2);
	DrawOption(option3);
	//Rotagraph displays from center
	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( 0.0f ), player_image, TRUE );


	DrawString( 20, 20, "十字キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "オプションがプレイヤーについてくる", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( option_image );
}

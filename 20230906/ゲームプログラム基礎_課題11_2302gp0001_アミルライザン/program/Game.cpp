#include "Main.h"
#include "Game.h"

//	プレイヤーの移動スピード
#define PLAYER_SPEED	3.0f

//	プレイヤー用の変数
int player_image;	//	画像
float player_x;		//	Ｘ座標
float player_y;		//	Ｙ座標

//	一応オプションの数用の定数
#define OPTION_MAX		4

//	オプション用の変数
int option_image;	//	画像
float option_x;		//	Ｘ座標
float option_y;		//	Ｙ座標

//	１：座標を記録する場所を用意
//	記録できる数
#define RECORD_MAX	100
//	プレイヤーの座標を記録していく用の変数
float record_x[RECORD_MAX];
float record_y[RECORD_MAX];


enum
{
	Right = 0,
	Down = 90,
	Left = 180,
	Up = 270
};

int record_facing[RECORD_MAX] = {};
int player_facing = 0;
int option_facing = 0;

struct Option
{
	int x_ = 0;
	int y_ = 0;
	int facing_ = 0;
	int delay = 20;

	static int num_instances;

	Option()
	{
		num_instances++;
	}

	void FollowAI(int delaymult)
	{
		//	３：オプションは記録した値を座標に設定する
		//	２０フレーム前のプレイヤー座標をオプションの座標にしようと思います
		x_ = record_x[delay * delaymult];
		y_ = record_y[delay * delaymult ];
		facing_ = record_facing[15 * delaymult];
	}

	void DrawOption()
	{
		DrawRotaGraphF(x_, y_, 1.0f, TO_RADIAN(facing_), option_image, TRUE);
	}
};
int Option::num_instances = 0;

Option option1;
Option option2;
Option option3;
Option option4;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	それぞれの画像の読み込み
	player_image	= LoadGraph( "data/player.bmp" );
	option_image	= LoadGraph( "data/option.bmp" );
	//	プレイヤーの初期座標設定
	player_x = 100.0f;
	player_y = 200.0f;
	//	オプションの初期座標（後々プレイヤーの座標についていくのでとりあえず）
	option_x = 100.0f;
	option_y = 200.0f;

	//	記録領域の初期設定
	for( int i = 0; i < RECORD_MAX; i++ ){
		//	全部にプレイヤー座標を入れていきます
		record_x[i] = player_x;
		record_y[i] = player_y;
	}
}




void GameUpdate()
{

	//	十字キーでプレイヤー座標の更新
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		player_x += PLAYER_SPEED;
		player_facing = Right;
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		player_x -= PLAYER_SPEED;
		player_facing = Left;
	}
	if( CheckHitKey( KEY_INPUT_DOWN ) ){
		player_y += PLAYER_SPEED;
		player_facing = Down;
	}
	if( CheckHitKey( KEY_INPUT_UP ) ){
		player_y -= PLAYER_SPEED;
		player_facing = Up;
	}

	//	２：プレイヤー座標の記録
	//	２－１：プレイヤー座標を配列の先頭に入れる前に今記録されている配列の中身を１個ずらします
	for( int i = RECORD_MAX - 1; i > 0; i-- ){
		record_x[i] = record_x[i - 1];
		record_y[i] = record_y[i - 1];
		record_facing[i] = record_facing[i-1];
	}

	//	２－２：配列の先頭に今のプレイヤー座標を入れます
	record_x[0] = player_x;
	record_y[0] = player_y;
	record_facing[0] = player_facing;

	////	３：オプションは記録した値を座標に設定する
	////	２０フレーム前のプレイヤー座標をオプションの座標にしようと思います
	//option_x = record_x[20];
	//option_y = record_y[20];
	//option_facing = record_facing[20];


	option1.FollowAI(1);
	option2.FollowAI(2);
	option3.FollowAI(3);
	option4.FollowAI(4);

}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	オプションの描画
	option1.DrawOption();
	option2.DrawOption();
	option3.DrawOption();
	option4.DrawOption();
	//	プレイヤーの描画
	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( player_facing ), player_image, TRUE );

	DrawString( 20, 20, "十字キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "オプションがプレイヤーについてくる", GetColor( 255, 255, 255 ) );
	DrawString( 20, 60, "→　オプションを複数にしてみる", GetColor( 255, 255, 0 ) );
	DrawString( 20, 80, "number of option spawned : ", GetColor( 255, 255, 0 ) );
	DrawFormatString(20, 80, GetColor(255, 255, 0), "number of option spawned : %d", Option::num_instances);
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( option_image );
}

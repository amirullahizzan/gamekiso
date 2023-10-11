#include "Main.h"
#include "Game.h"
#include "Hit.h"
//	Float2 構造体を使いたいので
#include "Float2.h"

//	プレイヤーの移動スピード（普通の）
#define PLAYER_NORMAL_SPEED	1.0f
//	速いスピード
#define PLAYER_FAST_SPEED	20.0f
//	ボタン画像の大きさ
#define BUTTON_SIZE		100.0f

//	ボタン画像用の変数
int button_image;
//	影画像用の変数
int shadow_image;
//	プレイヤー画像用の変数
int player_image;

bool isPressed = false;
int button_onpush_offset[2];

//	プレイヤー座標
Float2 player_pos;
//	プレイヤーの向き（度）
float player_rot;
//	プレイヤースピード
float player_speed;

//	ボタンのサイズ
Float2 button_size;
//	向き変更ボタンの座標
Float2 rot_button_pos;
//	スピード変更ボタン
Float2 speed_button_pos;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	ボタン画像の読み込み
	button_image = LoadGraph( "data/button.bmp" );
	//	影画像の読み込み
	shadow_image = LoadGraph( "data/shadow.bmp" );
	//	プレイヤー画像の読み込み
	player_image = LoadGraph( "data/player.bmp" );

	//	プレイヤーの初期座標設定
	player_pos.x = 100.0f;		//	player_pos の中にある x に 100.0f を入れます
	player_pos.y = 200.0f;		//	player_pos の中にある y に 200.0f を入れます
	//	向きは０度で開始
	player_rot = 0.0f;
	//	普通のスピードで開始
	player_speed = PLAYER_NORMAL_SPEED;

	//	ボタンサイズの設定
	button_size.x = BUTTON_SIZE;
	button_size.y = BUTTON_SIZE;

	//	向き変更ボタンの座標設定
	rot_button_pos.x = 200.0f;
	rot_button_pos.y = 300.0f;

	//	スピードボタンの座標
	speed_button_pos.x = 500.0f;
	speed_button_pos.y = 300.0f;
}

float player_speedmult = 1;

void GameUpdate()
{
	//	マウス座標の取得
	Float2 mouse;
	mouse.x = GetMouseX();
	mouse.y = GetMouseY();

	//	マウスボタンを押した瞬間（ボタン画像を押したら向きを変えたい）
	if( PushMouseInput() ){
		//	マウス座標が向き変更ボタンの四角の中にあったら（座標も大きさも Float2 なので Float2 で当たり判定する関数を使います）
		if( CheckPointBoxHit( mouse, rot_button_pos, button_size ) ){
			//	プレイヤーの向きをランダムに変更します
			int player_rot_index = GetRand( 3 );
			switch (player_rot_index)
			{
			case 0: player_rot = 0;
				break;
			case 1: player_rot = 90;
				break;
			case 2: player_rot = 180;
				break;
			case 3: player_rot = 270;
				break;
			}
		}
	}

	if (CheckMouseInput())
	{
		if (CheckPointBoxHit(mouse, rot_button_pos, button_size))
		{
			button_onpush_offset[1] = 5;
		}
	}
	else
	{
		button_onpush_offset[1] = 0;
	}


	//	まずはスピードを普通にしておいて
	player_speed = PLAYER_NORMAL_SPEED;

	//	マウスボタンを押しているとき（ボタン画像を押したらスピードを速くしたい）
	if( CheckMouseInput() )
	{
		//	マウス座標がスピードボタンのところにあったら
		if( CheckPointBoxHit( mouse, speed_button_pos, button_size ) ){
			//	スピードを速くする
			isPressed = true;
		}
		else
		{
			isPressed = false;
		}
		
		
	}
	

	if (isPressed)
	{
		if (player_speedmult < PLAYER_FAST_SPEED)
		{
			player_speedmult += 0.2;
		}
		button_onpush_offset[0] = 5;
	}
	else
	{
		button_onpush_offset[0] = 0;
		if (player_speedmult > 0.2)
		{
			player_speedmult -= 0.2;
		}

	}


	//	プレイヤーの座標移動（向いている方向に）（さらに変化するスピードの値を使って）
	player_pos.x += player_speedmult * player_speed * GetLength_RotSotte( TO_RADIAN( player_rot ) );
	player_pos.y += player_speedmult * player_speed * GetLength_RotMukai( TO_RADIAN( player_rot ) );

	//	プレイヤーが画面の端まで行ったら反対から出てくる
	if( player_pos.x < 0.0f )		player_pos.x = SCREEN_W;
	if( player_pos.x > SCREEN_W )	player_pos.x = 0.0f;
	if( player_pos.y < 0.0f )		player_pos.y = SCREEN_H;
	if( player_pos.y > SCREEN_H )	player_pos.y = 0.0f;
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	プレイヤーの座標（ player_pos ）と向き（ player_rot ）を使ってプレイヤー画像（ player_image ）の描画
	DrawRotaGraphF( player_pos.x, player_pos.y, 1.0f, TO_RADIAN( player_rot ), player_image, TRUE );
	//	向き変更ボタン画像の描画
	DrawGraphF(rot_button_pos.x+15 , rot_button_pos.y + 15, shadow_image, TRUE);
	DrawGraphF( rot_button_pos.x+ button_onpush_offset[1], rot_button_pos.y + button_onpush_offset[1], button_image, TRUE );
	//	スピードボタン画像の描画
	DrawGraphF( speed_button_pos.x+15, speed_button_pos.y+ 15, shadow_image, TRUE );
	DrawGraphF( speed_button_pos.x+ button_onpush_offset[0], speed_button_pos.y + button_onpush_offset[0], button_image, TRUE);

	DrawString( 16, 16, "左の四角をクリック　　：プレイヤー向きをランダムに変更", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "→　向く方向を「右」「下」「左」「上」の４つのランダムに", GetColor( 255, 255, 0 ) );
	DrawString( 16, 48, "右の四角を押している間：プレイヤーのスピードアップ", GetColor( 255, 255, 255 ) );
	DrawString( 16, 64, "→　押している間徐々にスピードアップ（押してなかったら徐々にスピードダウン）", GetColor( 255, 255, 0 ) );
	DrawString( 16, 96, "よりボタンらしく見せるために影の描画", GetColor( 255, 255, 0 ) );

	clsDx();
	//printfDx("%d",isPressed);
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( button_image );
	DeleteGraph( shadow_image );
	DeleteGraph( player_image );
}

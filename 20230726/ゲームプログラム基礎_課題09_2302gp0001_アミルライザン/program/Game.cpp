#include "Main.h"
#include "Game.h"

//	ＳＥデータ用の変数
int se_walk;	//	足音
int se_door;	//	ドアを開ける音
int se_rain;	//	雨の音

//	プレイヤー変数
//	プレイヤー画像
int player_image;
int field_image;
int room_image;
//	プレイヤーＸ座標
float player_x;

#define RAIN_AMOUNT 80

int rain_x[RAIN_AMOUNT];
int rain_y[RAIN_AMOUNT];
int rain_speed[RAIN_AMOUNT];
int getRainDuration() { return GetRand(100)+20; }
int rain_duration[RAIN_AMOUNT];

enum SceneEnum
{
	isInRoom = 0, isInField = 1
}; 

//int puddle_x[RAIN_AMOUNT];
//int puddle_y[RAIN_AMOUNT];
//int puddle_rad[RAIN_AMOUNT];
//int puddle_duration[RAIN_AMOUNT];
//
//void DrawPuddle()
//{
//	for (int i = 0; i < RAIN_AMOUNT; i++)
//	{
//		if (rain_duration[i] > getRainDuration())
//		{
//			puddle_x[i] = rain_x[i];
//			puddle_y[i] = rain_y[i];
//			DrawCircle(puddle_x[i], puddle_y[i], puddle_rad[i], GetColor(200, 200, 255), 0, 1);
//			puddle_rad[i]++;
//		}
//		
//	}
//}


void DrawRain()
{
	for (int i = 0; i < RAIN_AMOUNT; i++)
	{
		rain_duration[i]++;
		rain_speed[i] = GetRand(3) + 10;
		rain_x[i] += rain_speed[i];
		rain_y[i] += rain_speed[i];
		DrawLine(rain_x[i], rain_y[i], rain_x[i] + 5, rain_y[i] + 20, GetColor(200, 200, 255), 1);
		if (rain_duration[i] > getRainDuration())
		{
			rain_x[i] = GetRand(SCREEN_W)-200;
			rain_y[i] = GetRand(SCREEN_H / 2)-200;
			rain_duration[i] = 0;
		}
	}
	
}

void InitRain()
{
	for (int i = 0; i < RAIN_AMOUNT; i++)
	{
		rain_speed[i] = GetRand(3)+10;
		rain_x[i] = GetRand(SCREEN_W) - 200;
		rain_y[i] = GetRand(SCREEN_H) - 200;
	}

}

void GameInit()
{
	//	各ＳＥデータの読み込み
	se_walk = LoadSoundMem( "data/se_walk.mp3" );	//	足音
	se_door = LoadSoundMem( "data/se_door.mp3" );	//	ドアを開ける音
	se_rain = LoadSoundMem( "data/se_rain.mp3" );	//	雨の音

	//	プレイヤー画像の読み込み
	player_image = LoadGraph( "data/player.bmp" );
	field_image = LoadGraph( "data/image_field.bmp" );
	room_image = LoadGraph( "data/image_room.bmp" );
	//	プレイヤー初期座標設定
	player_x = 100.0f;

	InitRain();
	
}

SceneEnum sceneenum;

int scenenumber = 0;

void GameUpdate()
{
	//	右キーでプレイヤー移動
	if( CheckHitKey( KEY_INPUT_RIGHT )  )
	{
		player_x += 5.0f;
		if (!CheckSoundMem(se_walk))
		{
			PlaySoundMem(se_walk, 2);
		}

		if (scenenumber >= isInField )
		{
			if (!CheckSoundMem(se_rain))
			{
				PlaySoundMem(se_rain, 3);
			}
		}
	}

	

	//	画面右まで行ったら
	if( player_x > SCREEN_W-1 )
	{
		//	左にする
		scenenumber++;
		player_x = -50.0f;
		PlaySoundMem(se_door,2);
	}

	if (scenenumber == isInRoom)
	{
		StopSoundMem(se_rain);
	}
	if (scenenumber >= 2)
	{
		scenenumber = 0;
	}

}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	
	if (scenenumber == isInRoom)
	{
		DrawGraph(0, 0, room_image, 0);
	}
	else if (scenenumber >= isInField)
	{
		DrawGraph(0, 0, field_image, 0);
	}
	//	プレイヤー画像の描画
	DrawGraphF( player_x, 200.0f, player_image, TRUE );

	if (scenenumber >= isInField)
	{
		DrawRain();
		//DrawPuddle();
	}


	DrawString( 20,  20, "右キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
	DrawString( 20,  40, "→　移動中は se_walk 再生", GetColor( 255, 255, 0 ) );
	DrawString( 20,  60, "→　画面右まで行ったら左から出てくる", GetColor( 255, 255, 255 ) );
	DrawString( 20,  80, "→　そのたびに背景を変更する（切り替わるときのドア音 se_door ）", GetColor( 255, 255, 0 ) );
	DrawString( 20, 100, "→　フィールドの時は雨の描画と音（ se_rain ）", GetColor( 255, 255, 0 ) );
	

}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	InitSoundMem();
}

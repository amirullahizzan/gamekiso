#include "Main.h"
#include "Game.h"

//	プレイヤーの移動スピード
#define PLAYER_SPEED	3.0f
//	プレイヤー画像
int player_image;
int npc_image;
//	プレイヤー座標
float player_x;
float player_y;
float npc_x;
float npc_y;

//	ゲームモード
enum {
	MODE_WAIT,		//	０：何かキーが押されるまで待っているモード
	MODE_MOVE,		//	１：十字キーで移動するモード（座標の記録も）
	MODE_REPLAY,	//	２：リプレイを再生するモード
};

//	今が何モードか用の変数（０：待ち　１：操作　２：リプレイ）
int game_mode;

//	記録する場所の数
#define RECORD_MAX	300
//	プレイヤーの座標を記録する用の変数
float record_x[RECORD_MAX];
float record_y[RECORD_MAX];
//	今が何フレーム目かを数える用の変数
int frame_count;
int frame_countmult = 1;


//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	画像の読み込み
	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );
	//	初期座標の設定
	player_x = 100.0f;
	player_y = 200.0f;
	npc_x = -50;
	npc_y = -50;

	//	最初は待ち状態から開始します
	game_mode = MODE_WAIT;
	//	０フレーム目から開始
	frame_count = 0;
	//	記録座標を０初期化
	for( int i = 0; i < RECORD_MAX; i++ ){
		record_x[i] = 0.0f;
		record_y[i] = 0.0f;
	}
}


void GameUpdate()
{
	//	モードによって処理を分けます
	switch (game_mode) {
	case MODE_WAIT:		//	待ち状態のとき
		//	何かキーを押したら
		if (CheckHitKeyAll()) {
			//	プレイヤーを動かすモードにします
			game_mode = MODE_MOVE;
			//	０フレーム目から記録を開始
			frame_count = 0;
		}
		break;

	case MODE_MOVE:		//	移動状態のとき
		//	十字キーでプレイヤー座標の更新
		if (CheckHitKey(KEY_INPUT_RIGHT))	player_x += PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_LEFT))	player_x -= PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_DOWN))	player_y += PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_UP))		player_y -= PLAYER_SPEED;
		//	プレイヤーの座標の値を記録用のところに入れます
		record_x[frame_count] = player_x;
		record_y[frame_count] = player_y;

		//	カウントの値を増やす
		frame_count++;

		//	最後まで記録出来たら
		if (frame_count >= RECORD_MAX) {
			//	リプレイ開始
			game_mode = MODE_REPLAY;
			//	リプレイで使う時間も最初から
			frame_count = 0;
		}
		break;

	case MODE_REPLAY:	//	リプレイ状態のとき
		//	リプレイ再生（記録した座標 record_x を順番にプレイヤー座標 player_x に入れていく）
		npc_x = record_x[frame_count];
		npc_y = record_y[frame_count];

		//	カウントの値を増やす
		if (frame_count>=0)
		{
			frame_count += frame_countmult;
			if (frame_count<0)
			{
				frame_count = 0;
			}
		}

		//	最後まで再生したら
		if (frame_count >= RECORD_MAX) {
			//	待ちモードにする
			game_mode = MODE_WAIT;
			//	次の記録のためにフレームもリセット
			frame_count = 0;
		}
		break;
	}
}

void PlaybackControl()
{
	if (PushHitKey(KEY_INPUT_F1))
	{
		frame_countmult--;
	}
	if (PushHitKey(KEY_INPUT_F2))
	{
		frame_countmult = 0;
	}
	if (PushHitKey(KEY_INPUT_F3))
	{
		frame_countmult++;
	}
	if (PushHitKey(KEY_INPUT_F4))
	{
		frame_count = 0;
	}
}

int flickertimer = 0;

void PlaylistBar(int frame)
{
	int barposition = 220;
	DrawBox(220 - 5, 400 - 5, 520 + 5, 420 + 5, GetColor(0, 0, 0), 1);
	DrawBox(barposition,400, barposition+frame,420,GetColor(255,255,255),1);
}

void GameRender()
{
	//	画面にプレイヤー画像の描画

	//	モードごとに描画する文字列を変えます
	switch( game_mode ){
	case MODE_WAIT:		//	待ち状態の時
		DrawString( 20, 20, "十字キー：プレイヤー移動（と共に記録を開始します）", GetColor( 255, 255, 255 ) );
		DrawString( 20, 40, "リプレイ再生中は別キャラを動かす", GetColor( 255, 255, 0 ) );
		frame_countmult = 1;
		break;

	case MODE_MOVE:		//	移動状態の時
		DrawString( 20, 20, "十字キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
		DrawString( 20, 40, "リプレイ再生中は別キャラを動かす", GetColor( 255, 255, 0 ) );
		DrawFormatString( 20, 80, GetColor( 255, 255, 0 ), "プレイヤー座標記録中：%3d/%d", frame_count, RECORD_MAX );
		break;

	case MODE_REPLAY:	//	リプレイの時
		DrawGraphF(npc_x, npc_y, npc_image, TRUE);

		DrawString( 20, 20, "十字キー：プレイヤー移動", GetColor( 128, 128, 128 ) );
		DrawString( 20, 40, "リプレイ再生中は別キャラを動かす", GetColor( 255, 255, 0 ) );
		DrawString( 20, 60, "→　というわけでリプレイで移動するのはＮＰＣ（ npc.bmp ）", GetColor( 0, 255, 0 ) );
		DrawFormatString( 20, 80, GetColor( 0, 255, 255 ), "リプレイ再生中　　　：%3d/%d", frame_count, RECORD_MAX );
		//DrawFormatString( 20, 100, GetColor( 0, 255, 255 ), "flicker　　　：%3d", flickertimer );

		DrawString(20, 300, "f1 : Reverse/Slowdown", GetColor(0, 255, 0));
		DrawString(20, 320, "f2 : Pause", GetColor(0, 255, 0));
		DrawString(20, 340, "f3 : Resume/Fast Forward", GetColor(0, 255, 0));
		DrawString(20, 360, "f4 : Restart Replay", GetColor(0, 255, 0));
		DrawFormatString(20, 100, GetColor(0, 255, 255), "再生スピード　　：%d", frame_countmult);
		DrawFormatString(20, 220, GetColor(0, 255, 255), "frame % 100 : %d", frame_count % 100);


		PlaylistBar(frame_count);
		PlaybackControl();
		flickertimer++;
		//	この文字列を点滅させます
		if ((frame_count % 100 )< 70)
		{
			DrawString(200, 200, "「リプレイ中（この文字列を点滅させます）」", GetColor(255, 255, 0));
		}
		
		break;
	}
	DrawGraphF(player_x, player_y, player_image, TRUE);

}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
}

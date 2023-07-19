#include "Main.h"
#include "Game.h"

//	プレイヤー画像
int player_image;
//	プレイヤーＸ座標（今回は横にしか移動しないのでＸ座標だけ）
float player_x;


int bg_image[3];
int bg_imageIndex;
int bgm[3];
int bgmIndex;

void GameInit()
{
	//	プレイヤー画像の読み込み
	player_image = LoadGraph( "data/player.bmp" );

	bg_image[0] = LoadGraph("data/image_town.bmp");
	bg_image[1] = LoadGraph("data/image_field.bmp");
	bg_image[2] = LoadGraph("data/image_battle.bmp");

	bg_imageIndex = 0;
	bgmIndex = 0;

	//	初期座標設定
	player_x = 100.0f;

	//	とりあえず最初にＢＧＭの再生をしています
	PlayMusic("data/bgm_town.mp3", DX_PLAYTYPE_LOOP);
}

void ChangeMusic()
{
	StopMusic();
	if (bg_imageIndex == 0)
	{
		PlayMusic("data/bgm_town.mp3", DX_PLAYTYPE_LOOP);
	}
	if (bg_imageIndex == 1)
	{
		PlayMusic("data/atmosphere.wav", DX_PLAYTYPE_LOOP);
	}
	if (bg_imageIndex == 2)
	{
		PlayMusic("data/castle.wav", DX_PLAYTYPE_LOOP);
	}
}

void GameUpdate()
{
	//	右キーでプレイヤー移動
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		player_x += 15.0f;
	}
	//	画面右まで行ったら左にする
	if( player_x > SCREEN_W ){
		player_x = -50.0f;
		bg_imageIndex++;
		if (bg_imageIndex > 2)
		{
			bg_imageIndex = 0;
		}
		ChangeMusic();

	}

}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	DrawGraph(0, 0, bg_image[bg_imageIndex], 0);

	//	プレイヤー画像の描画
	DrawGraphF( player_x, 200.0f, player_image, TRUE );

	DrawString( 20, 20, "右キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "→　画面右まで行ったら左から出てくる", GetColor( 255, 255, 255 ) );
	DrawString( 20, 60, "→　そのたびに背景とＢＧＭを変更する", GetColor( 255, 255, 0 ) );

}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );

}

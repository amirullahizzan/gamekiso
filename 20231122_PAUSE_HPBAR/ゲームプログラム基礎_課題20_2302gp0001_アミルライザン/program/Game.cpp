#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"

#include "Player.h"
#include "Npc.h"

//	画像データ用の変数（ Game.cpp の最初に読み込んでクラスに渡す）
int player_image;
int npc_image;

//	プレイヤークラス（１個宣言）
Player player;
//	ＮＰＣの数（５個）
#define NPC_MAX	5
//	ＮＰＣの宣言
Npc npc[NPC_MAX];

//	ゲームモードの種類
enum {
	MODE_PLAY,		//	０：プレイ中
	MODE_PAUSE,		//	１：ポーズ中
};
//	今のゲームモード
int game_mode;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	それぞれの画像の読み込み
	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );

	//	上で読み込んだ画像番号を渡してクラスの初期化
	//	プレイヤーの初期化
	player.Init( player_image );
	//	ＮＰＣの初期化
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Init( npc_image );
	}

	//	最初は操作できる状態から開始
	game_mode = MODE_PLAY;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	ゲームモードによって処理を分けます
	switch( game_mode ){
	case MODE_PLAY:		//	ゲームプレイ中

		//	スペースキーを押したら
		if( PushHitKey( KEY_INPUT_SPACE ) ){
			//	モードをポーズに切り替える（ポーズメニューが開く）
			game_mode = MODE_PAUSE;
		}

		//	ゲームプレイ中のみ呼ぶようにします
		//	プレイヤーの更新処理（十字キーで移動）
		player.Update();
		//	ＮＰＣの更新処理（画面左に移動）
		for( int i = 0; i < NPC_MAX; i++ ){
			npc[i].Update();
		}

		break;

	case MODE_PAUSE:	//	ポーズ中

		//	スペースキーを押したら
		if( PushHitKey( KEY_INPUT_SPACE ) ){
			//	モードをプレイ中に切り替える
			game_mode = MODE_PLAY;
		}

		//	左右キーでプレイヤーのスピードの変更
		if( CheckHitKey( KEY_INPUT_RIGHT ) ){
			player.m_speed += 0.1f;
			//	プレイヤースピードの最大は 10.0f
			if( player.m_speed > 10.0f ){
				player.m_speed = 10.0f;
			}
		}
		if( CheckHitKey( KEY_INPUT_LEFT ) ){
			player.m_speed -= 0.1f;
			//	プレイヤースピードの最小は 1.0f
			if( player.m_speed < 1.0f ){
				player.m_speed = 1.0f;
			}
		}
		if (CheckHitKey(KEY_INPUT_UP)) {
			player.m_speed = 10.0f;
		}
		if (CheckHitKey(KEY_INPUT_DOWN)) {
			player.m_speed = 1.0f;
		}



		break;
	}

}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	プレイヤーやＮＰＣはモードにかかわらず描画しときます
	//	ＮＰＣの描画
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Render();
	}
	//	プレイヤーの描画
	player.Render();

	//	ポーズ中の時のみ描画します
	if( game_mode == MODE_PAUSE ){
		//	ポーズメニュー
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawFillBox( 150, 100, 650, 350, GetColor( 0, 0, 0 ) );
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawLineBox( 150, 100, 650, 350, GetColor( 255, 255, 255 ) );

		//	説明用の文字列
		DrawString( 200, 130, "←→キー：プレイヤースピード変更", GetColor( 255, 255, 255 ) );
		DrawString( 200, 150, "↑キー　：スピードを最大（ 10.0f ）に設定", GetColor( 255, 255, 0 ) );
		DrawString( 200, 170, "↓キー　：スピードを最小（  1.0f ）に設定", GetColor( 255, 255, 0 ) );
		//	プレイヤーのスピードを文字列で描画
		DrawFormatString( 200, 200, GetColor( 255, 255, 255 ), "プレイヤースピード：%4.1f", player.m_speed );
		//	ポーズメニューを閉じる説明用の文字列
		static int flickertick = 0;
		static bool isDisplayed = true;
		flickertick++;
		if (flickertick > 60)
		{
			isDisplayed = false;
		}
		if (flickertick > 80 )
		{
			isDisplayed = true;
			flickertick = 0;
		}

		if(isDisplayed)
		{
		DrawString( 200, 300, "スペース：ポーズ閉じる", GetColor( 255, 255, 255 ) );
		}

		





		DrawFillBox(200, 240, 200 + (30* (player.m_speed)), 260, GetColor(0, 255, 0));
		DrawLineBox(200, 240, 500, 260, GetColor(255, 255, 255)	);
	}

	DrawString( 16, 16, "十字キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "スペース：ポーズメニュー", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "ポーズメニューの背景画像の描画を半透明に", GetColor( 255, 255, 0 ) );
	DrawString( 16, 64, "プレイヤースピードをバーを使って表示", GetColor( 255, 255, 0 ) );
	
	DrawString( 16, 80, "「スペース：ポーズ閉じる」を点滅させる", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	player.Exit();
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Exit();
	}

	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}

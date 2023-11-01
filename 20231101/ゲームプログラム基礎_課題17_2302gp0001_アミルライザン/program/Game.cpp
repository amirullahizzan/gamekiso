#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Float2.h"
//	ランダム関係の関数を使えるようにインクルード
#include "Random.h"

//	ノイズ画像用の変数
int noise_image;
//	ノイズ画像を描画するかどうか（ true：描画します　false：描画しません）
bool noise_draw;
//	ノイズ画像の描画座標
Float2 noise_pos;

//	ＮＰＣの数
#define NPC_MAX		10
//	ＮＰＣ半径
#define NPC_RADIUS	25.0f

int npc_image;
//	ＮＰＣ座標
Float2 npc_pos[NPC_MAX];
float npc_rot[NPC_MAX];

void EnemiesOOBHandler(int i)
{
	while (npc_pos[i].x <= 100.0f + NPC_RADIUS)
	{
		npc_pos[i].x = GetRandomF(SCREEN_W);
	}
}

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	ＮＰＣ画像の読み込み
	npc_image = LoadGraph( "data/npc.bmp" );
	//	ノイズ画像の読み込み
	noise_image = LoadGraph( "data/noise.bmp" );

	//	ＮＰＣの初期設定
	for( int i = 0; i < NPC_MAX; i++ ){
		//	Ｘ座標は左の線（Ｘ座標：100.0f）より右にランダムに座標設定
		npc_pos[i].x = GetRandomF( SCREEN_W );
		npc_pos[i].y = GetRandomF( SCREEN_H );
		npc_rot[i] = GetRandomF( 360.0f );
		EnemiesOOBHandler(i);
	}

	noise_draw = false;
	noise_pos.x = 0.0f;
	noise_pos.y = 0.0f;

}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
static int noise_timer = 0;
static int noise_randomcd = GetRandomI(5, 7);

void GameUpdate()
{
	//	ＮＰＣの座標や向きのランダム更新
	if (noise_draw)
	{
		for (int i = 0; i < NPC_MAX; i++)
		{
			npc_pos[i].x = GetRandomF(SCREEN_W);
			npc_pos[i].y = GetRandomF(SCREEN_H);
			npc_rot[i] = GetRandomF(360.0f);

			EnemiesOOBHandler(i);
		}
	}

	

	for( int i = 0; i < NPC_MAX; i++ )
	{
		//	現状は特に何もしていません
		npc_pos[i].x += GetRandomI(-1.0f, 1.0f);
		npc_pos[i].y += GetRandomI(-1.0f, 1.0f);
		npc_rot[i] += GetRandomI(-3.0f, 3.0f);

	}

	//	マウス座標
	Float2 mouse;
	mouse.x = static_cast<float>(GetMouseX());
	mouse.y = static_cast<float>(GetMouseY());
	//	マウスクリック
	if( PushMouseInput() ){
		for( int i = 0; i < NPC_MAX; i++ ){
			//	ＮＰＣをクリックしたら
			if( CheckPointCircleHit( mouse, npc_pos[i], NPC_RADIUS ) ){
				//	ＮＰＣを画面左にする
				npc_pos[i].x = 50.0f;
			}
		}
	}

	//	現状はスペースキーで表示していますが、ランダム時間で表示・非表示を切り替えますので
	//	以下の処理はコメントにして新たに処理の実装をおこないます
	//if( CheckHitKey( KEY_INPUT_SPACE ) ){
	//	//	ノイズ画像を描画したい
	//	noise_draw = true;
	//}else{
	//	//	描画しない
	//	noise_draw = false;
	//}

	//	ノイズ画像の座標をランダムにしてみます
	//	Ｘ座標（ -200.0f ～ 0.0f ）
	noise_pos.x = GetRandomF( -200.0f, 0.0f );
	//	Ｙ座標（ -550.0f ～ 0.0f ）
	noise_pos.y = GetRandomF( -550.0f, 0.0f );

	noise_timer++;
	if (noise_timer % (60*noise_randomcd) == 0)
	{
		noise_draw = true;
	}

	if (noise_timer % (60 * (noise_randomcd + 1)) == 0 && noise_draw)
	{
		noise_randomcd = GetRandomI(5, 7);
		noise_timer = 0;
		noise_draw = false;
	}

	

}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	clsDx();
	//printfDx("timer : %d", noise_timer);
	{
		static int timeremaining = 0;
		if (!noise_draw)
		{
			timeremaining = 60 * noise_randomcd - noise_timer;
		}
		else
		{
			timeremaining = 60 * (noise_randomcd+1) - noise_timer;
		}

		DrawFormatString(20, 100, GetColor(255, 255, 255), "Time left : %d", timeremaining);
	}

	//	画面左の線の描画
	DrawLineAA( 100.0f, 0.0f, 100.0f, SCREEN_H, GetColor( 255, 255, 255 ) );

	//	ノイズ画像を描画するのであれば
	if( noise_draw ){
		//	ノイズ画像を半透明にします
		SetDrawBlendMode( DX_BLENDMODE_ALPHA, 100 );
		//	ノイズ画像を描画
		DrawGraphF( noise_pos.x, noise_pos.y, noise_image, TRUE );
		//	半透明設定を元に戻す
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
	}
	else
	{
		//	ＮＰＣの描画
		for (int i = 0; i < NPC_MAX; i++) {
			DrawRotaGraphF(npc_pos[i].x, npc_pos[i].y, 1.0f, TO_RADIAN(npc_rot[i]), npc_image, TRUE);
		}
	}

	DrawString( 16, 16, "ＮＰＣは左の線（Ｘ座標：100.0f）より右にランダムに座標設定", GetColor( 255, 255, 0 ) );
	DrawString( 16, 32, "ＮＰＣはランダムに座標移動（ -1.0f ～ 1.0f ）や回転（ -3.0f ～ 3.0f ）する", GetColor( 255, 255, 0 ) );
	DrawString( 16, 48, "マウスでＮＰＣをクリック → ＮＰＣを画面左へ", GetColor( 255, 255, 0 ) );
	DrawString( 16, 64, "ノイズ演出：表示１秒と非表示５～７秒を繰り返す", GetColor( 0, 255, 255 ) );
	DrawString( 16, 80, "→　ノイズ表示中はＮＰＣ非表示・ノイズ解除時にＮＰＣ座標リセット", GetColor( 0, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( npc_image );
	DeleteGraph( noise_image );
}

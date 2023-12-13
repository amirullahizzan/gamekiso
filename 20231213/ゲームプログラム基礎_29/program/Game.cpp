#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Hit.h"

//	プレイヤーの移動スピード
#define PLAYER_SPEED	3.0f
//	ＮＰＣの数
#define NPC_MAX			4

//	プレイヤー画像
int player_image;
//	プレイヤー座標
Float2 player_pos;

//	ＮＰＣ画像
int npc_image;
//	ＮＰＣ座標
Float2 npc_pos[NPC_MAX];

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	画像の読み込み
	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );
	//	初期座標の設定
	player_pos.clear();
	//	ＮＰＣはとりあえずランダムで
	for( int i = 0; i < NPC_MAX; i++ ){
		npc_pos[i].x = GetRandomF( SCREEN_W );
		npc_pos[i].y = GetRandomF( SCREEN_H );
	}

	FILE* player_fp = fopen("data/player.txt", "r");
	
	char text[256];
	int x, y;
	//4 steps 
	if (player_fp)
	{
	//fgets(text,256,player_fp);
	fgets(text, sizeof(text), player_fp);
	sscanf_s(text,"%d,%d", &x, &y); //other than format specifiers needs to be read
	//Float2 newpos = {x,y };
	player_pos.set(x,y);
	//player_pos.x = x;
	//player_pos.y = y;
	fclose(player_fp);
	player_fp = nullptr;
	}

	FILE* npc_fp = fopen("data/npc.txt","r");

	if (npc_fp)
	{
		//char text[256];
		//int x, y;
		for (int i = 0; i <NPC_MAX;i++)
		{
		fgets(text,sizeof(text),npc_fp); //read per line, when executed again will go to the next line
		sscanf_s(text,"%d,%d",&x,&y); //takes the value address
		npc_pos[i].set(x,y);
		}
		fclose(npc_fp);
	}

}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	十字キーでプレイヤー座標の更新
	if( CheckHitKey( KEY_INPUT_RIGHT ) )	player_pos.x += PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_LEFT ) )		player_pos.x -= PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_DOWN ) )		player_pos.y += PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_UP ) )		player_pos.y -= PLAYER_SPEED;
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	for( int i = 0; i < NPC_MAX; i++ ){
		DrawRotaGraphF( npc_pos[i].x, npc_pos[i].y, 1.0f, TO_RADIAN( 180.0f ), npc_image, TRUE );
	}

	DrawRotaGraphF( player_pos.x, player_pos.y, 1.0f, TO_RADIAN( 0.0f ), player_image, TRUE );

	DrawString( 16, 16, "十字キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "data フォルダに player.txt と npc.txt があります", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "起動時にそれぞれのテキストから数値を取得して座標の初期設定", GetColor( 255, 255, 255 ) );
	DrawString( 16, 64, "終了時に今のプレイヤー座標を「player.txt」に書き込む", GetColor( 255, 255, 255 ) );
	DrawString( 16, 80, "→　なので次に起動するとプレイヤーは前回終了した座標から始まります", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	//Saving player position on exit game

	FILE* saveFile = fopen("data/player.txt", "w");

	char text[256];
	if (saveFile)
	{
		int x = player_pos.x;
		int y = player_pos.y;
		sprintf(text,"%d,%d",x,y);
		//fwrite(text,sizeof(text),2, saveFile);
		fputs(text,saveFile);
		//if want to go to the next line
		fputs("\n", saveFile);

		fclose(saveFile);
	}

	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}

#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"

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
float npc_rotation_degree[NPC_MAX];

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

	FILE* readFile = fopen("data/start.txt","r");

	char text[256];
	float x, y, rotation;
	if (readFile)
	{
		fgets(text,sizeof(text),readFile);
		sscanf_s(text,"%f,%f",&x,&y);
		player_pos.set(x,y);

		for (int i = 0 ; i < NPC_MAX;i++)
		{
			fgets(text, sizeof(text), readFile);
			sscanf_s(text, "%f,%f,%f", &x, &y,&rotation);
			npc_pos[i].set(x, y);
			npc_rotation_degree[i] = rotation;
		}

		fclose(readFile);
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
		DrawRotaGraphF( npc_pos[i].x, npc_pos[i].y, 1.0f, TO_RADIAN(npc_rotation_degree[i]), npc_image, TRUE);
	}

	DrawRotaGraphF( player_pos.x, player_pos.y, 1.0f, TO_RADIAN( 0.0f ), player_image, TRUE );

	DrawString( 16, 16, "十字キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "今回の課題ではテキストファイルへの書き込みはありません", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "初期化で start.txt を読み込んで以下の情報を設定する", GetColor( 255, 255, 0 ) );
	DrawString( 16, 64, "テキスト１行目（プレイヤー情報）：Ｘ座標　Ｙ座標", GetColor( 255, 255, 0 ) );
	DrawString( 16, 80, "テキスト２～５行目（ＮＰＣ情報）：Ｘ座標　Ｙ座標　向き", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}

#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Hit.h"

#include "Player.h"
#include "Npc.h"

int player_image;
int npc_image;

Player	player;

#define NPC_MAX	5
Npc		npc[NPC_MAX];

int mini_map_image;
int mini_player_image;
int mini_npc_image;

#define MAP_X	525.0f
#define MAP_Y	200.0f

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );

	player.Init( player_image );
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Init( npc_image );
	}

	mini_map_image = LoadGraph( "data/mini_map.bmp" );
	mini_player_image = LoadGraph( "data/mini_player.bmp" );
	mini_npc_image = LoadGraph( "data/mini_npc.bmp" );
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	player.Update();


	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Update();
	}

}

class MiniMap
{
public:
	Float2 pos = { 0,0 };
	Float2 scale = { 0,0 };
	Float2 size = { 0,0 };
	void SetPos(float _x, float _y)
	{
		pos.x = _x;
		pos.y = _y;
	}
	void SetSize(float _x, float _y)
	{
		size.x = _x;
		size.y = _y;
	}
	void SetScale(float original_screen_size_x, float original_screen_size_y)
	{
		scale.x = original_screen_size_x / size.x;
		scale.y = original_screen_size_y / size.y;
	}

	void ScaleToMinimap(Float2& minimapEntityPos, const Float2& originalEntityPos)
	{
		minimapEntityPos = { MAP_X + (originalEntityPos.x / scale.x),
							 MAP_Y + (originalEntityPos.y / scale.y) };
	}

private:
};

MiniMap minimap;


void GameRender()
{
	clsDx();
	minimap.SetPos( MAP_X, MAP_Y);
	minimap.SetSize( 250,225 );
	minimap.SetScale(STAGE_W, STAGE_H);

	printfDx("scalex : %f", minimap.scale.x);

	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Render();
	}
	player.Render();

	Float2 blackBar = {STAGE_W,0};
	DrawBoxAA(blackBar.x, blackBar.y,SCREEN_W, SCREEN_H,GetColor(65, 65, 65),1);
	DrawGraphF(minimap.pos.x, minimap.pos.y, mini_map_image,1);

	//RenderMinimapEntities
	{
		Float2 minimap_player;
		minimap.ScaleToMinimap(minimap_player, player.m_pos);
		DrawRotaGraphF(minimap_player.x, minimap_player.y, 1.0f, TO_RADIAN(player.m_rot), mini_player_image, TRUE);
		for (int i = 0; i < NPC_MAX; i++)
		{
		Float2 minimap_npc;
		minimap.ScaleToMinimap(minimap_npc, npc[i].m_pos);
		DrawRotaGraphF(minimap_npc.x, minimap_npc.y, 1.0f, TO_RADIAN(npc[i].m_rot), mini_npc_image, TRUE);
		}
	}

	//STRING
	DrawString( STAGE_W + 20, 20, "左右キー：プレイヤーの回転", GetColor( 255, 255, 255 ) );
	DrawString(STAGE_W + 20, 40, "上キー　：向いている方向に移動", GetColor( 255, 255, 255 ) );
	DrawString(STAGE_W + 20, 180, "ミニマップの表示", GetColor( 255, 255, 255 ) );
	
	{
	static int game_frame = 0;
	game_frame++;
	DrawFormatString(STAGE_W + 20, 160, GetColor(255,255,255),"ゲーム開始から : %05d",game_frame);
	}
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( mini_map_image );
	DeleteGraph( mini_player_image );
	DeleteGraph( mini_npc_image );

	player.Exit();
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Exit();
	}

	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}

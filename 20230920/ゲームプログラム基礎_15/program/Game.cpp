#include "Main.h"
#include "Game.h"
#include "Hit.h"

#define NPC_RADIUS	25.0f

#define NPC_SPEED	3.0f

enum
{
	npc_pink, npc_orange, npc_red,

	TYPE_MAX
};

int npc_frame_data[TYPE_MAX] = {
120,60,180
};

int load_image[TYPE_MAX];
int npc_frame = 0;

int npc_type;
int npc_image;
float npc_x;
float npc_y;
float npc_rot;

void GameInit()
{
	/*load_image[npc_pink] = LoadGraph("data/npc0.bmp");
	load_image[npc_orange] = LoadGraph( "data/npc1.bmp" );
	load_image[npc_red] = LoadGraph( "data/npc2.bmp" );*/

	char filename[256];
	for (int i = 0;i<TYPE_MAX;i++)
	{
	sprintf_s(filename,"data/npc%d.bmp",i);
	load_image[i] = LoadGraph(filename);
	}

	npc_type = 0;
	npc_image = load_image[npc_type];
	npc_frame = npc_frame_data[npc_type];

	npc_x = SCREEN_W / 2;
	npc_y = SCREEN_H / 2;
	npc_rot = 0.0f;
}


void ReSpawn(float& posx, float& posy)
{
	int previous_type = npc_type;
	while (npc_type == previous_type)
	{
	npc_type = rand()%TYPE_MAX;
	}
	posx = GetRand(SCREEN_W - NPC_RADIUS) + NPC_RADIUS;
	posy = GetRand(SCREEN_H - NPC_RADIUS) + NPC_RADIUS;
	npc_frame = npc_frame_data[npc_type];
}

void GameUpdate()
{
	npc_image = load_image[npc_type];

	npc_rot += NPC_SPEED;
	npc_frame--;
	if (npc_frame < 0) { ReSpawn(npc_x, npc_y); }

	if( PushMouseInput() ){

		int mouse_x = GetMouseX();
		int mouse_y = GetMouseY();

		if( CheckPointCircleHit( mouse_x, mouse_y, npc_x, npc_y, NPC_RADIUS ) )
		{
			ReSpawn(npc_x, npc_y);
		}
	}
}

void GameRender()
{
	DrawRotaGraphF( npc_x, npc_y, 1.0f, TO_RADIAN( npc_rot ), npc_image, TRUE);

	DrawCircleAA( npc_x, npc_y, NPC_RADIUS, 100, GetColor( 255, 255, 0 ), FALSE );

	DrawString( 20, 20, "‚m‚o‚bƒNƒŠƒbƒNF•Êƒ^ƒCƒv‚Ì‚m‚o‚b‚ðƒ‰ƒ“ƒ_ƒ€‚ÈêŠ‚É", GetColor( 255, 255, 255 ) );
	DrawString( 20, 60, "‚m‚o‚b‚Íˆê’èŽžŠÔ‚ª‚½‚Á‚½‚çƒNƒŠƒbƒN‚³‚ê‚½Žž‚Æ“¯—l‚É•Êƒ^ƒCƒv‚É•ÏX", GetColor( 255, 255, 255 ) );
	DrawString( 20, 80, "¨@“oê‚µ‚Ä‚¢‚éŽžŠÔ‚Íƒ^ƒCƒv‚É‚æ‚Á‚Äˆá‚¤", GetColor( 255, 255, 255 ) );
}

void GameExit()
{
}

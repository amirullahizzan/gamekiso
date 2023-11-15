#include "Main.h"
#include "Game.h"
#include "Float2.h"
#include "Hit.h"
#include "Random.h"

#include "Npc.h"

#define NPC_MAX		7

Npc npc[NPC_MAX];

int npc_image = 0;

struct StartData {
	int frame;
	int x;
	int y;

};

StartData startData[NPC_MAX]
{
	{60,700.0f,300.0f},
	{120,700.0f,300.0f},
	{180,700.0f,300.0f},

	{300,700.0f,100.0f},
	{330,800.0f,100.0f},

	{500,800.0f,200.0f},
	{550,1100.0f,200.0f},
};

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	npc_image = LoadGraph("data/npc.bmp");
	for (int i = 0; i<NPC_MAX;i++)
	{
		npc[i].Init(npc_image);
	}

}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	static int game_frame = 0;
	static double lastFrame = static_cast<double>(GetNowCount());
	double pc_time = static_cast<double>(GetNowCount());
	double deltaTime_ms = (pc_time - lastFrame);
	float deltaTime = static_cast<float>(deltaTime_ms)/ 1000;
	lastFrame = pc_time;
	static double ms = 0;
	static double ms_total = 0;
	ms += deltaTime_ms;
	ms_total += deltaTime_ms;
	static double second = 0;
	second += deltaTime;
	if (ms > 1000)
	{
		ms = 0;
	}
	game_frame = static_cast<int>(ms_total)*0.1;
	
	clsDx();
	printfDx("deltaTime : %f\n", deltaTime_ms);
	printfDx("deltaTime : %f\n", deltaTime);
	printfDx("ms_total : %f\n", ms_total);
	printfDx("sec : %f\n", second);
	printfDx("game_frame : %d\n", game_frame);

	for (int i = 0; i < NPC_MAX; i++)
	{
		if (game_frame == startData[i].frame)
		{
			npc[i].m_pos.x = startData[i].x;
			npc[i].m_pos.y = startData[i].y;
			npc[i].m_type = 1;
		}
	}
	for (int i = 0; i < NPC_MAX; i++)
	{ 
		npc[i].Update();
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	for (int i = 0; i < NPC_MAX; i++)
	{
		if (npc[i].m_type != 0)
		{
	 npc[i].Render();
		}
	}


	DrawString( 16, 16, "ＮＰＣ決まったタイミングで決まった場所から登場（再び出てくることはない）", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	for (int i = 0; i < NPC_MAX; i++)
	{
	npc[i].Exit(npc_image);
	}
}

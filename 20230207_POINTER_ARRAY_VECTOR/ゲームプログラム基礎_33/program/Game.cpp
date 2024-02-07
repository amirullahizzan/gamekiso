#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Hit.h"

#include "Npc.h"

#include <vector>
//	マウス座標との当たり判定で使うＮＰＣの半径
#define NPC_RADIUS	25.0f

//	画像用の変数
int npc_image;

std::vector<Npc*> npcList;

void GameInit()
{
	//	画像の読み込み
	npc_image = LoadGraph("data/npc.bmp");

	Npc* newNpc = new Npc();
	newNpc->Init(npc_image);
	npcList.push_back(newNpc);

}

void GameUpdate()
{
	//	スペースキーを押したら
	if (PushHitKey(KEY_INPUT_RETURN))
	{
		for (size_t i = 0; i < npcList.size(); i++)
		{
			delete npcList[i];
			npcList[i] = nullptr;
		}
	}
#define DEBUG

#ifdef DEBUG
	if (CheckHitKey(KEY_INPUT_SPACE))
#else
	if (PushHitKey(KEY_INPUT_SPACE))
#endif // DEBUG
	{
		Npc* newNpc = new Npc();
		newNpc->Init(npc_image);
		npcList.push_back(newNpc);

		//if (npc[i]) { return; }
		//npc = new Npc();
		//npc->Init(npc_image);
	}

	if(PushHitKey(KEY_INPUT_5))
	{
		for (int i = 0;i < 50000;i++)
		{
		Npc* newNpc = new Npc();
		newNpc->Init(npc_image);
		npcList.push_back(newNpc);
		}

		//if (npc[i]) { return; }
		//npc = new Npc();
		//npc->Init(npc_image);
	}

	for (size_t i = 0; i < npcList.size(); i++)
	{
		if (npcList[i])npcList[i]->Update();
	}

	//	マウスクリックしたら
	if (PushMouseInput()) {
		Float2 mouse;
		mouse.x = GetMouseX();
		mouse.y = GetMouseY();
		//	マウス座標とＮＰＣで当たり判定
		for (size_t i = 0; i < npcList.size();i++)
		{
			if (!npcList[i])continue;
			if (CheckPointCircleHit(mouse, npcList[i]->m_pos, NPC_RADIUS))
			{
				npcList[i]->m_pos.set(GetRandomF(SCREEN_W), GetRandomF(SCREEN_H));
				delete npcList[i];	npcList[i] = nullptr;
				break;
			}
		}
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	for (size_t i = 0; i < npcList.size();i++)
	{
	if (npcList[i])npcList[i]->Render();
	}

	DrawString(16, 16, "スペースキー　：ＮＰＣ登場", GetColor(255, 255, 255));
	DrawString(16, 32, "ＮＰＣクリック：ＮＰＣ消す", GetColor(255, 255, 255));
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	for (size_t i = 0; i < npcList.size(); i++)
	{
	if (npcList[i])npcList[i]->Exit();
	}

	DeleteGraph(npc_image);
}

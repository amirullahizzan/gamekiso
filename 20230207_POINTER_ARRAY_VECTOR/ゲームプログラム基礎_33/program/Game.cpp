#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Hit.h"

#include "Npc.h"

#include <vector>
//	�}�E�X���W�Ƃ̓����蔻��Ŏg���m�o�b�̔��a
#define NPC_RADIUS	25.0f

//	�摜�p�̕ϐ�
int npc_image;

std::vector<Npc*> npcList;

void GameInit()
{
	//	�摜�̓ǂݍ���
	npc_image = LoadGraph("data/npc.bmp");

	Npc* newNpc = new Npc();
	newNpc->Init(npc_image);
	npcList.push_back(newNpc);

}

void GameUpdate()
{
	//	�X�y�[�X�L�[����������
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

	//	�}�E�X�N���b�N������
	if (PushMouseInput()) {
		Float2 mouse;
		mouse.x = GetMouseX();
		mouse.y = GetMouseY();
		//	�}�E�X���W�Ƃm�o�b�œ����蔻��
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
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	for (size_t i = 0; i < npcList.size();i++)
	{
	if (npcList[i])npcList[i]->Render();
	}

	DrawString(16, 16, "�X�y�[�X�L�[�@�F�m�o�b�o��", GetColor(255, 255, 255));
	DrawString(16, 32, "�m�o�b�N���b�N�F�m�o�b����", GetColor(255, 255, 255));
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	for (size_t i = 0; i < npcList.size(); i++)
	{
	if (npcList[i])npcList[i]->Exit();
	}

	DeleteGraph(npc_image);
}

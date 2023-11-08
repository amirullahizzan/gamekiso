#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Player.h"


void Player::Init()
{
	imagehandler = LoadGraph("data/player.bmp");

	pos.x = SCREEN_W / 2;
	pos.y = SCREEN_H / 2;

	//SetSize();
}

void Player::Update()
{
	//SetSize();

	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		pos.x -= speed;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		pos.x += speed;
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		pos.y -= speed;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		pos.y += speed;
	}
}

void Player::Render()
{
	DrawRotaGraphF(pos.x, pos.y, 1.0f, TO_RADIAN(0.0f), imagehandler, TRUE);
}

void Player::Exit()
{
	DeleteGraph(imagehandler);
}

#include "Main.h"
#include "Game.h"
#include "Hit.h"

//	ƒvƒŒƒCƒ„[—p‚Ì•Ï”
int player_image;	//	‰æ‘œ
float player_x;		//	‚wÀ•W
float player_y;		//	‚xÀ•W

//	‚m‚o‚b—p‚Ì•Ï”
int npc_image;		//	‰æ‘œ
float npc_x;		//	‚wÀ•W
float npc_y;		//	‚xÀ•W

int npc_alpha;

//---------------------------------------------------------------------------------
//	‰Šú‰»ˆ—
//---------------------------------------------------------------------------------
void GameInit()
{
	//	ƒvƒŒƒCƒ„[‚Ì‰ŠúÝ’è
	player_image = LoadGraph( "data/player.bmp" );
	player_x = 100.0f;
	player_y = 200.0f;

	//	‚m‚o‚b‚Ì‰ŠúÝ’è
	npc_image = LoadGraph( "data/npc.bmp" );
	npc_x = 350.0f;
	npc_y = 200.0f;
	npc_alpha = 256;
}
int alphaMode = 1;
void GameUpdate()
{
	//	ƒ}ƒEƒXÀ•W‚ðƒvƒŒƒCƒ„[‚ÌÀ•W‚É‚µ‚Ü‚·
	player_x = GetMouseX();
	player_y = GetMouseY();

	switch (alphaMode)
	{
	case 0:
		npc_alpha += 2;
		if (npc_alpha >= 256)
		{
			alphaMode = 1;
		}
		break;
	case 1:
		npc_alpha -= 2;
		if (npc_alpha <= 0)
		{
			npc_x = GetRand(SCREEN_W);
			npc_y = GetRand(SCREEN_H);
			alphaMode = 0;
		}
		break;
	}
}
//---------------------------------------------------------------------------------
//	•`‰æˆ—
//---------------------------------------------------------------------------------
void GameRender()
{
	//	ƒvƒŒƒCƒ„[‚Ì•`‰æ
	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( 0.0f ), player_image, TRUE );

	//	‚m‚o‚b‚ð”¼“§–¾‚É‚µ‚Ä•`‰æ‚µ‚½‚¢
	//	‚PF¡‚©‚ç•`‰æ‚·‚é‚à‚Ìi‚m‚o‚bj‚Ì“§–¾“x‚ðÝ’è
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, npc_alpha );
	//	‚QF‚¢‚Â‚à‚Ì•`‰æ
	//	‚m‚o‚b‚Ì•`‰æ
	DrawRotaGraphF( npc_x, npc_y, 1.0f, TO_RADIAN( 0.0f ), npc_image, TRUE );
	//	ŽŸ‚Ì•`‰æ‚Ì‚½‚ß‚É“§–¾“xÝ’è‚ðŒ³‚É–ß‚µ‚Ü‚·
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );

	//WHITE
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256/2);
	DrawFillBox(SCREEN_W / 2 - 280,SCREEN_H - 160, SCREEN_W / 2 + 280, SCREEN_H -50,GetColor(0,0,0));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawLineBox(SCREEN_W / 2 - 280, SCREEN_H - 160, SCREEN_W / 2 + 280, SCREEN_H - 50, GetColor(255, 255, 255));

	DrawString( SCREEN_W/2 - 220, SCREEN_H - 145, "ƒ}ƒEƒXÀ•W‚ÌŠ‚ÉƒvƒŒƒCƒ„[‰æ‘œ‚Ì•`‰æ", GetColor( 255, 255, 255 ) );
	DrawString(SCREEN_W / 2 - 220, SCREEN_H - 145 + 18, "‚m‚o‚b‚Ío‚½‚èÁ‚¦‚½‚è‚ðŒJ‚è•Ô‚·", GetColor( 255, 255, 0 ) );
	DrawString(SCREEN_W / 2 - 220, SCREEN_H - 145 + 18*2, "¨@o‚Ä‚­‚é‚Æ‚«‚ÍÀ•W‚ðƒ‰ƒ“ƒ_ƒ€‚É", GetColor( 255, 255, 0 ) );
	DrawString(SCREEN_W / 2 - 220, SCREEN_H - 145 + 18*3, "‚±‚Ì•¶Žš—ñ‚ðƒƒbƒZ[ƒW•\Ž¦‚Ý‚½‚¢‚É‚µ‚Ä‚Ý‚é", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	I—¹ˆ—
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}

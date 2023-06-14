#include "Main.h"
#include "Game.h"

int player_image;

int player_posx;
int player_posy;

int effect_image;

int effect_posx;
int effect_posy;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	player_image = LoadGraph( "data/player.bmp" );
	player_posx = 100;
	player_posy = 100;

	effect_image = LoadGraph( "data/effect.bmp" );
	effect_posx = 300;
	effect_posy = 100;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------

struct Player
{
private :

	int anim1 = 0;
	int anim2 = 50;
	int animtick = 0;
public :
	int anim = 0;
	void Anim()
	{
		animtick++;

		/*switch (animtick)
		{
		case 50: anim = anim2;
			break;
		case 100 : animtick = 0;
			break;
		default: anim = anim1;
			break;
		}*/

		if (animtick < 50)
		{
			anim = 0;
		}

		if (animtick > 50)
		{
		anim =+ 50;
		}
		
		if (animtick > 100)
		{
			animtick = 0;
		}
		
		
	}
};

struct Effect
{
private:

	int animtick = 0;

	void RandomizePos()
	{
		
			effect_posx = GetRand(SCREEN_W);
			effect_posy = GetRand(SCREEN_H);
	}

public:
	int anim = 0;
	int spawntick = 0;
	void Anim()
	{
		animtick++;

		if (animtick < 10)
		{
			anim += 50;
		}
		if (animtick > 60)
		{
			RandomizePos();

			animtick = 0;
			anim = 0;
		}
		

	}
};


Player player;
Effect effect;

void GameUpdate()
{
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		player_posx += 2;
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		player_posx -= 2;
	}
	if( CheckHitKey( KEY_INPUT_DOWN ) ){
		player_posy += 2;
	}
	if( CheckHitKey( KEY_INPUT_UP ) ){
		player_posy -= 2;
	}

	player.Anim();

	effect.Anim();

	

	/*anim += 50;
	if(anim >= 100)
	{
		anim = 0;
	}*/
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------

void GameRender()
{
	//DrawGraph( player_posx, player_posy, player_image, TRUE );
	DrawRectGraph(player_posx, player_posy, player.anim, 0, 50, 50, player_image, TRUE); // display cropped image (used for animation)
	DrawRectGraph(effect_posx, effect_posy, effect.anim, 0, 50, 50, effect_image, TRUE); // display cropped image (used for animation)

	
	

	//DrawGraph( effect_posx, effect_posy, effect_image, TRUE );

	DrawString( 20, 20, "アニメーション", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "十字キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( effect_image );
}

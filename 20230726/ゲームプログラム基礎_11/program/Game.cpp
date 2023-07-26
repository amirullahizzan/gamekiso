#include "Main.h"
#include "Game.h"




int SEvolume;
//bool isRainSoundOn;
//bool isPushSoundOn;

int pushSE;
int rainSE;
int masterVolume;

int rain_x[40];
int rain_y[40];
int rain_speed = 10;
int getRainDuration() { return 80; }
int rain_duration[40];


void GameInit()
{
	SEvolume = 255;
	//isRainSoundOn = true;
	//isPushSoundOn = false;

	rainSE = LoadSoundMem("data/se_rain.mp3");
	pushSE = LoadSoundMem("data/se_push.mp3");
	masterVolume = rainSE;
	PlaySoundMem(rainSE,3);

	for (int i = 0; i < 20; i++)
	{
		rain_duration[i] = getRainDuration();
		rain_x[i] = GetRand(SCREEN_W);
		rain_y[i] = GetRand(SCREEN_H/2);
	}
}

//int GetPushSound_DisplayTimer(){ return 80; }
//int PushSound_DisplayTimer = 80;

void GameUpdate()
{
	if( PushHitKey( KEY_INPUT_F1 ) && !CheckSoundMem(rainSE))
	{
		PlaySoundMem(rainSE, 3);
	}
	if( PushHitKey( KEY_INPUT_F2 ) )
	{
		StopSoundMem(rainSE);
	}

	if( PushHitKey( KEY_INPUT_SPACE ) && !CheckSoundMem(pushSE))
	{
		PlaySoundMem(pushSE, 2);
	}

	if( CheckHitKey( KEY_INPUT_RIGHT ) && SEvolume < 255)
	{
		SEvolume++;
		ChangeVolumeSoundMem(SEvolume, rainSE);
		ChangeVolumeSoundMem(SEvolume, pushSE);
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) && SEvolume > 0 )
	{
		SEvolume--;
		ChangeVolumeSoundMem(SEvolume, rainSE);
		ChangeVolumeSoundMem(SEvolume, pushSE);
	}
}




void DrawRain()
{
	for (int i = 0; i < 20; i++)
	{
		rain_x[i]+= rain_speed;
		rain_y[i]+= rain_speed;
		DrawLine(rain_x[i], rain_y[i], rain_x[i] + 10, rain_y[i] + 20, GetColor(200, 200, 255), 1);
		if (rain_duration[i] > getRainDuration())
		{
			rain_x[i] = GetRand(SCREEN_W);
			rain_y[i] = GetRand(SCREEN_H / 2);
			rain_duration[i] = getRainDuration();
		}
	}
}

void GameRender()
{
	DrawString( 20, 20, "スペース：ＳＥ（単発）再生", GetColor( 255, 255, 255 ) );
	DrawString( 20, 60, "Ｆ１キー：ＳＥ（ループ）再生", GetColor( 255, 255, 255 ) );
	DrawString( 20, 80, "Ｆ２キー：ＳＥ（ループ）停止", GetColor( 255, 255, 255 ) );

	DrawString( 20, 120, "←→キー：ボリューム変更", GetColor( 255, 255, 255 ) );

	DrawFormatString(20,140,GetColor(255,255,100), "音量 : %03d", SEvolume);
	DrawFormatString(20,280,GetColor(255,255,100), "Master Volume : %03d", masterVolume);


	if (CheckSoundMem(pushSE))
	{
		DrawString(20, 180, "SE再生中", GetColor(100, 180, 255));
	}
	if (CheckSoundMem(rainSE))
	{
		DrawString(20, 200, "SEループを再生中", GetColor(100, 220, 255));
	}

	DrawRain();
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	InitSoundMem();
}

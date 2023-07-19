#include "Main.h"
#include "Game.h"
#include <iostream>
#include <thread>
#include <chrono>

const int MaxVolume = 255;
int bgmvolume = 255;




//void MyCoroutine()
//{
//	// Coroutine code here
//	std::cout << "Coroutine started\n";
//
//	// Simulating some work
//	std::this_thread::sleep_for(std::chrono::seconds(2));
//
//	std::cout << "Coroutine finished\n";
//}

void GameInit()
{
	//std::cout << "Before coroutine\n";

	//// Start the coroutine in a separate thread
	//std::thread coroutineThread(MyCoroutine);

	//// Continue executing the main code

	//std::cout << "After coroutine start\n";

	//// Wait for the coroutine thread to finish
	//coroutineThread.join();

	//std::cout << "After coroutine finished\n";

}



void GameUpdate()
{
	if( PushHitKey( KEY_INPUT_F1 ) && CheckMusic() == false)
	{
		PlayMusic("data/bgm_sample.mp3",3); //DX_PLAYTYPE_LOOP (3)
		SetVolumeMusic(bgmvolume);

	}
	if( PushHitKey( KEY_INPUT_F2 ) )
	{
		StopMusic();
	}

	if (CheckHitKey(KEY_INPUT_LEFT) && bgmvolume > 0)
	{
		bgmvolume--;
		SetVolumeMusic(bgmvolume);
	}
	if( CheckHitKey( KEY_INPUT_RIGHT ) && bgmvolume < 255)
	{
		bgmvolume++;
		SetVolumeMusic(bgmvolume);

	}

}






bool isGame = false;

void GameRender()
{

	

	isGame = true;
	if(isGame)
	{
		DrawString(20, 20, "‚e‚PƒL[F‚a‚f‚lÄ¶", GetColor(255, 255, 255));
		DrawString(20, 40, "‚e‚QƒL[F‚a‚f‚l’âŽ~", GetColor(255, 255, 255));

		DrawString(20, 60, "©¨ƒL[Fƒ{ƒŠƒ…[ƒ€•ÏX", GetColor(255, 255, 255));

		DrawFormatString(20, 80, GetColor(220, 220, 20), "‰¹—Ê@F %d", bgmvolume);
		if (CheckMusic())
		{
			DrawString(20, 120, "Ä¶’†‚Å‚·", GetColor(140, 220, 255));
		}
	}
	

}
//---------------------------------------------------------------------------------
//	I—¹ˆ—
//---------------------------------------------------------------------------------
void GameExit()
{
}

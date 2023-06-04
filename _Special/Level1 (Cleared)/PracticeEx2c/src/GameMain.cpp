#include "WinMain.h"

// =====================================================
//	グローバル変数
//	複数の関数で共通して使いたい変数はここに書く
// =====================================================



struct Board
{
public : 
	int xpos[9] = { 5,15,25,35,45,55,65,75,85 };
	int gapmult = 6;
	void DrawGridVertical()
	{
		//int grid[9] = {};
		
		int ypos = 0;
		int xpos2[9] = { 5,15,25,35,45,55,65,75,85 };
		int ypos2 = WINDOW_H;
	
		int TopOffset = 20;
		int LeftOffset = 0;

		for (int i = 0;i<9;i++)
		{
			DrawLine((xpos[i]* gapmult), 10+TopOffset + ypos, (xpos2[i] * gapmult), ypos2 - TopOffset, BLACK, 3);
		}
	}

	
	int ypos[9] = { 5,15,25,35,45,55,65,75,85 };
	void DrawGridHorizontal()
	{
		
		int xpos = 0;
		int ypos2[9] = { 5,15,25,35,45,55,65,75,85 };
		int xpos2 = WINDOW_W;
		//	int gapmult = 6;
		int LeftOffset = 30;
		int TopOffset = 0;
		for (int i = 0; i < 9; i++)
		{
			DrawLine(LeftOffset + xpos, (ypos[i] * gapmult)+TopOffset, xpos2 - 20, (ypos2[i] * gapmult), BLACK, 3);
		}
	}

	void DrawKomaWhite()
	{
		DrawCircle((xpos[4]*gapmult) - 30, (ypos[4] * gapmult)-30, 25, WHITE, 1, 1);
		DrawCircle((xpos[5]*gapmult) - 30, (ypos[5] * gapmult)-30, 25, WHITE, 1, 1);
	}

	void DrawKomaBlack()
	{
		DrawCircle((xpos[4] * gapmult) - 30, (ypos[5] * gapmult) - 30, 25, BLACK, 1, 1);
		DrawCircle((xpos[5] * gapmult) - 30, (ypos[4] * gapmult) - 30, 25, BLACK, 1, 1);
	}


};

void GameInit()
{


}
// =====================================================
//		更新
//	ゲームが終了されるまで実行される関数
//	1秒間に約60回呼ばれる
//	1フレームで行う処理をここに書く
// =====================================================
void GameUpdate()
{


}
// =====================================================
//		描画
//	ゲームが終了されるまで実行される関数
//	1秒間に約60回呼ばれる
//	GameUpdate関数が実行された後に実行される関数
// =====================================================
Board board;
void GameDraw()
{
	board.DrawGridVertical();
	board.DrawGridHorizontal();
	board.DrawKomaWhite();
	board.DrawKomaBlack();

}
// =====================================================
//		終了
//	ゲームが終了する前に1回だけ実行される関数
//	何か最後に後片付けを行うときに使う
// =====================================================
void GameExit()
{


}

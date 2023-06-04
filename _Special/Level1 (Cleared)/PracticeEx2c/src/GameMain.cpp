#include "WinMain.h"

// =====================================================
//	�O���[�o���ϐ�
//	�����̊֐��ŋ��ʂ��Ďg�������ϐ��͂����ɏ���
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
//		�X�V
//	�Q�[�����I�������܂Ŏ��s�����֐�
//	1�b�Ԃɖ�60��Ă΂��
//	1�t���[���ōs�������������ɏ���
// =====================================================
void GameUpdate()
{


}
// =====================================================
//		�`��
//	�Q�[�����I�������܂Ŏ��s�����֐�
//	1�b�Ԃɖ�60��Ă΂��
//	GameUpdate�֐������s���ꂽ��Ɏ��s�����֐�
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
//		�I��
//	�Q�[�����I������O��1�񂾂����s�����֐�
//	�����Ō�Ɍ�Еt�����s���Ƃ��Ɏg��
// =====================================================
void GameExit()
{


}

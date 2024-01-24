#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Hit.h"

#define LINE_MAX	5

char draw_text[LINE_MAX][256];

int color_r;
int color_g;
int color_b;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	FILE* fp = fopen("data/sample.txt", "r");
	if (fp)
	{
		char text[256];

		fgets(text,256,fp);

		sscanf_s(text,"%d,%d,%d",&color_r,&color_g,&color_b);
		for (int i = 0; i < LINE_MAX; i++)
		{
			fgets(draw_text[i], 256, fp);
		}
		fclose(fp);
	}
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	for( int i = 0; i < LINE_MAX; i++ ){
		int r = color_r;
		int g = color_g;
		int b = color_b;

		DrawString( 100, 100 + 20 * i, draw_text[i], GetColor( r, g, b ) );
	}

	DrawString( 16, 16, "�e�L�X�g�t�@�C���̕�����̕`��", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
}

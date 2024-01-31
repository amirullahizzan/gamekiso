#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Hit.h"

//	��̕�����
const char *base_text = {
	"�����͎����ő����܂��B�X�y�[�X�L�[�������Ă��鎞�͑����Ȃ�܂��B",
};

//	�P�F�`��p�̕��������
char draw_text[256]; //storage

//	�������ڂ̕����������̂��𐔂���p�̕ϐ�
int draw_count;

//	��̕�����̒��������Ă����p�̕ϐ�
int base_length;

int autoTextAdvanceTimer;


//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�`��p�̕�����̏�����
	//	�Ƃ肠�����S���ɂO�����Ƃ��܂�
	for( int i = 0; i < 256; i++ ){
		draw_text[i] = 0;
	}
	//	�O�����ڂ���J�n
	draw_count = 0;
	//	��̕�����̒������擾
	base_length = (int)strlen( base_text );
}

void DisplayLetter()
{
	//	�Q�F�`��p���������ɂP���������i�܂��Ō�܂ōs���Ă��Ȃ����j
	if (draw_count < base_length) {

		//	�S�p�����̏ꍇ�͓����������Q�񂨂��Ȃ�
		//	���̂��߂ɍ��̏ꏊ�̕����񂪑S�p�̂P�ڂ��ǂ������ׂ�
		if (IsDBCSLeadByte(base_text[draw_count])) {
			//	�S�p�����������炱�̏���������
			draw_text[draw_count] = base_text[draw_count];
			draw_count++;
		}

		//	base_text �� draw_count �Ԗڂ̒l�� draw_text �ɓ����
		draw_text[draw_count] = base_text[draw_count];
		//	���̏ꏊ�ɐi�߂�
		draw_count++;
	}
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
		autoTextAdvanceTimer++;
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		if (autoTextAdvanceTimer % 3 == 0) { DisplayLetter(); }
	}
	else
	{
		if (autoTextAdvanceTimer % 10 == 0) { DisplayLetter(); }
	}

	//	�E�L�[���������Ƃ�
	//	�i����͉E�L�[�łP�������₵�Ă��܂��������ő����܂��̂ł��̔���͕ς��܂��j
	if( PushHitKey( KEY_INPUT_RIGHT ) ){

		DisplayLetter();
	}

	//	���L�[���������Ƃ�
	if( PushHitKey( KEY_INPUT_LEFT ) ){
		//	�ŏ����當����̕`������܂�
		draw_count = 0;
		//	�`��p�����������S���O�ɂ��܂�
		for( int i = 0; i < 256; i++ ){
			draw_text[i] = 0;
		}
	}
}

//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	clsDx();

	//	��̕���������̂܂ܕ`��
	DrawString( 100, 100, base_text, GetColor( 255, 255, 0 ) );

	//	�t�H���g�̍���
	int h = GetFontSize();
	//	��̕������`�悵���Ƃ��̒���
	int base_w = GetDrawStringWidth( base_text, -1 );
	//	��̕�����̉��ɐ�������
	DrawLine( 100, 100 + h, 100 + base_w, 100 + h, GetColor( 255, 255, 0 ) );


	//	�P�������̕�
	//	�R�F�`��p���������̕��̕�����̕`��
	//	���F�̕�����̕`��
	DrawString( 100, 200, draw_text, GetColor( 0, 255, 255 ) ); // BLUE
	//	��̕������`�悵���Ƃ��̒���
	base_w = GetDrawStringWidth(base_text, draw_count);
	//	��̕�����̉��ɐ�������
	DrawLine(100, 200 + h, 100 + base_w, 200 + h, GetColor(0, 255, 255));

	DrawString( 20, 20, "���b�Z�[�W�̕`��i�����ŕ����𑝂₵�Ă����܂��j", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "�X�y�[�X�L�[�F���₷�X�s�[�h�𑬂�", GetColor( 255, 255, 255 ) );

	DrawString( 100, 180, "������̒����ɍ��킹�ĉ���������", GetColor( 255, 255, 255 ) );
	DrawString( 100, 280, "�����񂪉E���獶�ɗ���悤��", GetColor( 255, 255, 255 ) );

	//GREEN
	//	��̕������`�悵���Ƃ��̒���
	base_w = GetDrawStringWidth(base_text, -1); //get the full provided sentence
	int draw_w = GetDrawStringWidth(draw_text, -1); //get the current storage instead of the full provided sentence.
	//printfDx("string width %d ", base_w2);
	//	�ΐF�̕�����̕`��i����͐��F�̕�����Ɠ������������Ă��܂��j
	
	DrawString( 
		100+base_w -(draw_w),
		300, draw_text, GetColor(0, 255, 0)
	); //GREEN

	//	�ڈ��̏c���i��̕�����̍Ōォ��c�ɐ��̕`��j
	DrawLine( 100 + base_w, 0, 100 + base_w, SCREEN_H, GetColor( 150, 150, 150 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
}

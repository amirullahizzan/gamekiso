#include "Main.h"
#include "Game.h"



//	�J�E���g�P�p�̕ϐ��i�������l������悤�Ȃ̂� int �^�j
//	��ɂP�����Ă����ϐ�


//	�J�E���g�Q�p�̕ϐ��i���E�L�[�łP���₵����P���炵���肷��j


class Counter1
{
public:
	int count1COLOR = GREEN;
	int count1 = 200;
	void Draw()
	{
		DrawString(100, 60, "�J�E���g�P�@�F��Ɍ��葱����i�O�܂Łj", GetColor(255, 255, 0));
		DrawString(100, 80, "�X�y�[�X�L�[�F�Q�O�O�ɖ߂�", GetColor(255, 255, 0));
		DrawString(100, 100, "���������ɐF��ς��Ă݂�i�Ⴆ�Δ����ɂȂ�����΂��物�F�Ɂj", GetColor(255, 255, 0));

		//	�J�E���g�P�p�̗΂̎l�p�i�΂̎l�p�̎�O�ɘg��`�������̂ł�������ɕ`�悵�܂��j
		DrawFillBox(100, 120, 100 + count1, 140, count1COLOR);
		//	�΂̎l�p�̂Ƃ���ɖڈ��Ƃ��Ęg�����̎l�p
		DrawLineBox(100, 120, 300, 140, GetColor(255, 255, 255));
	}

	void Update()
	{
		count1--;
		//	�J�E���g�P�̒l���Q�O�O�𒴂�����
		if (count1 < 100) {
			//	�Q�O�O�ɂ���
			count1COLOR = YELLOW;
		}
		if (count1 < 0) {
			//	�Q�O�O�ɂ���
			count1 = 0;
		}
		//	�X�y�[�X�L�[����������J�E���g�P�̒l���O�ɂ��܂��i PushHitKey�F�������u�Ԃ��� if ���ɓ���܂��j
		if (PushHitKey(KEY_INPUT_SPACE)) {
			count1 = 200;
			count1COLOR = GREEN;
		}

	}
};

class Counter2
{
public:
	int count2;
	void Draw()
	{
		//	�J�E���g�Q�p
		DrawString(100, 180, "�J�E���g�Q�@�F���E�L�[�Œl�̑����i�O�`�P�O�O�j", GetColor(255, 255, 255));

		//	�J�E���g�Q�̒l���g���Đ��F�̎l�p�̕`��
		DrawFillBox(100, 200, 100 + count2, 220, GetColor(0, 255, 255));
		//	�J�E���g�Q�̖ڈ��̘g�̕`��
		DrawLineBox(100, 200, 200, 220, GetColor(255, 255, 255));

		DrawString(100, 230, "�o�[�̌����ڂ�ς��Ă݂�", GetColor(0, 255, 255));
	}
	void Move()
	{
		//	�E�L�[�������Ă���Ƃ��i CheckHitKey�F�����Ă���� if ���ɓ���܂��j
		if (CheckHitKey(KEY_INPUT_RIGHT)) {
			//	�J�E���g�Q�̒l���P���₷
			count2++;
			//	�J�E���g�Q�̒l�͂P�O�O���傫���Ȃ�Ȃ�
			if (count2 > 100) {
				count2 = 100;
			}
		}
		//	���L�[�������Ă���Ƃ���
		if (CheckHitKey(KEY_INPUT_LEFT)) {
			//	�J�E���g�Q�̒l���P���炷
			count2--;
			//	�J�E���g�Q�̒l�͂O��菬�����Ȃ�Ȃ�
			if (count2 < 0) {
				count2 = 0;
			}
		}
	}
};

Counter1 counter1;
Counter2 counter2;

class Slider
{
public:
	int slider_x;
	void Draw()
	{
		DrawLine(100, 260, 200, 260, LIGHTBLUE);
		DrawCircle(slider_x, 260, 5, LIGHTBLUE, 1, 1);
	}
	void SliderManager()
	{
		slider_x = 100 + counter2.count2;
	}
};

Slider slider;
//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	slider.slider_x = 0;
	counter1.count1 = 200;
	counter2.count2 = 0;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------

void GameUpdate()
{
	counter1.Update();
	counter2.Move();
	slider.SliderManager();
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------

void GameRender()
{
	slider.Draw();
	counter1.Draw();
	counter2.Draw();
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
}


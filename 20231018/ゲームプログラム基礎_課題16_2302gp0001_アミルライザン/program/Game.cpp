#include "Main.h"
#include "Game.h"
#include "Float2.h"
#include "Hit.h"

//	�I�����ڂɎg��������͂R��
#define TEXT_MAX	3

//	�I�𕶎���R��
const char *sample_text[TEXT_MAX] = {
	"�͂��߂���",
	"��������",
	"�Q�[���̐ݒ�",
};
//	���̕�����̍��W�R��
Float2 pos[TEXT_MAX];

Float2 text_size[TEXT_MAX];
int text_color[TEXT_MAX];
int pos_offset[TEXT_MAX];

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//ChangeFont("UD �f�W�^�� ���ȏ��� NK-B");

	for( int i = 0; i < TEXT_MAX; i++ ){
		//	�Ƃ肠���������w���W����ʂ̐^�񒆂ɂ��܂�
		pos_offset[i] = GetDrawStringWidth(sample_text[i], -1, 0);

		pos[i].x = SCREEN_W / 2 - pos_offset[i] / 2;
		//	�x���W�� 300 ���� 30 �����炵�Ă��܂�
		pos[i].y = 300.0f + 30.0f * i;
		text_size[i].x = GetDrawStringWidth(sample_text[i], -1, 0);
		text_size[i].y = GetFontSize();
	}
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	�}�E�X���W���擾
	Float2 mouse;

	mouse.x = GetMouseX();
	mouse.y = GetMouseY();

	for (int i = 0;i<TEXT_MAX;i++)
	{
		text_color[i] = GetColor(255, 255, 255);

	if (CheckPointBoxHit(mouse,pos[i],text_size[i] ) )
	{
		text_color[i] = GetColor(255,255,0);
	}

	}

}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
int text_flicker = 255;
int text_flickerMode = 0;

void GameRender()
{
	//	��ʂ̐^�񒆂Ɋ�̐��̕`��
	DrawLine( SCREEN_W / 2, 0, SCREEN_W / 2, SCREEN_H, GetColor( 255, 255, 255 ) );

	//	���j���[���ڗp�̕������`��
	for( int i = 0; i < TEXT_MAX; i++ ){
		DrawStringF( pos[i].x +2, pos[i].y, sample_text[i], GetColor(0,0,0));
		DrawStringF( pos[i].x, pos[i].y, sample_text[i], text_color[i]);
		//DrawCircle(pos[i].x, pos[i].y,25,1,1);
	}

	//	�u�}�E�X�őI���v������𔼓����ŕ`��
	switch (text_flickerMode)
	{
	case 1: 
		text_flicker+=5;
		if (text_flicker >= 255)
		{
			text_flickerMode = 0;
		}
		break;
	default:
		text_flicker-= 5;
		if (text_flicker <= 0)
		{
		text_flickerMode = 1;
		}
		break;
	}


	SetDrawBlendMode( DX_BLENDMODE_ALPHA, text_flicker );
	DrawString( 100+2, 400, "�}�E�X�őI��", GetColor( 0, 0, 0 ) );
	DrawString( 100, 400, "�}�E�X�őI��", GetColor( 255, 255, 255 ) );
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );

	DrawString( 16, 16, "sample_tex �𒆉��\����", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "���@�}�E�X�����镶����̐F��ύX", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "�u�}�E�X�őI���v������𓧖��x��ύX���ē_��", GetColor( 255, 255, 255 ) );
	DrawString( 16, 64, "���ꂼ��̕�����ɉe�����Ă݂�", GetColor( 255, 255, 255 ) );

}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
}

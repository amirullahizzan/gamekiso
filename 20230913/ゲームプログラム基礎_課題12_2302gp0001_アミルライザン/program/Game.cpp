#include "Main.h"
#include "Game.h"

//	�^�C�g���֌W�̊֐����Ăׂ�悤�ɂ��邽�߂�
#include "Title.h"
//	�X�e�[�W�֌W�̊֐����Ăׂ�悤�ɂ��邽�߂�
#include "Stage.h"
//GameClear
#include "Clear.h"

//	���ǂ��̃V�[���ɂ���̂�������p�̕ϐ�
int scene_num;
//	���ɍs�������V�[���ԍ�������p�̕ϐ�
int scene_next;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�ŏ��̓^�C�g������J�n
	scene_num = SCENE_TITLE;
	scene_next = SCENE_TITLE;

	//	���ꂼ��̃V�[���̃f�[�^�̓ǂݍ���
	TitleLoad();	//	�^�C�g��
	StageLoad();	//	�X�e�[�W
	GameClearLoad();	//	GameClear

	//	�^�C�g����ʂ̏�����
	TitleInit();
	StageInit();
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	���̃V�[���ԍ��Ǝ��ɍs�������V�[���ԍ���
	//	����Ă����炱�̒��̏��������܂�
	if( scene_num != scene_next ){
		//	���̃V�[���ԍ������̔ԍ��ɐ؂�ւ���
		scene_num = scene_next;
		//	���̃V�[���ɍ��킹���������֐����Ăт܂�
		switch( scene_num ){
		case SCENE_TITLE:
			TitleInit();
			break;
		case SCENE_STAGE:
			StageInit();
			break;
		case SCENE_CLEAR : 
			GameClearInit();
			break;
		}
	}

	//	���̃V�[���ԍ��ɍ��킹���X�V�������Ă�
	switch( scene_num ){
	case SCENE_TITLE:
		TitleUpdate();
		break;
	case SCENE_STAGE:
		StageUpdate();
		break;
	case SCENE_CLEAR:
		GameClearUpdate();
		break;
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	���̃V�[���ԍ��ɍ��킹���`�揈�����Ă�
	switch( scene_num ){
	case SCENE_TITLE:
		TitleRender();
		break;
	case SCENE_STAGE:
		StageRender();
		break;
	case SCENE_CLEAR:
		GameClearRender();
		break;
	}
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	TitleExit();
	StageExit();
}

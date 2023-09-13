#include "Main.h"
#include "Game.h"

#include "Title.h"
#include "Stage.h"

int scene_num;
int scene_next;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	scene_num = SCENE_TITLE;
	scene_next = SCENE_TITLE;

	TitleLoad();
	StageLoad();

	TitleInit();
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//so it doesnt loop
	if( scene_num != scene_next )
	{
		//stopping the loop
		scene_num = scene_next;
		switch( scene_num ){
		case SCENE_TITLE:
			TitleInit();
			//executes when start from Scene_Stage
			break;
		case SCENE_STAGE:
			StageInit();
			break;
		}
	}

	switch( scene_num ){
	case SCENE_TITLE:
		TitleUpdate();
		break;
	case SCENE_STAGE:
		StageUpdate();
		break;
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	switch( scene_num ){
	case SCENE_TITLE:
		TitleRender();
		break;
	case SCENE_STAGE:
		StageRender();
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

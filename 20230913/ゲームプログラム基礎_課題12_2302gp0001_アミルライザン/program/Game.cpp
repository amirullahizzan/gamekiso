#include "Main.h"
#include "Game.h"

//	タイトル関係の関数を呼べるようにするために
#include "Title.h"
//	ステージ関係の関数を呼べるようにするために
#include "Stage.h"
//GameClear
#include "Clear.h"

//	今どこのシーンにいるのかを見る用の変数
int scene_num;
//	次に行きたいシーン番号を入れる用の変数
int scene_next;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	最初はタイトルから開始
	scene_num = SCENE_TITLE;
	scene_next = SCENE_TITLE;

	//	それぞれのシーンのデータの読み込み
	TitleLoad();	//	タイトル
	StageLoad();	//	ステージ
	GameClearLoad();	//	GameClear

	//	タイトル画面の初期化
	TitleInit();
	StageInit();
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	今のシーン番号と次に行きたいシーン番号が
	//	違っていたらこの中の処理をします
	if( scene_num != scene_next ){
		//	今のシーン番号を次の番号に切り替えて
		scene_num = scene_next;
		//	そのシーンに合わせた初期化関数を呼びます
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

	//	今のシーン番号に合わせた更新処理を呼ぶ
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
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	今のシーン番号に合わせた描画処理を呼ぶ
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
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	TitleExit();
	StageExit();
}

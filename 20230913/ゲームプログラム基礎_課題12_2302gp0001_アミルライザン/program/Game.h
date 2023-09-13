#pragma once

#define SCREEN_W	800
#define SCREEN_H	450

void GameInit();	//	初期化処理
void GameUpdate();	//	更新処理
void GameRender();	//	描画処理
void GameExit();	//	終了処理

//	各シーンの番号
enum {
	SCENE_TITLE,	//	０：タイトル
	SCENE_STAGE,	//	１：ステージ
	SCENE_CLEAR,	//	２：ステージ
};

//	scene_next を外のファイルで使えるようにするための外部参照宣言
//	extern：外部参照宣言
//	extern で記述された変数は実態ではないので
//	必ずどこかに宣言をしておく必要があります
extern int scene_next;

extern int stage_frame;


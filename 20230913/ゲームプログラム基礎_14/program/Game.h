#pragma once

#define SCREEN_W	800
#define SCREEN_H	450

void GameInit();	//	初期化処理
void GameUpdate();	//	更新処理
void GameRender();	//	描画処理
void GameExit();	//	終了処理

enum {
	SCENE_TITLE,
	SCENE_STAGE,
};

extern int scene_next;

#pragma once

#define SCREEN_W	800
#define SCREEN_H	450

void GameInit();	//	‰Šú‰»ˆ—
void GameUpdate();	//	XVˆ—
void GameRender();	//	•`‰æˆ—
void GameExit();	//	I—¹ˆ—

enum {
	SCENE_TITLE,
	SCENE_STAGE,
};

extern int scene_next;

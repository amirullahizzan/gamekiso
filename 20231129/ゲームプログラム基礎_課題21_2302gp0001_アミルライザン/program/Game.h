#pragma once

//	画面サイズ用の定数
#define SCREEN_W	800		//	幅
#define SCREEN_H	450		//	高さ

//	プレイヤーやＮＰＣのいるステージの範囲
#define STAGE_W		500		//	幅
#define STAGE_H		450		//	高さ

//	ステージの左側は 300 の事です
#define STAGE_LEFT	( SCREEN_W - STAGE_W )

void GameInit();	//	初期化処理
void GameUpdate();	//	更新処理
void GameRender();	//	描画処理
void GameExit();	//	終了処理

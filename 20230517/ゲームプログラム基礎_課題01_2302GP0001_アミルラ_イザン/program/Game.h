#pragma once

#define SCREEN_W	800
#define SCREEN_H	450
#define GREEN GetColor( 0, 255, 0 )
#define YELLOW GetColor( 200, 200, 0 )
#define LIGHTBLUE GetColor( 120, 200, 225 )

void GameInit();	//	����������
void GameUpdate();	//	�X�V����
void GameRender();	//	�`�揈��
void GameExit();	//	�I������

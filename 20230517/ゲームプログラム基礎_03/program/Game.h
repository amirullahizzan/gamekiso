#pragma once

#define SCREEN_W	800
#define SCREEN_H	450
#define GREEN GetColor( 0, 255, 0 )
#define BLUE GetColor(0, 0, 255)

void GameInit();	//	����������
void GameUpdate();	//	�X�V����
void GameRender();	//	�`�揈��
void GameExit();	//	�I������

#pragma once

//	��ʃT�C�Y�p�̒萔
#define SCREEN_W	800		//	��
#define SCREEN_H	450		//	����

//	�v���C���[��m�o�b�̂���X�e�[�W�͈̔�
#define STAGE_W		500		//	��
#define STAGE_H		450		//	����

//	�X�e�[�W�̍����� 300 �̎��ł�
#define STAGE_LEFT	( SCREEN_W - STAGE_W )

void GameInit();	//	����������
void GameUpdate();	//	�X�V����
void GameRender();	//	�`�揈��
void GameExit();	//	�I������

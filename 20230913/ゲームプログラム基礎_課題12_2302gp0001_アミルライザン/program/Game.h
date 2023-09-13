#pragma once

#define SCREEN_W	800
#define SCREEN_H	450

void GameInit();	//	����������
void GameUpdate();	//	�X�V����
void GameRender();	//	�`�揈��
void GameExit();	//	�I������

//	�e�V�[���̔ԍ�
enum {
	SCENE_TITLE,	//	�O�F�^�C�g��
	SCENE_STAGE,	//	�P�F�X�e�[�W
	SCENE_CLEAR,	//	�Q�F�X�e�[�W
};

//	scene_next ���O�̃t�@�C���Ŏg����悤�ɂ��邽�߂̊O���Q�Ɛ錾
//	extern�F�O���Q�Ɛ錾
//	extern �ŋL�q���ꂽ�ϐ��͎��Ԃł͂Ȃ��̂�
//	�K���ǂ����ɐ錾�����Ă����K�v������܂�
extern int scene_next;

extern int stage_frame;


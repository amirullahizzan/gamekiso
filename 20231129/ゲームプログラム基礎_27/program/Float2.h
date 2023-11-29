#pragma once

//---------------------------------------------------------------------------------
//	Float2 �N���X
//---------------------------------------------------------------------------------
class Float2
{
public:
	float x;
	float y;

	Float2() {};									//	�R���X�g���N�^
	Float2(float _x, float _y);									//	�R���X�g���N�^
	void clear();								//	�[��������
	void set( float x, float y );				//	�l�̃Z�b�g
	void set( Float2 v );
};

//	�Q�� Float2 �̋��������߂�
float GetFloat2Distance( Float2 pos1, Float2 pos2 );

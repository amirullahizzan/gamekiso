#pragma once

//---------------------------------------------------------------------------------
//	Float2 クラス
//---------------------------------------------------------------------------------
class Float2
{
public:
	float x;
	float y;

	Float2() {};									//	コンストラクタ
	Float2(float _x, float _y);									//	コンストラクタ
	void clear();								//	ゼロ初期化
	void set( float x, float y );				//	値のセット
	void set( Float2 v );
};

//	２つの Float2 の距離を求める
float GetFloat2Distance( Float2 pos1, Float2 pos2 );

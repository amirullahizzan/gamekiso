#include "Main.h"
#include "Game.h"
#include "Hit.h"

//	今回は半径がタイプごとに変わるのでこの定数は使いません
#define NPC_RADIUS	25.0f

//	今回はスピードがタイプごとに変わるのでこの定数は使いません
#define NPC_SPEED	3.0f

//	ＮＰＣのタイプ名は画像に合わせてサイズが分かる名前にしています
enum {
	TYPE_NORMAL,	//	０：いつもの大きさ
	TYPE_LARGE,		//	１：大きい画像
	TYPE_SMALL,		//	２：小さい画像

	TYPE_MAX		//	３：全部で３つのタイプがあります
};

//	使う画像を読み込んで番号を入れておく用の変数
int load_image[TYPE_MAX];

//	ＮＰＣ用の変数
int npc_type;		//	タイプ
int npc_image;		//	画像
float npc_x;		//	Ｘ座標
float npc_y;		//	Ｙ座標
float npc_rot;		//	向き（度）
int npc_frame;		//	一定時間を数える用の変数（減らしていこうと思っています）
int npc_speed;		//	一定時間を数える用の変数（減らしていこうと思っています）
int npc_radius;		//	一定時間を数える用の変数（減らしていこうと思っています）

//	タイプごとの登場時間用のデータ
int npc_frame_data[TYPE_MAX] = {
	120,	//	TYPE_NORMAL	：２秒
	 60,	//	TYPE_ORANGE	：１秒
	180,	//	TYPE_RED	：３秒
};

int npc_radius_data[TYPE_MAX] = {
	25,	//	TYPE_NORMAL	：２秒
	 40,	//	TYPE_ORANGE	：１秒
	15,	//	TYPE_RED	：３秒
};

float npc_speed_data[TYPE_MAX] =
{
	3,2,8
};

//---------------------------------------------------------------------------------
//	ＮＰＣのタイプや座標とかを変更する関数
//---------------------------------------------------------------------------------
void ResetNPC()
{
	//	タイプの変更前の値をとっておきます
	int old_type = npc_type;

	//	新しいタイプと古いタイプが同じだったらくり返す
	while( npc_type == old_type ){
		//	ＮＰＣのタイプを変更
		npc_type = rand() % TYPE_MAX;
	}

	//	タイプに合わせた画像の設定
	npc_image = load_image[npc_type];
	//	座標をランダムに
	if (GetMouseX() > SCREEN_W/2) { npc_x = GetRand(SCREEN_W / 2); }
	else { npc_x = GetRand(SCREEN_W - SCREEN_W / 2) + SCREEN_W / 2; }

	npc_y = GetRand( SCREEN_H );
	//	タイプに合わせた登場時間の設定
	npc_frame = npc_frame_data[npc_type];
	npc_speed = npc_speed_data[npc_type];
	npc_radius = npc_radius_data[npc_type];
}

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	for( int i = 0; i < TYPE_MAX; i++ ){
		//	文字列を入れる用の変数（ char：文字列型）２５６文字分
		char text[256];
		//	"data/npc0.bmp" という文字列を text に入れます
		sprintf( text, "data/npc%d.bmp", i );
		//	その文字列を使って画像の読み込み関数を呼びます
		load_image[i] = LoadGraph( text );
	}

	//	最初のタイプを設定
	npc_type = TYPE_NORMAL;

	//	タイプに合わせた画像番号を設定します
	npc_image = load_image[npc_type];

	//	初期座標や向きの設定
	npc_x = SCREEN_W / 2;
	npc_y = SCREEN_H / 2;
	npc_rot = 0.0f;
	//	タイプに合わせた登場時間の設定
	npc_frame = npc_frame_data[npc_type];
	npc_speed = npc_speed_data[npc_type];
	npc_radius = npc_radius_data[npc_type];
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	常に回転する
	npc_rot += npc_speed;

	//	時間を減らしていく
	npc_frame--;
	//	時間が０になったら
	if( npc_frame <= 0 ){
		//	ＮＰＣ再設定
		ResetNPC();
	}

	//	マウスクリックで
	if( PushMouseInput() ){
		//	マウスの座標を取得
		int mouse_x = GetMouseX();
		int mouse_y = GetMouseY();
		//	マウス座標（点）とＮＰＣ（円）で当たり判定
		if( CheckPointCircleHit( mouse_x, mouse_y, npc_x, npc_y, npc_radius ) ){
			//	ＮＰＣの再設定
			ResetNPC();
		}
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	マウス座標とＮＰＣの登場座標の目安で画面の真ん中に線を描画しています
	DrawLine( SCREEN_W / 2, 0, SCREEN_W / 2, SCREEN_H, GetColor( 50, 50, 50 ) );

	//	ＮＰＣの描画
	DrawRotaGraphF( npc_x, npc_y, 1.0f, TO_RADIAN( npc_rot ), npc_image, TRUE );
	//	ＮＰＣの座標と半径を使って円を描画
	DrawCircleAA( npc_x, npc_y, npc_radius, 100, GetColor( 255, 255, 0 ), FALSE );

	DrawString( 20,  20, "ＮＰＣクリック：別タイプのＮＰＣをランダムな場所に", GetColor( 255, 255, 255 ) );
	DrawString( 20,  40, "→　ＮＰＣの登場場所は、マウスが画面左の時は画面右に、マウスが画面右の時は画面左に", GetColor( 255, 255, 0 ) );
	DrawString( 20,  60, "ＮＰＣは一定時間がたったらクリックされた時と同様に別タイプに変更", GetColor( 255, 255, 255 ) );
	DrawString( 20,  80, "→　登場している時間はタイプによって違う", GetColor( 255, 255, 255 ) );
	DrawString( 20, 100, "→　半径や回転スピードもタイプによって違う", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	for( int i = 0; i < TYPE_MAX; i++ ){
		DeleteGraph( load_image[i] );
	}
}

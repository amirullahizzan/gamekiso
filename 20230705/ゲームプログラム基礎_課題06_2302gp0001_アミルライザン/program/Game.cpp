#include "Main.h"
#include "Game.h"

//	ブロックの大きさ
#define BLOCK_SIZE	50
//	四角を並べる数
#define MAP_W		16		//	横
#define	MAP_H		 9		//	縦

//	マップ用の変数（２次元配列で）：宣言したついでに決まった数値を設定します
int map[MAP_H][MAP_W] =
{
	{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,0,0,0,0,0,0,1,1,1,0,1,1,1,0,2 },
	{ 2,0,0,0,0,0,0,1,0,0,0,0,0,1,0,2 },
	{ 2,0,0,0,0,0,0,1,0,0,0,0,0,1,0,2 },
	{ 2,0,0,0,0,0,0,1,1,1,1,1,1,1,0,2 },
	{ 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
	{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
};
//	ブロック画像用の変数（０：緑　１：灰色　２：水色）
int block_image[3];

int num;
int player_state = map[2][2];



//	プレイヤー画像
int player_image;
int enemy_image;
//	プレイヤーが（２次元配列的に）何番目のところにいるのか（座標ではないです）
int player_w;	//	横の何番目
int player_h;	//	縦の何番目

int enemy_w;
int enemy_h;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	ブロック画像の読み込み
	block_image[0] = LoadGraph( "data/block0.bmp" );
	block_image[1] = LoadGraph( "data/block1.bmp" );
	block_image[2] = LoadGraph( "data/block2.bmp" );

	//	プレイヤー画像の読み込み
	player_image = LoadGraph( "data/player.bmp" );
	enemy_image = LoadGraph( "data/npc.bmp" );
	//	どこの場所から開始するか（座標ではないくて、画面を５０区切りにした時の何番目のところか）
	player_w = 2;
	player_h = 2;

	enemy_w = 5;
	enemy_h = 6;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
int frame = 0;
int enemyrandomizer = 0;

void GameUpdate()
{
	//	右キーをしたらプレイヤーを１マス右に移動させる

	if (PushHitKey(KEY_INPUT_RIGHT)) 
	{
		//	次に行きたいところがマップの中だったら（配列の数より小さかったら）
		if (player_w + 1 <= MAP_W - 1 && map[player_h][player_w+1] == 0)
		{
			player_w++;
		}
	}
	//	左キー
	if( PushHitKey( KEY_INPUT_LEFT ) )
	{
		//	次に行きたいところ（１マス左）がマップの中だったら（配列の範囲内だったら）
		if( player_w - 1 >= 0 && map[player_h][player_w - 1] == 0){
			//	左に１マス進める（配列的に１マイナス）
			player_w--;
		}
	}
	//	上下キーも
	if( PushHitKey( KEY_INPUT_DOWN ) && map[player_h+1][player_w] == 0){
		if( player_h + 1 <= MAP_H - 1 ){
			player_h++;
		}
	}
	if( PushHitKey( KEY_INPUT_UP ) && map[player_h - 1][player_w] == 0){
		if( player_h - 1 >= 0 ){
			player_h--;
		}
	}

	frame++;
	
	if (frame == 50)
	{
		enemyrandomizer += GetRand(4);

		if (enemyrandomizer == 1 && map[enemy_h][enemy_w + 1] == 0)
		{
			enemy_w += 1;
		}
		else if (enemyrandomizer == 2 && map[enemy_h][enemy_w-1] == 0)
		{
			enemy_w -= 1;
		}
		else if (enemyrandomizer == 3 && map[enemy_h + 1][enemy_w] == 0)
		{
			enemy_h += 1;
		}
		else if (enemyrandomizer == 4 && map[enemy_h - 1][enemy_w] == 0)
		{
			enemy_h -= 1;
		}

		enemyrandomizer = 0;
		frame = 0;
	}

	
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	マップの描画（２次元配列の番号を１個ずつ見ていって、その番号の画像を描画します）
	for( int h = 0; h < MAP_H; h++ ){
		for( int w = 0; w < MAP_W; w++ ){
			//	その場所のマップの番号を取得
			num = map[h][w];
			//	画面のどこに描画するかの座標（ブロックの大きさ分ずらして）
			int x = w * BLOCK_SIZE;
			int y = h * BLOCK_SIZE;
			//	その座標にその番号の画像を描画
			DrawGraph( x, y, block_image[num], TRUE );
		}
	}

	//	プレイヤーの描画（画面のどこに描画するか決める）
	//	→　今のプレイヤーのポイント（ player_w player_h ）が画面的にどこの座標になるか
	int px = player_w * BLOCK_SIZE;
	int py = player_h * BLOCK_SIZE;
	//	そこの座標にプレイヤー画像を描画
	DrawGraph( px, py, player_image, TRUE );

	int ex = enemy_w * BLOCK_SIZE;
	int ey = enemy_h * BLOCK_SIZE;
	DrawGraph(ex, ey, enemy_image, TRUE);


	DrawString( 20, 20, "十字キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "灰色（１：壁っぽい）や青（２：水っぽい）のところは進めない", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( block_image[0] );
	DeleteGraph( block_image[1] );
	DeleteGraph( block_image[2] );

	DeleteGraph( player_image );
}

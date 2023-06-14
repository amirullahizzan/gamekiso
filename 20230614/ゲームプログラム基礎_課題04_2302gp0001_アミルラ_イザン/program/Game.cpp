#include "Main.h"
#include "Game.h"


struct Player
{
	//	プレイヤー画像
	int image;
	//	プレイヤー座標（画面のどこに）
	int posx;
	int posy;
	//	プレイヤー画像のどこから使うのかの画像座標
	int imgx;
	int imgy;

	//	一定時間を数える用の変数
	int frame;

	void Draw()
	{
		DrawRectGraph(posx, posy, imgx, imgy, 50, 50, image, TRUE);
	}

	void Init()
	{
		//	プレイヤー画像の読み込み
		image = LoadGraph("data/player.bmp");
		//	初期座標の設定
		posx = 100;
		posy = 200;
		//	画像のどこからかの初期設定
		imgx = 0;
		frame = 0;
	}

	void Control()
	{
		if (CheckHitKey(KEY_INPUT_RIGHT)) {
			posx += 2;
			imgy = 100;
		}
		if (CheckHitKey(KEY_INPUT_LEFT)) {
			posx -= 2;
			imgy = 50;
		}
		if (CheckHitKey(KEY_INPUT_DOWN)) {
			posy += 2;
			imgy = 0;

		}
		if (CheckHitKey(KEY_INPUT_UP)) {
			posy -= 2;
			imgy = 150;
		}
	}

	void Anim()
	{
		//	プレイヤー用のカウントを増やす
		frame++;
		//	カウントの値が３０以上になったら
		if (frame >= 30)
		{
			//	次に３０を数えるために０にします
			frame = 0;
			//	プレイヤー画像のどこから使うのかの値を変更します
			//	５０増やして次のコマにします
			imgx += 50;
			//	２コマしかないので１００１００以上になったら
			if (imgx >= 100)
			{
				//	０にします
				imgx = 0;
			}
		}
	}

};

struct NPC
{
	//	ＮＰＣ画像
	int image;
	//	ＮＰＣ座標
	int x[5];
	int y[5];

	void Init()
	{
		for (int i = 0;i<5;i++)
		{

		image = LoadGraph("data/npc.bmp");
		x[i] = GetRand(SCREEN_W);
		y[i] = GetRand(SCREEN_H);

		}
	}

	void Draw()
	{
		//	ＮＰＣの描画
		for (int i = 0;i<5;i++)
		{
		DrawGraph(x[i], y[i], image, TRUE);
		}
	}

	void Move()
	{
		for (int i = 0; i < 5; i++)
		{
			x[i] -= 5;
			if (x[i] < -100)
			{
				x[i] = SCREEN_W;
				y[i] = GetRand(400);
			}
		}
	}

};

NPC npc;

struct Effect 
{
	//	エフェクト画像
	int image;
	//	エフェクト座標（画面のどこに）
	int posx;
	int posy;
	//	エフェクト画像のどこからにするのか
	int imgx;
	//	エフェクト用の一定時間数える変数
	int frame;

	void Init()
	{
		for (int i = 0; i < 5; i++)
		{
			image = LoadGraph("data/effect.bmp");
			posx = 300;
			posy = 100;
			imgx = 0;
			frame = 0;
		}
	}

	void Anim()
	{
		//	エフェクト用カウンターを進める
		frame++;
		//	一定時間たったら
		if (frame >= 10) {
			//	次の一定時間を数えるためにリセット
			frame = 0;
			//	そのタイミングで画像のどこを使うかを切り替える
			imgx += 50;
			//	８コマｘ５０の大きさを超えたら
			if (imgx >= 400)
			{
				//	１コマ目の場所から
				imgx = 0;

				//	エフェクトの画面座標をランダムに
				//	今回は座標のランダムは使いません
	//			effect_posx = GetRand( 750 );
	//			effect_posy = GetRand( 400 );
			}
		}
	}

	void Draw()
	{
		for(int i = 0;i<5;i++)
		{
	posx = npc.x[i] + 50;
	posy = npc.y[i];
	DrawRectGraph(posx, posy, imgx, 0, 50, 50, image, TRUE);
		}
	}

};



Player player;
Effect effect;


void GameInit()
{
	player.Init();

	effect.Init();
	
	npc.Init();
	//	ＮＰＣ画像の読み込みと座標の初期設定

}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	十字キーでプレイヤー座標の更新
	player.Control();
	player.Anim();
	
	npc.Move();
	
	effect.Anim();


}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	プレイヤー画像の一部分をプレイヤー座標の場所に描画します
	player.Draw();

	//for()


	//	エフェクト画像の一部分を使った描画
	npc.Draw();
	effect.Draw();
	

	DrawString( 20, 20, "十字キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "→　移動に合わせて向きを変える", GetColor( 255, 255, 0 ) );
	DrawString( 20, 60, "ＮＰＣは画面左に移動（左まで行ったら右から出てくる・Ｙ座標はランダムに）", GetColor( 255, 255, 0 ) );
	DrawString( 20, 80, "→　ＮＰＣの座標に合わせてエフェクト", GetColor( 255, 255, 0 ) );

	DrawString( 20, 120, "→　ＮＰＣを複数表示", GetColor( 50, 190, 200 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player.image );
	DeleteGraph( npc.image );
	DeleteGraph( effect.image );
}

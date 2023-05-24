#include "Main.h"
#include "Game.h"



//	カウント１用の変数（何か数値を入れるようなので int 型）
//	常に１増えていく変数


//	カウント２用の変数（左右キーで１増やしたり１減らしたりする）


class Counter1
{
public:
	int count1COLOR = GREEN;
	int count1 = 200;
	void Draw()
	{
		DrawString(100, 60, "カウント１　：常に減り続ける（０まで）", GetColor(255, 255, 0));
		DrawString(100, 80, "スペースキー：２００に戻る", GetColor(255, 255, 0));
		DrawString(100, 100, "いい感じに色を変えてみる（例えば半分になったら緑から黄色に）", GetColor(255, 255, 0));

		//	カウント１用の緑の四角（緑の四角の手前に枠を描きたいのでこちらを先に描画します）
		DrawFillBox(100, 120, 100 + count1, 140, count1COLOR);
		//	緑の四角のところに目安として枠だけの四角
		DrawLineBox(100, 120, 300, 140, GetColor(255, 255, 255));
	}

	void Update()
	{
		count1--;
		//	カウント１の値が２００を超えたら
		if (count1 < 100) {
			//	２００にする
			count1COLOR = YELLOW;
		}
		if (count1 < 0) {
			//	２００にする
			count1 = 0;
		}
		//	スペースキーを押したらカウント１の値を０にします（ PushHitKey：押した瞬間だけ if 文に入ります）
		if (PushHitKey(KEY_INPUT_SPACE)) {
			count1 = 200;
			count1COLOR = GREEN;
		}

	}
};

class Counter2
{
public:
	int count2;
	void Draw()
	{
		//	カウント２用
		DrawString(100, 180, "カウント２　：左右キーで値の増減（０～１００）", GetColor(255, 255, 255));

		//	カウント２の値を使って水色の四角の描画
		DrawFillBox(100, 200, 100 + count2, 220, GetColor(0, 255, 255));
		//	カウント２の目安の枠の描画
		DrawLineBox(100, 200, 200, 220, GetColor(255, 255, 255));

		DrawString(100, 230, "バーの見た目を変えてみる", GetColor(0, 255, 255));
	}
	void Move()
	{
		//	右キーを押しているとき（ CheckHitKey：押している間 if 文に入ります）
		if (CheckHitKey(KEY_INPUT_RIGHT)) {
			//	カウント２の値を１増やす
			count2++;
			//	カウント２の値は１００より大きくならない
			if (count2 > 100) {
				count2 = 100;
			}
		}
		//	左キーを押しているときは
		if (CheckHitKey(KEY_INPUT_LEFT)) {
			//	カウント２の値を１減らす
			count2--;
			//	カウント２の値は０より小さくならない
			if (count2 < 0) {
				count2 = 0;
			}
		}
	}
};

Counter1 counter1;
Counter2 counter2;

class Slider
{
public:
	int slider_x;
	void Draw()
	{
		DrawLine(100, 260, 200, 260, LIGHTBLUE);
		DrawCircle(slider_x, 260, 5, LIGHTBLUE, 1, 1);
	}
	void SliderManager()
	{
		slider_x = 100 + counter2.count2;
	}
};

Slider slider;
//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	slider.slider_x = 0;
	counter1.count1 = 200;
	counter2.count2 = 0;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------

void GameUpdate()
{
	counter1.Update();
	counter2.Move();
	slider.SliderManager();
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------

void GameRender()
{
	slider.Draw();
	counter1.Draw();
	counter2.Draw();
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
}


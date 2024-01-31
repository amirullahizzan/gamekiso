#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Hit.h"

const char *base_text[2] = {
	"ABCDEFG0123456", //半角
	"文字列を１文字ずつ描画ABCDEFG0123456", //全角
};

int textDisplayCount = 0;

char displayText[256] = {};

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	for (int i = 0; i < 256;i++)
	{
		displayText[i] = 0;
	}
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------

int autoTextAdvanceTimer = 0;

void DisplayLetter()
{
	if (textDisplayCount >= strlen(base_text[1])) { return; } //get max digits, and return
	if (IsDBCSLeadByte(base_text[1][textDisplayCount])) //if Double-Byte, display twice
	{
		for (int i = 0; i < 2; i++)
		{
			displayText[textDisplayCount] = base_text[1][textDisplayCount];
			textDisplayCount++;
		}
	}
	else
	{
		displayText[textDisplayCount] = base_text[1][textDisplayCount];
		textDisplayCount++;
	}
}

void DisplayAllLetters(const char* _base_text)
{
	while (textDisplayCount < strlen(_base_text))
	{
		if (IsDBCSLeadByte(_base_text[textDisplayCount]))
		{
			for (int i = 0; i < 2; i++)
			{
				displayText[textDisplayCount] = _base_text[textDisplayCount];
				textDisplayCount++;
			}
		}
		else
		{
			displayText[textDisplayCount] = _base_text[textDisplayCount];
			textDisplayCount++;
		}
	}
}

bool IsAllLettersDisplayed(const char* _base_text)
{
	return textDisplayCount >= strlen(_base_text);
}

void Input()
{
	if (PushHitKey(KEY_INPUT_RIGHT))
	{
		DisplayLetter();
		autoTextAdvanceTimer = 0;
		//Display letters one by one each press
	}
	if (PushHitKey(KEY_INPUT_RETURN))
	{
		if (IsAllLettersDisplayed(base_text[1])) { exit(0); }
		DisplayAllLetters(base_text[1]);
		autoTextAdvanceTimer = 0;
		//Display letters one by one each press
	}

	if (PushHitKey(KEY_INPUT_LEFT))
	{
		textDisplayCount = 0;
		for (int i = 0; i < 256; i++)
		{
			displayText[i] = 0;
		}
		//Resets all letters
	}
}

void GameUpdate()
{
	clsDx();
	printfDx("Count %d" , textDisplayCount);
	autoTextAdvanceTimer++;
	if (autoTextAdvanceTimer % 3 == 0) { DisplayLetter(); }
	Input();
}

//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	DrawString( 20, 140, displayText, GetColor(75, 220, 255));

	DrawString( 100, 100, base_text[1], GetColor(255, 255, 0));
	DrawString( 20, 20, "文字列を１文字ずつ描画", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "→キー　：１文字増やす", GetColor( 255, 255, 255 ) );
	DrawString( 20, 60, "←キー　：最初に戻す", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
}

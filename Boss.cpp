#include "pch.h"
#include "Boss.h"

#define LEFT_WALK 0
#define RIGHT_WALK 1
#define R2L_TURN 2
#define L2R_TURN 3

BOSS* InitBoss(DOUBLEBUFFER* db)
{
	BOSS* Temp;
	Temp = (BOSS*)malloc(sizeof(BOSS));
	Temp->DB = db;
	Temp->invisibleColor = RGB(255, 0, 0);

	Temp->SP[0] = InitSprite(L"./Image/Fish/BOSS/boss_left.bmp", 160, 160, 10, Temp->invisibleColor);
	Temp->SP[1] = InitSprite(L"./Image/Fish/BOSS/boss_right.bmp", 160, 160, 10, Temp->invisibleColor);

	Temp->ptPos.x = 0;
	Temp->ptPos.y = 300;

	Temp->nCurrentState = RIGHT_WALK;
	Temp->nMaxState = 3;

	return Temp;
}

void Process(BOSS* boss)
{
	static bool isLeftDir = true;

	static int dx = -1;
	static int dy = 0;

	if (boss->ptPos.x <= 0)
	{
		isLeftDir = false;
		boss->nCurrentState = RIGHT_WALK;
		dx *= -1;
	}
	if (boss->ptPos.x >= boss->DB->BufferSize.right - 100)
	{
		isLeftDir = true;
		boss->nCurrentState = LEFT_WALK;
		dx *= -1;
	}

	boss->ptPos.x += dx;
	boss->ptPos.y += dy;

	SetPos(boss->SP[boss->nCurrentState], boss->ptPos.x, boss->ptPos.y);
	Process(boss->SP[boss->nCurrentState], 300);
}

void Render(BOSS* boss)
{
	Render(boss->SP[boss->nCurrentState], boss->DB);
}

void Release(BOSS* boss)
{
	Release(boss->SP[0]);
	Release(boss->SP[1]);
	free(boss);
}
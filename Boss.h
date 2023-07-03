#pragma once

typedef struct tagBOSS 
{
	DOUBLEBUFFER* DB;
	SPRITE* SP[2];
	COLORREF invisibleColor;
	POINT ptPos;
	int nCurrentState;
	int nMaxState;
}BOSS;

BOSS* InitBoss(DOUBLEBUFFER* db);
void Process(BOSS* boss);
void Render(BOSS* boss);
void Release(BOSS* boss);
#pragma once

typedef struct tagNostraObject
{
	DOUBLEBUFFER* DB;
	SPRITE* Sprite[4];
	COLORREF InvisibleColor;
	POINT ptPosition;
	int nCurrentState;
	int nMaxState;
}NOSTRAOBJ;

NOSTRAOBJ* InitNostra(DOUBLEBUFFER* db);

void Process(NOSTRAOBJ* Object);

void Render(NOSTRAOBJ* Object);

void Release(NOSTRAOBJ* Object);

void NextFrameSprite(NOSTRAOBJ* pNostra, int state, int frame);

void SetPosition(NOSTRAOBJ* Object, int x, int y);


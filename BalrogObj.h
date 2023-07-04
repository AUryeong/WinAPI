#pragma once

typedef struct tagBalrogObject
{
	DOUBLEBUFFER* DB;
	SPRITE* Sprite[4];
	COLORREF InvisibleColor;
	POINT ptPosition;
	int nCurrentState;
	int nMaxState;
}BALROGOBJ;

BALROGOBJ* InitBalrog(DOUBLEBUFFER* db);

void Process(BALROGOBJ* Object);

void Render(BALROGOBJ* Object);

void Release(BALROGOBJ* Object);

void NextFrameSprite(BALROGOBJ* pBalrog, int state, int frame);

void SetPosition(BALROGOBJ* Object, int x, int y);


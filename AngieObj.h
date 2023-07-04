#pragma once

typedef struct tagAngieObject
{
	DOUBLEBUFFER* DB;
	SPRITE* Sprite[4];
	COLORREF InvisibleColor;
	POINT ptPosition;
	int nCurrentState;
	int nMaxState;
}ANGIEOBJ;

ANGIEOBJ* InitAngie(DOUBLEBUFFER* db);

void Process(ANGIEOBJ* Object);

void Render(ANGIEOBJ* Object);

void Release(ANGIEOBJ* Object);

void NextFrameSprite(ANGIEOBJ* pAngie, int state, int frame);

void SetPosition(ANGIEOBJ* Object, int x, int y);


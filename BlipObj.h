#pragma once

typedef struct tagBlipObject
{
	DOUBLEBUFFER* DB;
	SPRITE* Sprite[4];
	COLORREF InvisibleColor;
	POINT ptPosition;
	int nCurrentState;
	int nMaxState;
}BLIPOBJ;

BLIPOBJ* InitBlip(DOUBLEBUFFER* db);

void Process(BLIPOBJ* Object);

void Render(BLIPOBJ* Object);

void Release(BLIPOBJ* Object);

void NextFrameSprite(BLIPOBJ* pMermaid, int frame);

void SetPosition(BLIPOBJ* Object, int x, int y);


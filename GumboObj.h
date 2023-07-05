#pragma once

typedef struct tagGumboObject
{
	DOUBLEBUFFER* DB;
	SPRITE* Sprite[4];
	COLORREF InvisibleColor;
	POINT ptPosition;
	int nCurrentState;
	int nMaxState;
}GUMBOOBJ;

GUMBOOBJ* InitGumbo(DOUBLEBUFFER* db);

void Process(GUMBOOBJ* Object);

void Render(GUMBOOBJ* Object);

void Release(GUMBOOBJ* Object);

void NextFrameSprite(GUMBOOBJ* pGumbo, int state, int frame);

void SetPosition(GUMBOOBJ* Object, int x, int y);


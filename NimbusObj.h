#pragma once

typedef struct tagNimbusObject
{
	DOUBLEBUFFER* DB;
	SPRITE* Sprite[4];
	COLORREF InvisibleColor;
	POINT ptPosition;
	int nCurrentState;
	int nMaxState;
}NIMBUSOBJ;

NIMBUSOBJ* InitNimbus(DOUBLEBUFFER* db);

void Process(NIMBUSOBJ* Object);

void Render(NIMBUSOBJ* Object);

void Release(NIMBUSOBJ* Object);

void NextFrameSprite(NIMBUSOBJ* pNimbus, int state, int frame);

void SetPosition(NIMBUSOBJ* Object, int x, int y);


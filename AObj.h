#pragma once

typedef struct tagAObject
{
	DOUBLEBUFFER* DB;
	SPRITE* Sprite;
	COLORREF InvisibleColor;
	POINT ptPosition;
	BOOL isActiving;
	float lastTime;
	float elapsedTime;
}AOBJ;

AOBJ* InitA(DOUBLEBUFFER* db);

void Process(AOBJ* Object);

void Render(AOBJ* Object);

void Release(AOBJ* Object);

void SetPosition(AOBJ* Object, int x, int y);


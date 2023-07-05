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

	int score; // ���ݱ��� ���� ���ֿ� ��
}AOBJ;

AOBJ* InitA(DOUBLEBUFFER* db);

void Process(AOBJ* Object);

void Click(AOBJ* Object, int x, int y);

void Render(AOBJ* Object);

void Release(AOBJ* Object);

void SetPosition(AOBJ* Object, int x, int y);


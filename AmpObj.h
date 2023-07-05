#pragma once

typedef struct tagAmpObject
{
	DOUBLEBUFFER* DB;
	SPRITE* Sprite[4];
	COLORREF InvisibleColor;
	POINT ptPosition;
	int nCurrentState;
	int nMaxState;
	
	// 여러개의 앰프 생성을 위한 변수들 ( 기존엔 static )
	int DX;
	float lastTime;
	float elapsedTime;
}AMPOBJ;

AMPOBJ* InitAmp(DOUBLEBUFFER* db, int speed= 15);

void Process(AMPOBJ* Object);

void Render(AMPOBJ* Object);

void Release(AMPOBJ* Object);

void NextFrameSprite(AMPOBJ* pAmp, int state, int frame);

void SetPosition(AMPOBJ* Object, int x, int y);


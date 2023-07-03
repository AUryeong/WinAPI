#pragma once

#define SWIM 0
#define TURN 1

#define LEFT_SWIM 0
#define RIGHT_SWIM 1
#define R2L_TURN 2
#define L2R_TURN 3

typedef struct tagMermaidObject
{
	DOUBLEBUFFER* DB;
	SPRITE* Sprite[4];
	COLORREF InvisibleColor;
	POINT ptPosition;
	int nCurrentState;
	int nMaxState;
}MERMAIDOBJ;

MERMAIDOBJ* InitMermaid(DOUBLEBUFFER* db);

void Process(MERMAIDOBJ* Object);

void Render(MERMAIDOBJ* Object);

void Release(MERMAIDOBJ* Object);

void NextFrameSprite(MERMAIDOBJ* pMermaid, int frame);

void SetPosition(MERMAIDOBJ* Object, int x, int y);


#pragma once

typedef struct SummonAObj
{
	AOBJ* AObj;
	DOUBLEBUFFER* db;
}SUMMONAOBJ;

SUMMONAOBJ* InitSummonA(DOUBLEBUFFER* DB);
void Process(SUMMONAOBJ* Object);
void Render(SUMMONAOBJ* Object);
void Release(SUMMONAOBJ* Object);
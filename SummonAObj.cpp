#include "pch.h"

SUMMONAOBJ* InitSummonA(DOUBLEBUFFER* DB) 
{
	SUMMONAOBJ* Temp;

	Temp = (SUMMONAOBJ*)malloc(sizeof(SUMMONAOBJ));
	Temp->db = DB;

	return Temp;
}

void Process(SUMMONAOBJ* Object) 
{
	static float lastTime = GetTickCount() * 0.001f;
	static float elapsedTime = 0.0f;

	float currentTime = GetTickCount() * 0.001f;
	float deltaTime = currentTime - lastTime;
	float desiredFPS = 6.0f;

	elapsedTime += deltaTime;
	lastTime = currentTime;

	if (elapsedTime > desiredFPS)
	{
		elapsedTime -= desiredFPS;
		Object->AObj = InitA(Object->db);
	}
}

void Render(SUMMONAOBJ* Object) 
{

}

void Release(SUMMONAOBJ* Object) 
{

}
#include "pch.h"

// 돌고래 오브젝트 생성
AOBJ* InitA(DOUBLEBUFFER* db)
{
	srand((unsigned int)time(NULL));

	AOBJ* Temp;

	Temp = (AOBJ*)malloc(sizeof(AOBJ));

	Temp->DB = db;

	Temp->InvisibleColor = RGB(255, 0, 0);

	//이미지 로딩
	Temp->Sprite = InitSprite(L"./Image/Mouse.bmp", 81, 81, 0, 10, Temp->InvisibleColor);

	Temp->ptPosition.x = 0;
	Temp->ptPosition.y = 400;

	Temp->isActiving = FALSE;

	Temp->lastTime = GetTickCount() * 0.001f;
	Temp->elapsedTime = 0.0f;

	return Temp;
}

void ACreateProcess(AOBJ* Object)
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

		lastTime = GetTickCount() * 0.001f;

		Object->isActiving = TRUE;

		int posX = rand() % (Object->DB->BufferSize.right - 100);
		int posY = rand() % (Object->DB->BufferSize.bottom - 100);

		SetPosition(Object, posX, posY);

		Object->lastTime = GetTickCount() * 0.001f;
		Object->elapsedTime = 0.0f;
	}
}

void ARemoveProcess(AOBJ* Object)
{
	float currentTime = GetTickCount() * 0.001f;
	float deltaTime = currentTime - Object->lastTime;
	float desiredFPS = 6.0f;

	Object->elapsedTime += deltaTime;
	Object->lastTime = currentTime;

	if (Object->elapsedTime > desiredFPS)
	{
		Object->elapsedTime -= desiredFPS;
		Object->isActiving = FALSE;
	}
}

//  오브젝트 처리
void Process(AOBJ* Object)
{
	if (Object->isActiving)
		ARemoveProcess(Object);
	else
		ACreateProcess(Object);
}

// 돌고래 오브젝트 렌더링
void Render(AOBJ* Object)
{
	if (Object->isActiving)
	{
		SetPos(Object->Sprite, Object->ptPosition.x, Object->ptPosition.y);
		Render(Object->Sprite, Object->DB);
	}
}

// 돌고래 오브젝트의 위치 변경
void SetPosition(AOBJ* Object, int x, int y)
{
	Object->ptPosition.x = x;
	Object->ptPosition.y = y;
}

// 돌고래 오브젝트 해제
void Release(AOBJ* Object)
{
	Release(Object->Sprite);
	free(Object);
}
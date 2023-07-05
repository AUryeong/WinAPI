#include "pch.h"

// 기주영 소환 오브젝트 생성, 기주영을 계속 주변에 나두게 할거
AOBJ* InitA(DOUBLEBUFFER* db)
{
	srand((unsigned int)time(NULL));

	AOBJ* Temp;

	Temp = (AOBJ*)malloc(sizeof(AOBJ));

	Temp->DB = db;

	Temp->InvisibleColor = RGB(0, 0, 0);

	//이미지 로딩
	Temp->Sprite = InitSprite(L"./Image/Juyoung.bmp", 256, 341, 0, 1, Temp->InvisibleColor);

	Temp->ptPosition.x = 0;
	Temp->ptPosition.y = 400;

	Temp->isActiving = FALSE;

	Temp->lastTime = GetTickCount() * 0.001f;
	Temp->elapsedTime = 0.0f;
	Temp->score = 0;

	return Temp;
}

// 기주영이 꺼져있을때 작동하는 처리, 기주영을 소환함
void UnactivatingProcess(AOBJ* Object)
{
	static float elapsedTime = 0.0f;

	float currentTime = GetTickCount() * 0.001f;
	float deltaTime = currentTime - Object->lastTime;
	float desiredFPS = 6.0f;

	elapsedTime += deltaTime;
	Object->lastTime = currentTime;

	if (elapsedTime > desiredFPS)
	{
		elapsedTime -= desiredFPS;

		Object->isActiving = TRUE;

		int posX = rand() % (Object->DB->BufferSize.right - 356);
		int posY = rand() % (Object->DB->BufferSize.bottom - 441);
		
		SetPosition(Object, posX, posY);

		Object->elapsedTime = 0.0f;
	}
}

// 기주영을 삭제하는 처리, 기주영을 없앰
void RemoveProcess(AOBJ* Object)
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

// 기주영이 켜져있을때 작동하는 처리, 위치를 이동하고 기주영을 삭제하는 처리를 실행함
void ActivatingProcess(AOBJ* Object)
{
	static int DY = -5;
	if (Object->ptPosition.y >= Object->DB->BufferSize.top - 100)
	{
		DY *= -1;
	}
	if (Object->ptPosition.y <= Object->DB->BufferSize.bottom - 200)
	{
		DY *= -1;
	}
	Object->ptPosition.y += DY;
	RemoveProcess(Object);
}

// 처리
void Process(AOBJ* Object)
{
	if (Object->isActiving)
		ActivatingProcess(Object);
	else
		UnactivatingProcess(Object);
}

// 클릭했을때 감지해서 기주영 없애기
void Click(AOBJ* Object, int x, int y) 
{
	if (Object->isActiving) 
	{
		if (x - Object->ptPosition.x  <= Object->Sprite->nWidth && Object->ptPosition.y-y <= Object->Sprite->nHeight)
		{
			Object->score++;
			Object->isActiving = FALSE;
		}
	}
}

// 오브젝트 렌더링, 기주영 켜져있을때만 보이게
void Render(AOBJ* Object)
{
	if (Object->isActiving)
	{
		SetPos(Object->Sprite, Object->ptPosition.x, Object->ptPosition.y);
		Render(Object->Sprite, Object->DB);
	}
}

// 기주영 오브젝트의 위치 변경
void SetPosition(AOBJ* Object, int x, int y)
{
	Object->ptPosition.x = x;
	Object->ptPosition.y = y;
}

// 오브젝트 삭제
void Release(AOBJ* Object)
{
	Release(Object->Sprite);
	free(Object);
}
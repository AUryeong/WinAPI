#include "pch.h"

// ���ֿ� ��ȯ ������Ʈ ����, ���ֿ��� ��� �ֺ��� ���ΰ� �Ұ�
AOBJ* InitA(DOUBLEBUFFER* db)
{
	srand((unsigned int)time(NULL));

	AOBJ* Temp;

	Temp = (AOBJ*)malloc(sizeof(AOBJ));

	Temp->DB = db;

	Temp->InvisibleColor = RGB(0, 0, 0);

	//�̹��� �ε�
	Temp->Sprite = InitSprite(L"./Image/Juyoung.bmp", 256, 341, 0, 1, Temp->InvisibleColor);

	Temp->ptPosition.x = 0;
	Temp->ptPosition.y = 400;

	Temp->isActiving = FALSE;

	Temp->lastTime = GetTickCount() * 0.001f;
	Temp->elapsedTime = 0.0f;
	Temp->score = 0;

	return Temp;
}

// ���ֿ��� ���������� �۵��ϴ� ó��, ���ֿ��� ��ȯ��
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

// ���ֿ��� �����ϴ� ó��, ���ֿ��� ����
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

// ���ֿ��� ���������� �۵��ϴ� ó��, ��ġ�� �̵��ϰ� ���ֿ��� �����ϴ� ó���� ������
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

// ó��
void Process(AOBJ* Object)
{
	if (Object->isActiving)
		ActivatingProcess(Object);
	else
		UnactivatingProcess(Object);
}

// Ŭ�������� �����ؼ� ���ֿ� ���ֱ�
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

// ������Ʈ ������, ���ֿ� ������������ ���̰�
void Render(AOBJ* Object)
{
	if (Object->isActiving)
	{
		SetPos(Object->Sprite, Object->ptPosition.x, Object->ptPosition.y);
		Render(Object->Sprite, Object->DB);
	}
}

// ���ֿ� ������Ʈ�� ��ġ ����
void SetPosition(AOBJ* Object, int x, int y)
{
	Object->ptPosition.x = x;
	Object->ptPosition.y = y;
}

// ������Ʈ ����
void Release(AOBJ* Object)
{
	Release(Object->Sprite);
	free(Object);
}
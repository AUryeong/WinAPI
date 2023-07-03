#include "pch.h"

// ���� ������Ʈ ����
BLIPOBJ* InitBlip(DOUBLEBUFFER* db)
{
	BLIPOBJ* Temp;

	Temp = (BLIPOBJ*)malloc(sizeof(BLIPOBJ));

	Temp->DB = db;

	Temp->InvisibleColor = RGB(255, 0, 0);

	//�̹��� �ε�
	Temp->Sprite[LEFT_SWIM] = InitSprite(L"./Image/Fish/Blip/blip.bmp", 80, 80, 0, 10, Temp->InvisibleColor);
	Temp->Sprite[RIGHT_SWIM] = InitSprite(L"./Image/Fish/Blip/blip2.bmp", 80, 80, 0, 10, Temp->InvisibleColor);
	Temp->Sprite[R2L_TURN] = InitSprite(L"./Image/Fish/Blip/blip2.bmp", 80, 80, 80, 10, Temp->InvisibleColor, TRUE);
	Temp->Sprite[L2R_TURN] = InitSprite(L"./Image/Fish/Blip/blip.bmp", 80, 80, 80, 10, Temp->InvisibleColor);

	Temp->ptPosition.x = 0;
	Temp->ptPosition.y = 400;

	Temp->nCurrentState = RIGHT_SWIM;
	Temp->nMaxState = L2R_TURN;

	return Temp;
}

// ���� ������Ʈ ó��
void Process(BLIPOBJ* Object)
{
	static int frame = 10;
	static int DX = 14 * ((Object->nCurrentState != LEFT_SWIM) ? 1 : -1);

	//���� �ε��� �� ���� ���� �ϵ���
	if (Object->ptPosition.x <= Object->DB->BufferSize.left) // ���� ��
	{
		Object->nCurrentState = L2R_TURN; // ��-> �� ��
	}

	if (Object->ptPosition.x >= Object->DB->BufferSize.right - 100) // ������ ��
	{
		Object->nCurrentState = R2L_TURN; // ��-> �� ��
	}

	//������ �� ���� ���� 
	if (Object->Sprite[Object->nCurrentState]->nCurrentFrame >= Object->Sprite[Object->nCurrentState]->nLastFrame) // nCurrentFrame �ȵ� �����غ���
	{
		switch (Object->nCurrentState)
		{
		case R2L_TURN:
			Object->nCurrentState = LEFT_SWIM;
			DX *= -1;
			Process(Object->Sprite[R2L_TURN], 1000); //�ִϸ��̼� ������
			break;
		case L2R_TURN:
			Object->nCurrentState = RIGHT_SWIM;
			DX *= -1;
			Process(Object->Sprite[L2R_TURN], 1000); //�ִϸ��̼� ������
			break;
		default:
			break;
		}
	}

	//������ ����
	if (Object->nCurrentState == LEFT_SWIM)			Object->ptPosition.x += DX;
	if (Object->nCurrentState == RIGHT_SWIM)		Object->ptPosition.x += DX;
	//Process(Object->Sprite[Object->nCurrentState], frame); //�ִϸ��̼� ������
	NextFrameSprite(Object, frame);
	Sleep(3);
}

// ���� ���������� ��������Ʈ ������Ʈ
void NextFrameSprite(BLIPOBJ* pBlip, int frameRate)
{
	static float lastTime = GetTickCount() * 0.001f;
	static float elapsedTime = 0.0f;

	float currentTime = GetTickCount() * 0.001f;
	float deltaTime = currentTime - lastTime;
	float desiredFPS = 1.0f / frameRate;

	elapsedTime += deltaTime;
	lastTime = currentTime;

	if (elapsedTime > desiredFPS)
	{
		elapsedTime -= desiredFPS;
		pBlip->Sprite[pBlip->nCurrentState]->nCurrentFrame++;
		if (pBlip->Sprite[pBlip->nCurrentState]->nCurrentFrame > pBlip->Sprite[pBlip->nCurrentState]->nLastFrame)
			pBlip->Sprite[pBlip->nCurrentState]->nCurrentFrame = 0;
	}
}

// ���� ������Ʈ ������
void Render(BLIPOBJ* Object)
{
	SetPos(Object->Sprite[Object->nCurrentState], Object->ptPosition.x, Object->ptPosition.y);
	Render(Object->Sprite[Object->nCurrentState], Object->DB);
}

// ���� ������Ʈ�� ��ġ ����
void SetPosition(BLIPOBJ* Object, int x, int y)
{
	Object->ptPosition.x = x;
	Object->ptPosition.y = y;
}

// ���� ������Ʈ ����
void Release(BLIPOBJ* Object)
{
	Release(Object->Sprite[0]);
	Release(Object->Sprite[1]);
	Release(Object->Sprite[2]);
	Release(Object->Sprite[3]);
	free(Object);
}
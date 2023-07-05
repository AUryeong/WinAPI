#include "pch.h"

// �Թ��� ������Ʈ ����
NIMBUSOBJ* InitNimbus(DOUBLEBUFFER* db)
{
	NIMBUSOBJ* Temp;

	Temp = (NIMBUSOBJ*)malloc(sizeof(NIMBUSOBJ));

	Temp->DB = db;

	Temp->InvisibleColor = RGB(0, 0, 0);

	//�̹��� �ε�
	Temp->Sprite[LEFT_SWIM] = InitSprite(L"./Image/Fish/NIMBUS/NIMBUS.bmp", 80, 80, 0, 10, Temp->InvisibleColor);
	Temp->Sprite[RIGHT_SWIM] = InitSprite(L"./Image/Fish/NIMBUS/NIMBUS2.bmp", 80, 80, 0, 10, Temp->InvisibleColor);
	Temp->Sprite[R2L_TURN] = InitSprite(L"./Image/Fish/NIMBUS/NIMBUS2.bmp", 80, 80, 80, 10, Temp->InvisibleColor, TRUE);
	Temp->Sprite[L2R_TURN] = InitSprite(L"./Image/Fish/NIMBUS/NIMBUS.bmp", 80, 80, 80, 10, Temp->InvisibleColor);

	Temp->ptPosition.x = 0;
	Temp->ptPosition.y = 400;

	Temp->nCurrentState = RIGHT_SWIM;
	Temp->nMaxState = L2R_TURN;

	return Temp;
}

// �Թ��� ������Ʈ ó��
void Process(NIMBUSOBJ* Object)
{
	static int frame = 10;
	static int DX = 12 * ((Object->nCurrentState != LEFT_SWIM) ? 1 : -1);
	static int DY = -2;

	//���� �ε��� �� ���� ���� �ϵ���
	if (Object->ptPosition.x <= Object->DB->BufferSize.left) // ���� ��
	{
		Object->nCurrentState = L2R_TURN; // ��-> �� ��
	}

	if (Object->ptPosition.x >= Object->DB->BufferSize.right - 100) // ������ ��
	{
		Object->nCurrentState = R2L_TURN; // ��-> �� ��
	}

	if (Object->ptPosition.y >= Object->DB->BufferSize.top)
	{
		DY *= -1;
	}

	if (Object->ptPosition.y <= Object->DB->BufferSize.bottom - 100)
	{
		DY *= -1;
	}

	//������ �� ���� ���� 
	if (Object->Sprite[Object->nCurrentState]->nCurrentFrame >= Object->Sprite[Object->nCurrentState]->nLastFrame) // nCurrentFrame �ȵ� �����غ���
	{
		switch (Object->nCurrentState)
		{
		case R2L_TURN:
			Object->nCurrentState = LEFT_SWIM;
			DX *= -1;
			NextFrameSprite(Object, R2L_TURN, 1000); //�ִϸ��̼� ������
			break;
		case L2R_TURN:
			Object->nCurrentState = RIGHT_SWIM;
			DX *= -1;
			NextFrameSprite(Object, L2R_TURN, 1000); //�ִϸ��̼� ������
			break;
		default:
			break;
		}
	}

	//������ ����
	if (Object->nCurrentState == LEFT_SWIM || Object->nCurrentState == RIGHT_SWIM)
	{
		Object->ptPosition.x += DX;
		Object->ptPosition.y += DY;
	}
	//Process(Object->Sprite[Object->nCurrentState], frame); //�ִϸ��̼� ������
	NextFrameSprite(Object, Object->nCurrentState, frame);
}

// ���� ���������� ��������Ʈ ������Ʈ
void NextFrameSprite(NIMBUSOBJ* pNimbus, int state, int frameRate)
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
		pNimbus->Sprite[state]->nCurrentFrame++;
		if (pNimbus->Sprite[state]->nCurrentFrame > pNimbus->Sprite[state]->nLastFrame)
			pNimbus->Sprite[state]->nCurrentFrame = 0;
	}
}

// �Թ��� ������Ʈ ������
void Render(NIMBUSOBJ* Object)
{
	SetPos(Object->Sprite[Object->nCurrentState], Object->ptPosition.x, Object->ptPosition.y);
	Render(Object->Sprite[Object->nCurrentState], Object->DB);
}

// �Թ��� ������Ʈ�� ��ġ ����
void SetPosition(NIMBUSOBJ* Object, int x, int y)
{
	Object->ptPosition.x = x;
	Object->ptPosition.y = y;
}

// �Թ��� ������Ʈ ����
void Release(NIMBUSOBJ* Object)
{
	Release(Object->Sprite[0]);
	Release(Object->Sprite[1]);
	Release(Object->Sprite[2]);
	Release(Object->Sprite[3]);
	free(Object);
}
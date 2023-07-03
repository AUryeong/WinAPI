#include "pch.h"

// �ξ� ������Ʈ ����
MERMAIDOBJ* InitMermaid(DOUBLEBUFFER* db)
{
	MERMAIDOBJ* Temp;

	Temp = (MERMAIDOBJ*)malloc(sizeof(MERMAIDOBJ));

	Temp->DB = db;

	Temp->InvisibleColor = RGB(255, 0, 0);

	//�̹��� �ε�
	Temp->Sprite[LEFT_SWIM] = InitSprite(L"./Image/Fish/Mermaid/Mermaid_Left.bmp", 80, 80, 0, 10, Temp->InvisibleColor);
	Temp->Sprite[RIGHT_SWIM] = InitSprite(L"./Image/Fish/Mermaid/Mermaid_Right.bmp", 80, 80, 0, 10, Temp->InvisibleColor);
	Temp->Sprite[R2L_TURN] = InitSprite(L"./Image/Fish/Mermaid/Mermaid_R2LTurn.bmp", 80, 80, 0, 10, Temp->InvisibleColor);
	Temp->Sprite[L2R_TURN] = InitSprite(L"./Image/Fish/Mermaid/Mermaid_L2RTurn.bmp", 80, 80, 0, 10, Temp->InvisibleColor);

	Temp->ptPosition.x = 0;
	Temp->ptPosition.y = 400;

	Temp->nCurrentState = RIGHT_SWIM;
	Temp->nMaxState = L2R_TURN;

	return Temp;
}

// �ξ� ������Ʈ ó��
void Process(MERMAIDOBJ* Object)
{
	static int frame = 10;
	static int DX = 4 * ((Object->nCurrentState!=LEFT_SWIM)?1:-1);

	//���� �ε��� �� ���� ���� �ϵ���
	if (Object->ptPosition.x <= Object->DB->BufferSize.left) // ���� ��
	{
		Object->nCurrentState = L2R_TURN; // ��-> �� ��
	}

	if (Object->ptPosition.x >= Object->DB->BufferSize.right-100) // ������ ��
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
void NextFrameSprite(MERMAIDOBJ* pMermaid, int frameRate)
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
		pMermaid->Sprite[pMermaid->nCurrentState]->nCurrentFrame++;
		if (pMermaid->Sprite[pMermaid->nCurrentState]->nCurrentFrame > pMermaid->Sprite[pMermaid->nCurrentState]->nLastFrame)
			pMermaid->Sprite[pMermaid->nCurrentState]->nCurrentFrame = 0;
	}
}

// �ξ� ������Ʈ ������
void Render(MERMAIDOBJ* Object)
{
	SetPos(Object->Sprite[Object->nCurrentState], Object->ptPosition.x, Object->ptPosition.y);
	Render(Object->Sprite[Object->nCurrentState], Object->DB);
}

// �ξ� ������Ʈ�� ��ġ ����
void SetPosition(MERMAIDOBJ* Object, int x, int y)
{
	Object->ptPosition.x = x;
	Object->ptPosition.y = y;
}

// �ξ� ������Ʈ ����
void Release(MERMAIDOBJ* Object)
{
	Release(Object->Sprite[0]);
	Release(Object->Sprite[1]);
	Release(Object->Sprite[2]);
	Release(Object->Sprite[3]);
	free(Object);
}
#include "pch.h"

// 앰프 오브젝트 생성, 여러개 소환할 수 있게 static 없앰
AMPOBJ* InitAmp(DOUBLEBUFFER* db, int speed)
{
	AMPOBJ* Temp;

	Temp = (AMPOBJ*)malloc(sizeof(AMPOBJ));

	Temp->DB = db;

	Temp->InvisibleColor = RGB(0, 0, 0);

	//이미지 로딩
	Temp->Sprite[LEFT_SWIM] = InitSprite(L"./Image/Fish/AMP/AMP.bmp", 160, 60, 0, 10, Temp->InvisibleColor);
	Temp->Sprite[RIGHT_SWIM] = InitSprite(L"./Image/Fish/AMP/AMP2.bmp", 160, 60, 0, 10, Temp->InvisibleColor);
	Temp->Sprite[R2L_TURN] = InitSprite(L"./Image/Fish/AMP/AMP2.bmp", 160, 60, 60, 10, Temp->InvisibleColor, TRUE);
	Temp->Sprite[L2R_TURN] = InitSprite(L"./Image/Fish/AMP/AMP.bmp", 160, 60, 60, 10, Temp->InvisibleColor);

	Temp->ptPosition.x = 0;
	Temp->ptPosition.y = 400;

	Temp->nCurrentState = RIGHT_SWIM;
	Temp->nMaxState = L2R_TURN;

	Temp->lastTime = GetTickCount() * 0.001f;
	Temp->elapsedTime = 0.0f;

	Temp->DX = speed * ((Temp->nCurrentState != LEFT_SWIM) ? 1 : -1);

	return Temp;
}

// 앰프 오브젝트 처리
void Process(AMPOBJ* Object)
{
	static int frame = 10;

	//벽에 부딪힐 때 상태 전이 턴동작
	if (Object->ptPosition.x <= Object->DB->BufferSize.left) // 왼쪽 벽
	{
		Object->nCurrentState = L2R_TURN; // 왼-> 오 턴
	}

	if (Object->ptPosition.x >= Object->DB->BufferSize.right - 100) // 오른쪽 벽
	{
		Object->nCurrentState = R2L_TURN; // 오-> 왼 턴
	}

	//수영할 때 상태 전이 
	if (Object->Sprite[Object->nCurrentState]->nCurrentFrame >= Object->Sprite[Object->nCurrentState]->nLastFrame) // nCurrentFrame 안됨 수정해보셈
	{
		switch (Object->nCurrentState)
		{
		case R2L_TURN:
			Object->nCurrentState = LEFT_SWIM;
			Object->DX *= -1;
			NextFrameSprite(Object, R2L_TURN, 1000); //애니메이션 프레임
			break;
		case L2R_TURN:
			Object->nCurrentState = RIGHT_SWIM;
			Object->DX *= -1;
			NextFrameSprite(Object, L2R_TURN, 1000); //애니메이션 프레임
			break;
		default:
			break;
		}
	}

	//움직임 구간
	if (Object->nCurrentState == LEFT_SWIM || Object->nCurrentState == RIGHT_SWIM)
	{
		Object->ptPosition.x += Object->DX;
	}
	//Process(Object->Sprite[Object->nCurrentState], frame); //애니메이션 프레임
	NextFrameSprite(Object, Object->nCurrentState, frame);
}

// 다음 프레임으로 스프라이트 업데이트
void NextFrameSprite(AMPOBJ* pAmp, int state, int frameRate)
{

	float currentTime = GetTickCount() * 0.001f;
	float deltaTime = currentTime - pAmp->lastTime;
	float desiredFPS = 1.0f / frameRate;

	pAmp->elapsedTime += deltaTime;
	pAmp->lastTime = currentTime;

	if (pAmp->elapsedTime > desiredFPS)
	{
		pAmp->elapsedTime -= desiredFPS;
		pAmp->Sprite[state]->nCurrentFrame++;
		if (pAmp->Sprite[state]->nCurrentFrame > pAmp->Sprite[state]->nLastFrame)
			pAmp->Sprite[state]->nCurrentFrame = 0;
	}
}

// 앰프 오브젝트 렌더링
void Render(AMPOBJ* Object)
{
	SetPos(Object->Sprite[Object->nCurrentState], Object->ptPosition.x, Object->ptPosition.y);
	Render(Object->Sprite[Object->nCurrentState], Object->DB);
}

// 앰프 오브젝트의 위치 변경
void SetPosition(AMPOBJ* Object, int x, int y)
{
	Object->ptPosition.x = x;
	Object->ptPosition.y = y;
}

// 앰프 오브젝트 해제
void Release(AMPOBJ* Object)
{
	Release(Object->Sprite[0]);
	Release(Object->Sprite[1]);
	Release(Object->Sprite[2]);
	Release(Object->Sprite[3]);
	free(Object);
}
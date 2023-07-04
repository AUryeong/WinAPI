#include "pch.h"

// 안기 오브젝트 생성
ANGIEOBJ* InitAngie(DOUBLEBUFFER* db)
{
	ANGIEOBJ* Temp;

	Temp = (ANGIEOBJ*)malloc(sizeof(ANGIEOBJ));

	Temp->DB = db;

	Temp->InvisibleColor = RGB(255, 0, 0);

	//이미지 로딩
	Temp->Sprite[LEFT_SWIM] = InitSprite(L"./Image/Fish/ANGIE/ANGIE.bmp", 80, 80, 0, 10, Temp->InvisibleColor);
	Temp->Sprite[RIGHT_SWIM] = InitSprite(L"./Image/Fish/ANGIE/ANGIE2.bmp", 80, 80, 0, 10, Temp->InvisibleColor);
	Temp->Sprite[R2L_TURN] = InitSprite(L"./Image/Fish/ANGIE/ANGIE2.bmp", 80, 80, 80, 10, Temp->InvisibleColor, TRUE);
	Temp->Sprite[L2R_TURN] = InitSprite(L"./Image/Fish/ANGIE/ANGIE.bmp", 80, 80, 80, 10, Temp->InvisibleColor);

	Temp->ptPosition.x = 0;
	Temp->ptPosition.y = 400;

	Temp->nCurrentState = RIGHT_SWIM;
	Temp->nMaxState = L2R_TURN;

	return Temp;
}

// 안기 오브젝트 처리
void Process(ANGIEOBJ* Object)
{
	static int frame = 10;
	static int DX = 6 * ((Object->nCurrentState != LEFT_SWIM) ? 1 : -1);
	static int DY = 6;

	//벽에 부딪힐 때 상태 전이 턴동작
	if (Object->ptPosition.x <= Object->DB->BufferSize.left) // 왼쪽 벽
	{
		Object->nCurrentState = L2R_TURN; // 왼-> 오 턴
	}

	if (Object->ptPosition.x >= Object->DB->BufferSize.right - 100) // 오른쪽 벽
	{
		Object->nCurrentState = R2L_TURN; // 오-> 왼 턴
	}

	if (Object->ptPosition.y >= Object->DB->BufferSize.top)
	{
		DY *= -1;
	}

	if (Object->ptPosition.y <= Object->DB->BufferSize.bottom - 100)
	{
		DY *= -1;
	}

	//수영할 때 상태 전이 
	if (Object->Sprite[Object->nCurrentState]->nCurrentFrame >= Object->Sprite[Object->nCurrentState]->nLastFrame) // nCurrentFrame 안됨 수정해보셈
	{
		switch (Object->nCurrentState)
		{
		case R2L_TURN:
			Object->nCurrentState = LEFT_SWIM;
			DX *= -1;
			NextFrameSprite(Object, R2L_TURN, 1000); //애니메이션 프레임
			break;
		case L2R_TURN:
			Object->nCurrentState = RIGHT_SWIM;
			DX *= -1;
			NextFrameSprite(Object, L2R_TURN, 1000); //애니메이션 프레임
			break;
		default:
			break;
		}
	}

	//움직임 구간
	if (Object->nCurrentState == LEFT_SWIM || Object->nCurrentState == RIGHT_SWIM)
	{
		Object->ptPosition.x += DX;
		Object->ptPosition.y += DY;
	}
	//Process(Object->Sprite[Object->nCurrentState], frame); //애니메이션 프레임
	NextFrameSprite(Object, Object->nCurrentState, frame);
}

// 다음 프레임으로 스프라이트 업데이트
void NextFrameSprite(ANGIEOBJ* pAngie, int state, int frameRate)
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
		pAngie->Sprite[state]->nCurrentFrame++;
		if (pAngie->Sprite[state]->nCurrentFrame > pAngie->Sprite[state]->nLastFrame)
			pAngie->Sprite[state]->nCurrentFrame = 0;
	}
}

// 안기 오브젝트 렌더링
void Render(ANGIEOBJ* Object)
{
	SetPos(Object->Sprite[Object->nCurrentState], Object->ptPosition.x, Object->ptPosition.y);
	Render(Object->Sprite[Object->nCurrentState], Object->DB);
}

// 안기 오브젝트의 위치 변경
void SetPosition(ANGIEOBJ* Object, int x, int y)
{
	Object->ptPosition.x = x;
	Object->ptPosition.y = y;
}

// 안기 오브젝트 해제
void Release(ANGIEOBJ* Object)
{
	Release(Object->Sprite[0]);
	Release(Object->Sprite[1]);
	Release(Object->Sprite[2]);
	Release(Object->Sprite[3]);
	free(Object);
}
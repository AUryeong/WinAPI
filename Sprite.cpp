#include "pch.h"

// 스프라이트 생성, flip은 애니메이션 반전 여부
SPRITE* InitSprite(const TCHAR* filename, int w, int h, int y, int lastFrame, COLORREF crInvisible, BOOL flip)
{
	SPRITE* Temp;
	Temp = (SPRITE*)malloc(sizeof(SPRITE));
	Temp->hBitmap = LoadBMP(filename);
	if (Temp->hBitmap == NULL)
	{
		MessageBox(NULL, L"파일이 없어요", L"Error", MB_OK);
		exit(0);
	}
	Temp->InvisibleColor = crInvisible;
	Temp->nWidth = w;
	Temp->nHeight = h;
	Temp->nLastFrame = lastFrame - 1;
	Temp->nCurrentFrame = 0;
	Temp->nPosY = y;
	Temp->isFlip = flip;
	SetPos(Temp, 0, 0);
	return Temp;
}

// 스프라이트 삭제
void Release(SPRITE* pObj)
{
	DeleteObject(pObj->hBitmap);
	free(pObj);
}

// 다음 프레임의 스프라이트 가져오기
void NextFrameSprite(SPRITE* pSP, int frameRate)
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
		pSP->nCurrentFrame++;
		if (pSP->nCurrentFrame > pSP->nLastFrame)
			pSP->nCurrentFrame = 0;
	}
}

// 스프라이트 처리
void Process(SPRITE* pObj, int frameRate)
{
	NextFrameSprite(pObj, frameRate);
}

// 스프라이트 렌더링 isFlip으로 반대로 출력하게 처리
void Render(SPRITE* pObj, DOUBLEBUFFER* pDB)
{
	int x, y, w, h;
	x = (pObj->isFlip) ? (pObj->nLastFrame - pObj->nCurrentFrame) * pObj->nWidth : pObj->nCurrentFrame * pObj->nWidth;
	y = pObj->nPosY;
	w = pObj->nWidth;
	h = pObj->nHeight;

	HDC hdc = CreateCompatibleDC(pDB->hdcFront);  //여기에 넣는 것 안좋음
	SelectObject(hdc, pObj->hBitmap);

	TransparentBlt(pDB->hdcBack,  //화면
		pObj->Position.x, pObj->Position.y, //화면 출력 위치
		w, h, //화면 표시 위치
		hdc,
		x, y, //이미지에서 소스 위치
		w, h, //이미지에서 소스 크기
		pObj->InvisibleColor); //이미지에서 삭제할 색
	DeleteDC(hdc);
}
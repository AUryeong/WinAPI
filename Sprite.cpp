#include "pch.h"

// ��������Ʈ ����, flip�� �ִϸ��̼� ���� ����
SPRITE* InitSprite(const TCHAR* filename, int w, int h, int y, int lastFrame, COLORREF crInvisible, BOOL flip)
{
	SPRITE* Temp;
	Temp = (SPRITE*)malloc(sizeof(SPRITE));
	Temp->hBitmap = LoadBMP(filename);
	if (Temp->hBitmap == NULL)
	{
		MessageBox(NULL, L"������ �����", L"Error", MB_OK);
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

// ��������Ʈ ����
void Release(SPRITE* pObj)
{
	DeleteObject(pObj->hBitmap);
	free(pObj);
}

// ���� �������� ��������Ʈ ��������
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

// ��������Ʈ ó��
void Process(SPRITE* pObj, int frameRate)
{
	NextFrameSprite(pObj, frameRate);
}

// ��������Ʈ ������ isFlip���� �ݴ�� ����ϰ� ó��
void Render(SPRITE* pObj, DOUBLEBUFFER* pDB)
{
	int x, y, w, h;
	x = (pObj->isFlip) ? (pObj->nLastFrame - pObj->nCurrentFrame) * pObj->nWidth : pObj->nCurrentFrame * pObj->nWidth;
	y = pObj->nPosY;
	w = pObj->nWidth;
	h = pObj->nHeight;

	HDC hdc = CreateCompatibleDC(pDB->hdcFront);  //���⿡ �ִ� �� ������
	SelectObject(hdc, pObj->hBitmap);

	TransparentBlt(pDB->hdcBack,  //ȭ��
		pObj->Position.x, pObj->Position.y, //ȭ�� ��� ��ġ
		w, h, //ȭ�� ǥ�� ��ġ
		hdc,
		x, y, //�̹������� �ҽ� ��ġ
		w, h, //�̹������� �ҽ� ũ��
		pObj->InvisibleColor); //�̹������� ������ ��
	DeleteDC(hdc);
}
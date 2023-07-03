#pragma once

typedef struct tagSPRITE
{
	HBITMAP hBitmap;          //�̹���
	COLORREF InvisibleColor;  //�� ��
	POINT Position;           //��ġ
	int nCurrentFrame;        //���� �̹���
	int nLastFrame;           //������ �̹���
	int nWidth;               //�̹��� ��
	int nHeight;              //�̹��� ����
	int nPosY;
	BOOL isFlip;
}SPRITE;

SPRITE* InitSprite(const TCHAR* filename, int w, int h, int y, int lastFrame, COLORREF crInvisible, BOOL flip = FALSE);
void Release(SPRITE* pObj);
void Process(SPRITE* pObj, int frameRate);
void Render(SPRITE* pObj, DOUBLEBUFFER* pDB);

// ��������Ʈ ��ġ �� ����
inline void SetPos(SPRITE* pObj, int x, int y) { pObj->Position.x = x; pObj->Position.y = y; }

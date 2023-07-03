#pragma once

typedef struct tagSPRITE
{
	HBITMAP hBitmap;          //이미지
	COLORREF InvisibleColor;  //뺄 색
	POINT Position;           //위치
	int nCurrentFrame;        //현재 이미지
	int nLastFrame;           //마지막 이미지
	int nWidth;               //이미지 폭
	int nHeight;              //이미지 높이
	int nPosY;
	BOOL isFlip;
}SPRITE;

SPRITE* InitSprite(const TCHAR* filename, int w, int h, int y, int lastFrame, COLORREF crInvisible, BOOL flip = FALSE);
void Release(SPRITE* pObj);
void Process(SPRITE* pObj, int frameRate);
void Render(SPRITE* pObj, DOUBLEBUFFER* pDB);

// 스프라이트 위치 값 설정
inline void SetPos(SPRITE* pObj, int x, int y) { pObj->Position.x = x; pObj->Position.y = y; }

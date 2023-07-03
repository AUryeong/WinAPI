#pragma once

typedef struct tagDOUBLEBUFFER
{
	HWND hWnd;  //윈도우 핸들
	HDC  hdcFront; //전면버퍼
	HDC  hdcBack; //후면버퍼
	HDC  hdcImage; //이미지 버퍼
	HBITMAP hbmBack; //후면 버퍼 이미지 저장소
	HBITMAP hbmImage; //이미지 버퍼 이미지 저장소
	RECT BufferSize; //버퍼 크기

}DOUBLEBUFFER;

DOUBLEBUFFER* CreateDoubleBuffer(HWND hWnd); //더블버퍼 초기화
void Release(DOUBLEBUFFER* Obj);
void Process(DOUBLEBUFFER* Obj);
void Render(DOUBLEBUFFER* Obj);

void SwapBuffer(DOUBLEBUFFER* Obj);

void LoadBMP(DOUBLEBUFFER* Obj, const TCHAR* filename);
HBITMAP LoadBMP(const TCHAR* filename);
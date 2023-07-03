#include "pch.h"
#include "DoubleBuffer.h"

DOUBLEBUFFER* CreateDoubleBuffer(HWND hWnd)
{
	DOUBLEBUFFER* Temp;
	Temp = (DOUBLEBUFFER*)malloc(sizeof(DOUBLEBUFFER)); //메모리 정의
	Temp->hWnd = hWnd;
	GetClientRect(hWnd, &Temp->BufferSize); //현재 윈도우 클라이언트 영역 크기 얻기
	
	Temp->hdcFront = GetDC(hWnd);   //주버퍼 생성
//====================================================================
	Temp->hdcBack = CreateCompatibleDC(Temp->hdcFront); //보조버퍼 생성
	int cx = Temp->BufferSize.right - Temp->BufferSize.left; //너비
	int cy = Temp->BufferSize.bottom - Temp->BufferSize.top; //높이
	Temp->hbmBack = CreateCompatibleBitmap(Temp->hdcFront, cx, cy); //보조버퍼
	SelectObject(Temp->hdcBack, Temp->hbmBack); //보조버퍼 <==> 보조버퍼이미지 연결
//====================================================================
	Temp->hdcImage = CreateCompatibleDC(Temp->hdcFront);	

	return Temp;
}

void Release(DOUBLEBUFFER* Obj)
{
	DeleteObject(Obj->hdcImage);
	DeleteObject(Obj->hbmBack);
	DeleteDC(Obj->hdcBack);
	DeleteDC(Obj->hdcFront);
}

void Process(DOUBLEBUFFER* Obj)
{

}

void Render(DOUBLEBUFFER* Obj)
{
	int x, y; //좌표
	int w, h; //크기

	x = Obj->BufferSize.left;
	y = Obj->BufferSize.top;
	w = Obj->BufferSize.right - Obj->BufferSize.left; //너비
	h = Obj->BufferSize.bottom - Obj->BufferSize.top; //높이
/*
	//===================================================
	//윈도우 클라이언트 영역 정보 얻기
	RECT rtScreen;
	GetClientRect(Obj->hWnd, &rtScreen);
	int ScreenW = rtScreen.right - rtScreen.left;
	int ScreenH = rtScreen.bottom - rtScreen.top;
	//===================================================
//*/
	//===================================================
	//이미지에서 정보 얻기
	BITMAP bmpInfo;
	GetObject(Obj->hbmImage, sizeof(BITMAP), &bmpInfo);
	int ImgW = bmpInfo.bmWidth;
	int ImgH = bmpInfo.bmHeight;
	//===================================================
//*/

	//BitBlt(Obj->hdcBack, x, y, w, h, Obj->hdcImage, 0, 0, SRCCOPY);
	StretchBlt(Obj->hdcBack, x, y, w, h, 
		Obj->hdcImage, 0, 0, ImgW, ImgH, SRCCOPY);
}

// 백 버퍼에서 메인 버퍼로 복사
void SwapBuffer(DOUBLEBUFFER* Obj)
{
	int x, y; //좌표
	int w, h; //크기

	x = Obj->BufferSize.left;
	y = Obj->BufferSize.top;
	w = Obj->BufferSize.right - Obj->BufferSize.left; //너비
	h = Obj->BufferSize.bottom - Obj->BufferSize.top; //높이

	//후면버퍼 전면버퍼로 고속복사
	BitBlt(Obj->hdcFront, x, y, w, h, Obj->hdcBack, 0, 0, SRCCOPY);
}

//====================================================
// 비트맵이미지 읽어오기
void LoadBMP(DOUBLEBUFFER* Obj, const TCHAR* filename)
{
	HINSTANCE hInst = GetModuleHandle(NULL);
	Obj->hbmImage = (HBITMAP)LoadImage(hInst, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(Obj->hdcImage, Obj->hbmImage);
}

HBITMAP LoadBMP(const TCHAR* filename)
{
	HBITMAP hbmTemp;
	HINSTANCE hInst = GetModuleHandle(NULL);
	hbmTemp = (HBITMAP)LoadImage(hInst, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	return hbmTemp;
}

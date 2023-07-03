#include "pch.h"
#include "DoubleBuffer.h"

DOUBLEBUFFER* CreateDoubleBuffer(HWND hWnd)
{
	DOUBLEBUFFER* Temp;
	Temp = (DOUBLEBUFFER*)malloc(sizeof(DOUBLEBUFFER)); //�޸� ����
	Temp->hWnd = hWnd;
	GetClientRect(hWnd, &Temp->BufferSize); //���� ������ Ŭ���̾�Ʈ ���� ũ�� ���
	
	Temp->hdcFront = GetDC(hWnd);   //�ֹ��� ����
//====================================================================
	Temp->hdcBack = CreateCompatibleDC(Temp->hdcFront); //�������� ����
	int cx = Temp->BufferSize.right - Temp->BufferSize.left; //�ʺ�
	int cy = Temp->BufferSize.bottom - Temp->BufferSize.top; //����
	Temp->hbmBack = CreateCompatibleBitmap(Temp->hdcFront, cx, cy); //��������
	SelectObject(Temp->hdcBack, Temp->hbmBack); //�������� <==> ���������̹��� ����
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
	int x, y; //��ǥ
	int w, h; //ũ��

	x = Obj->BufferSize.left;
	y = Obj->BufferSize.top;
	w = Obj->BufferSize.right - Obj->BufferSize.left; //�ʺ�
	h = Obj->BufferSize.bottom - Obj->BufferSize.top; //����
/*
	//===================================================
	//������ Ŭ���̾�Ʈ ���� ���� ���
	RECT rtScreen;
	GetClientRect(Obj->hWnd, &rtScreen);
	int ScreenW = rtScreen.right - rtScreen.left;
	int ScreenH = rtScreen.bottom - rtScreen.top;
	//===================================================
//*/
	//===================================================
	//�̹������� ���� ���
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

// �� ���ۿ��� ���� ���۷� ����
void SwapBuffer(DOUBLEBUFFER* Obj)
{
	int x, y; //��ǥ
	int w, h; //ũ��

	x = Obj->BufferSize.left;
	y = Obj->BufferSize.top;
	w = Obj->BufferSize.right - Obj->BufferSize.left; //�ʺ�
	h = Obj->BufferSize.bottom - Obj->BufferSize.top; //����

	//�ĸ���� ������۷� ��Ӻ���
	BitBlt(Obj->hdcFront, x, y, w, h, Obj->hdcBack, 0, 0, SRCCOPY);
}

//====================================================
// ��Ʈ���̹��� �о����
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

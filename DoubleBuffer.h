#pragma once

typedef struct tagDOUBLEBUFFER
{
	HWND hWnd;  //������ �ڵ�
	HDC  hdcFront; //�������
	HDC  hdcBack; //�ĸ����
	HDC  hdcImage; //�̹��� ����
	HBITMAP hbmBack; //�ĸ� ���� �̹��� �����
	HBITMAP hbmImage; //�̹��� ���� �̹��� �����
	RECT BufferSize; //���� ũ��

}DOUBLEBUFFER;

DOUBLEBUFFER* CreateDoubleBuffer(HWND hWnd); //������� �ʱ�ȭ
void Release(DOUBLEBUFFER* Obj);
void Process(DOUBLEBUFFER* Obj);
void Render(DOUBLEBUFFER* Obj);

void SwapBuffer(DOUBLEBUFFER* Obj);

void LoadBMP(DOUBLEBUFFER* Obj, const TCHAR* filename);
HBITMAP LoadBMP(const TCHAR* filename);
#include "pch.h"
#include "MainProc.h"

extern HINSTANCE hInst;
extern BOOL bIsActive;

int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    Initialize(hWnd);
    bIsActive = TRUE; //���ӷ��� Ȱ��ȭ

    return TRUE;
}

int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    Release(hWnd);
    PostQuitMessage(0);
    return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:     return OnCreate(hWnd, wParam, lParam);
    case WM_DESTROY:    return OnDestroy(hWnd, wParam, lParam);
    default:            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

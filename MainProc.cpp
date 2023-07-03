#include "pch.h"
#include "MainProc.h"

extern HINSTANCE hInst;
extern BOOL bIsActive;

int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    Initialize(hWnd);
    bIsActive = TRUE; //게임루프 활성화

    return TRUE;
}

int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    Release(hWnd);
    PostQuitMessage(0);
    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
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

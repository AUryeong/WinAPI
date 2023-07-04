// 게임 메인 루프
#include "pch.h"
#include <windowsx.h>

extern BOOL bIsActive;
DOUBLEBUFFER* pDB;
BG* pBG;
MERMAIDOBJ* pMermaid;
BLIPOBJ* pBlip;
ANGIEOBJ* pAngie;
AMPOBJ* pAmp;
BALROGOBJ* pBalrog;
AOBJ* pA;
SPRITE* pMouse;

POINT ptMouse = { 0, 0 };
TCHAR strScoreCoord[128];

// 게임 초기화 및 로딩
void Initialize(HWND hWnd)
{
    while (ShowCursor(FALSE) >= 0);

    pDB = CreateDoubleBuffer(hWnd);
    pBG = InitBG(pDB);

    pMermaid = InitMermaid(pDB);
    SetPosition(pMermaid, 200, 400);

    pBlip = InitBlip(pDB);
    SetPosition(pBlip, 200, 400);

    pAngie = InitAngie(pDB);
    SetPosition(pAngie, 600, 200);

    pAmp = InitAmp(pDB);
    SetPosition(pAmp, 430, 100);

    pBalrog = InitBalrog(pDB);
    SetPosition(pBalrog, 100, 300);  

    pA = InitA(pDB);
    SetPosition(pA, 600, 200);

    pMouse = InitSprite(L"./Image/Mouse.bmp", 81, 81, 0, 1, RGB(255, 0, 0));

    //LoadBMP(pDB, L"./Image/BG/aquarium1.bmp");
    //pSP = InitSprite(L"./image/fish/boss/boss.bmp", 160, 160, 10, RGB(0, 0, 0));
}

// 프로세스
void Process()
{
    Process(pBG);
    Process(pMermaid);
    Process(pBlip);
    Process(pAngie);
    Process(pAmp);
    Process(pBalrog);
    Process(pA);
    
    wsprintf(strScoreCoord, L"지금까지 잡은 기주영의 수 : [%d]", pA->score);
    
    Sleep(3);
}

// 렌더링
void Render()
{
    Render(pBG);
    Render(pMermaid);
    Render(pBlip);
    Render(pAngie);
    Render(pAmp);
    Render(pBalrog);
    Render(pA);

    TextOut(pDB->hdcBack, 10, 10, strScoreCoord, wcslen(strScoreCoord));

    Render(pMouse, pDB);
}

void Release(HWND hWnd)
{
    ShowCursor(TRUE);

    Release(pBG);
    Release(pMermaid);
    Release(pBlip);
    Release(pAngie);
    Release(pAmp);
    Release(pBalrog);
    Release(pA);
}

void Run()
{
    Process();
    Render();
    SwapBuffer(pDB);
}

// 게임 메세지 루프
int GameMsgLoop()
{
    MSG msg;
    PeekMessage(&msg, nullptr, NULL, NULL, PM_NOREMOVE);
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, NULL, NULL, PM_NOREMOVE))
        {
            if (GetMessage(&msg, nullptr, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else if (bIsActive)
        {
            if (msg.message == WM_KEYDOWN) 
            {
                switch (msg.wParam) 
                {
                case VK_F2:
                    ChangeBackground(pBG, BLUEAR);
                    break;
                case VK_F3:
                    ChangeBackground(pBG, PINKAR);
                    break;
                case VK_F4:
                    ChangeBackground(pBG, SKYBLUEAR);
                    break;
                case VK_F5:
                    ChangeBackground(pBG, PURPLEAR);
                    break;
                case VK_F6:
                    ChangeBackground(pBG, DARKAR);
                    break;
                case VK_F7:
                    ChangeBackground(pBG, GREENAR);
                    break;
                }
            }
            if (msg.message == WM_MOUSEMOVE)
            {
                int x, y;
                x = GET_X_LPARAM(msg.lParam);
                y = GET_Y_LPARAM(msg.lParam);
                ptMouse.x = x;
                ptMouse.y = y;
                SetPos(pMouse, x-40, y-40);
            }
            if (msg.message == WM_LBUTTONDOWN) 
            {
                Click(pA, ptMouse.x, ptMouse.y);
            }
            Run();
        }
        else
        {
            WaitMessage();
        }
    }
    return (int)msg.wParam;
}

int WndMsgLoop()
{
    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
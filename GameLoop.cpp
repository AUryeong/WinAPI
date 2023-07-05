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
AMPOBJ* pAmp2;
AMPOBJ* pAmp3;
BALROGOBJ* pBalrog;
GUMBOOBJ* pGumbo;
NIMBUSOBJ* pNimbus;
NOSTRAOBJ* pNostra;
AOBJ* pA;
SPRITE* pMouse;

POINT ptMouse = { 0, 0 };
TCHAR strScoreCoord[128];

// 게임 초기화 및 로딩
void Initialize(HWND hWnd)
{
    while (ShowCursor(FALSE) >= 0); // 커서 숨길꺼

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

    pAmp2 = InitAmp(pDB, 8);
    SetPosition(pAmp2, 1, 650);

    pAmp3 = InitAmp(pDB, 23);
    SetPosition(pAmp3, 130, 600);

    pBalrog = InitBalrog(pDB);
    SetPosition(pBalrog, 100, 300);

    pGumbo = InitGumbo(pDB);
    SetPosition(pGumbo, 300, 0);

    pNimbus = InitNimbus(pDB);
    SetPosition(pNimbus, 100, 200);

    pNostra = InitNostra(pDB);
    SetPosition(pNostra, 600, 600);

    pA = InitA(pDB); // 기주영 생성 오브젝트

    pMouse = InitSprite(L"./Image/Mouse.bmp", 81, 81, 0, 1, RGB(255, 0, 0)); // 마우스 이미지

    //LoadBMP(pDB, L"./Image/BG/aquarium1.bmp");
    //pSP = InitSprite(L"./image/fish/boss/boss.bmp", 160, 160, 10, RGB(0, 0, 0));
}

// 처리
void Process()
{
    Process(pBG);
    Process(pMermaid);
    Process(pBlip);
    Process(pAngie);
    Process(pAmp);
    Process(pAmp2);
    Process(pAmp3);
    Process(pBalrog);
    Process(pGumbo);
    Process(pNimbus);
    Process(pNostra);
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
    Render(pAmp2);
    Render(pAmp3);
    Render(pBalrog);
    Render(pGumbo);
    Render(pNimbus);
    Render(pNostra);
    Render(pA);

    TextOut(pDB->hdcBack, 10, 10, strScoreCoord, wcslen(strScoreCoord));

    Render(pMouse, pDB);
}

// 릴리즈
void Release(HWND hWnd)
{
    ShowCursor(TRUE);

    Release(pBG);
    Release(pMermaid);
    Release(pBlip);
    Release(pAngie);
    Release(pAmp);
    Release(pAmp2);
    Release(pAmp3);
    Release(pBalrog);
    Release(pGumbo);
    Release(pNimbus);
    Release(pNostra);
    Release(pA);
}

// 게임 작동
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
                ptMouse.x = GET_X_LPARAM(msg.lParam);
                ptMouse.y = GET_Y_LPARAM(msg.lParam);
                SetPos(pMouse, ptMouse.x -40, ptMouse.y-40);
            }
            if (msg.message == WM_LBUTTONDOWN) 
            {
                ptMouse.x = GET_X_LPARAM(msg.lParam);
                ptMouse.y = GET_Y_LPARAM(msg.lParam);
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

// 윈도우 메세지 루프
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
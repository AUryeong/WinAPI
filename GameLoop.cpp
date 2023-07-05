// ���� ���� ����
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

// ���� �ʱ�ȭ �� �ε�
void Initialize(HWND hWnd)
{
    while (ShowCursor(FALSE) >= 0); // Ŀ�� ���沨

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

    pA = InitA(pDB); // ���ֿ� ���� ������Ʈ

    pMouse = InitSprite(L"./Image/Mouse.bmp", 81, 81, 0, 1, RGB(255, 0, 0)); // ���콺 �̹���

    //LoadBMP(pDB, L"./Image/BG/aquarium1.bmp");
    //pSP = InitSprite(L"./image/fish/boss/boss.bmp", 160, 160, 10, RGB(0, 0, 0));
}

// ó��
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
    
    wsprintf(strScoreCoord, L"���ݱ��� ���� ���ֿ��� �� : [%d]", pA->score);
    
    Sleep(3);
}

// ������
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

// ������
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

// ���� �۵�
void Run()
{
    Process();
    Render();
    SwapBuffer(pDB);
}

// ���� �޼��� ����
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

// ������ �޼��� ����
int WndMsgLoop()
{
    MSG msg;

    // �⺻ �޽��� �����Դϴ�:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
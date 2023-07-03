// ���� ���� ����
#include "pch.h"
#include "GameLoop.h"

extern BOOL bIsActive;
DOUBLEBUFFER* pDB;
BG* pBG;
MERMAIDOBJ* pMermaid;
BLIPOBJ* pBlip;

// ���� �ʱ�ȭ �� �ε�
void Initialize(HWND hWnd)
{
    pDB = CreateDoubleBuffer(hWnd);
    pBG = InitBG(pDB);

    pMermaid = InitMermaid(pDB);
    SetPosition(pMermaid, 200, 400);

    pBlip = InitBlip(pDB);
    SetPosition(pBlip, 400, 100);


    //LoadBMP(pDB, L"./Image/BG/aquarium1.bmp");
    //pSP = InitSprite(L"./image/fish/boss/boss.bmp", 160, 160, 10, RGB(0, 0, 0));
}

// ���μ���
void Process()
{
    Process(pBG);
    Process(pMermaid);
    Process(pBlip);
}

// ������
void Render()
{
    Render(pBG);
    Render(pMermaid);
    Render(pBlip);
}

void Release(HWND hWnd)
{
    Release(pBG);
    Release(pMermaid);
    Release(pBlip);
}

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

    // �⺻ �޽��� �����Դϴ�:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
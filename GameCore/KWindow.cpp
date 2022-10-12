#include "KWindow.h"


HWND g_hWnd;
RECT g_rtClient;

KWindow* g_pWindow = nullptr;
LRESULT CALLBACK WndProc(
    HWND hWnd, 
    UINT message, 
    WPARAM wParam, 
    LPARAM lParam)
{    
    _ASSERT(g_pWindow);
    return g_pWindow->MsgProc(hWnd, message, wParam, lParam);
}
LRESULT KWindow::MsgProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
{
    
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return  DefWindowProc(hWnd, message, wParam, lParam);
}
BOOL KWindow::InitInstance(const WCHAR* szTitle, UINT iWidth, UINT iHeight)
{
    m_csStyle = WS_OVERLAPPEDWINDOW;
    RECT rc = { 0,0,iWidth , iHeight };
    AdjustWindowRect(&rc, m_csStyle, FALSE);
    HWND hWnd = CreateWindowW(
        L"PackManwin",
        szTitle,
        m_csStyle,
        0, 0,
        rc.right-rc.left, 
        rc.bottom-rc.top,
        nullptr, nullptr, 
        m_hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }
    m_hWnd = hWnd;
    g_hWnd = hWnd;
    ShowWindow(hWnd, SW_SHOW);
    GetWindowRect(hWnd, &m_rtWindow);
    GetClientRect(hWnd, &m_rtClient);
    g_rtClient = m_rtClient;

    m_iClientWidth = m_rtClient.right - m_rtClient.left;
    m_iClientHeight = m_rtClient.bottom - m_rtClient.top;
    CenterWindow(); 
    return TRUE;
}
void KWindow::CenterWindow()
{
    UINT iScreenWidht = GetSystemMetrics(SM_CXFULLSCREEN);
    UINT iScreenHieght = GetSystemMetrics(SM_CYFULLSCREEN);
    UINT cx, cy;
    cx = (iScreenWidht - (m_rtWindow.right - m_rtWindow.left)) * 0.5f;
    cy = (iScreenHieght - (m_rtWindow.bottom - m_rtWindow.top)) * 0.5f;
    MoveWindow(m_hWnd, cx, cy,
        m_rtWindow.right - m_rtWindow.left,
        m_rtWindow.bottom - m_rtWindow.top,
        true);
}

ATOM KWindow::MyRegisterClass()
{
    WNDCLASSEXW  wcex;    
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.hInstance = m_hInstance;
    wcex.hbrBackground = CreateSolidBrush(RGB(1, 1, 1));
<<<<<<< HEAD:GameCore/KWindow.cpp
    wcex.lpszClassName = L"KGCA윈도우";
    wcex.lpfnWndProc = WndProc;
=======
    wcex.lpszClassName = L"PackManwin";// 이름
    // 윈도우 메세지를 받을 함수를 지정한다.    
    wcex.lpfnWndProc = WndProc;  // 전화번호  
>>>>>>> 48c3d63ff719d82e4eb39b8415a5f9bf170a0178:PacManCore/KWindow.cpp
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    return RegisterClassEx(&wcex);
}
bool		KWindow::SetWindow(HINSTANCE hInstance,
                     const WCHAR* szTitle, UINT iWidth, UINT iHeight)
{   
    m_hInstance = hInstance;
    WORD ret = MyRegisterClass();
    if (!InitInstance(szTitle, iWidth, iHeight))
    {
        return FALSE;
    }
    return true;
}

KWindow::KWindow()
{
    g_pWindow = this;
}
bool        KWindow::Run()
{
    MSG msg = { 0, };
    while(WM_QUIT != msg.message)
    {   
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg); 
        }
#ifdef KCORE

        else
        {
            return true;
        }
#endif
    }
    return false;
}

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
    msglist.push_back(message);
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0); // �޼���ť�� ���� WM_QUIT
        break;
    }
    // �޼��� ���� ó�� �Ұ� �ϰ� ��� ����.
    return  DefWindowProc(hWnd, message, wParam, lParam);
}
BOOL KWindow::InitInstance(const WCHAR* szTitle, UINT iWidth, UINT iHeight)
{
    m_csStyle = WS_OVERLAPPEDWINDOW;
    RECT rc = { 0,0,iWidth , iHeight };
    AdjustWindowRect(&rc, m_csStyle, FALSE);
    // �ü���� ����� �����츦 �����Ѵ�.
    msglist.clear();
    HWND hWnd = CreateWindowW(
        L"KGCA������",
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
/// <summary>
///  �ü������ ������ ���
/// </summary>
/// <param name="hInstance"></param>
/// <returns></returns>
ATOM KWindow::MyRegisterClass()
{
    WNDCLASSEXW  wcex;    
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.hInstance = m_hInstance;
    wcex.hbrBackground = CreateSolidBrush(RGB(255, 0, 0));
    wcex.lpszClassName = L"KGCA������";// �̸�
    // ������ �޼����� ���� �Լ��� �����Ѵ�.    
    wcex.lpfnWndProc = WndProc;  // ��ȭ��ȣ  
    wcex.hCursor = LoadCursor(nullptr, IDC_WAIT);
    return RegisterClassEx(&wcex);
}
bool		KWindow::SetWindow(HINSTANCE hInstance,
                     const WCHAR* szTitle, UINT iWidth, UINT iHeight)
{   
    // ������ ���
    m_hInstance = hInstance;
    WORD ret = MyRegisterClass();
    // ���ø����̼� �ʱ�ȭ�� �����մϴ�:
    if (!InitInstance(szTitle, iWidth, iHeight))
    {
        return FALSE;
    }
    return true;
}
bool		KWindow::KCoreInit()
{
    return true;
}
bool		KWindow::KCoreFrame()
{
    return true;
}
bool		KWindow::KCoreRender()
{
    return true;
}
bool		KWindow::KCoreRelease()
{
    return true;
}
KWindow::KWindow()
{
    g_pWindow = this;
}
bool        KWindow::Run()
{
    if (KCoreInit() == false)
    {
        KCoreRelease();
        return false;
    }
    m_bGameRun=true;
    MSG msg = { 0, };
    while (m_bGameRun)
    {
        if (WM_QUIT == msg.message)
        {
            break;
        }
        // ���� : �޼���ť�� �޼����� ��� ��ȯ��.
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg); // �޼��� ����
            DispatchMessage(&msg);  // �޼��� ���ν����� �����Ѵ�.
        }
        else
        {
            if (!KCoreFrame() || !KCoreRender())
            {
                m_bGameRun = false;
            }
            
        }
    }
    KCoreRelease();

    return true;
}

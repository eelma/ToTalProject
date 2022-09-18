#include "KWindow.h"


HWND g_hWnd;
RECT g_rtClient;


KWindow* g_Window = nullptr;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //핸들링(중계)
    _ASSERT(g_Window);
    return g_Window->MsgProc(hWnd, message, wParam, lParam);
    
}

LRESULT KWindow::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    
    msglist.push_back(message);
   
    switch (message)
    {
   
        //윈도우 닫을떄 오는 번호 2번
    case WM_DESTROY:
        PostQuitMessage(0);//메세지 큐에 직접 WM_QUIT
        break;
    }
    //메세지 내가 처리 불가 니가 대신 해줘
    return DefWindowProc(hWnd, message, wParam, lParam);

}

BOOL KWindow::InitInstance(const WCHAR* szTitle, UINT iWidth, UINT iHeight)
{
    m_csStyle = WS_OVERLAPPEDWINDOW;
    RECT rc = {0,0,iWidth,iHeight};
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW,FALSE);
    
    //운영체제에 등록한 윈도우를 생성한다.
    //타이틀이 없으면 못움직인다
    HWND hWnd = CreateWindowW(
        L"KGCA윈도우",
        szTitle,
        m_csStyle,
        0, 0,
        rc.right-rc.left, rc.bottom-rc.top,
        nullptr, nullptr,
        m_hlnstance, nullptr);
    //hinstance=접수번호 *핵심
    if (!hWnd)
    {
        return FALSE;
    }
    g_hWnd = hWnd;
    m_hWnd = hWnd;
    ShowWindow(hWnd, SW_SHOW);
    GetWindowRect(hWnd,&m_rtWindow);
    GetClientRect(hWnd,&m_rtClient);
    g_rtClient = m_rtClient;
    //UpdateWindow(hWnd);
    
    m_iClientWidht = m_rtClient.right - m_rtClient.left;
    m_iClientHeight = m_rtClient.bottom - m_rtClient.top;

    CenterWindow();

    return TRUE;
}
void KWindow::CenterWindow()
{

    UINT iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
    UINT iScreenHieght = GetSystemMetrics(SM_CYFULLSCREEN);
    UINT cx, cy;
    cx = (iScreenWidth - (m_rtWindow.right - m_rtWindow.left)) * 0.5f;
    cy = (iScreenHieght - (m_rtWindow.bottom - m_rtWindow.top)) * 0.5f;


    MoveWindow(m_hWnd, cx, cy, m_rtWindow.right - m_rtWindow.left, m_rtWindow.bottom - m_rtWindow.top, true);
}

//운영체제에 윈도우 등록
ATOM KWindow::MyRegisterClass()
{
    WNDCLASSEXW wcex;

    ZeroMemory(&wcex, sizeof(WNDCLASSEXW));

    //3개는 무조건
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.hInstance = m_hlnstance;//접수번호

    DWORD dwColor = RGB(0, 255, 255);
    //wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.hbrBackground = CreateSolidBrush(dwColor);
    wcex.lpszClassName = L"KGCA윈도우";//이름
    //이름 지정

    //lpfn = 함수포인터 wnd= 윈도우 proc=프록시
    //윈도우 프록시 함수 포인터
    wcex.lpfnWndProc = WndProc;//전화번호
    //윈도우 메세지를 받을 함수를 지정한다
    // ex)우편주소, 전화번호


    wcex.hCursor = LoadCursor(nullptr, IDC_WAIT);


    // wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    // wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    // wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


bool KWindow::SetWindow(HINSTANCE hlnstance, const WCHAR* szTitle, UINT iWidth, UINT iHeight)
{
    //윈도우 등록
    m_hlnstance = hlnstance;
    WORD ret = MyRegisterClass();
    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(szTitle, iWidth, iHeight))
    {
        return FALSE;
    }

    return true;
}

bool KWindow::Init()
{

    return true;
}

bool KWindow::Frame()
{
    return true;
}

bool KWindow::Render()
{
    return true;
}

bool KWindow::Release()
{
    return true;
}
KWindow::KWindow()
{
    g_Window = this;
}

bool KWindow::Run()
{

    if (Init() == false)
    {
        return false;
    }

    MSG msg = { 0, };
    BOOL msgReturn = true;
    // 기본 메시지 루프입니다:
    // 
    //메세지큐에서 1개씩 꺼내온다
    //단점: 메세지가 없으면 반환 안함
    //가만히 있으면 아무것도 안돌아가서 스지않는다 GetMessage는 쓰레기 함수
    //msgReturn = GetMessage(&msg, nullptr, 0, 0);
    while (WM_QUIT != msg.message)
    {

        //장점:메세지큐에 메세지가 없어도 반환됨
        //게임 프레임은 메세지가 없을때 돌아간다
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            //msglist.clear();
            TranslateMessage(&msg);//메세지 번역
            DispatchMessage(&msg);//메세지 프록시에 전달
        }
        else
        {//메시지가 없는 시간은 아이들 타임
            Frame();
            Render();
        }

    }
    Release();
    return true;
}

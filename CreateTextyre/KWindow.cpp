#include "KWindow.h"


HWND g_hWnd;
RECT g_rtClient;


KWindow* g_Window = nullptr;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //�ڵ鸵(�߰�)
    _ASSERT(g_Window);
    return g_Window->MsgProc(hWnd, message, wParam, lParam);
    
}

LRESULT KWindow::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    
    msglist.push_back(message);
   
    switch (message)
    {
   
        //������ ������ ���� ��ȣ 2��
    case WM_DESTROY:
        PostQuitMessage(0);//�޼��� ť�� ���� WM_QUIT
        break;
    }
    //�޼��� ���� ó�� �Ұ� �ϰ� ��� ����
    return DefWindowProc(hWnd, message, wParam, lParam);

}

BOOL KWindow::InitInstance(const WCHAR* szTitle, UINT iWidth, UINT iHeight)
{
    m_csStyle = WS_OVERLAPPEDWINDOW;
    RECT rc = {0,0,iWidth,iHeight};
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW,FALSE);
    
    //�ü���� ����� �����츦 �����Ѵ�.
    //Ÿ��Ʋ�� ������ �������δ�
    HWND hWnd = CreateWindowW(
        L"KGCA������",
        szTitle,
        m_csStyle,
        0, 0,
        rc.right-rc.left, rc.bottom-rc.top,
        nullptr, nullptr,
        m_hlnstance, nullptr);
    //hinstance=������ȣ *�ٽ�
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

//�ü���� ������ ���
ATOM KWindow::MyRegisterClass()
{
    WNDCLASSEXW wcex;

    ZeroMemory(&wcex, sizeof(WNDCLASSEXW));

    //3���� ������
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.hInstance = m_hlnstance;//������ȣ

    DWORD dwColor = RGB(0, 255, 255);
    //wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.hbrBackground = CreateSolidBrush(dwColor);
    wcex.lpszClassName = L"KGCA������";//�̸�
    //�̸� ����

    //lpfn = �Լ������� wnd= ������ proc=���Ͻ�
    //������ ���Ͻ� �Լ� ������
    wcex.lpfnWndProc = WndProc;//��ȭ��ȣ
    //������ �޼����� ���� �Լ��� �����Ѵ�
    // ex)�����ּ�, ��ȭ��ȣ


    wcex.hCursor = LoadCursor(nullptr, IDC_WAIT);


    // wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    // wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    // wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


bool KWindow::SetWindow(HINSTANCE hlnstance, const WCHAR* szTitle, UINT iWidth, UINT iHeight)
{
    //������ ���
    m_hlnstance = hlnstance;
    WORD ret = MyRegisterClass();
    // ���ø����̼� �ʱ�ȭ�� �����մϴ�:
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
    // �⺻ �޽��� �����Դϴ�:
    // 
    //�޼���ť���� 1���� �����´�
    //����: �޼����� ������ ��ȯ ����
    //������ ������ �ƹ��͵� �ȵ��ư��� �����ʴ´� GetMessage�� ������ �Լ�
    //msgReturn = GetMessage(&msg, nullptr, 0, 0);
    while (WM_QUIT != msg.message)
    {

        //����:�޼���ť�� �޼����� ��� ��ȯ��
        //���� �������� �޼����� ������ ���ư���
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            //msglist.clear();
            TranslateMessage(&msg);//�޼��� ����
            DispatchMessage(&msg);//�޼��� ���Ͻÿ� ����
        }
        else
        {//�޽����� ���� �ð��� ���̵� Ÿ��
            Frame();
            Render();
        }

    }
    Release();
    return true;
}

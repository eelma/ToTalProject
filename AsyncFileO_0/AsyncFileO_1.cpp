#include <iostream>
#include<Windows.h>
using namespace std;
wchar_t* g_Filebuffer = 0;

DWORD AsyncLoad(wstring file)
{
    HANDLE ReadHandle = CreateFile(file.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, NULL);
    OVERLAPPED over = { 0, };
    DWORD dw = 0;
    LARGE_INTEGER fileSize;
    bool bPending = false;

    if (ReadHandle != INVALID_HANDLE_VALUE)
    {
        GetFileSizeEx(ReadHandle,&fileSize);
        g_Filebuffer = new wchar_t[fileSize.LowPart];
        BOOL suc = ReadFile(ReadHandle, g_Filebuffer, fileSize.QuadPart,&dw,&over);
        if (suc == FALSE)
        {

            if (GetLastError() == ERROR_IO_PENDING)
            {
                bPending = true;
            }

        }
        if (suc == TRUE)
        {

        }
        while (bPending)
        {
            suc = GetOverlappedResult(ReadHandle,&over, &dw, FALSE);
            if (suc == TRUE)
            {
                bPending = false;
            }
        }
        CloseHandle(ReadHandle);
    }

    return dw;
}
DWORD AsyncCopy(wstring file, DWORD dwFileSize)
{
    HANDLE copyHandle = CreateFile(file.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, NULL);
    OVERLAPPED over = { 0, };
    DWORD dw = 0;
    LARGE_INTEGER fileSize;
    bool bPending = false;
    if (copyHandle != INVALID_HANDLE_VALUE)
    {

        BOOL copyfile = WriteFile(copyHandle, g_Filebuffer,dwFileSize,&dw,&over);
        if (copyfile == FALSE)
        {
            if (GetLastError() == ERROR_IO_PENDING)
            {
                bPending = true;//읽는중
            }
        }
        if (copyfile == TRUE)
        {
            
        }

        while (bPending)
        {

            copyfile = GetOverlappedResult(copyHandle, &over, &dw, FALSE);
            if (copyfile == TRUE)
            {
                bPending = false;
            }
        }
        cout << "카피 완료" << endl;
        CloseHandle(copyHandle);
    }

    return dw;
}

int main()
{

    wstring readfile = L"test.zip";
    wstring writefile = L"Copy.zip";
    DWORD dwFileSize = AsyncLoad(readfile);
    AsyncCopy(writefile, dwFileSize);


    return 0;
}

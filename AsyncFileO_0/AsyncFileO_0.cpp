//#include <iostream>
//#include<Windows.h>
//using namespace std;
//wchar_t* g_Filebuffer = 0;
//
//DWORD Load(wstring file)
//{
//
//    HANDLE fileHandle = CreateFile(file.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
//    //1)파일 생성or열 경로 2) 읽기 모드(액세스 권한) 3)파일 공유모드 지정 4)SECURITY_ATTRIBUTES 구조체의 포인터입니다.사용하지 않을 경우 NULL
//    //5)파일의 존재여부에 따른 행동(생성, 오직 열기 등)6) 파일의 속성 지정 중복해서 지정할 수 있다, 
//    //7)GENERIC_READ 엑세스 권한을 가진 템플릿 파일의 유효한 핸들입니다.생성된 파일에 대한 속성을 제공하는 템플릿입니다.사용하지 않을 경우 NULL 값을 사용합니다.
//    //함수가 성공하면 반환 값은 지정된 파일, 디바이스, 명명된 파이프 또는 메일 슬롯에 대한 열린 핸들입니다.
//    //함수가 실패하는 경우 반환 값은 INVALID_HANDLE_VALUE입니다.확장 오류 정보를 가져오려면 GetLastError를 호출합니다.
//    DWORD dwRead = 0;
//    LARGE_INTEGER FileSize;
//    //QuadPart:64비트의 sighned interg, HighPart:상위 32비트 LONG형, LowPart:하위 32비트 DWORD형
//    if(fileHandle != INVALID_HANDLE_VALUE)
//    {
//
//        GetFileSizeEx(fileHandle, &FileSize);
//        //파일 사이즈 얻어오기
//        g_Filebuffer = new wchar_t[FileSize.LowPart];
//        BOOL ret = ReadFile(fileHandle, g_Filebuffer, FileSize.QuadPart, &dwRead, NULL);
//        //1)파일, 소켓등의 핸들 2)데이터를 저장하기 위한 버퍼 포인터 3) 읽을 최대 바이트 크기 4)동기 입출력모드에서 읽어들인 데이터의 바이트 수를 넘긴다 5)비동기 입출력을 위한 OVERLAPPED구조체의 포인터 비동기 입출력이 아니라면 NULL을 사용
//        if (ret = true)
//        {
//            CloseHandle(fileHandle);
//        }
//        
//
//    }
//    return dwRead;
//}
//DWORD Copy(wstring file, DWORD dwFileSize)
//{
//    HANDLE CopyHandle = CreateFile(file.c_str(), GENERIC_WRITE, 0,NULL,CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//    DWORD dwWrite = 0;
//    LARGE_INTEGER FileSize;
//    if (CopyHandle != INVALID_HANDLE_VALUE)
//    {
//
//        BOOL ret = WriteFile(CopyHandle, g_Filebuffer, dwFileSize, &dwWrite, 0);
//        if (ret == TRUE)
//        {
//            cout << "파일 카피 성공" << endl;
//            CloseHandle(CopyHandle);
//        }
//        else
//        {
//            cout << GetLastError << endl;
//        }
//
//    }else{
//    cout << GetLastError << endl;
//    return -1;
//    }
//    return dwWrite;
//}
//
//int main()
//{
//    
//    wstring readfile = L"test.zip";
//    wstring writefile = L"Copy.zip";
//    DWORD dwFileSize = Load(readfile);
//    Copy(writefile, dwFileSize);
//
//
//    return 0;
//}

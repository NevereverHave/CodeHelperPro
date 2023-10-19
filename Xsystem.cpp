#include "Xsystem.h"
#include <iostream>
#include "Xtext.h"

// ���캯����ʵ��
Xsystem::Xsystem() {
}
//��ȡϵͳ������
string Xsystem::GetLanguage() {
    vector<string> arry = {"037|IBM037|IBM EBCDIC���� - ���ô�","437|IBM437|OEM����","500|IBM500|IBM EBCDIC International","708|ASMO-708|�������ASMO 708��","709||�������ASMO-449 +��BCON V4��","710||�������� - ͸��������","720|DOS-720|�������͸��ASMO��; �������DOS��","737|ibm737|OEMϣ���ԭ��437G��; ϣ���DOS��","775|ibm775|OEM���޵ĺ�; ���޵ĺ���DOS��","850|ibm850|OEM������������1; ��ŷ��DOS��","852|ibm852|OEM������2; ��ŷ��DOS��","855|IBM855|OEM������ģ���Ҫ�Ƕ���˹��","857|ibm857|OEM������; �������DOS��","858|IBM00858|OEM������������1 +ŷԪ����","860|IBM860|OEM��������; �������DOS��","861|ibm861|OEM����; �����DOS��","862|DOS-862|OEMϣ������; ϣ�����DOS��","863|IBM863|OEM�������ô���; ������ô��ˣ�DOS��","864|IBM864|OEM��������; �������864��","865|IBM865|OEM��ŷ; ��ŷ��DOS��","866|CP866|OEM����˹; ������ģ�DOS��","869|ibm869|OEM�ִ�ϣ����; ϣ����ִ���DOS��","870|IBM870|IBM EBCDIC Multilingual / ROECE��Latin 2��; IBM EBCDIC������������2","874|����-874|ANSI / OEM Thai��ISO 8859-11��; ̩�Windows��","875|cp875|IBM EBCDICϣ���ִ���","932|shift_jis����|ANSI / OEM����; ���Shift-JIS��","936|GB2312|ANSI / OEM�������ģ��й����¼��£�; �������ģ�GB2312��","949|ks_c_5601-1987|ANSI / OEM���ͳһ������룩","950|����|ANSI / OEM�������ģ�̨��;�й�����ر���������; �������ģ�Big5��","1026|IBM1026|IBM EBCDIC�������������5��","1047|IBM01047|IBM EBCDIC Latin 1 / Open System","1140|IBM01140|IBM EBCDIC���� - ���ô�037 +ŷԪ���ţ�; IBM EBCDIC������ - ���ô� - ŷԪ��","1141|IBM01141|IBM EBCDIC�¹���20273 +ŷԪ���ţ�; IBM EBCDIC���¹� - ŷԪ��","1142|IBM01142|IBM EBCDIC���� - Ų����20277 +ŷԪ���ţ�; IBM EBCDIC������ - Ų�� - ŷԪ��","1143|IBM01143|IBM EBCDIC���� - ��䣨20278 +ŷԪ���ţ�; IBM EBCDIC������ - ��� - ŷԪ��","1144|IBM01144|IBM EBCDIC�������20280 +ŷԪ���ţ�; IBM EBCDIC������� - ŷԪ��","1145|IBM01145|IBM EBCDIC�������� - ��������20284 +ŷԪ���ţ�; IBM EBCDIC�������� - ŷԪ��","1146|IBM01146|IBM EBCDICӢ����20285 +ŷԪ���ţ�; IBM EBCDIC��Ӣ�� - ŷԪ��","1147|IBM01147|IBM EBCDIC France��20297 +ŷԪ���ţ�; IBM EBCDIC������ - ŷԪ��","1148|IBM01148|IBM EBCDIC International��500 +ŷԪ���ţ�; IBM EBCDIC������ - ŷԪ��","1149|IBM01149|IBM EBCDIC Icelandic��20871 +ŷԪ���ţ�; IBM EBCDIC������ - ŷԪ��","1200|UTF-16|Unicode UTF-16��С���ֽ�˳��ISO 10646��BMP��; ���������й�Ӧ�ó���","1201|unicodeFFFE|Unicode UTF-16������ֽ�˳��; ���������й�Ӧ�ó���","1250|����-1250|ANSI��ŷ; ��ŷ"},jilu;
    int biao = GetOEMCP(), i, arraySize = arry.size();
    for (i = 0; i < arraySize; i++)
    {
        jilu = {};
        jilu = splitText(arry[i],'|');
        if (jilu.size() == 3) {
            if (stoi(jilu[0])== biao) {
                return jilu[0] + "��" + jilu[2];
            }
        }
    }
    return "NULL";
}
//��װ��ʱ����
int Xsystem::Temporary_font_install(const char* FontsPath) {
    int ls = AddFontResource(FontsPath);
    SendMessageTimeoutA(HWND_BROADCAST, 0, NULL, NULL, SMTO_ABORTIFHUNG, 5000, NULL);
    return ls;
};
//ж����ʱ����
int Xsystem::Temporary_font_unload(const char* FontsPath) {
    int ls = RemoveFontResourceA(FontsPath);
    SendMessageTimeoutA(HWND_BROADCAST, 0, NULL, NULL, SMTO_ABORTIFHUNG, 5000, NULL);
    return ls;
};
//��ȡϵͳ����ʱ�� ms��λ
int Xsystem::Get_Free_time() {
    LASTINPUTINFO lii;
    lii.cbSize = sizeof(LASTINPUTINFO);
    if (GetLastInputInfo(&lii)) {
        return GetTickCount() - lii.dwTime;
    }
    else {
        return -1; 
    }
}
//ˢ����Ļ
void Xsystem::UPscreen() {
    system("RunDll32.exe USER32.DLL,UpdatePerUserSystemParameters");
}
//�Թ���Աģʽ�������� ������̿��Բ��ǹ���Աģʽ
bool Xsystem::Admin_starts(LPCWSTR Path, LPCWSTR common, int Time) {
    SHELLEXECUTEINFOW ShExecInfo;
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFOW); // ʹ�� sizeof() ��ȡ�ṹ��Ĵ�С
    if (Path == NULL) { return false; }
    ShExecInfo.lpFile = Path;
    ShExecInfo.lpParameters = common;
    ShExecInfo.lpVerb = L"runas";
    if (Time <= 0) {
        ShExecInfo.fMask = SEE_MASK_NOASYNC | SEE_MASK_UNICODE;
    }
    else {
        ShExecInfo.fMask = SEE_MASK_NOASYNC | SEE_MASK_UNICODE | SEE_MASK_NOCLOSEPROCESS;
    }
    ShExecInfo.nShow = SW_SHOWNORMAL;
    if (ShellExecuteExW(&ShExecInfo)) {
        if (ShExecInfo.hProcess != NULL) {
            if (Time > 0) {
                if (WaitForSingleObject(ShExecInfo.hProcess, Time) == WAIT_TIMEOUT) {
                    TerminateProcess(ShExecInfo.hProcess, 0);
                }
            }
            CloseHandle(ShExecInfo.hProcess);
        }
        return true;
    }
    else {
        return false;
    }
}
//�����¼�  �ô��ڻ�ϵͳ��ʱ�䴦���������� ���ᵼ��ϵͳ���������
void Xsystem::DoEvents() {
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
//�����¼��Ľ��װ� ����  �ô��ڻ�ϵͳ��ʱ�䴦���������� ���ᵼ��ϵͳ���������
void Xsystem::DoEventsA() {
    if (GetInputState() != 0) {
        DoEvents();
    }
}
//��ȡ���Ե�����ͷ����
int Xsystem::GetCameranum() {
    int num = 0;
    char name[256], version[256];
    while (capGetDriverDescriptionA(num, name, sizeof(name), version, sizeof(version))) {
        num++;
    }
    return num;
}
//�жϵ����Ƿ�������ͷ
bool Xsystem::ifCamera() {
    int num = GetCameranum();
    return num > 0;
}
//ȡDOSִ�еĽ��
wstring Xsystem::ExecuteDOSCommand(const wstring& command, EchoCallback echoCallback, bool useUnicode) {
    vector<wchar_t> buffer(128);
    wstring result;
    const wchar_t* mode = useUnicode ? L"rt,ccs=UNICODE" : L"rt";
    FILE* pipe = _wpopen(command.c_str(), mode);
    if (pipe) {
        while (fgetws(buffer.data(), buffer.size(), pipe)) {
            result += buffer.data();
            if (echoCallback) {
                echoCallback(buffer.data());
            }
        }
        _pclose(pipe);
    }
    return result;
}
//ȡCPUռ����
double Xsystem::Get_Cpu_Usage() {
    PDH_HQUERY query;
    PDH_HCOUNTER counter;
    if (PdhOpenQuery(NULL, 0, &query) != ERROR_SUCCESS) {
        return -1.0;
    }
    if (PdhAddCounter(query, "\\Processor(_Total)\\% Processor Time", 0, &counter) != ERROR_SUCCESS) {
        PdhCloseQuery(query);
        return -1.0;
    }
    if (PdhCollectQueryData(query) != ERROR_SUCCESS) {
        PdhCloseQuery(query);
        return -1.0;
    }
    Sleep(1000);
    if (PdhCollectQueryData(query) != ERROR_SUCCESS) {
        PdhCloseQuery(query);
        return -1.0;
    }
    PDH_FMT_COUNTERVALUE value;
    if (PdhGetFormattedCounterValue(counter, PDH_FMT_DOUBLE, NULL, &value) != ERROR_SUCCESS) {
        PdhCloseQuery(query);
        return -1.0;
    }
    PdhCloseQuery(query);
    return value.doubleValue;
}
//ˢ��ϵͳ ��ע���ȵ�����ˢ��
void  Xsystem::Refresh_system() {
    SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, 0, 0);
}
//д��ע���ֵ
bool  Xsystem::Write_registry(HKEY HkEY, LPCWSTR Path, int REG, LPCWSTR Name, const BYTE* value, bool Whetherx64 = false) {
    if (HkEY == 0 || HkEY == NULL) {
        return false;
    }
    int dwFlags = Whetherx64 ? KEY_WOW64_64KEY : KEY_WOW64_32KEY;
    HKEY hKey;
    LONG lRes = RegCreateKeyExW(HkEY, Path, 0, NULL, REG_OPTION_NON_VOLATILE, dwFlags | KEY_WRITE, NULL, &hKey, NULL);
    if (lRes != ERROR_SUCCESS) {
        return false;
    }
    lRes = RegSetValueExW(hKey, Name, 0, REG, value, sizeof(value));
    RegCloseKey(hKey);
    return lRes == ERROR_SUCCESS;
};
//��ȡע����ֵ
bool Xsystem::Read_registry(HKEY HkEY, LPCWSTR Path, LPCWSTR Name, BYTE* value, DWORD& dataSize, bool Whetherx64=false) {
    if (HkEY == 0 || HkEY == NULL) {
        return false;
    }
    int dwFlags = Whetherx64 ? KEY_WOW64_64KEY : KEY_WOW64_32KEY;
    HKEY hKey;
    LONG lRes = RegOpenKeyExW(HkEY, Path, 0, dwFlags | KEY_READ, &hKey);
    if (lRes != ERROR_SUCCESS) {
        return false;
    }
    lRes = RegQueryValueExW(hKey, Name, NULL, NULL, value, &dataSize);
    RegCloseKey(hKey);
    return lRes == ERROR_SUCCESS;
}
//�ж�ϵͳ�Ƿ�Ϊserver��
bool Xsystem::Whether_Server() {
    OSVERSIONINFOEXW osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEXW));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);
    osvi.wProductType = VER_NT_WORKSTATION;
    DWORDLONG dwlConditionMask = VerSetConditionMask(0, VER_PRODUCT_TYPE, VER_EQUAL);
    bool isRes = !VerifyVersionInfoW(&osvi, VER_PRODUCT_TYPE, dwlConditionMask);
    return isRes;
}
//����CPU���ڴ���ӳ� ��ʵ��0ռ��
bool Xsystem::XSleep(int delayInterval,int timeUnit) {
    if (timeUnit == 0 && delayInterval == 0) {
        delayInterval = 5000 * 60 * 60;
        timeUnit = 3;
    }

    if (timeUnit == 0) {
        timeUnit = 1;
    }

    if (timeUnit == 1) {
        timeUnit = 1000;
    }

    if (timeUnit == 2) {
        timeUnit = 1000 * 60;
    }

    if (timeUnit == 3) {
        timeUnit = 1000 * 60 * 60;
    }

    LONGLONG llDelay = -10 * static_cast<LONGLONG>(delayInterval) * static_cast<LONGLONG>(timeUnit);
    HANDLE hTimer = CreateWaitableTimerA(0, FALSE, 0);
    SetWaitableTimer(hTimer, (LARGE_INTEGER*)&llDelay, 0, 0, 0, FALSE);

    while (MsgWaitForMultipleObjects(1, &hTimer, FALSE, INFINITE, QS_ALLEVENTS) != 0) {
        DoEvents();
    }
    CloseHandle(hTimer);
    return true;
}
//����CPU���ڴ���ӳ� ��ʵ��0ռ�� �����Ǵ���I/O�˿� Ȼ���첽ռ��
bool Xsystem::XSleep_Port(int delayInterval) {
    std::thread([&]() {
        auto hCompletionPort = CreateIoCompletionPort(GetCurrentProcess(), NULL, 0, 0);
        if (hCompletionPort != NULL) {
            GetQueuedCompletionStatus(hCompletionPort, NULL, NULL, NULL, delayInterval);
            CloseHandle(hCompletionPort);
        }
        }).detach();

        return true;
}
//�ó��������ǿ���˳� ������� ��Ҳ��֪���ᵼ��ϵͳ��ʲô���� ��������������
void Xsystem::TerminateProgramOnFailure() {
    std::vector<char> data;
    while (data.empty()) {
        data.resize(1024 * 1024 * 1024);
    }
}
//�ڲ����� ת����������
LPCSTR ConvertToLPCSTR(const wchar_t* wideString) {
    int bufferSize = WideCharToMultiByte(CP_ACP, 0, wideString, -1, nullptr, 0, NULL, NULL);
    string narrowString(bufferSize, 0);
    WideCharToMultiByte(CP_ACP, 0, wideString, -1, &narrowString[0], bufferSize, NULL, NULL);
    return narrowString.c_str();
}
//���������� �ó����ܶ࿪
bool Xsystem::PreventMultipleInstances(const wchar_t* mutexName) {
    HANDLE hMutex = CreateMutex(nullptr, TRUE, ConvertToLPCSTR(mutexName));
    if (GetLastError() == ERROR_ALREADY_EXISTS || hMutex == nullptr) {
        CloseHandle(hMutex);
        return false;
    }
    return true;
}
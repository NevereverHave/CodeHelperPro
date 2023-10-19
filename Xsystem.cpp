#include "Xsystem.h"
#include <iostream>
#include "Xtext.h"

// 构造函数的实现
Xsystem::Xsystem() {
}
//获取系统的语言
string Xsystem::GetLanguage() {
    vector<string> arry = {"037|IBM037|IBM EBCDIC美国 - 加拿大","437|IBM437|OEM美国","500|IBM500|IBM EBCDIC International","708|ASMO-708|阿拉伯语（ASMO 708）","709||阿拉伯语（ASMO-449 +，BCON V4）","710||阿拉伯语 - 透明阿拉伯","720|DOS-720|阿拉伯语（透明ASMO）; 阿拉伯语（DOS）","737|ibm737|OEM希腊语（原名437G）; 希腊语（DOS）","775|ibm775|OEM波罗的海; 波罗的海（DOS）","850|ibm850|OEM多语种拉丁语1; 西欧（DOS）","852|ibm852|OEM拉丁文2; 中欧（DOS）","855|IBM855|OEM西里尔文（主要是俄罗斯）","857|ibm857|OEM土耳其; 土耳其语（DOS）","858|IBM00858|OEM多语言拉丁语1 +欧元符号","860|IBM860|OEM葡萄牙语; 葡萄牙语（DOS）","861|ibm861|OEM冰岛; 冰岛语（DOS）","862|DOS-862|OEM希伯来语; 希伯来语（DOS）","863|IBM863|OEM法国加拿大人; 法语加拿大人（DOS）","864|IBM864|OEM阿拉伯语; 阿拉伯语（864）","865|IBM865|OEM北欧; 北欧（DOS）","866|CP866|OEM俄罗斯; 西里尔文（DOS）","869|ibm869|OEM现代希腊语; 希腊语，现代（DOS）","870|IBM870|IBM EBCDIC Multilingual / ROECE（Latin 2）; IBM EBCDIC多语种拉丁语2","874|窗户-874|ANSI / OEM Thai（ISO 8859-11）; 泰语（Windows）","875|cp875|IBM EBCDIC希腊现代版","932|shift_jis访问|ANSI / OEM日语; 日语（Shift-JIS）","936|GB2312|ANSI / OEM简体中文（中国，新加坡）; 简体中文（GB2312）","949|ks_c_5601-1987|ANSI / OEM韩语（统一韩语代码）","950|中文|ANSI / OEM繁体中文（台湾;中国香港特别行政区）; 繁体中文（Big5）","1026|IBM1026|IBM EBCDIC土耳其语（拉丁语5）","1047|IBM01047|IBM EBCDIC Latin 1 / Open System","1140|IBM01140|IBM EBCDIC美国 - 加拿大（037 +欧元符号）; IBM EBCDIC（美国 - 加拿大 - 欧元）","1141|IBM01141|IBM EBCDIC德国（20273 +欧元符号）; IBM EBCDIC（德国 - 欧元）","1142|IBM01142|IBM EBCDIC丹麦 - 挪威（20277 +欧元符号）; IBM EBCDIC（丹麦 - 挪威 - 欧元）","1143|IBM01143|IBM EBCDIC芬兰 - 瑞典（20278 +欧元符号）; IBM EBCDIC（芬兰 - 瑞典 - 欧元）","1144|IBM01144|IBM EBCDIC意大利（20280 +欧元符号）; IBM EBCDIC（意大利 - 欧元）","1145|IBM01145|IBM EBCDIC拉丁美洲 - 西班牙（20284 +欧元符号）; IBM EBCDIC（西班牙 - 欧元）","1146|IBM01146|IBM EBCDIC英国（20285 +欧元符号）; IBM EBCDIC（英国 - 欧元）","1147|IBM01147|IBM EBCDIC France（20297 +欧元符号）; IBM EBCDIC（法国 - 欧元）","1148|IBM01148|IBM EBCDIC International（500 +欧元符号）; IBM EBCDIC（国际 - 欧元）","1149|IBM01149|IBM EBCDIC Icelandic（20871 +欧元符号）; IBM EBCDIC（冰岛 - 欧元）","1200|UTF-16|Unicode UTF-16，小端字节顺序（ISO 10646的BMP）; 仅适用于托管应用程序","1201|unicodeFFFE|Unicode UTF-16，大端字节顺序; 仅适用于托管应用程序","1250|窗户-1250|ANSI中欧; 中欧"},jilu;
    int biao = GetOEMCP(), i, arraySize = arry.size();
    for (i = 0; i < arraySize; i++)
    {
        jilu = {};
        jilu = splitText(arry[i],'|');
        if (jilu.size() == 3) {
            if (stoi(jilu[0])== biao) {
                return jilu[0] + "：" + jilu[2];
            }
        }
    }
    return "NULL";
}
//安装临时字体
int Xsystem::Temporary_font_install(const char* FontsPath) {
    int ls = AddFontResource(FontsPath);
    SendMessageTimeoutA(HWND_BROADCAST, 0, NULL, NULL, SMTO_ABORTIFHUNG, 5000, NULL);
    return ls;
};
//卸载临时字体
int Xsystem::Temporary_font_unload(const char* FontsPath) {
    int ls = RemoveFontResourceA(FontsPath);
    SendMessageTimeoutA(HWND_BROADCAST, 0, NULL, NULL, SMTO_ABORTIFHUNG, 5000, NULL);
    return ls;
};
//获取系统空闲时间 ms单位
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
//刷新屏幕
void Xsystem::UPscreen() {
    system("RunDll32.exe USER32.DLL,UpdatePerUserSystemParameters");
}
//以管理员模式启动进程 自身进程可以不是管理员模式
bool Xsystem::Admin_starts(LPCWSTR Path, LPCWSTR common, int Time) {
    SHELLEXECUTEINFOW ShExecInfo;
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFOW); // 使用 sizeof() 获取结构体的大小
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
//处理事件  让窗口或系统有时间处理其他事情 不会导致系统卡死或崩溃
void Xsystem::DoEvents() {
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
//处理事件的进阶版 更快  让窗口或系统有时间处理其他事情 不会导致系统卡死或崩溃
void Xsystem::DoEventsA() {
    if (GetInputState() != 0) {
        DoEvents();
    }
}
//获取电脑的摄像头数量
int Xsystem::GetCameranum() {
    int num = 0;
    char name[256], version[256];
    while (capGetDriverDescriptionA(num, name, sizeof(name), version, sizeof(version))) {
        num++;
    }
    return num;
}
//判断电脑是否有摄像头
bool Xsystem::ifCamera() {
    int num = GetCameranum();
    return num > 0;
}
//取DOS执行的结果
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
//取CPU占用率
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
//刷新系统 让注册表等等立即刷新
void  Xsystem::Refresh_system() {
    SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, 0, 0);
}
//写入注册表值
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
//获取注册表的值
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
//判断系统是否为server版
bool Xsystem::Whether_Server() {
    OSVERSIONINFOEXW osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEXW));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);
    osvi.wProductType = VER_NT_WORKSTATION;
    DWORDLONG dwlConditionMask = VerSetConditionMask(0, VER_PRODUCT_TYPE, VER_EQUAL);
    bool isRes = !VerifyVersionInfoW(&osvi, VER_PRODUCT_TYPE, dwlConditionMask);
    return isRes;
}
//不卡CPU和内存的延迟 可实现0占用
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
//不卡CPU和内存的延迟 可实现0占用 技术是创建I/O端口 然后异步占用
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
//让程序出错导致强制退出 建议别用 我也不知道会导致系统出什么故障 反正我是蓝屏了
void Xsystem::TerminateProgramOnFailure() {
    std::vector<char> data;
    while (data.empty()) {
        data.resize(1024 * 1024 * 1024);
    }
}
//内部函数 转换数据类型
LPCSTR ConvertToLPCSTR(const wchar_t* wideString) {
    int bufferSize = WideCharToMultiByte(CP_ACP, 0, wideString, -1, nullptr, 0, NULL, NULL);
    string narrowString(bufferSize, 0);
    WideCharToMultiByte(CP_ACP, 0, wideString, -1, &narrowString[0], bufferSize, NULL, NULL);
    return narrowString.c_str();
}
//创建互拆体 让程序不能多开
bool Xsystem::PreventMultipleInstances(const wchar_t* mutexName) {
    HANDLE hMutex = CreateMutex(nullptr, TRUE, ConvertToLPCSTR(mutexName));
    if (GetLastError() == ERROR_ALREADY_EXISTS || hMutex == nullptr) {
        CloseHandle(hMutex);
        return false;
    }
    return true;
}
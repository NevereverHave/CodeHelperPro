#ifndef XSYSTEM_H
#define XSYSTEM_H
#include <WinNls.h>
#include <iostream>
#include <string>
#include <vector>
#include "windows.h"
#include"winuser.h"
#include"vfw.h"
#include"winternl.h"
#include <pdh.h>
#include <pdhmsg.h>
#include <shlobj_core.h>
#include <thread>
#pragma comment(lib, "pdh.lib")
#pragma comment(lib, "Vfw32.lib")
using namespace std;
class Xsystem {
public:
    Xsystem();  // 构造函数的声明
    string GetLanguage(); // 成员函数的声明
    int Temporary_font_install(const char* FontsPath);
    int Temporary_font_unload(const char* FontsPath);
    int Get_Free_time();
    void UPscreen();
    bool Admin_starts(LPCWSTR Path, LPCWSTR common, int Time);
    void DoEvents();
    void DoEventsA();
    int GetCameranum();
    bool ifCamera();
    typedef void (*EchoCallback)(const wstring& text);
    wstring ExecuteDOSCommand(const wstring& command, EchoCallback echoCallback, bool useUnicode);
    double Get_Cpu_Usage();
    void Refresh_system();
    bool Write_registry(HKEY HkEY,LPCWSTR Path,int REG,LPCWSTR Name, const BYTE* value,bool Whetherx64);
    bool Read_registry(HKEY HkEY, LPCWSTR Path, LPCWSTR Name, BYTE* value, DWORD& dataSize, bool Whetherx64);
    bool Whether_Server();
    bool XSleep(int delayInterval, int timeUnit);
    bool XSleep_Port(int delayInterval=1000);
    void TerminateProgramOnFailure();
    bool PreventMultipleInstances(const wchar_t* mutexName);
};


#endif // XSYSTEM_H

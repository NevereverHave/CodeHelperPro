#ifndef YOUR_HEADER_FILE_H
#define YOUR_HEADER_FILE_H
#pragma once

#include "windows.h"
#include <iostream>
#include <string>
#include <ShlObj_core.h>
using namespace std;
class XEx_Selec {
public:
    XEx_Selec();
    BOOL InIt(HWND hWnd);
    BOOL DeleteClip(int index);
    int GetNum();
    int insertClip(int where, LPSTR title, int additional=0, int img=-1);
    string GetTitle(int index);
    int GetAdditional(int index);
    bool SetTitle(int index, LPSTR Title);
    bool SetAdditional(int index,int v=1);
    void SetCurrentClip(int index);
    int GetCurrentClip();
    void DeleteAll();
    void SetSize(int Width, int Height);
    void SetWidth(int Width);
private:
    HWND SelecHwND;
};
#endif // YOUR_HEADER_FILE_H
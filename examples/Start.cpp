// Start.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "Xsystem.h"
int main()
{
    Xsystem mySystem; // 创建 Xsystem 类的对象
   // cout<<mySystem.GetLanguage(); // 调用 Xsystem 类的方法
    cout << mySystem.Get_Cpu_Usage();
    mySystem.XSleep_Port();
    return 0;
}

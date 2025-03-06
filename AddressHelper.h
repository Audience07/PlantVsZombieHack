#pragma once
#include "stdafx.h"

//废弃
LPVOID xGetProcessImageBase(HANDLE hProcess, LPCSTR moduleName)//dwProcessId就是程序的标识符
{
    LPVOID pProcessImageBase = NULL;
    // 遍历进程模块,
    HMODULE hModule[100] = { 0 };
    DWORD dwRet = 0;
    BOOL bRet = EnumProcessModules(hProcess, (HMODULE*)(hModule), sizeof(hModule), &dwRet);
    if (FALSE == bRet)
    {
        CloseHandle(hProcess);
        return pProcessImageBase;
    }
    int iSel = 0;
    for (int i = 0; i < (dwRet / sizeof(HMODULE)); i++)
    {
        TCHAR szModName[MAX_PATH];

        // Get the full path to the module's file.

        if (GetModuleFileNameEx(hProcess, hModule[i], szModName,
            sizeof(szModName) / sizeof(TCHAR)))
        {
            // 遍历模块名，与传入的模块名比较，相同则记录序号（只比较文件名，不比较路径，注意文件名带扩展名）
            std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> >
                str(szModName);
            if (str.find_last_of('\\') >= 0)
                str = str.substr(str.find_last_of(_T("\\")) + 1);

            if (_tcsicmp(str.c_str(), moduleName) == 0)
            {
                iSel = i;
                break;
            }
            _tprintf(TEXT("\t%s (0x%08X)\n"), szModName, hModule[i]);
        }
    }
    // 获取指定名称模块的加载基址，未找到则返回第0个
    pProcessImageBase = hModule[iSel];
    return pProcessImageBase;
}





//获取模块基地址
LPVOID xGetModuleAddr(HANDLE hProcess, const TCHAR* ModuleName) {
    TCHAR szModName[MAX_PATH];
    DWORD cbNeeded;
    HMODULE ModuleList[1024];
    //将模块枚举出来，放到ModuleList中，cbneeded输出大小
    EnumProcessModules(hProcess, ModuleList, sizeof(ModuleList), &cbNeeded);
    for (int i = 0; i < cbNeeded / sizeof(HMODULE); i++) {
        //获取模块名字
        GetModuleFileNameEx(hProcess, ModuleList[i], szModName, sizeof(szModName));

        //对比名字，如果对应上，那么将查看模块
        if (_tcsstr(szModName, ModuleName)) {
            HMODULE hTargetDll = ModuleList[i];
            MODULEINFO modInfo;
            //获取模块信息，返回模块地址
            if ((GetModuleInformation(hProcess, hTargetDll, &modInfo, sizeof(modInfo)))) {
                return modInfo.lpBaseOfDll;
            }
        }
    }
    return NULL;

}



//获取最终地址
LPVOID xGetFinalAddr(IN HANDLE hProcess, IN LPVOID BaseAddr, std::vector<DWORD> Offset) {
    LPVOID Address = BaseAddr;
    //若直接加偏移加到最后一个，就直接把数据的值读取出来了，所以这里要减1，得到偏移后的地址
    for (int i = 0; i < Offset.size() - 1; i++) {
        ReadProcessMemory(hProcess, (LPCVOID)((BYTE*)Address + Offset[i]), &Address, sizeof(DWORD), NULL);
    }
    return (BYTE*)Address + SunshineBaseAddress_offset.back();
}
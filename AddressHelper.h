#pragma once
#include "stdafx.h"

LPVOID xGetProcessImageBase(HANDLE hProcess, LPCSTR moduleName)//dwProcessId���ǳ���ı�ʶ��
{
    LPVOID pProcessImageBase = NULL;
    // ��������ģ��,
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
            // ����ģ�������봫���ģ�����Ƚϣ���ͬ���¼��ţ�ֻ�Ƚ��ļ��������Ƚ�·����ע���ļ�������չ����
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
    // ��ȡָ������ģ��ļ��ػ�ַ��δ�ҵ��򷵻ص�0��
    pProcessImageBase = hModule[iSel];
    return pProcessImageBase;
}





//��ȡģ�����ַ
LPVOID xGetModuleAddr(HANDLE hProcess, const TCHAR* ModuleName) {
    TCHAR szModName[MAX_PATH];
    DWORD cbNeeded;
    HMODULE ModuleList[1024];
    //��ģ��ö�ٳ������ŵ�ModuleList�У�cbneeded�����С
    EnumProcessModules(hProcess, ModuleList, sizeof(ModuleList), &cbNeeded);
    for (int i = 0; i < cbNeeded / sizeof(HMODULE); i++) {
        //��ȡģ������
        GetModuleFileNameEx(hProcess, ModuleList[i], szModName, sizeof(szModName));

        //�Ա����֣������Ӧ�ϣ���ô���鿴ģ��
        if (_tcsstr(szModName, ModuleName)) {
            HMODULE hTargetDll = ModuleList[i];
            MODULEINFO modInfo;
            //��ȡģ����Ϣ������ģ���ַ
            if ((GetModuleInformation(hProcess, hTargetDll, &modInfo, sizeof(modInfo)))) {
                return modInfo.lpBaseOfDll;
            }
        }
    }
    return NULL;

}


//��ȡģ���ַ
LPSTR GetBaseAddress(LPCSTR ModuleName) {
    HMODULE hModule = GetModuleHandle(ModuleName);
    if (hModule == NULL) {
        return NULL; // ��ȡʧ��
    }
    return (LPSTR)hModule;
}
#pragma once
#include <iostream>
#include <Windows.h>
#include <locale>
#include <vector>
#include <psapi.h>
#include <tchar.h>
#include "GameAddr.h"

//״̬
#define Success -1
#define FindWindowError -2
#define WriteMemoryError -3
#define FindModuleError -4





//�򿪽���
HANDLE xOpenProcessByName(IN LPCSTR lpClassName, IN LPCSTR lpWindowName) {
	DWORD ProcessID;
	HWND hWnd = FindWindow(lpClassName, lpWindowName);
	GetWindowThreadProcessId(hWnd, &ProcessID);
	HANDLE Process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
	return Process;
}

//�����̾��������������
DWORD xShowSunshine(IN HANDLE Process) {
	DWORD Address = SunshineBaseAddress;


	for (int i = 0; i < SunshineBaseAddress_offset.size(); i++) {
		ReadProcessMemory(Process, (LPCVOID)(Address += SunshineBaseAddress_offset[i]), &Address, sizeof(DWORD), NULL);
		//Address += SunshineBaseAddress_offset[i];
	}
	return Address;
}


//�����̾����Ҫ�޸ĵ�����
DWORD xChangeSunshine(IN HANDLE Process,IN DWORD ChValue) {
	DWORD Address = SunshineBaseAddress;

	//��ֱ�Ӽ�ƫ�Ƽӵ����һ������ֱ�Ӱ����ݵ�ֵ��ȡ�����ˣ���������Ҫ��1���õ�ƫ�ƺ�ĵ�ַ
	for (int i = 0; i < SunshineBaseAddress_offset.size()-1; i++) {
		ReadProcessMemory(Process, (LPCVOID)(Address += SunshineBaseAddress_offset[i]), &Address, sizeof(DWORD), NULL);
	}
	WriteProcessMemory(Process, (LPVOID)(Address + SunshineBaseAddress_offset.back()), &ChValue, sizeof(DWORD), NULL);
	return Success;
}

//��ȡģ�����ַ
DWORD xGetModuleAddr(HANDLE hProcess,const TCHAR* ModuleName) {
	TCHAR szModName[MAX_PATH];
	DWORD cbNeeded;
	HMODULE ModuleList[1024];
	//��ģ��ö�ٳ������ŵ�ModuleList�У�cbneeded�����С
	EnumProcessModules(hProcess, ModuleList, sizeof(ModuleList), &cbNeeded);
	for (int i = 0; i < cbNeeded / sizeof(HMODULE); i++) {
		//��ȡģ������
		GetModuleFileNameEx(hProcess, ModuleList[i], szModName, sizeof(TCHAR));

		//�Ա����֣������Ӧ�ϣ���ô���鿴ģ��
		if (_tcsstr(szModName, ModuleName)) {
			HMODULE hTargetDll = ModuleList[i];
			MODULEINFO modInfo;
			//��ȡģ����Ϣ������ģ���ַ
			if ((GetModuleInformation(hProcess, hTargetDll, &modInfo, sizeof(modInfo)))) {
				return (DWORD)modInfo.lpBaseOfDll;
			}
		}

	}
	return FindModuleError;



}
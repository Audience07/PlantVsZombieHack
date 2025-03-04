#pragma once
#include <iostream>
#include <Windows.h>
#include <locale>
#include <vector>
#include <psapi.h>
#include <tchar.h>
#include "GameAddr.h"

//状态
#define Success -1
#define FindWindowError -2
#define WriteMemoryError -3
#define FindModuleError -4





//打开进程
HANDLE xOpenProcessByName(IN LPCSTR lpClassName, IN LPCSTR lpWindowName) {
	DWORD ProcessID;
	HWND hWnd = FindWindow(lpClassName, lpWindowName);
	GetWindowThreadProcessId(hWnd, &ProcessID);
	HANDLE Process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
	return Process;
}

//传进程句柄返回阳光数量
DWORD xShowSunshine(IN HANDLE Process) {
	DWORD Address = SunshineBaseAddress;


	for (int i = 0; i < SunshineBaseAddress_offset.size(); i++) {
		ReadProcessMemory(Process, (LPCVOID)(Address += SunshineBaseAddress_offset[i]), &Address, sizeof(DWORD), NULL);
		//Address += SunshineBaseAddress_offset[i];
	}
	return Address;
}


//传进程句柄，要修改的阳光
DWORD xChangeSunshine(IN HANDLE Process,IN DWORD ChValue) {
	DWORD Address = SunshineBaseAddress;

	//若直接加偏移加到最后一个，就直接把数据的值读取出来了，所以这里要减1，得到偏移后的地址
	for (int i = 0; i < SunshineBaseAddress_offset.size()-1; i++) {
		ReadProcessMemory(Process, (LPCVOID)(Address += SunshineBaseAddress_offset[i]), &Address, sizeof(DWORD), NULL);
	}
	WriteProcessMemory(Process, (LPVOID)(Address + SunshineBaseAddress_offset.back()), &ChValue, sizeof(DWORD), NULL);
	return Success;
}

//获取模块基地址
DWORD xGetModuleAddr(HANDLE hProcess,const TCHAR* ModuleName) {
	TCHAR szModName[MAX_PATH];
	DWORD cbNeeded;
	HMODULE ModuleList[1024];
	//将模块枚举出来，放到ModuleList中，cbneeded输出大小
	EnumProcessModules(hProcess, ModuleList, sizeof(ModuleList), &cbNeeded);
	for (int i = 0; i < cbNeeded / sizeof(HMODULE); i++) {
		//获取模块名字
		GetModuleFileNameEx(hProcess, ModuleList[i], szModName, sizeof(TCHAR));

		//对比名字，如果对应上，那么将查看模块
		if (_tcsstr(szModName, ModuleName)) {
			HMODULE hTargetDll = ModuleList[i];
			MODULEINFO modInfo;
			//获取模块信息，返回模块地址
			if ((GetModuleInformation(hProcess, hTargetDll, &modInfo, sizeof(modInfo)))) {
				return (DWORD)modInfo.lpBaseOfDll;
			}
		}

	}
	return FindModuleError;



}
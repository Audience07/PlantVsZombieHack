#pragma once
#include "stdafx.h"

//状态
#define Success -1
#define FindWindowError -2
#define WriteMemoryError -3
#define FindModuleError -4

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
DWORD xChangeSunshine(IN HANDLE Process, LPVOID BaseAddr, IN DWORD ChValue) {
	LPVOID Address = BaseAddr;

	//若直接加偏移加到最后一个，就直接把数据的值读取出来了，所以这里要减1，得到偏移后的地址
	for (int i = 0; i < SunshineBaseAddress_offset.size() - 1; i++) {
		ReadProcessMemory(Process, (LPCVOID)((BYTE*)Address + SunshineBaseAddress_offset[i]), &Address, sizeof(DWORD), NULL);
	}
	WriteProcessMemory(Process, (LPVOID)((BYTE*)Address + SunshineBaseAddress_offset.back()), &ChValue, sizeof(DWORD), NULL);
	return Success;
}
#pragma once
#include "stdafx.h"

//״̬
#define Success -1
#define FindWindowError -2
#define WriteMemoryError -3
#define FindModuleError -4

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
DWORD xChangeSunshine(IN HANDLE Process, LPVOID BaseAddr, IN DWORD ChValue) {
	LPVOID Address = BaseAddr;

	//��ֱ�Ӽ�ƫ�Ƽӵ����һ������ֱ�Ӱ����ݵ�ֵ��ȡ�����ˣ���������Ҫ��1���õ�ƫ�ƺ�ĵ�ַ
	for (int i = 0; i < SunshineBaseAddress_offset.size() - 1; i++) {
		ReadProcessMemory(Process, (LPCVOID)((BYTE*)Address + SunshineBaseAddress_offset[i]), &Address, sizeof(DWORD), NULL);
	}
	WriteProcessMemory(Process, (LPVOID)((BYTE*)Address + SunshineBaseAddress_offset.back()), &ChValue, sizeof(DWORD), NULL);
	return Success;
}
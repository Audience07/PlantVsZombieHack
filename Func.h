#pragma once
#include "stdafx.h"
#include "AddressHelper.h"
#include "Process.h"

//״̬
#define Success -1
#define FindWindowError -2
#define WriteMemoryError -3
#define FindModuleError -4



//�޸�����
void xChangeSunsine(DWORD Value) {

	HANDLE hProcess = xOpenProcessByName("MainWindow", "Plants vs. Zombies 1.2.0.1073 RELEASE");
	if (!hProcess) {
		std::cout << "[-]��ȡ����ʧ��,��������Ƿ��" << std::endl;
	}

	LPVOID BaseAddr = xGetModuleAddr(hProcess, ModuleName);
	LPVOID FinalAddr = xGetFinalAddr(hProcess, BaseAddr, SunshineBaseAddress_offset);

	//xChangeValue(hProcess, FinalAddr, Value);
	WriteProcessMemory(hProcess, FinalAddr, &Value, sizeof(Value), NULL);

}

//��������
DWORD xShowSunshine() {
	DWORD dValue;
	HANDLE hProcess = xOpenProcessByName("MainWindow", "Plants vs. Zombies 1.2.0.1073 RELEASE");
	if (!hProcess) {
		std::cout << "[-]��ȡ����ʧ��,��������Ƿ��" << std::endl;
	}

	LPVOID BaseAddr = xGetModuleAddr(hProcess, ModuleName);
	LPVOID FinalAddr = xGetFinalAddr(hProcess, BaseAddr, SunshineBaseAddress_offset);
	ReadProcessMemory(hProcess, FinalAddr, &dValue, sizeof(dValue), NULL);
	return dValue;
}
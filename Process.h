#pragma once
#include "stdafx.h"
#include <tlhelp32.h>

//�򿪽���,ʧ�ܷ���NULL
HANDLE xOpenProcessByWndName(IN LPCSTR lpClassName, IN LPCSTR lpWindowName) {
	DWORD PID;
	HWND hWnd = FindWindow(lpClassName, lpWindowName);
	if (!hWnd) {
		return NULL;
	}
	GetWindowThreadProcessId(hWnd, &PID);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
	if (!hProcess) {
		return NULL;
	}
	return hProcess;
}

HANDLE xOpenProcessByPcName(IN LPCSTR PcName) {
	DWORD dwProcessID = NULL;


	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (!hSnapShot) {
		return NULL;
	}
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hSnapShot, &pe32)) {
		return NULL;
	}
	while (Process32Next(hSnapShot, &pe32)) {
		if (!(_tcsicmp(PcName, pe32.szExeFile))) {
			dwProcessID = pe32.th32ProcessID;
			break;
		}
	}
	CloseHandle(hSnapShot);
	//û��ƥ�䵽��ͬ�Ľ�������
	if (!dwProcessID) {
		return NULL;
	}
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessID);
	if (!hProcess) {
		return NULL;
	}
	return hProcess;
}
#pragma once
#include "stdafx.h"
//打开进程,失败返回NULL
HANDLE xOpenProcessByName(IN LPCSTR lpClassName, IN LPCSTR lpWindowName) {
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
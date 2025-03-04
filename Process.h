#pragma once
#include "stdafx.h"
//�򿪽���,ʧ�ܷ���NULL
HANDLE xOpenProcessByName(IN LPCSTR lpClassName, IN LPCSTR lpWindowName) {
	HANDLE Error = NULL;
	DWORD ProcessID;
	HWND hWnd = FindWindow(lpClassName, lpWindowName);
	if (!hWnd) {
		return Error;
	}
	GetWindowThreadProcessId(hWnd, &ProcessID);
	HANDLE Process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
	if (!Process) {
		return Error;
	}
	return Process;
}
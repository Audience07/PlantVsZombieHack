#pragma once
#include "stdafx.h"
//�򿪽���,ʧ�ܷ���NULL
HANDLE xOpenProcessByName(IN LPCSTR lpClassName, IN LPCSTR lpWindowName) {
	DWORD ProcessID;
	HWND hWnd = FindWindow(lpClassName, lpWindowName);
	if (!hWnd) {
		return NULL;
	}
	GetWindowThreadProcessId(hWnd, &ProcessID);
	HANDLE Process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
	if (!Process) {
		return NULL;
	}
	return Process;
}
#include "stdafx.h"



int main() {
	//设置地区编码
	setlocale(LC_ALL, "");


	//局部变量
	HANDLE hProcess;			//进程句柄
	

	//打开进程
	if (!(hProcess = xOpenProcessByName("MainWindow", "Plants vs. Zombies 1.2.0.1073 RELEASE"))) {
		std::cout << "未发现进程" << std::endl;
		return FindWindowError;
	}


	//获取exe的基址
	LPVOID ExeBase = (BYTE*)GetBaseAddress(ModuleName) + 0x3578F8;


	//修改阳光
	xChangeSunshine(hProcess, ExeBase, 3000);





	//关闭句柄
	CloseHandle(hProcess);

	return 0;
}
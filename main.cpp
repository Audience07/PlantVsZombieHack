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



	//读取阳光
	/*while (true)
	{
		std::cout << xShowSunshine(hProcess) << std::endl;
		Sleep(100);
		system("CLS");
	}*/


	//修改阳光
	/*if ((xChangeSunshine(hProcess,500))==WriteMemoryError) {
		std::cout << "写入内存失败";
		CloseHandle(hProcess);
		return WriteMemoryError;
	}*/

	
	xGetModuleAddr(hProcess, ModuleName);





	//关闭句柄
	CloseHandle(hProcess);

	return 0;
}
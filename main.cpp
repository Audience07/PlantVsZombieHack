#include "stdafx.h"



int main() {
	//���õ�������
	setlocale(LC_ALL, "");


	//�ֲ�����
	HANDLE hProcess;			//���̾��
	

	//�򿪽���
	if (!(hProcess = xOpenProcessByName("MainWindow", "Plants vs. Zombies 1.2.0.1073 RELEASE"))) {
		std::cout << "δ���ֽ���" << std::endl;
		return FindWindowError;
	}



	//��ȡ����
	/*while (true)
	{
		std::cout << xShowSunshine(hProcess) << std::endl;
		Sleep(100);
		system("CLS");
	}*/


	//�޸�����
	/*if ((xChangeSunshine(hProcess,500))==WriteMemoryError) {
		std::cout << "д���ڴ�ʧ��";
		CloseHandle(hProcess);
		return WriteMemoryError;
	}*/

	
	xGetModuleAddr(hProcess, ModuleName);





	//�رվ��
	CloseHandle(hProcess);

	return 0;
}
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


	//��ȡexe�Ļ�ַ
	LPVOID ExeBase = (BYTE*)GetBaseAddress(ModuleName) + 0x3578F8;


	//�޸�����
	xChangeSunshine(hProcess, ExeBase, 3000);





	//�رվ��
	CloseHandle(hProcess);

	return 0;
}
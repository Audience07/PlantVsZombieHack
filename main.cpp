#include "stdafx.h"


int main() {
	//���õ�������
	setlocale(LC_ALL, "");

	while (1) {
		DWORD dValue = xShowSunshine();
		std::cout << dValue << std::endl;
		Sleep(300);
		system("CLS");
	}
	
}


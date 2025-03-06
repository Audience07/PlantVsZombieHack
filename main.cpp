#include "stdafx.h"


int main() {
	//ÉèÖÃµØÇø±àÂë
	setlocale(LC_ALL, "");

	while (1) {
		DWORD dValue = xShowSunshine();
		std::cout << dValue << std::endl;
		Sleep(300);
		system("CLS");
	}
	
}


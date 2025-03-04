#pragma onces
//存储游戏数据


/*基址
PlantsVsZombies.exe + 3578F8
868
5578
*/

//Sunshine
DWORD SunshineBaseAddress = 0x029F9F50;
std::vector<DWORD> SunshineBaseAddress_offset = { 0x868,0x5578 };


const TCHAR* ModuleName = "PlantsVsZombies.exe";
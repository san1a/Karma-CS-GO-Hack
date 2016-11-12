#include "Misc.h"
#include "Xor.h"
cMisc* g_pMisc = new cMisc;

bool cMisc::DebugConsole(char* strConName)
{
	FILE* g_pFileBuf;
	if (!AttachConsole(ATTACH_PARENT_PROCESS))
		if (!AllocConsole())
			return false;
	if (!SetConsoleTitleA(strConName))
		return false;
	auto iErrorCode = freopen_s(&g_pFileBuf, "CONOUT$", "w", stdout);
	if (iErrorCode != NULL)
		return false;
	return true;
}

bool cMisc::SetTextColor(DWORD dwFore, DWORD dwBack)
{
	auto hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	return SetConsoleTextAttribute(hConsole, dwFore | dwBack << 4);
}

void cMisc::SetConsoleState(bool bVis)
{
	HWND Hide;
	AllocConsole();
	Hide = FindWindowA(nullptr, XorStr("Karma - CSGO"));
	ShowWindow(Hide, bVis);
}
#include "SDK.h"
#include "Config.h"
#include "Accessors.h"
#include "misc.h"
#include "HWID.h"
#include "IRC.h"
HMODULE g_hDll;
static bool bVisible;
static bool Setups = true;
DWORD __stdcall HandleConfigs(void* args);
DWORD __stdcall Securitythread(void* args)
{
	while (true)
	{
		if (g_pSecurity->Trampoline(true, NULL))
		{
			if (Setups)
			{
				Setup();
				Setups = false;
				CreateThread(nullptr, 0, HandleConfigs, g_hDll, 0, nullptr);//Handle configs outside of a gamethread to speed out threads up.
			}
		}
		Sleep(24);
	}
}
void MainThread(LPVOID lpArgs)
{
	ConSys->CheckConfigs();
	CreateThread(nullptr, 0, Securitythread, g_hDll, 0, nullptr);
}
DWORD __stdcall DeAttach(void* args)
{
	while(true)
	{
		ConSys->Handle();
		if (GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_UP) && GetAsyncKeyState(VK_RIGHT) & 1)
		{
			bVisible = !bVisible;
			//g_pMisc->SetConsoleState(bVisible);
		}
		if (!g_pSecurity->RunSecurityChecks())
		{
			FreeConsole();
			FreeLibraryAndExitThread(static_cast<HMODULE>(args), NULL);
		}
		if (Options.Cheat.Uninject && GetForegroundWindow() == FindWindowA(XorStr("Valve001"), XorStr("Counter-Strike: Global Offensive")))//make sure we are in CSGO and that our first statment is true
		{
			DestroyHooks();
			Sleep(2000);// 2 seconds to let our VMT hooks unhook
			//g_pMisc->SetConsoleState(false);
			FreeConsole();
			FreeLibraryAndExitThread(static_cast<HMODULE>(args), NULL);
		}
		Sleep(24);
	}
}
DWORD __stdcall HandleConfigs(void* args)
{
	while (true)
	{
		g_pIRC->Thread();
		g_pLegit->HandleConfigs();
		if (Options.Cheat.Uninject)
			ExitThread(NULL);
		Sleep(24);
	}
}
DWORD WINAPI DllMain(HMODULE hDll, DWORD dwReasonForCall, LPVOID lpReserved)
{
	switch(dwReasonForCall)
	{
	case DLL_PROCESS_ATTACH:
		//add these back when its in the loader
		#if NDEBUG		
		HideModule(hDll);
		HideModuleFromPEB(hDll);
		HideModuleXta(hDll);
		RemovePeHeader(reinterpret_cast<DWORD>(hDll));
		DestroyModuleHeader(hDll);
		g_hDll = hDll;
        #endif
		//g_pMisc->DebugConsole(XorStr("Karma - CSGO"));
		//XorCompileTime::w_printf(XorStr("Build Date: %s Build Time: %s\n"),__DATE__,__TIME__);
		//XorCompileTime::w_printf(XorStr("Authenticating...\n"));
		if (g_pSecurity->RunSecurityChecks())
		{
			//g_pMisc->SetTextColor(Green, Black);
			//XorCompileTime::w_printf(XorStr("Successfully Authenticated User: %s\n"), g_pSecurity->User);
			Sleep(3000);
			//XorCompileTime::w_printf(XorStr("You Can Now Close The Console.\n"));
			_beginthread(MainThread, 0, nullptr);
			CreateThread(nullptr, 0,DeAttach, hDll, 0, nullptr);//LOOK MA NO CASTS
		}
		else
		{
			//g_pMisc->SetTextColor(Red, Black);
			//XorCompileTime::w_printf(XorStr("Authentication Failed, You Do Not Have Access"));
			Sleep(3000);
			FreeLibrary(hDll);
		}
		return 1;
		
	case DLL_PROCESS_DETACH:
	{
		DestroyHooks();
		Sleep(2000);// 2 seconds to let our VMT hooks unhook
		//g_pMisc->SetConsoleState(false);
		FreeConsole();
		FreeLibraryAndExitThread(hDll, NULL);
		return 1;
	}

	default:
		return 1;
	}
}
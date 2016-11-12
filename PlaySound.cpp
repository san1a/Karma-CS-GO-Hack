#include "Hooks.h"
#include "Globals.h"
#include "Cheats.h"
PlaySoundFn oPlaySound;

void __stdcall Game::Hooked_PlaySound(const char* szFileName) {
	static auto IsReady = reinterpret_cast<void(__cdecl*)()>(Memory::FindPatternIDA(XorStr("client.dll"), XorStr("55 8B EC 51 56 8B 35 ? ? ? ? 8B 4E 58")));
	oPlaySound(Surface, szFileName);

	if (!Options.Visuals.ESP.AutoAccept || Engine->IsInGame()) return;
	if (!XorCompileTime::w_strcmp(szFileName, XorStr("weapons/hegrenade/beep.wav"))) {
		IsReady();
		FLASHWINFO fi;
		fi.cbSize = sizeof(FLASHWINFO);
		fi.hwnd = Global::Window;
		fi.dwFlags = FLASHW_ALL | FLASHW_TIMERNOFG;
		fi.uCount = 0;
		fi.dwTimeout = 0;
		FlashWindowEx(&fi);
	}
}
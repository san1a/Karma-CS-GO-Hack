#include "Hooks.h"
#include "Globals.h"
#include "Accessors.h"
OverrideViewFn oOverrideView;
void __fastcall Game::HookedOverrideView(void* ecx, void* edx, CViewSetup* pSetup)
{
	if (Engine->IsInGame() && Engine->IsConnected())
	{
		if (Global::LocalPlayer)
		{
			if (Options.Visuals.ESP.FOV > 0)
			{
				pSetup->fov += Options.Visuals.ESP.FOV;
			}
		}
	}
	oOverrideView(ecx, edx, pSetup);
}







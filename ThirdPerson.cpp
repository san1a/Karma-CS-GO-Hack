#include "Hooks.h"
#include "Globals.h"
#include "Cheats.h"

ThirdPersonFn oThirdPerson;

bool __fastcall Game::hkdShouldDrawLocalPlayer(void* ecx, void* edx, CBaseEntity* pPlayer)
{
	if (Options.Visuals.ESP.ThirdPerson)
		return true;

	oThirdPerson(ecx, edx, pPlayer);

}
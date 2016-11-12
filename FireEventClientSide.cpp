#include "hooks.h"
#include "Globals.h"
#include <unordered_map>
#pragma comment(lib,"Winmm.lib")
FireEventClientSideFn oFireEventClientSide;

std::unordered_map<const char*, const char*> m_KillIcons;


void KillIcons()
{
	// Define replacement kill icons. (these only apply to you)
	if (Options.Skins.KnifeSelect == 3)
	{
		m_KillIcons["knife_default_ct"] = "knife_karambit";
		m_KillIcons["knife_t"] = "knife_karambit";
	}
	else if (Options.Skins.KnifeSelect == 0)
	{
		m_KillIcons["knife_default_ct"] = "bayonet";
		m_KillIcons["knife_t"] = "bayonet";
	}
	else if (Options.Skins.KnifeSelect == 4)
	{
		m_KillIcons["knife_default_ct"] = "knife_m9_bayonet";
		m_KillIcons["knife_t"] = "knife_m9_bayonet";
	}
	else if (Options.Skins.KnifeSelect == 1)
	{
		m_KillIcons["knife_default_ct"] = "knife_flip";
		m_KillIcons["knife_t"] = "knife_flip";
	}
	else if (Options.Skins.KnifeSelect == 2)
	{
		m_KillIcons["knife_default_ct"] = "knife_gut";
		m_KillIcons["knife_t"] = "knife_gut";
	}
	else if (Options.Skins.KnifeSelect == 5)
	{
		m_KillIcons["knife_default_ct"] = "knife_tactical";
		m_KillIcons["knife_t"] = "knife_tactical";
	}
	else if (Options.Skins.KnifeSelect == 6)
	{
		m_KillIcons["knife_default_ct"] = "knife_butterfly";
		m_KillIcons["knife_t"] = "knife_butterfly";
	}
	else if (Options.Skins.KnifeSelect == 8)
	{
		m_KillIcons["knife_default_ct"] = "knife_push";
		m_KillIcons["knife_t"] = "knife_push";
	}
	else if (Options.Skins.KnifeSelect == 7)
	{
		m_KillIcons["knife_default_ct"] = "knife_falchion";
		m_KillIcons["knife_t"] = "knife_falchion";
	}
	else if (Options.Skins.KnifeSelect == 9)
	{
		m_KillIcons["knife_default_ct"] = "knife_survival_bowie";
		m_KillIcons["knife_t"] = "knife_survival_bowie";
	}
}

bool ApplyCustomKillIcon(IGameEvent* pEvent)
{
	if (!pEvent)
		return false;

	// Get the user ID of the attacker.
	KillIcons();
	
    int nUserID = Engine->GetPlayerForUserID(pEvent->GetInt("userid"));
	int nAttackerID = Engine->GetPlayerForUserID(pEvent->GetInt("attacker")); // thats why
	int nLocalPlayerID = Engine->GetLocalPlayer();

	// just so you know this entire function runs. 100% it just doesnt change through the unordered map all the time only half the time. yea but ur not properly checking some shit let me try
	// Only continue if we were the attacker.
	if (nAttackerID != nLocalPlayerID || nUserID == nLocalPlayerID)
		return false;

	// Get the original weapon used to kill.
	const char* szWeapon = pEvent->GetString("weapon");

	for (auto ReplacementIcon : m_KillIcons)
	{
		// Search for a valid replacement.
		if (!strcmp(szWeapon, ReplacementIcon.first))
		{
			// Replace with user defined value.
			pEvent->SetString("weapon", ReplacementIcon.second);
			break;
		}
	}

	return true;
}


float  _flHurtTime;
bool __fastcall Game::FireEventClientSideThink(void* ecx, void* edx, IGameEvent* pEvent) {
	// If the event pointer is invalid just call the original.
	if (!pEvent)
		return oFireEventClientSide(ecx, pEvent);

	// Run our replacement function when a "player_death" event is fired.
	if (!strcmp(pEvent->GetName(), "player_death"))
	ApplyCustomKillIcon(pEvent);


	if (Options.Visuals.ESP.Hitmarker)
	{
		if (!strcmp(pEvent->GetName(), "player_hurt")) {
			int attacker = pEvent->GetInt("attacker");
			if (Engine->GetPlayerForUserID(attacker) == Engine->GetLocalPlayer()) {
				PlaySoundA(XorStr("C:\\Karma\\Pictures\\hitsound.wav"), nullptr, SND_ASYNC);
				Global::flHurtTime = Globals->curtime;
			}
		}
	}
	// Run the original FireEventClientSide function.
	return oFireEventClientSide(ecx, pEvent);
};
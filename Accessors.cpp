#include "Accessors.h"
cManagers* g_pManagers = new cManagers;
cpSilent* g_pSilent = new cpSilent;

void cManagers::CreateMove(CUserCmd* pCmd, bool& bSendPackets)
{
	//call Create Move Features Here
	if (!Global::LocalPlayer) return;

	if (!Options.AntiCheat.SMAC && Options.Visuals.ESP.ThirdPerson)
		g_pPlayer->SpoofConvars();

	if (Options.Visuals.ESP.ThirdPerson)
		g_pPlayer->ForceThirdPerson(pCmd);

	if (!Global::LocalPlayer->GetAlive()) return;

	g_pPlayer->ForceUpdate();
	
	auto LocalWep = Global::LocalPlayer->GetWeapon();
	if (LocalWep)
		g_pSilent->Setup();

	if (Options.PlayerMods.bhop.Enabled)
	   g_pPlayer->Bhop(pCmd);

	if (Options.PlayerMods.AutoStrafe.Enabled && Options.PlayerMods.AutoStrafe.Silent)
	    g_pPlayer->AutoStrafe(pCmd);

	if (Options.PlayerMods.AutoStrafe.Enabled && !Options.PlayerMods.AutoStrafe.Silent)
		g_pPlayer->RageAutoStrafe(pCmd);

	if (Options.Legit.Aimbot.Enabled && !Options.AntiCheat.FACEIT && g_pSilent->bCanFire)
		g_pLegit->Aimbot();

	if (Options.Legit.Aimbot.Enabled && Options.AntiCheat.FACEIT && GetAsyncKeyState(VK_LBUTTON))
	{
		if (Engine->IsInGame() && Engine->IsConnected() && Global::LocalPlayer->GetHealth() > 0) // Prevent a crashing issue?
		{
			if (Global::LocalPlayer)
			{
				g_pLegit->subtleAim(pCmd, Options.Legit.Aimbot.Bone);
			}
		}
	}

	g_pRage->Invoke(pCmd, bSendPackets, g_pSilent->bCanFire);

	if (pCmd->buttons & IN_ATTACK && !g_pRage->IsAimbotting && Options.Visuals.Removals.Recoil)
		pCmd->viewangles -= Global::LocalPlayer->GetPunch() * 2.f;

	g_pLegit->HandleTrigger(pCmd);

	if (Options.PlayerMods.AirStuck.Enabled)
		g_pPlayer->AirStuck(pCmd);

	if (Options.PlayerMods.FakeLag.Enabled)
		g_pPlayer->FakeLag(pCmd, bSendPackets);

	g_pSilent->Handle(bSendPackets);
	
	if (Options.AntiCheat.MM 
		|| Options.AntiCheat.SMAC 
		|| Options.AntiCheat.CEVO 
		|| Options.AntiCheat.FACEIT)
	this->Clamp(pCmd);
}

void cManagers::Painttraverse(HFont hFont)
{
	//call Drawn Features Here
}

void cManagers::Clamp(CUserCmd* pCmd)
{
	pCmd->viewangles.Normalize();
	if (pCmd->forwardmove > 450.f)
		pCmd->forwardmove = 450.f;
	else if (pCmd->forwardmove < -450.f)
		pCmd->forwardmove = -450.f;

	if (pCmd->sidemove > 450.f)
		pCmd->sidemove = 450.f;
	else if (pCmd->sidemove < -450.f)
		pCmd->sidemove = -450.f;

	if (pCmd->upmove > 320.f)
		pCmd->upmove = 320.f;
	else if (pCmd->upmove < -320.f)
		pCmd->upmove = -320.f;

	pCmd->viewangles.Clamp();
}

void cpSilent::Setup()
{
    bCanFire = true;
	flCurTime = Globals->interval_per_tick * (Global::LocalPlayer->GetTickBase() + 1);
	flNextPrimary = Global::LocalPlayer->GetWeapon()->GetNextPrimaryAttack();
	if (flNextPrimary > flCurTime || bOldBullet)
		bCanFire = false;
	if (!(flNextPrimary > flCurTime))
		bOldBullet = false;
}

void cpSilent::Handle(bool& bSendPackets)
{
	if (!Options.Legit.Aimbot.PerfectSilentAim)return;
	if (bCanFire && Global::pCmd->buttons & IN_ATTACK)
	{
		bSendPackets = false;
		iChokedticks++;
	}
	//So we dont kill ourselfs
	if (iChokedticks > iMaxChokedticks)
		bSendPackets = true;//this will overwrite fakelag values when psilent is on
	if (bSendPackets)
	{
		iChokedticks = 0;
		Global::pCmd->viewangles = Global::oCmd->viewangles;
		Global::pCmd->forwardmove = Global::oCmd->forwardmove;
		Global::pCmd->sidemove = Global::oCmd->sidemove;
	}
}

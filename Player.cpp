#include "Cheats.h"
cPlayer* g_pPlayer = new cPlayer;
void cPlayer::Bhop(CUserCmd* pCmd)
{
	static auto bJumped = false;
	static auto bFake = false;
	if(!bJumped && bFake)
	{ 
		bFake = false;
		pCmd->buttons |= IN_JUMP;
	}
	else if(pCmd->buttons & IN_JUMP)
	{
		if(Global::LocalPlayer->GetFlags() & FL_ONGROUND)
		{
			bJumped = true;
			bFake   = true;
		}
		else
		{
			pCmd->buttons &= ~IN_JUMP;
			bJumped = false;
		}
	}
	else
	{
		bJumped = false;
		bFake = false;
	}
}
template<class T, class U>
T Clamp(T in, U low, U high)
 {
	if (in <= low)
		 return low;
	
		if (in >= high)
		 return high;

	return in;
}
void cPlayer::ForceThirdPerson(CUserCmd* pCmd)
{
	static auto ThirdPerson = false;

	if (Engine->IsInGame() && Engine->IsConnected())
	{
		if (Global::LocalPlayer)
		{

			if (Options.Visuals.ESP.ThirdPerson)
			{
				auto LifeState = Global::LocalPlayer->GetAlive();
				static auto oLifeState = !LifeState;

				if (oLifeState != LifeState)
				{
					if (LifeState)				
						Engine->ExecuteClientCmd("thirdperson");			
					else
						Engine->ExecuteClientCmd("firstperson");
				}
				oLifeState = LifeState;
				ThirdPerson = true;
			}
			
		
		}
	}
	if (!Options.Visuals.ESP.ThirdPerson && ThirdPerson)
	{
		ThirdPerson = false;
		Engine->ExecuteClientCmd("firstperson");
	}
}

void cPlayer::AutoStrafe(CUserCmd* pCmd)
{
if (Global::LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP || Global::LocalPlayer->GetMoveType() == MOVETYPE_LADDER) return;
		static float move = 650.f;
	float s_move = move * 0.5065f;
	if ((Global::LocalPlayer->GetFlags() & FL_ONGROUND)) return;

	pCmd->forwardmove = move * 0.015f;
	pCmd->sidemove += static_cast<float>(((pCmd->tick_count % 2) * 2) - 1) * s_move;
	
		if (pCmd->mousedx)
		 pCmd->sidemove = static_cast<float>(Clamp(pCmd->mousedx, -1, 1)) * s_move;
	
		static auto strafe = pCmd->viewangles.y;
	
		float rt = pCmd->viewangles.y, rotation;
	rotation = strafe - rt;
	
		if (rotation < -Globals->interval_per_tick)
		 pCmd->sidemove = -s_move;
	
		if (rotation > Globals->interval_per_tick)
		 pCmd->sidemove = s_move;
	
		strafe = rt;

}
void cPlayer::FakeLag(CUserCmd* pCmd, bool& bSendPacket) 
{
	if (pCmd->buttons & IN_ATTACK) return;
	if (Global::LocalPlayer->GetVelocity() == Vector(0, 0, 0)) return;
	static int iTicks;
	if (iTicks > Options.PlayerMods.FakeLag.Choke)
		iTicks = 0;
	bSendPacket = iTicks < Options.PlayerMods.FakeLag.Send;
	iTicks++;
}

void cPlayer::AirStuck(CUserCmd* pCmd)
{
	static auto bAirStucked = false;
	if (pCmd->buttons & IN_ATTACK) return;
	if (GetAsyncKeyState(Options.PlayerMods.AirStuck.Key) & 1)
		bAirStucked = !bAirStucked;
	if (bAirStucked)
		pCmd->tick_count = 0xFFFFFFF;
}

void cPlayer::SpoofConvars()
{
	auto svcheats = Cvar->FindVar("sv_cheats");
	auto svcheatsspoof = new SpoofedConvar(svcheats);
	svcheatsspoof->SetInt(1);
}

void cPlayer::ForceUpdate()
{
	if (GetAsyncKeyState(VK_HOME))
	{
		Engine->ExecuteClientCmd("cl_fullupdate"); // best meme method for forceupdate
	}
}

void cPlayer::RageAutoStrafe(CUserCmd* pCmd)
{
	if (GetAsyncKeyState(0x57)//W 
		|| GetAsyncKeyState(0x41)//A
		|| GetAsyncKeyState(0x53)//S
		|| GetAsyncKeyState(0x44))//D
		return;

	 if (GetAsyncKeyState(VK_SPACE)  && (Global::LocalPlayer->GetFlags() & FL_ONGROUND)
		 && Global::LocalPlayer->GetVelocity().Length() <= 60.f)
	 {
		 pCmd->forwardmove = 450.f;
	 }
	 auto Delta = 0.f;
	 if (Global::LocalPlayer->GetVelocity().Length() > 60.f)
	 {
		 auto x = 30.f;
		 auto z = x / Global::LocalPlayer->GetVelocity().Length();
		 z = fabsf(z);
		 auto a = x * z;
		 Delta = a;
	 }
	 if (GetAsyncKeyState(VK_SPACE) && !(Global::LocalPlayer->GetFlags() & FL_ONGROUND))
	 {
		 if (pCmd->mousedx < 0)
			 pCmd->sidemove = -450;
		 if (pCmd->mousedx > 0)
			 pCmd->sidemove = 450;
		 if (pCmd->tick_count % 2)
		 {
			 pCmd->sidemove = -450;
		 }
		 else
		 {
			 pCmd->viewangles.y += Delta;
			 pCmd->sidemove = 450;
		 }
	 }
}

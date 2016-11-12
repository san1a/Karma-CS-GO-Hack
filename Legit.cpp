#include "Cheats.h"
cLegit* g_pLegit = new cLegit;
//Nice Gamer food legit bot...
//You don't need to return after every Statment

cLegit::cLegit()
{
	bestTarget = -1;

	viewAngles = QAngle(0.f, 0.f, 0.f);
	hitboxPosition = Vector(0.f, 0.f, 0.f);
	finalAngles = QAngle(0.f, 0.f, 0.f);
}
void cLegit::HandleTrigger(CUserCmd* pCmd)
{
	if (Options.Legit.Trigger.Enabled)
		if (Options.Legit.Trigger.Delay > 1)
		{
			static auto TriggerTick = GetTickCount();
			if ((DWORD(TriggerTick) + Options.Legit.Trigger.Delay) <= GetTickCount())
			{
				TriggerTick = DWORD(GetTickCount());
				this->triggerbot(pCmd);
			}
		}
		else
		{
			this->triggerbot(pCmd);
		}
}
bool cLegit::ValidEntity(int i)
{
	CBaseEntity* pTarget = nullptr;

	if (pTarget = ClientEntList->GetClientEntity(i))
	 if (!(pTarget == Global::LocalPlayer))
	  if (pTarget->GetHealth() >= 0)
	   if (!pTarget->GetImmune())
	    if (!pTarget->GetDormant())
	     if (!(pTarget->GetTeam() == Global::LocalPlayer->GetTeam()))
	      if (pTarget->IsVisible(Options.Legit.Aimbot.Bone))
	    	{
			  QAngle Angles;
			  CalcAngle(Global::LocalPlayer->GetEyePosition(), pTarget->GetBonePosition(Options.Legit.Aimbot.Bone), Angles);
			   if (GetFov(Global::pCmd->viewangles, Angles) <= Options.Legit.Aimbot.Fov)
				  return true;
		    }
	return false;
}

void cLegit::HandleConfigs()
{
	if (!Options.Legit.Aimbot.WeaponConfigs) return;
	if (!Engine->IsInGame() || !Engine->IsConnected()) return;
	if (!Global::LocalPlayer)return;
	if (!Global::LocalPlayer->GetWeapon()) return;
	auto Weapon = Global::LocalPlayer->GetWeapon()->GetWeaponType();
	if (Weapon == WEPCLASS_KNIFE || Weapon == WEPCLASS_INVALID)
	{
		Options.Legit.Trigger.Enabled = false;
		Options.Legit.Aimbot.Enabled = false;
		Options.Legit.Aimbot.Bone = 0;
		Options.Legit.Aimbot.RCS = false;
		//Options.Legit.Aimbot.pRCS = false;
		//Options.Legit.Aimbot.lSmooth - 0.0f;
		Options.Legit.Aimbot.Smooth[0] = 0.f;
		Options.Legit.Aimbot.Smooth[1] = 0.f;
		Options.Legit.Aimbot.Fov = false;
		Options.Legit.Aimbot.SilentAim = false;
		Options.Legit.Aimbot.PerfectSilentAim = false;
		Options.Legit.Aimbot.LFOV = false;
		Options.Legit.Aimbot.AimSpeed = 0;
		Options.Legit.Aimbot.MultiplySpeed = 0;
		Options.Legit.Aimbot.FOVBOOST = 0;
		return;
	}

	if (Weapon == WEPCLASS_RIFLE)
	{
		Options.Legit.Trigger.Enabled = Options.Legit.Aimbot.Configs.Rifles.Trigger;
	    Options.Legit.Aimbot.Enabled  = Options.Legit.Aimbot.Configs.Rifles.Enabled;
		Options.Legit.Aimbot.Bone = Options.Legit.Aimbot.Configs.Rifles.Bone;
		Options.Legit.Aimbot.RCS = Options.Legit.Aimbot.Configs.Rifles.RCS;
		//Options.Legit.Aimbot.pRCS = Options.Legit.Aimbot.Configs.Rifles.pRCS;
		//Options.Legit.Aimbot.lSmooth = Options.Legit.Aimbot.Configs.Rifles.lSmooth;
		Options.Legit.Aimbot.Smooth[0] = Options.Legit.Aimbot.Configs.Rifles.Smooth[0];
		Options.Legit.Aimbot.Smooth[1] = Options.Legit.Aimbot.Configs.Rifles.Smooth[1];
		Options.Legit.Aimbot.Fov = Options.Legit.Aimbot.Configs.Rifles.Fov;
		Options.Legit.Aimbot.SilentAim = Options.Legit.Aimbot.Configs.Rifles.SilentAim;
		Options.Legit.Aimbot.PerfectSilentAim = Options.Legit.Aimbot.Configs.Rifles.PerfectSilentAim;
		// Begin League Options
		Options.Legit.Aimbot.LFOV = Options.Legit.Aimbot.Configs.Rifles.LFOV;
		Options.Legit.Aimbot.AimSpeed = Options.Legit.Aimbot.Configs.Rifles.AimSpeed;
		Options.Legit.Aimbot.MultiplySpeed = Options.Legit.Aimbot.Configs.Rifles.MultiplySpeed;
		Options.Legit.Aimbot.FOVBOOST = Options.Legit.Aimbot.Configs.Rifles.FOVBOOST;
	}
	if (Weapon == WEPCLASS_PISTOL)
	{
		Options.Legit.Trigger.Enabled = Options.Legit.Aimbot.Configs.Pistols.Trigger;
		Options.Legit.Aimbot.Enabled = Options.Legit.Aimbot.Configs.Pistols.Enabled;
		Options.Legit.Aimbot.Bone = Options.Legit.Aimbot.Configs.Pistols.Bone;
		Options.Legit.Aimbot.RCS = Options.Legit.Aimbot.Configs.Pistols.RCS;
		Options.Legit.Aimbot.pRCS = Options.Legit.Aimbot.Configs.Pistols.pRCS;
		Options.Legit.Aimbot.lSmooth = Options.Legit.Aimbot.Configs.Pistols.lSmooth;
		Options.Legit.Aimbot.Smooth[0] = Options.Legit.Aimbot.Configs.Pistols.Smooth[0];
		Options.Legit.Aimbot.Smooth[1] = Options.Legit.Aimbot.Configs.Pistols.Smooth[1];
		Options.Legit.Aimbot.Fov = Options.Legit.Aimbot.Configs.Pistols.Fov;
		Options.Legit.Aimbot.SilentAim = Options.Legit.Aimbot.Configs.Pistols.SilentAim;
		Options.Legit.Aimbot.PerfectSilentAim = Options.Legit.Aimbot.Configs.Pistols.PerfectSilentAim;
		// Begin League Options
		Options.Legit.Aimbot.LFOV = Options.Legit.Aimbot.Configs.Pistols.LFOV;
		Options.Legit.Aimbot.AimSpeed = Options.Legit.Aimbot.Configs.Pistols.AimSpeed;
		Options.Legit.Aimbot.MultiplySpeed = Options.Legit.Aimbot.Configs.Pistols.MultiplySpeed;
		Options.Legit.Aimbot.FOVBOOST = Options.Legit.Aimbot.Configs.Pistols.FOVBOOST;
	}
	if (Weapon == WEPCLASS_SNIPER)
	{
		Options.Legit.Trigger.Enabled = Options.Legit.Aimbot.Configs.Snipers.Trigger;
		Options.Legit.Aimbot.Enabled = Options.Legit.Aimbot.Configs.Snipers.Enabled;
		Options.Legit.Aimbot.Bone = Options.Legit.Aimbot.Configs.Snipers.Bone;
		Options.Legit.Aimbot.RCS = Options.Legit.Aimbot.Configs.Snipers.RCS;
		Options.Legit.Aimbot.pRCS = Options.Legit.Aimbot.Configs.Snipers.pRCS;
		Options.Legit.Aimbot.lSmooth = Options.Legit.Aimbot.Configs.Snipers.lSmooth;
		Options.Legit.Aimbot.Smooth[0] = Options.Legit.Aimbot.Configs.Snipers.Smooth[0];
		Options.Legit.Aimbot.Smooth[1] = Options.Legit.Aimbot.Configs.Snipers.Smooth[1];
		Options.Legit.Aimbot.Fov = Options.Legit.Aimbot.Configs.Snipers.Fov;
		Options.Legit.Aimbot.SilentAim = Options.Legit.Aimbot.Configs.Snipers.SilentAim;
		Options.Legit.Aimbot.PerfectSilentAim = Options.Legit.Aimbot.Configs.Snipers.PerfectSilentAim;
		// Begin League Options
		Options.Legit.Aimbot.LFOV = Options.Legit.Aimbot.Configs.Snipers.LFOV;
		Options.Legit.Aimbot.AimSpeed = Options.Legit.Aimbot.Configs.Snipers.AimSpeed;
		Options.Legit.Aimbot.MultiplySpeed = Options.Legit.Aimbot.Configs.Snipers.MultiplySpeed;
		Options.Legit.Aimbot.FOVBOOST = Options.Legit.Aimbot.Configs.Snipers.FOVBOOST;
	}
	if (Weapon == WEPCLASS_SMG)
	{
		Options.Legit.Trigger.Enabled = Options.Legit.Aimbot.Configs.SMGs.Trigger;
		Options.Legit.Aimbot.Enabled = Options.Legit.Aimbot.Configs.SMGs.Enabled;
		Options.Legit.Aimbot.Bone = Options.Legit.Aimbot.Configs.SMGs.Bone;
		Options.Legit.Aimbot.RCS = Options.Legit.Aimbot.Configs.SMGs.RCS;
		Options.Legit.Aimbot.pRCS = Options.Legit.Aimbot.Configs.SMGs.pRCS;
		Options.Legit.Aimbot.lSmooth = Options.Legit.Aimbot.Configs.SMGs.lSmooth;
		Options.Legit.Aimbot.Smooth[0] = Options.Legit.Aimbot.Configs.SMGs.Smooth[0];
		Options.Legit.Aimbot.Smooth[1] = Options.Legit.Aimbot.Configs.SMGs.Smooth[1];
		Options.Legit.Aimbot.Fov = Options.Legit.Aimbot.Configs.SMGs.Fov;
		Options.Legit.Aimbot.SilentAim = Options.Legit.Aimbot.Configs.SMGs.SilentAim;
		Options.Legit.Aimbot.PerfectSilentAim = Options.Legit.Aimbot.Configs.SMGs.PerfectSilentAim;
		// Begin League Options
		Options.Legit.Aimbot.LFOV = Options.Legit.Aimbot.Configs.SMGs.LFOV;
		Options.Legit.Aimbot.AimSpeed = Options.Legit.Aimbot.Configs.SMGs.AimSpeed;
		Options.Legit.Aimbot.MultiplySpeed = Options.Legit.Aimbot.Configs.SMGs.MultiplySpeed;
		Options.Legit.Aimbot.FOVBOOST = Options.Legit.Aimbot.Configs.SMGs.FOVBOOST;
	}
	if (Weapon == WEPCLASS_SHOTGUN)
	{
		Options.Legit.Trigger.Enabled = Options.Legit.Aimbot.Configs.Shotguns.Trigger;
		Options.Legit.Aimbot.Enabled = Options.Legit.Aimbot.Configs.Shotguns.Enabled;
		Options.Legit.Aimbot.Bone = Options.Legit.Aimbot.Configs.Shotguns.Bone;
		Options.Legit.Aimbot.RCS = Options.Legit.Aimbot.Configs.Shotguns.RCS;
		Options.Legit.Aimbot.pRCS = Options.Legit.Aimbot.Configs.Shotguns.pRCS;
		Options.Legit.Aimbot.lSmooth = Options.Legit.Aimbot.Configs.Shotguns.lSmooth;
		Options.Legit.Aimbot.Smooth[0] = Options.Legit.Aimbot.Configs.Shotguns.Smooth[0];
		Options.Legit.Aimbot.Smooth[1] = Options.Legit.Aimbot.Configs.Shotguns.Smooth[1];
		Options.Legit.Aimbot.Fov = Options.Legit.Aimbot.Configs.Shotguns.Fov;
		Options.Legit.Aimbot.SilentAim = Options.Legit.Aimbot.Configs.Shotguns.SilentAim;
		Options.Legit.Aimbot.PerfectSilentAim = Options.Legit.Aimbot.Configs.Shotguns.PerfectSilentAim;
		// Begin League Options
		Options.Legit.Aimbot.LFOV = Options.Legit.Aimbot.Configs.Shotguns.LFOV;
		Options.Legit.Aimbot.AimSpeed = Options.Legit.Aimbot.Configs.Shotguns.AimSpeed;
		Options.Legit.Aimbot.MultiplySpeed = Options.Legit.Aimbot.Configs.Shotguns.MultiplySpeed;
		Options.Legit.Aimbot.FOVBOOST = Options.Legit.Aimbot.Configs.Shotguns.FOVBOOST;
	}
	if (Weapon == WEPCLASS_MACHINEGUN)
	{
		Options.Legit.Trigger.Enabled = Options.Legit.Aimbot.Configs.Machineguns.Trigger;
		Options.Legit.Aimbot.Enabled = Options.Legit.Aimbot.Configs.Machineguns.Enabled;
		Options.Legit.Aimbot.Bone = Options.Legit.Aimbot.Configs.Machineguns.Bone;
		Options.Legit.Aimbot.RCS = Options.Legit.Aimbot.Configs.Machineguns.RCS;
		Options.Legit.Aimbot.pRCS = Options.Legit.Aimbot.Configs.Machineguns.pRCS;
		Options.Legit.Aimbot.lSmooth = Options.Legit.Aimbot.Configs.Machineguns.lSmooth;
		Options.Legit.Aimbot.Smooth[0] = Options.Legit.Aimbot.Configs.Machineguns.Smooth[0];
		Options.Legit.Aimbot.Smooth[1] = Options.Legit.Aimbot.Configs.Machineguns.Smooth[1];
		Options.Legit.Aimbot.Fov = Options.Legit.Aimbot.Configs.Machineguns.Fov;
		Options.Legit.Aimbot.SilentAim = Options.Legit.Aimbot.Configs.Machineguns.SilentAim;
		Options.Legit.Aimbot.PerfectSilentAim = Options.Legit.Aimbot.Configs.Machineguns.PerfectSilentAim;
		// Begin League Options
		Options.Legit.Aimbot.LFOV = Options.Legit.Aimbot.Configs.Machineguns.LFOV;
		Options.Legit.Aimbot.AimSpeed = Options.Legit.Aimbot.Configs.Machineguns.AimSpeed;
		Options.Legit.Aimbot.MultiplySpeed = Options.Legit.Aimbot.Configs.Machineguns.MultiplySpeed;
		Options.Legit.Aimbot.FOVBOOST = Options.Legit.Aimbot.Configs.Machineguns.FOVBOOST;
	}
}

// Begin leaguebot rewrite

bool cLegit::isBoneVisible(CBaseEntity* target, int bone)
{
	Vector vEnd;
	(vEnd = target->GetBonePosition(Options.Legit.Aimbot.Bone));

	trace_t tr;
	Ray_t ray;

	CTraceFilter filter;
	filter.pSkip = Global::LocalPlayer;
	ray.Init(Global::LocalPlayer->GetEyePosition(), vEnd);
	EngineTrace->TraceRay(ray, CONTENTS_SOLID | CONTENTS_GRATE | CONTENTS_HITBOX, &filter, &tr);
	if (!tr.m_pEnt)
		return false;
	if (tr.hitgroup <= 7 && tr.hitgroup > 0)
		return true;
	return false;
}

bool cLegit::isPlayerVisible(CBaseEntity* target)
{
	for (int i = 0; i < 6; i++)
	{
		if (isBoneVisible(target, i))
			return true;
	}
	return false;
}

QAngle cLegit::calcViewangleAdjustment(CBaseEntity* target, CUserCmd* cmd, int bone, bool doubleRecoilComp)
{
	auto localVecAimedFrom = Global::LocalPlayer->GetEyePosition();
	Vector targetVecAbs;
	(targetVecAbs = target->GetBonePosition(Options.Legit.Aimbot.Bone));
	auto targetVecRel = targetVecAbs - localVecAimedFrom;
	auto localPlayerWep = Global::LocalPlayer->GetWeapon();
	QAngle result;
	VectorAngles(targetVecRel, result);
	result -= cmd->viewangles;
	if (localPlayerWep->GetWeaponType() == WEPCLASS_RIFLE || localPlayerWep->GetWeaponType() == WEPCLASS_MACHINEGUN || localPlayerWep->GetWeaponType() == WEPCLASS_SMG)
	{
		result -= doubleRecoilComp ? Global::LocalPlayer->GetPunch() * 2 : Global::LocalPlayer->GetPunch();
	}
	if (result.x > 180)
		result.x -= 360;
	if (result.y > 180)
		result.y -= 360;
	return result;
}

float cLegit::screenDifference(QAngle& ang)
{
	return sqrt((ang.x * ang.x) + (ang.y * ang.y));
}

CBaseEntity* cLegit::getTargetNearestCrosshair(CUserCmd* cmd, int bone, QAngle* deviance)
{
	CBaseEntity* closestEntity = nullptr;
	QAngle diff;
	diff.x = 999;
	diff.y = 999;
	QAngle newAngle;
	CBaseEntity* targetEntity;
	for (auto i = 0; i <= ClientEntList->GetHighestEntityIndex(); i++)
	{
		Vector targetVec;
		if (!(targetEntity = static_cast<CBaseEntity*>(ClientEntList->GetClientEntity(i))))
			continue;
		if (targetEntity == Global::LocalPlayer)
			continue;

		if (!targetEntity->GetAlive() || targetEntity->GetDormant())
			continue;
		player_info_t throwaway;
		if (!Engine->GetPlayerInfo(i, &throwaway))
			continue;

		if (Options.Legit.Aimbot.EnemyOnly)
			if (targetEntity->GetTeam() == Global::LocalPlayer->GetTeam())
				continue;

		(targetVec = targetEntity->GetBonePosition(Options.Legit.Aimbot.Bone));
		if (targetVec == Vector(0, 0, 0))
			continue;
		newAngle = calcViewangleAdjustment(targetEntity, cmd, bone, false);
		if (screenDifference(newAngle) < screenDifference(diff))
		{
			diff = newAngle;
			closestEntity = targetEntity;
		}
	}
	if (deviance)
		*deviance = diff;
	return closestEntity;
}


void cLegit::applyLinearAdjustment(int desiredX, int desiredY, int maxDistancePerSecond, float lastIteration)
{
	if (!g_pCInput->m_fMouseActive)
		return;
	auto maxAdjust = static_cast<float>(maxDistancePerSecond) * (Globals->realtime - lastIteration);
	float xAdjust, yAdjust;
	int width, height;
	Engine->GetScreenSize(width, height);
	auto centerX = width / 2;
	auto centerY = height / 2;
	auto negative = desiredX - centerX < 0;
	xAdjust = min(maxAdjust / 2.f, abs((float)(desiredX - centerX))) * (negative ? -1.f : 1.f);
	negative = desiredY - centerY < 0;
	if (xAdjust < (maxAdjust / 2.f))
		yAdjust = min(maxAdjust - xAdjust, abs((float)(desiredY - centerY))) * (negative ? -1.f : 1.f);
	else
		yAdjust = min(maxAdjust / 2.f, abs((float)(desiredY - centerY))) * (negative ? -1.f : 1.f);
	negative = xAdjust < 0;
	xAdjust = ceil(abs(xAdjust)) * (negative ? -1 : 1);
	negative = yAdjust < 0;
	yAdjust = ceil(abs(yAdjust)) * (negative ? -1 : 1);
	mouse_event(MOUSEEVENTF_MOVE, static_cast<int>(xAdjust), static_cast<int>(yAdjust), NULL, NULL);
}

int g_maxDeviance = 0;
void cLegit::subtleAim(CUserCmd* cmd, int bone)
{
	static float lastIteration = 0;
	if (Globals->realtime - lastIteration > 0.2f)
		lastIteration = Globals->realtime; 
	CBaseEntity* target;
	QAngle deviance;

	auto localPlayerWep = Global::LocalPlayer->GetWeapon();

	auto gravityStrength = Options.Legit.Aimbot.AimSpeed; 
	g_maxDeviance = Options.Legit.Aimbot.LFOV;

	if (localPlayerWep)
	{
		if (localPlayerWep->GetWeaponType() == WEPCLASS_INVALID || localPlayerWep->GetWeaponType() == WEPCLASS_KNIFE)
			return;
		if (localPlayerWep->GetWeaponType() == WEPCLASS_RIFLE || localPlayerWep->GetWeaponType() == WEPCLASS_MACHINEGUN || localPlayerWep->GetWeaponType() == WEPCLASS_SMG)
		{
			auto clip = *reinterpret_cast<int*>(DWORD(localPlayerWep) + offsets.m_iClip1);
			if (clip > 0 && cmd->buttons & IN_ATTACK)
			{
				gravityStrength *= Options.Legit.Aimbot.MultiplySpeed;
				g_maxDeviance += Options.Legit.Aimbot.FOVBOOST;
			}
		}
	}

	if (!(target = getTargetNearestCrosshair(cmd, bone, &deviance)))
		return;
	if (!isPlayerVisible(target))
		return;
	auto desiredAngle = calcViewangleAdjustment(target, cmd, bone, false) + cmd->viewangles;
	Vector targetPos, targetScrPos;
	AngleVectors(desiredAngle, &targetPos, nullptr, nullptr);
	targetPos += Global::LocalPlayer->GetEyePosition();
	if (!WorldToScreen(targetPos, targetScrPos))
		return;

	if (screenDifference(deviance) < g_maxDeviance)
		applyLinearAdjustment(targetScrPos.x, targetScrPos.y, gravityStrength, lastIteration);
	lastIteration = Globals->realtime;
}

int cLegit::GetTargetClosest()
{
	
	auto pFov = Options.Legit.Aimbot.Fov;
	auto iBestTarget = -1;
	for (auto i = 0; i <= Globals->maxClients; i++)
	{
		CBaseEntity* pTarget = nullptr;;
		QAngle Angles;
		if (!ValidEntity(i))
			continue;
		if (!(pTarget = ClientEntList->GetClientEntity(i)))
			continue;

		CalcAngle(Global::LocalPlayer->GetEyePosition(), pTarget->GetBonePosition(Options.Legit.Aimbot.Bone), Angles);
		auto fov = GetFov(Global::pCmd->viewangles, Angles);

		if (fov < pFov)
		{
			pFov = fov;
			iBestTarget = i;
		}
	}
	if (iBestTarget != -1)
		return iBestTarget;
	return -1;
}

// Given to me by a friend, dont know where he got it, but all credits to whoever it came from.
// I went ahead and changed it up a bit to adjust it to what we want.
// It works though, But we definitely will add other methods later.
// Might not be enough, will look into later.

float lastX;
float lastY;

float destX;
float destY;

float curX;
float curY;
QAngle Randomize(QAngle Angles, QAngle oAngle)// you need to actually initalize the variables you know that right?
{
	curX = oAngle.x;
	curY = oAngle.y;
	destX = Angles.x;
	destY = Angles.y;
	if (abs(curX - destX) < .05f)
	{
		destX = rand() % static_cast<int>(Options.Legit.Aimbot.Human * 10) + 1;
		destX /= 500;
		auto positive = rand() % 2 + 1;
		if (positive == 2)
			destX = -destX;
	}

	if (abs(curY - destY) < .05f)
	{
		destY = rand() % static_cast<int>(Options.Legit.Aimbot.Human * 10) + 1;
		destY /= 500;
		auto positive = rand() % 2 + 1;
		if (positive == 2)
			destY = -destY;
	}

	auto speed = 20 - int(Options.Legit.Aimbot.HumanSpeed);
	curX += (destX - curX) / ((15 * speed) + 10);
	curY += (destY - curY) / ((15 * speed) + 10);

	Angles.x += curX;
	Angles.y += curY;


	return Angles;

}


void cLegit::GoToTarget(CBaseEntity* pTarget)
{
	static QAngle qSetAngles;
	Engine->GetViewAngles(qSetAngles);
	qSetAngles.Normalize();
	if (pTarget->GetHealth() <= 0)
		return;
	CalcAngle(Global::LocalPlayer->GetEyePosition(),
		pTarget->GetBonePosition(Options.Legit.Aimbot.Bone),
		Global::pCmd->viewangles);
	if (Options.AntiCheat.FACEIT)
	{
		Randomize(Global::pCmd->viewangles, qSetAngles);
		Global::pCmd->viewangles -= Global::LocalPlayer->GetPunch() * 2.00f;
	}
 else
	{
		if (Options.Legit.Aimbot.RCS)
			Global::pCmd->viewangles -= Global::LocalPlayer->GetPunch() * 2.00f;
		auto qDelta = Global::pCmd->viewangles - qSetAngles;
		qDelta.Normalize();

		Global::pCmd->viewangles.x = qSetAngles.x + qDelta.x / Options.Legit.Aimbot.Smooth[0];
		Global::pCmd->viewangles.y = qSetAngles.y + qDelta.y / Options.Legit.Aimbot.Smooth[1];
	}
	Global::pCmd->viewangles.Normalize();
	if(!Options.Legit.Aimbot.SilentAim)
	Engine->SetViewAngles(Global::pCmd->viewangles);
}

void cLegit::Aimbot()
{
	if (!Global::LocalPlayer->GetWeapon()->IsGun() || Global::LocalPlayer->GetWeapon()->IsEmpty() || Options.Legit.Aimbot.Fov <= 0)
		return;
	CBaseEntity* pTarget = nullptr;
	auto iTarget = -1;
	if (!(Global::pCmd->buttons & IN_ATTACK) || !pTarget)
		iTarget = this->GetTargetClosest();

	if (iTarget != -1)
		pTarget = ClientEntList->GetClientEntity(iTarget);

	if (pTarget && Global::pCmd->buttons & IN_ATTACK)
		GoToTarget(pTarget);
}

CBaseEntity* cLegit::getTargetUnderCrosshair(CUserCmd* cmd, bool enemiesOnly, bool visibleOnly, trace_t* trOut) const
{
	Vector vEnd;
	auto view = cmd->viewangles;

	trace_t tr;
	Ray_t ray;

	CTraceFilter filter;
	filter.pSkip = Global::LocalPlayer;

	AngleVectors(view, &vEnd, nullptr, nullptr);

	vEnd = vEnd * 8192.0f + Global::LocalPlayer->GetEyePosition();

	ray.Init(Global::LocalPlayer->GetEyePosition(), vEnd);
	EngineTrace->TraceRay(ray, CONTENTS_SOLID | CONTENTS_GRATE | CONTENTS_HITBOX, &filter, &tr);

	if (!tr.m_pEnt)
		return nullptr;
	if (tr.m_pEnt->GetTeam() == Global::LocalPlayer->GetTeam() && enemiesOnly)
		return nullptr;
	if (tr.hitgroup <= 7 && tr.hitgroup > 0)
	{
		if (trOut)
			*trOut = tr;
		return tr.m_pEnt;
	}
	else
		return nullptr;
}

void cLegit::triggerbot(CUserCmd* cmd)
{
	if (!GetAsyncKeyState(Options.Legit.Trigger.Key)) return;
	CBaseEntity* target = nullptr;
	auto bShoot = false;
	auto localPlayerWep = Global::LocalPlayer->GetWeapon();
	if (!localPlayerWep)return;
	auto maxdist = localPlayerWep->GetCSWpnData()->m_flRange;//as far as a bullet can travel
	auto weaponID = *reinterpret_cast<int*>(reinterpret_cast<DWORD>(localPlayerWep) + offsets.m_iItemDefinitionIndex);
	
	trace_t tr;
	if ((target = getTargetUnderCrosshair(cmd, Options.Legit.Trigger.TriggerFriends, true, &tr)))
	{
		auto vecToTarget = tr.endpos - Global::LocalPlayer->GetEyePosition();
		switch (Options.Legit.Trigger.Filter)
		{
		case FILTER_MOSTDAMAGE:
		{
			if (tr.hitgroup > HITGROUP_GENERIC && tr.hitgroup <= HITGROUP_STOMACH)
				bShoot = true;
			break;         
		}
		case FILTER_BODYONLY:
		{
			if ( tr.hitgroup > HITGROUP_HEAD && tr.hitgroup <= HITGROUP_RIGHTLEG)
				bShoot = true;
			break;
		}
		case FILTER_BODYNOARMS:
		{
			if (tr.hitgroup > HITGROUP_HEAD && tr.hitgroup <= HITGROUP_STOMACH)
				bShoot = true;
			break;
		}
		case FILTER_HEADONLY:
		{
			if (tr.hitgroup == HITGROUP_HEAD)
				bShoot = true;
			break;
		}
		case FILTER_ARMSONLY:
		{
			if (tr.hitgroup > HITGROUP_STOMACH && tr.hitgroup <= HITGROUP_RIGHTLEG)
				bShoot = true;
			break;
		}
		default:
			bShoot = true;
			break;
		}
		if (vecToTarget.Length() < maxdist && bShoot)
		{
			static auto bFlip = false;

			if (localPlayerWep->GetNextPrimaryAttack() < Globals->curtime)
			{
				cmd->buttons |= IN_ATTACK;
			}
			else
			{
				cmd->buttons &= ~IN_ATTACK;
			}
		}
	}
}

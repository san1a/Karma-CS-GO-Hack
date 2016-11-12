#include "SDK.h"
#include <string>
#include "Globals.h"

int	CBaseEntity::GetHealth()
{
	return *reinterpret_cast<int*>((DWORD)this + offsets.m_iHealth);
}

int CBaseEntity::GetTeam()
{
	return *reinterpret_cast<int*>((DWORD)this + offsets.m_iTeamNum);
}

int CBaseEntity::GetFlags()
{
	return *(int*)((DWORD)this + offsets.m_fFlags);
}

int CBaseEntity::GetTickBase()
{
	return *(int*)((DWORD)this + offsets.m_nTickBase);
}

int CBaseEntity::GetShotsFired()
{
	return *(int*)((DWORD)this + offsets.m_iShotsFired);
}

int CBaseEntity::GetMoveType()
{
	return *(int*)((DWORD)this + offsets.m_nMoveType);
}

int CBaseEntity::GetModelIndex()
{
	return *(int*)((DWORD)this + offsets.m_nModelIndex);
}

int CBaseEntity::GetHitboxSet()
{
	return *(int*)((DWORD)this + offsets.m_nHitboxSet);
}

int CBaseEntity::GetUserID()
{
	return this->GetPlayerInfo().userid;
}

int CBaseEntity::GetArmor()
{
	return *(int*)((DWORD)this + offsets.m_ArmorValue);
}

int CBaseEntity::PhysicsSolidMaskForEntity()
{
	typedef unsigned int(__thiscall* OriginalFn)(void*);
	return GetVFunc<OriginalFn>(this, 154)(this);
}

int CBaseEntity::GetOwner()
{
	return *(int*)((DWORD)this + offsets.m_hOwnerEntity);
}

int CBaseEntity::GetGlowIndex()
{
	return *(int*)((DWORD)this + offsets.m_iGlowIndex);
}

float CBaseEntity::GetBombTimer()
{
	float bombTime = *(float*)((DWORD)this + offsets.m_flC4Blow);
	float returnValue = bombTime - Globals->curtime;
	return (returnValue < 0) ? 0.f : returnValue;
}

float CBaseEntity::GetFlashDuration()
{
	return *(float*)((DWORD)this + offsets.m_flFlashDuration);
}

bool CBaseEntity::IsFlashed()
{
	return GetFlashDuration() > 0 ? true : false;
}

bool CBaseEntity::GetAlive()
{
	return (bool)(*(int*)((DWORD)this + offsets.m_lifeState) == 0);
}

int CBaseEntity::GetIndex() {
	return *(int*)((DWORD)this + 0x64);
}

bool CBaseEntity::GetDormant()
{
	return *(bool*)((DWORD)this + offsets.m_bDormant);
}

bool CBaseEntity::GetImmune()
{
	return *(bool*)((DWORD)this + offsets.m_bGunGameImmunity);
}

bool CBaseEntity::HasHelmet()
{
	return *(bool*)((DWORD)this + offsets.m_bHasHelmet);
}



bool CBaseEntity::IsTargetingLocal()
{
	Vector src, dst, forward;
	trace_t tr;

	if (!this)
		return false;

	QAngle viewangle = this->GetEyeAngles();

	AngleVectors(viewangle, &forward);
	forward *= 8142.f;
	src = this->GetEyePosition();
	dst = src + forward;

	TraceLine(src, dst, MASK_SHOT, this, &tr);

	if (tr.m_pEnt == Global::LocalPlayer)
		return true;

	return false;
}

model_t* CBaseEntity::GetModel()
{
	return *(model_t**)((DWORD)this + 0x6C);
}

model_t* CBaseCombatWeapon::GetModel()
{
	return *(model_t**)((DWORD)this + 0x6C);
}


bool CBaseEntity::IsEnemy()
{
	return (this->GetTeam() == Global::LocalPlayer->GetTeam() || this->GetTeam() == 0) ? false : true;
}

bool CBaseEntity::IsVisible(int bone)
{
	Ray_t ray;
	trace_t tr;
	m_visible = false;
	ray.Init(Global::LocalPlayer->GetEyePosition(), this->GetBonePosition(bone)); // replace with config->aimbone

	CTraceFilter filter;
	filter.pSkip = Global::LocalPlayer;

	EngineTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);

	if (tr.m_pEnt == this)
	{
		m_visible = true;
		return true;
	}

	return false;
}

bool CBaseEntity::IsEntireVisible()
{
	for (auto i = 0; i < 32; i++)
	{
		if (this->IsVisible(i))
			return true;
	}
	return false;
}

bool CBaseEntity::IsBroken()
{
	return *reinterpret_cast<bool*>(reinterpret_cast<DWORD>(this) + offsets.m_bIsBroken);
}

QAngle CBaseEntity::GetViewPunch()
{
	return *(QAngle*)((DWORD)this + offsets.m_viewPunchAngle);
}

QAngle CBaseEntity::GetPunch()
{
	return *(QAngle*)((DWORD)this + offsets.m_aimPunchAngle);
}

QAngle CBaseEntity::GetEyeAngles()
{
	return *(QAngle*)((DWORD)this + offsets.m_angEyeAngles);
}

Vector CBaseEntity::GetOrigin()
{
	return *(Vector*)((DWORD)this + offsets.m_vecOrigin);
}

Vector CBaseCombatWeapon::GetOrigin()
{
	return *(Vector*)((DWORD)this + offsets.m_vecOrigin);
}

Vector CBaseEntity::GetEyePosition()
{
	Vector origin = this->GetOrigin();
	Vector offset = *(Vector*)((DWORD)this + offsets.m_vecViewOffset);

	return(origin + offset);
}

Vector CBaseEntity::GetBonePosition(int iBone)
{
	matrix3x4_t boneMatrixes[128];
	if (this->SetupBones(boneMatrixes, 128, 0x100, 0))
	{
		matrix3x4_t boneMatrix = boneMatrixes[iBone];
		return Vector(boneMatrix.m_flMatVal[0][3], boneMatrix.m_flMatVal[1][3], boneMatrix.m_flMatVal[2][3]);
	}
	else return Vector(0, 0, 0);
}

bool CBaseEntity::SetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
{
	__asm
	{
		mov edi, this
		lea ecx, dword ptr ds : [edi + 0x4]
		mov edx, dword ptr ds : [ecx]
		push currentTime
		push boneMask
		push nMaxBones
		push pBoneToWorldOut
		call dword ptr ds : [edx + 0x34]
	}
}

Vector CBaseEntity::GetVelocity()
{
	return *reinterpret_cast<Vector*>((DWORD)this + offsets.m_vecVelocity);
}

Vector CBaseEntity::GetPredicted(Vector p0)
{
	return ExtrapolateTick(p0, this->GetVelocity());
}

ICollideable* CBaseEntity::GetCollideable()
{
	return reinterpret_cast<ICollideable*>((DWORD)this + offsets.m_Collision);
}

player_info_t CBaseEntity::GetPlayerInfo()
{
	player_info_t pinfo;
	Engine->GetPlayerInfo(this->index, &pinfo);
	return pinfo;
}

std::string	CBaseEntity::GetName()
{
	return this->GetPlayerInfo().name;
}

std::string	CBaseEntity::GetSteamID()
{
	return this->GetPlayerInfo().name;
}

std::string CBaseEntity::GetLastPlace()
{
	return std::string(reinterpret_cast<const char*>(this) + offsets.m_szLastPlaceName);
}

CBaseCombatWeapon* CBaseEntity::GetWeapon()
{
	DWORD weaponData = *(DWORD*)((DWORD)this + offsets.m_hActiveWeapon);
	return (CBaseCombatWeapon*)ClientEntList->GetClientEntityFromHandle(weaponData);
}

ClientClass* CBaseEntity::GetClientClass()
{
	PVOID pNetworkable = (PVOID)((DWORD)(this) + 0x8);
	typedef ClientClass*(__thiscall* OriginalFn)(PVOID);
	return GetVFunc<OriginalFn>(pNetworkable, 2)(pNetworkable);
}

bool CBaseEntity::IsScoped()
{
	return *(bool*)((DWORD)this + offsets.m_bScoped);
}

int CBaseEntity::GetCollisionGroup()
{
	return *(int*)((DWORD)this + offsets.m_CollisionGroup);
}

int& CBaseCombatWeapon::GetWeaponID()
{
	return *(int*)((DWORD)this + offsets.m_iWeaponID);
}

float& CBaseCombatWeapon::GetNextPrimaryAttack()
{
	return *(float*)((DWORD)this + offsets.m_flNextPrimaryAttack);
}

float& CBaseCombatWeapon::GetAccuracyPenalty()
{
	return *(float*)((DWORD)this + offsets.m_fAccuracyPenalty);
}

int& CBaseCombatWeapon::GetXUIDLow()
{
	return *(int*)((DWORD)this + offsets.m_OriginalOwnerXuidLow);
}

int& CBaseCombatWeapon::GetXUIDHigh()
{
	return *(int*)((DWORD)this + offsets.m_OriginalOwnerXuidHigh);
}

int& CBaseCombatWeapon::GetEntityQuality()
{
	return *(int*)((DWORD)this + offsets.m_iEntityQuality);
}

int& CBaseCombatWeapon::GetAccountID()
{
	return *(int*)((DWORD)this + offsets.m_iAccountID);
}

int& CBaseCombatWeapon::GetItemIDHigh()
{
	return *(int*)((DWORD)this + offsets.m_iItemIDHigh);
}

int& CBaseCombatWeapon::GetItemDefinitionIndex()
{
	return *(int*)((DWORD)this + offsets.m_iItemDefinitionIndex);
}

int& CBaseCombatWeapon::GetFallbackPaintKit()
{
	return *(int*)((DWORD)this + offsets.m_nFallbackPaintKit);
}

int& CBaseCombatWeapon::GetFallbackStatTrak()
{
	return *(int*)((DWORD)this + offsets.m_nFallbackStatTrak);
}

float& CBaseCombatWeapon::GetFallbackWear()
{
	return *(float*)((DWORD)this + offsets.m_flFallbackWear);
}

int CBaseCombatWeapon::GetModelIndex() {
	// DT_BaseViewModel -> m_nModelIndex
	return *(int*)((DWORD)this + 0x254);
}

WeaponInfo_t* CBaseCombatWeapon::GetCSWpnData()
{
	if (!this) return nullptr;

	typedef WeaponInfo_t*(__thiscall* OriginalFn)(void*);
	return GetVFunc<OriginalFn>(this, 456)(this);
}

bool CBaseCombatWeapon::IsEmpty()
{
	int clip = *(int*)((DWORD)this + offsets.m_iClip1);
	return clip == 0;
}

bool CBaseCombatWeapon::IsReloading()
{
	return *(bool*)((DWORD)this + 0x3235);
}

bool CBaseCombatWeapon::GetOwner()
{
	return *(int*)((DWORD)this + offsets.m_hOwnerEntity);
}


void CBaseCombatWeapon::UpdateAccuracyPenalty()
{
	typedef void(__thiscall *FunctionFn)(void*);
	reinterpret_cast<FunctionFn>(*reinterpret_cast<PDWORD>(*reinterpret_cast<PDWORD>(this) + 0x748))((void*)this);
}

float CBaseCombatWeapon::GetWeaponCone()
{
	if (!this)
		return 0.f;

	typedef float(__thiscall* OriginalFn)(void*);
	return GetVFunc<OriginalFn>(this, 478)(this);
}

float CBaseCombatWeapon::GetWeaponSpread()
{
	if (!this)
		return 0.f;

	typedef float(__thiscall* OriginalFn)(void*);
	return GetVFunc<OriginalFn>(this, 484)(this);
}


bool CBaseCombatWeapon::IsGun()
{
	if (!this)
		return false;

	int id = this->GetWeaponID();

	switch (id)
	{
	case WEAPON_DEAGLE:
	case WEAPON_ELITE:
	case WEAPON_FIVESEVEN:
	case WEAPON_GLOCK:
	case WEAPON_AK47:
	case WEAPON_AUG:
	case WEAPON_AWP:
	case WEAPON_FAMAS:
	case WEAPON_G3SG1:
	case WEAPON_GALILAR:
	case WEAPON_M249:
	case WEAPON_M4A1:
	case WEAPON_MAC10:
	case WEAPON_P90:
	case WEAPON_UMP45:
	case WEAPON_XM1014:
	case WEAPON_BIZON:
	case WEAPON_MAG7:
	case WEAPON_NEGEV:
	case WEAPON_SAWEDOFF:
	case WEAPON_TEC9:
		return true;
	case WEAPON_TASER:
		return false;
	case WEAPON_HKP2000:
	case WEAPON_MP7:
	case WEAPON_MP9:
	case WEAPON_NOVA:
	case WEAPON_P250:
	case WEAPON_SCAR20:
	case WEAPON_SG556:
	case WEAPON_SSG08:
		return true;
	case WEAPON_KNIFE:
	case WEAPON_FLASHBANG:
	case WEAPON_HEGRENADE:
	case WEAPON_SMOKEGRENADE:
	case WEAPON_MOLOTOV:
	case WEAPON_DECOY:
	case WEAPON_INCGRENADE:
	case WEAPON_C4:
	case WEAPON_KNIFE_T:
		return false;
	case WEAPON_M4A1_SILENCER:
	case WEAPON_USP_SILENCER:
	case WEAPON_CZ75A:
	case WEAPON_REVOLVER:
		return true;
	default:
		return false;
	}
}


std::string CBaseCombatWeapon::GetWeaponName()
{
	if (!this)
		return "";

	auto id = this->GetWeaponID();

	switch (id)
	{
	case WEAPON_DEAGLE:
		return XorStr("Desert Eagle");
	case WEAPON_ELITE:
		return XorStr("Dual Berettas");
	case WEAPON_FIVESEVEN:
		return XorStr("Five-SeveN");
	case WEAPON_GLOCK:
		return XorStr("Glock-18");
	case WEAPON_AK47:
		return XorStr("AK-47");
	case WEAPON_AUG:
		return XorStr("AUG");
	case WEAPON_AWP:
		return XorStr("AWP");
	case WEAPON_FAMAS:
		return XorStr("FAMAS");
	case WEAPON_G3SG1:
		return XorStr("G3SG1");
	case WEAPON_GALILAR:
		return XorStr("Galil");
	case WEAPON_M249:
		return XorStr("M249");
	case WEAPON_M4A1:
		return XorStr("M4A1");
	case WEAPON_MAC10:
		return XorStr("MAC-10");
	case WEAPON_P90:
		return XorStr("P90");
	case WEAPON_UMP45:
		return XorStr("UMP-45");
	case WEAPON_XM1014:
		return XorStr("XM1014");
	case WEAPON_BIZON:
		return XorStr("PP-Bizon");
	case WEAPON_MAG7:
		return XorStr("MAG-7");
	case WEAPON_NEGEV:
		return XorStr("Negev");
	case WEAPON_SAWEDOFF:
		return XorStr("Sawed-Off");
	case WEAPON_TEC9:
		return XorStr("Tec-9");
	case WEAPON_TASER:
		return XorStr("Taser");
	case WEAPON_HKP2000:
		return XorStr("P2000");
	case WEAPON_MP7:
		return XorStr("MP7");
	case WEAPON_MP9:
		return XorStr("MP9");
	case WEAPON_NOVA:
		return XorStr("Nova");
	case WEAPON_P250:
		return XorStr("P250");
	case WEAPON_SCAR20:
		return XorStr("SCAR-20");
	case WEAPON_SG556:
		return XorStr("SG 553");
	case WEAPON_SSG08:
		return XorStr("SSG 08");
	case WEAPON_KNIFE:
		return XorStr("Knife");
	case WEAPON_FLASHBANG:
		return XorStr("Flashbang");
	case WEAPON_HEGRENADE:
		return XorStr("HE Grenade");
	case WEAPON_SMOKEGRENADE:
		return XorStr("Smoke Grenade");
	case WEAPON_MOLOTOV:
		return XorStr("Molotov");
	case WEAPON_DECOY:
		return XorStr("Decoy");
	case WEAPON_INCGRENADE:
		return XorStr("Incendiary Grenade");
	case WEAPON_C4:
		return XorStr("C4");
	case WEAPON_KNIFE_T:
		return XorStr("Knife");
	case WEAPON_M4A1_SILENCER:
		return XorStr("M4A1-S");
	case WEAPON_USP_SILENCER:
		return XorStr("USP-S");
	case WEAPON_CZ75A:
		return XorStr("CZ75-Auto");
	case WEAPON_REVOLVER:
		return XorStr("R8 Revolver");
	default:
		return XorStr("Knife");
	}

	return "";
}

int CBaseCombatWeapon::GetWeaponType()
{
	if (!this) return WEPCLASS_INVALID;
	auto id = this->GetWeaponID();
	switch (id)
	{
	case WEAPON_DEAGLE:
	case WEAPON_ELITE:
	case WEAPON_FIVESEVEN:
	case WEAPON_HKP2000:
	case WEAPON_USP_SILENCER:
	case WEAPON_CZ75A:
	case WEAPON_TEC9:
	case WEAPON_REVOLVER:
	case WEAPON_GLOCK:
	case WEAPON_P250:
        return WEPCLASS_PISTOL;
	break;
	case WEAPON_AK47:
	case WEAPON_M4A1:
	case WEAPON_M4A1_SILENCER:
	case WEAPON_GALILAR:
	case WEAPON_AUG:
	case WEAPON_FAMAS:
	case WEAPON_SG556:
	    return WEPCLASS_RIFLE;
	break;
	case WEAPON_P90:
	case WEAPON_BIZON:
	case WEAPON_MP7:
	case WEAPON_MP9:
	case WEAPON_MAC10:
	case WEAPON_UMP45:
		return WEPCLASS_SMG;
	break;
	case WEAPON_AWP:
	case WEAPON_G3SG1:
	case WEAPON_SCAR20:
	case WEAPON_SSG08:
		return WEPCLASS_SNIPER;
	break;
	case WEAPON_NEGEV:
	case WEAPON_M249:
		return WEPCLASS_MACHINEGUN;
	break;
	case WEAPON_MAG7:
	case WEAPON_SAWEDOFF:
	case WEAPON_NOVA:
	case WEAPON_XM1014:
		return WEPCLASS_SHOTGUN;
	break;
	case WEAPON_KNIFE:
	case WEAPON_KNIFE_BAYONET:
	case WEAPON_KNIFE_BUTTERFLY:
	case WEAPON_KNIFE_FALCHION:
	case WEAPON_KNIFE_FLIP:
	case WEAPON_KNIFE_GUT:
	case WEAPON_KNIFE_KARAMBIT:
	case WEAPON_KNIFE_TACTICAL:
	case WEAPON_KNIFE_M9_BAYONET:
	case WEAPON_KNIFE_PUSH:
	case WEAPON_KNIFE_SURVIVAL_BOWIE:
	case WEAPON_KNIFE_T:
		return WEPCLASS_KNIFE;
	break;

	default:
		return WEPCLASS_INVALID;
	}
}

bool CBaseCombatWeapon::IsScopedWeapon()
{
	if (!this) return false;
	auto WeaponID = this->GetWeaponID();
	if (WeaponID == WEAPON_AWP
		|| WeaponID == WEAPON_SCAR20
		|| WeaponID == WEAPON_G3SG1
		|| WeaponID == WEAPON_SSG08
		|| WeaponID == WEAPON_AUG
		|| WeaponID == WEAPON_SG556)
		return true;
	return false;
}

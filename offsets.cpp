#include "SDK.h"
COffsets offsets;

void GrabOffsets()
{
	offsets.m_iHealth = NetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_iHealth"));
	offsets.m_iTeamNum = NetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_iTeamNum"));
	offsets.m_ArmorValue = NetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_ArmorValue"));
	offsets.m_bHasHelmet = NetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_bHasHelmet"));
	offsets.m_iClass = NetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_iClass"));
	offsets.m_bDormant = 0xE9;
	offsets.m_bGunGameImmunity = NetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_bGunGameImmunity"));
	offsets.m_lifeState = NetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_lifeState"));
	offsets.m_fFlags = NetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_fFlags"));
	offsets.m_Local = NetVars->GetOffset(XorStr("DT_BasePlayer"), XorStr("m_Local"));
	offsets.m_nTickBase = NetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_nTickBase"));
	offsets.m_nForceBone = NetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_nForceBone"));
	offsets.m_angEyeAngles = NetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_angEyeAngles"));
	offsets.m_angEyeAnglesX = NetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_angEyeAngles[0]"));
	offsets.m_angEyeAnglesY = NetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_angEyeAngles[1]"));
	offsets.m_flFlashDuration = NetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_flFlashDuration"));
	offsets.m_iGlowIndex = offsets.m_flFlashDuration + 0x18;
	offsets.m_mBoneMatrix = offsets.m_nForceBone + 0x1C;
	offsets.m_nModelIndex = NetVars->GetOffset(XorStr("DT_BasePlayer"), XorStr("m_nModelIndex"));
	offsets.m_viewPunchAngle = NetVars->GetOffset(XorStr("DT_BasePlayer"), XorStr("m_viewPunchAngle"));
	offsets.m_aimPunchAngle = NetVars->GetOffset(XorStr("DT_BasePlayer"), XorStr("m_aimPunchAngle"));
	offsets.m_vecOrigin = NetVars->GetOffset(XorStr("DT_BasePlayer"), XorStr("m_vecOrigin"));
	offsets.m_vecViewOffset = NetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_vecViewOffset[0]"));
	offsets.m_vecVelocity = NetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_vecVelocity[0]"));
	offsets.m_szLastPlaceName = NetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_szLastPlaceName"));
	offsets.m_hActiveWeapon = NetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_hActiveWeapon"));
	offsets.m_fAccuracyPenalty = NetVars->GetOffset(XorStr("DT_WeaponCSBase"), XorStr("m_fAccuracyPenalty"));
	offsets.m_Collision = NetVars->GetOffset(XorStr("DT_BasePlayer"), XorStr("m_Collision"));
	offsets.m_CollisionGroup = NetVars->GetOffset(XorStr("DT_BasePlayer"), XorStr("m_CollisionGroup"));
	offsets.m_iShotsFired = NetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_iShotsFired"));
	offsets.m_iWeaponID = NetVars->GetOffset(XorStr("DT_WeaponCSBase"), XorStr("m_fAccuracyPenalty")) + 0x2C;
	offsets.m_hOwnerEntity = NetVars->GetOffset(XorStr("DT_BaseEntity"), XorStr("m_hOwnerEntity"));
	offsets.m_hOwner = NetVars->GetOffset(XorStr("DT_BaseEntity"), XorStr("m_hOwner"));
	offsets.m_nMoveType = 0x258;
	offsets.m_bScoped = NetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_bIsScoped"));
	offsets.m_nHitboxSet = NetVars->GetOffset(XorStr("DT_BasePlayer"), XorStr("m_nHitboxSet"));
	offsets.m_bIsBroken = NetVars->GetOffset(XorStr("DT_BreakableSurface"), XorStr("m_bIsBroken"));
	offsets.m_flC4Blow = NetVars->GetOffset(XorStr("DT_PlantedC4"), XorStr("m_flC4Blow"));
	offsets.m_flEyePos = NetVars->GetOffset(XorStr("DT_BasePlayer"), XorStr("m_vecViewOffset[0]"));
	offsets.m_bReloadVisuallyComplete = NetVars->GetOffset(XorStr("DT_WeaponCSBase"), XorStr("m_bReloadVisuallyComplete"));
	offsets.m_flNextPrimaryAttack = NetVars->GetOffset(XorStr("DT_BaseCombatWeapon"), XorStr("m_flNextPrimaryAttack"));
	offsets.m_nFallbackPaintKit = NetVars->GetOffset(XorStr("DT_BaseCombatWeapon"), XorStr("m_nFallbackPaintKit"));
	offsets.m_nFallbackSeed = NetVars->GetOffset(XorStr("DT_BaseCombatWeapon"), XorStr("m_nFallbackSeed"));
	offsets.m_flFallbackWear = NetVars->GetOffset(XorStr("DT_BaseCombatWeapon"), XorStr("m_flFallbackWear"));
	offsets.m_nFallbackStatTrak = NetVars->GetOffset(XorStr("DT_BaseCombatWeapon"), XorStr("m_nFallbackStatTrak"));
	offsets.m_AttributeManager = NetVars->GetOffset(XorStr("DT_BaseCombatWeapon"), XorStr("m_AttributeManager"));
	offsets.m_Item = NetVars->GetOffset(XorStr("DT_BaseCombatWeapon"), XorStr("m_Item"));
	offsets.m_iEntityLevel = NetVars->GetOffset(XorStr("DT_BaseCombatWeapon"), XorStr("m_iEntityLevel"));
	offsets.m_iItemIDHigh = NetVars->GetOffset(XorStr("DT_BaseCombatWeapon"), XorStr("m_iItemIDHigh"));
	offsets.m_iItemIDLow = NetVars->GetOffset(XorStr("DT_BaseCombatWeapon"), XorStr("m_iItemIDLow"));
	offsets.m_iAccountID = NetVars->GetOffset(XorStr("DT_BaseCombatWeapon"), XorStr("m_iAccountID"));
	offsets.m_iEntityQuality = NetVars->GetOffset(XorStr("DT_BaseCombatWeapon"), XorStr("m_iEntityQuality"));
	offsets.m_iClip1 = NetVars->GetOffset(XorStr("DT_BaseCombatWeapon"), XorStr("m_iClip1"));
	offsets.m_OriginalOwnerXuidLow = NetVars->GetOffset(XorStr("DT_BaseAttributableItem"), XorStr("m_OriginalOwnerXuidLow"));
	offsets.m_OriginalOwnerXuidHigh = NetVars->GetOffset(XorStr("DT_BaseAttributableItem"), XorStr("m_OriginalOwnerXuidHigh"));
	offsets.m_iItemDefinitionIndex = NetVars->GetOffset(XorStr("DT_BaseAttributableItem"), XorStr("m_iItemDefinitionIndex"));
	offsets.dwDeadFlag = NetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("deadflag"));
	offsets.ViewModelIndex = NetVars->GetOffset(XorStr("DT_BaseCombatWeapon"), XorStr("m_iViewModelIndex"));
	offsets.WorldModelIndex = NetVars->GetOffset(XorStr("DT_BaseCombatWeapon"), XorStr("m_iWorldModelIndex"));
	offsets.m_hObserverTarget = NetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_hObserverTarget"));
	offsets.m_iObserverMode = NetVars->GetOffset(XorStr("DT_BasePlayer"), XorStr("m_iObserverMode"));
	offsets.m_szCustomName = NetVars->GetOffset(XorStr("DT_BaseAttributableItem"), XorStr("m_szCustomName"));
	offsets.m_iCompetitiveRanking = NetVars->GetOffset(XorStr("DT_CSPlayerResource"), XorStr("m_iCompetitiveRanking"));
	offsets.m_iCompetitiveWins = NetVars->GetOffset(XorStr("DT_CSPlayerResource"), XorStr("m_iCompetitiveWins"));

	offsets.CalcPlayerView = Memory::FindPatternIDA(XorStr("client.dll"), XorStr(" 84 C0 75 08 57 8B CE E8 ?? ?? ?? ?? 8B 06"));
	offsets.d3d9Device = **reinterpret_cast<DWORD**>(Memory::FindPatternIDA(XorStr("shaderapidx9.dll"), XorStr("A1 ? ? ? ? 50 8B 08 FF 51 0C")) + 0x1);
	offsets.LoadFromBufferEx = Memory::FindPatternIDA(XorStr("client.dll"), XorStr("55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04"));
	offsets.InitKeyValuesEx = Memory::FindPatternIDA(XorStr("client.dll"), XorStr("55 8B EC 51 33 C0 C7 45"));
}


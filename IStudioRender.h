#pragma once

class IStudioRender;
class CMoveHelper
{
public:
	void SetHost(CBaseEntity* pPlayer)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, CBaseEntity* pPlayer);
		GetVFunc<OriginalFn>(this, 1)(this, pPlayer);
	}
};

class CGameMovement
{
public:
	void ProcessMovement(CBaseEntity* pPlayer, PVOID moveData)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, CBaseEntity* pPlayer, PVOID moveData);
		GetVFunc<OriginalFn>(this, 1)(this, pPlayer, moveData);
	}
};
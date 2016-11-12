#pragma once

class IPrediction
{
public:
	void SetupMove(CBaseEntity* player, CUserCmd* ucmd, PVOID empty, PVOID moveData)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, CBaseEntity* player, CUserCmd* ucmd, PVOID empty, PVOID moveData);
		GetVFunc<OriginalFn>(this, 20)(this, player, ucmd, nullptr, moveData);
	}

	void FinishMove(CBaseEntity* player, CUserCmd* ucmd, PVOID moveData)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, CBaseEntity* player, CUserCmd* ucmd, PVOID moveData);
		GetVFunc<OriginalFn>(this, 21)(this, player, ucmd, moveData);
	}
};
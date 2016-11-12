#pragma once
#include "common.h"

class IGameEvent {
public:
	const char* GetName() {
		return GetVFunc<const char*(__thiscall *)(void*)>(this, 1)(this);
	}

	int GetInt(const char* szKeyName, int nDefault = 0) {
		return GetVFunc<int(__thiscall *)(void*, const char*, int)>(this, 6)(this, szKeyName, nDefault);
	}

	const char* GetString(const char* szKeyName) {
		return GetVFunc<const char*(__thiscall *)(void*, const char*, int)>(this, 9)(this, szKeyName, 0);
	}

	void SetString(const char* szKeyName, const char* szValue) {
		return GetVFunc<void(__thiscall *)(void*, const char*, const char*)>(this, 16)(this, szKeyName, szValue);
	}
};

class IGameEventManager2 {
public:
	bool FireEventClientSide(IGameEvent* pEvent) {
		return GetVFunc<bool(__thiscall *)(void*, IGameEvent*)>(this, 8)(this, pEvent);
	}
};
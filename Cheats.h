#pragma once
#include "SDK.h"
#include "Globals.h"
extern DWORD __stdcall Visuals(void* args);
class cLegit
{
public:
	cLegit();
	void HandleTrigger(CUserCmd* pCmd);
	void triggerbot(CUserCmd*);
	CBaseEntity* getTargetUnderCrosshair(CUserCmd*, bool, bool, trace_t*) const;
	void Aimbot();
	int getBestTarget(CBaseEntity* local, CBaseCombatWeapon* weapon, Vector& dest);
	int GetTargetClosest();
	void GoToTarget(CBaseEntity* pTarget);
    bool ValidEntity(int i);
	void HandleConfigs();
	bool isBoneVisible(CBaseEntity* target, int bone);
	bool isPlayerVisible(CBaseEntity* target);
	QAngle calcViewangleAdjustment(CBaseEntity* target, CUserCmd* cmd, int bone, bool doubleRecoilComp);
	float screenDifference(QAngle& ang);
	CBaseEntity* getTargetNearestCrosshair(CUserCmd* cmd, int bone, QAngle* deviance);
	void applyLinearAdjustment(int desiredX, int desiredY, int maxDistancePerSecond, float lastIteration);
	void subtleAim(CUserCmd* cmd, int bone);
private:
	int bestTarget;

	QAngle viewAngles;
	Vector hitboxPosition;
	QAngle finalAngles;
};
extern cLegit* g_pLegit;
struct FireBulletData
{
	Vector src;
	trace_t enter_trace;
	Vector direction;
	CTraceFilter filter;
	float trace_length;
	float trace_length_remaining;
	float current_damage;
	int penetrate_count;
};

class class_autowall
{
public:
	class_autowall();
	bool AutoWall(CBaseEntity* pLocal, CBaseCombatWeapon* pWeapon, Vector& point);
	float GetDamage(Vector& point);
	float GetHitgroupDamage(int iHitgroup);
	void ScaleDamage(int Hitgroup, CBaseEntity* pEntity, float weapon_armor_ratio, float& current_damage);
	static bool DidHitNonWorldEntity(CBaseEntity* m_pEnt);
	bool TraceToExit(Vector& end, trace_t* enter_trace, Vector start, Vector dir, trace_t* exit_trace);

	bool SimulateFireBullet(CBaseEntity* pLocal, CBaseCombatWeapon* pWeapon, FireBulletData& data);
	bool HandleBulletPenetration(WeaponInfo_t* wpn_data, FireBulletData& data);
	bool SimulateBullet(CBaseEntity* pLocal, CBaseCombatWeapon* pWeapon, Vector& point, CBaseEntity* target);
	float SimulateBulletDamage(CBaseEntity* pLocal, CBaseCombatWeapon* pWeapon, Vector& point, CBaseEntity* target);
	bool IsFuckingAutowalling;
	float Invasive(Vector vEnd);
	float bIsPointPenetrable(Vector vEnd);
private:
	CTraceFilterNoPlayer tfNoPlayers;
};

extern class_autowall g_pAutowall;
struct Hitbox
{
	Hitbox(void)
	{
		hitbox = -1;
	}

	Hitbox(int newHitBox)
	{
		hitbox = newHitBox;
	}

	int  hitbox;
	Vector points[9];
};

enum
{
	FL_HIGH = (1 << 0),
	FL_LOW = (1 << 1),
	FL_SPECIAL = (1 << 2)
};

struct BestPoint
{
	BestPoint(void)
	{
		hitbox = -1;
		point = Vector(0, 0, 0);
		index = -1;
		dmg = -1;
		flags = 0;
	}

	explicit BestPoint(int newHitBox)
	{
		hitbox = newHitBox;
		point = Vector(0, 0, 0);
		index = -1;
		dmg = -1;
		flags = 0;
	}

	Vector point;
	int  index;
	int  dmg;
	int  flags;
	int  hitbox;
};
class CFixMove
{
public:
	void Start();
	void End();
private:
	float m_oldforward, m_oldsidemove;
	QAngle m_oldangle;
};// stolen from a5
class cRage
{
public:
	void Invoke(CUserCmd*,bool&,bool);
	bool GetHitbox(CBaseEntity*, Hitbox*);
	bool GetBestPoint(CBaseEntity*, Hitbox*, BestPoint*);
	bool CustomMultipoint(CBaseEntity*, Hitbox*, BestPoint*);
	bool BestAimPointAll(CBaseEntity*, Vector&);
	bool BestAimPoint(CBaseEntity* target, Vector& hitboxs);
	bool BestAimPointHitbox(CBaseEntity*, Vector&);
	bool IsValidEntity(int);
	bool CustomHitscans(CBaseEntity*, Vector&);
	void SetViewAngles(CUserCmd*, QAngle&);
	float AimNearPlayer(CBaseEntity*);
	void StopPlayer(CUserCmd*);
	int TargetSelection(CUserCmd*);
	void AntiAim(CUserCmd*, bool&);
	void Aimbot(CUserCmd*);
	void EnginePred(CUserCmd*);
	void MoniterNoSpread(CUserCmd*);
	int target;
	bool IsAimbotting, IsStopped;
};
extern cRage* g_pRage;
class cPlayer
{
public:
	void Bhop(CUserCmd*);
	void ForceThirdPerson(CUserCmd* pCmd);
	void AutoStrafe(CUserCmd*);
	void FakeLag(CUserCmd*, bool&);
	void AirStuck(CUserCmd*);
	void SpoofConvars();
	void ForceUpdate();
	void RageAutoStrafe(CUserCmd*);
	void ShowRank();
};
extern cPlayer* g_pPlayer;

class cVisuals
{
public:
	void Direct3D(IDirect3DDevice9*);
	void PaintTraverse();
	void RunLoop();
private:
	void RunMath(CBaseEntity*);
	void DrawCleanBox(Color, int, int, int, int);
	void RunTrace(CBaseEntity*, Vector&, Vector&);
	void DrawAimPoint(Color cColor, CBaseEntity* pEnt);
	void DrawTraceLine(Color, CBaseEntity*);
	void DrawHealth(Color, int, int, HFont, CBaseEntity*);
	void DrawWeapon(Color, int, int, HFont, CBaseEntity*);
	void DrawName(Color, int, int, HFont, CBaseEntity*);
	void DrawBone(CBaseEntity*);
	void DrawDLight(CBaseEntity* p_ent);
	void ShowRank(Color cColor, int topx, int topy, HFont hFont, CBaseEntity* pEnt);
	char* WeaponIDName(int weaponID);
	void LocationSpam(CBaseEntity* pEnt);

	struct
	{
		CBaseEntity* pEnt[64];
		int topx[64];
		int topy[64];
		int boty[64];
		int botx[64];
	}ESPINFO;
};
extern cVisuals* g_pVisuals;

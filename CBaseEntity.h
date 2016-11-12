#pragma once
#pragma once

enum MoveType_t
{
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC,
	MOVETYPE_WALK,
	MOVETYPE_STEP,
	MOVETYPE_FLY,
	MOVETYPE_FLYGRAVITY,
	MOVETYPE_VPHYSICS,
	MOVETYPE_PUSH,
	MOVETYPE_NOCLIP,
	MOVETYPE_LADDER,
	MOVETYPE_OBSERVER,
	MOVETYPE_CUSTOM,
	MOVETYPE_LAST = MOVETYPE_CUSTOM,
	MOVETYPE_MAX_BITS = 4
};

class CBaseCombatWeapon;
class CBaseEntity
{
public:
	char				__pad[0x64];
	int					index;
	int					GetHealth();
	int					GetTeam();
	int					GetFlags();
	int					GetTickBase();
	int					GetShotsFired();
	int					GetMoveType();
	int					GetModelIndex();
	int					GetHitboxSet();
	int					GetUserID();
	int					GetArmor();
	int					GetCollisionGroup();
	int					PhysicsSolidMaskForEntity();
	int					GetOwner();
	int					GetGlowIndex();
	bool				GetAlive();
	int GetIndex();
	bool				GetDormant();
	bool				GetImmune();
	bool				IsEnemy();
	bool				IsVisible(int bone);
	bool                IsEntireVisible();
	bool				m_visible;
	bool				IsBroken();
	bool				HasHelmet();
	bool				IsFlashed();
	bool				IsTargetingLocal();
	float				GetFlashDuration();
	float				GetBombTimer();
	QAngle				GetViewPunch();
	QAngle				GetPunch();
	QAngle				GetEyeAngles();
	Vector				GetOrigin();
	Vector				GetEyePosition();
	Vector				GetBonePosition(int iBone);
	bool				SetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime);
	Vector				GetVelocity();
	Vector				GetPredicted(Vector p0);
	ICollideable*		GetCollideable();
	player_info_t		GetPlayerInfo();
	model_t*			GetModel();
	std::string			GetName();
	std::string			GetSteamID();
	std::string			GetLastPlace();
	int&				GetXUIDLow();
	int&				GetXUIDHigh();
	CBaseCombatWeapon*	GetWeapon();
	ClientClass*		GetClientClass();
	bool                IsScoped();

};
/*
struct WeaponInfo_t
{
float m_flArmorRatio;
float m_flPenetration;
float m_iDamage;
float m_flRange;
float m_flRangeModifier;
};
*/
class CHudTexture
{
public:
	char type[64]; //0x0000
	char subtype[64]; //0x0040
	char unknowndata00[2]; //0x0080
	char charinFont; //0x0082
	char unknowndata01[1]; //0x0083
};//Size=0x00AC
/*
class WeaponInfo_t
{
public:
	char m_cPrintName[32]; //0x0000 
	uint8_t pad_0x0020[0x158]; //0x0020
	int32_t m_iBucket; //0x0178 
	int32_t m_iBucketPosition; //0x017C 
	int32_t m_iClipSize; //0x0180 
	int32_t m_iDefaultClip1; //0x0184 
	int32_t m_iDefaultClip2; //0x0188 
	uint8_t pad_0x018C[0x4]; //0x018C
	int32_t m_iWeight; //0x0190 
	int32_t m_iRumble; //0x0194 
	uint8_t pad_0x0198[0x78]; //0x0198
	char m_cUnknownString[80]; //0x0210 
	char m_cSingleShot[80]; //0x0260 
	uint8_t pad_0x02B0[0x140]; //0x02B0
	char m_cReload[80]; //0x03F0 
	uint8_t pad_0x0440[0x330]; //0x0440
	CHudTexture* m_pHUDWeaponIcon; //0x0770 
	CHudTexture* m_pHUDWeaponIconSmall; //0x0774 
	CHudTexture* m_pHUDWeaponAmmoIncon; //0x0778 
	uint8_t pad_0x077C[0x28]; //0x077C
	bool m_bIsFullAuto; //0x07A4 
	uint8_t pad_0x07A5[0x3]; //0x07A5
	float m_flHeatPerShot; //0x07A8 
	int32_t m_iWeaponPrice; //0x07AC  "in game price"
	float m_flArmorRatio; //0x07B0 "armor ratio"
	float m_flMaxPlayerSpeed; //0x07B4 "max player speed"
	float m_flMaxPlayerSpeedAlt; //0x07B8 "max player speed alt"
	float m_flCrosshairMinDistance; //0x07BC "crosshair min distance"
	float m_flCrosshairDeltaDistance; //0x07C0 "crosshair delta distance"
	float m_flPenetration; //0x07C4 "penetration"
	int32_t m_iDamage; //0x07C8 "damage"
	float m_flRange; //0x07CC "range"
	float m_flRangeModifier; //0x07D0 "range modifier"
	int32_t m_iBullets; //0x07D4 "bullets"
	float m_flCycleTime; //0x07D8 "cycletime"
	float m_flCycleTimeAlt; //0x07DC "cycletime alt"
	uint8_t pad_0x07E0[0x19C]; //0x07E0
	float m_flTracerFrequency; //0x097C "tracer frequency"
	float m_flSpread; //0x0980 "spread"
	float m_flSpreadAlt; //0x0984  "spread alt"
	float m_flInaccuracyCrouch; //0x0988 "inaccuracy crouch"
	float m_flInaccuracyCrouchAlt; //0x098C "inaccuracy crouch alt"
	float m_flInaccuracyStand; //0x0990 "inaccuracy stand"
	float m_flInaccuracyStandAlt; //0x0994 "inaccuracy stand alt"
	float m_flInaccuracyJump; //0x0998 "inaccuracy jump"
	float m_flInaccuracyJumpAlt; //0x099C "inaccuracy jump alt"
	float m_flInaccuracyLand; //0x09A0 "inaccuracy land"
	float m_flInaccuracyLandAlt; //0x09A4 "inaccuracy land alt"
	float m_flInaccuracyLadder; //0x09A8 "inaccuracy ladder"
	float m_flInaccuracyLadderAlt; //0x09AC "inaccuracy ladder alt"
	float m_flInaccuracyFire; //0x09B0 "inaccuracy fire"
	float m_flInaccuracyFireAlt; //0x09B4 "inaccuracy fire alt"
	float m_flInaccuracyMove; //0x09B8 "inaccuracy move"
	float m_flInaccuracyMoveAlt; //0x09BC "inaccuracy move alt"
	float m_flStandRecoveryTime; //0x09C0 "recovery time stand"
	float m_flCrouchRecoveryTime; //0x09C4 "recovery time crouch"
	float m_flInaccuracyReload; //0x09C8 "inaccuracy reload"
	uint8_t pad_0x09CC[0x4]; //0x09CC
	float m_flRecoilAngle; //0x09D0  "recoil angle"
	float m_flRecoilAngleAlt; //0x09D4   "recoil angle alt"
	float m_flRecoilAngleVariance; //0x09D8 "recoil angle variance"
	float m_flRecoilAngleVarianceAlt; //0x09DC "recoil angle variance alt"
	float m_flRecoilMagnitude; //0x09E0 "recoil magnitude"
	float m_flRecoilMagnitudeAlt; //0x09E4 "recoil magnitude alt"
	float m_flRecoilMagnitudeVariance; //0x09E8 "recoil magnitude variance"
	float m_flRecoilMagnitudeVarianceAlt; //0x09EC "recoil magnitude variance alt"
	int32_t m_iRecoilSeed; //0x09F0 "recoil seed"
	float m_flFlinchVelocityModifierLarge; //0x09F4 "flinch velocity modifier large"
	float m_flFlinchVelocityModifierSmall; //0x09F8 "flinch velocity modifier small"
	float m_flTimeToIdle; //0x09FC "time to idle"
	float m_flIdleInterval; //0x0A00 "idle interval"
	uint8_t pad_0x0A04[0x400]; //0x0A04
	int32_t m_iZoomLevels; //0x0E04 "zoom levels"
	uint8_t pad_0x0E08[0x4]; //0x0E08
	int32_t m_iZoomFoV1; //0x0E0C "zoom fov 1"
	int32_t m_iZoomFoV2; //0x0E10 "zoom fov 2"
	float m_flZoomTime0; //0x0E14 "zoom time 0"
	float m_flZoomTime1; //0x0E18 "zoom time 1"
	float m_flZoomTime2; //0x0E1C "zoom time 2"
	uint8_t m_bHideViewModelZoomed; //0x0E20 "hide view model zoomed"
	uint8_t pad_0x0E21[0xA7]; //0x0E21
	bool m_bCanUseWithShield; //0x0EC8 "shield view model"
	uint8_t pad_0x0EC9[0x17B]; //0x0EC9

};
*/
class WeaponInfo_t
{
public:
	char _0x0000[4];
	BYTE m_bParsedScript; //0x0004 
	BYTE m_bLoadedHudElements; //0x0005 
	BYTE m_szClassName; //0x0006 
	char _0x0007[1961];
	__int32 m_iAmmoType; //0x07B0 
	char _0x07B4[12];
	CHudTexture* m_pHudTexture_WeaponSilenced; //0x07C0 
	CHudTexture* m_pHudTexture_Weapon; //0x07C4 
	CHudTexture* m_pHudTexture_Ammo; //0x07C8 
	char _0x07CC[4];
	CHudTexture* m_pHudTexture_Crosshair; //0x07D0 
	char _0x07D4[20];
	__int32 m_iWeaponType; //0x07E8 
	__int32 m_iTeam; //0x07EC 
	__int32 m_iWeaponId; //0x07F0 
	BYTE m_bFullAuto; //0x07F4 
	char _0x07F5[3];
	float m_flHeatPerShot; //0x07F8 
	__int32 m_iWeaponPrice; //0x07FC 
	float m_flArmorRatio; //0x0800 
	float m_flMaxPlayerSpeed; //0x0804 
	float m_flMaxPlayerSpeedAlt; //0x0808 
	__int32 m_iCrosshairMinDistance; //0x080C 
	__int32 m_iCrosshairDeltaDistance; //0x0810 
	float m_flPenetration; //0x0814 
	__int32 m_iDamage; //0x0818 
	float m_flRange; //0x081C 
	float m_flRangeModifier; //0x0820 
	__int32 m_iBullets; //0x0824 
	float m_flCycleTime; //0x0828 
	float m_flCycleTimeAlt; //0x082C 
	char _0x0830[416];
	float m_flSpread; //0x09D0 
	float m_flSpreadAlt; //0x09D4 
	float m_flInaccuracyCrouch; //0x09D8 
	float m_flInaccuracyCrouchAlt; //0x09DC 
	float m_flInaccuracyStand; //0x09E0 
	float m_flInaccuracyStandAlt; //0x09E4 
	float m_flInaccuracyJump; //0x09E8 
	float m_flInaccuracyJumpAlt; //0x09EC 
	float m_flInaccuracyLand; //0x09F0 
	float m_flInaccuracyLandAlt; //0x09F4 
	float m_flInaccuracyLadder; //0x09F8 
	float m_flInaccuracyLadderAlt; //0x09FC 
	float m_flInaccuracyFire; //0x0A00 
	float m_flInaccuracyFireAlt; //0x0A04 
	float m_flInaccuracyMove; //0x0A08 
	float m_flInaccuracyMoveAlt; //0x0A0C 
	float m_flRecoveryTimeStand; //0x0A10 
	float m_flRecoveryTimeCrouch; //0x0A14 
	float m_flInaccuracyReload; //0x0A18 
	float m_flInaccuracyAltSwitch; //0x0A1C 
	float m_flRecoilAngle; //0x0A20 
	float m_flRecoilAngleAlt; //0x0A24 
	float m_flRecoilAngleVariance; //0x0A28 
	float m_flRecoilAngleVarianceAlt; //0x0A2C 
	float m_flRecoilMagnitude; //0x0A30 
	float m_flRecoilMagnitudeAlt; //0x0A34 
	float m_flRecoilMagnitudeVariance; //0x0A38 
	float m_flRecoilMagnitudeVarianceAlt; //0x0A3C 
	__int32 m_iRecoilSeed; //0x0A40 
	float m_flFlinchVelocityModifierLarge; //0x0A44 
	float m_flFlinchVelocityModifierSmall; //0x0A48 
	float m_flTimeToIdle; //0x0A4C 
	float m_flIdleInterval; //0x0A50                      // 0x0828
};
class CBaseCombatWeapon
{
public:
	char			__pad[0x64];
	int				index;
	model_t* GetModel();
	Vector GetOrigin();
	int&			GetWeaponID();
	float&			GetNextPrimaryAttack();
	float&			GetAccuracyPenalty();
	int&			GetXUIDLow();
	int&			GetXUIDHigh();
	int&			GetEntityQuality();
	int&			GetAccountID();
	int&			GetItemIDHigh();
	int&			GetItemDefinitionIndex();
	int&			GetFallbackPaintKit();
	int&			GetFallbackStatTrak();
	float&			GetFallbackWear();
	int GetModelIndex();
	bool			IsEmpty();
	bool			IsReloading();
	bool GetOwner();
	void			UpdateAccuracyPenalty();
	float			GetWeaponSpread();
	float			GetWeaponCone();
	WeaponInfo_t*	GetCSWpnData();
	bool			IsGun();
	std::string		GetWeaponName();
	int             GetWeaponType();
	bool            IsScopedWeapon();
};
enum WEAPONCLASS
{
	WEPCLASS_INVALID,
	WEPCLASS_RIFLE,
	WEPCLASS_PISTOL,
	WEPCLASS_SHOTGUN,
	WEPCLASS_SNIPER,
	WEPCLASS_SMG,
	WEPCLASS_MACHINEGUN,
	WEPCLASS_KNIFE,
};
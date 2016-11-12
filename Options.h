#pragma once
#include "sdk.h"
enum TriggerFilters
{
	FILTER_NONE,
	FILTER_MOSTDAMAGE,
	FILTER_BODYONLY,
	FILTER_BODYNOARMS,
	FILTER_HEADONLY,
	FILTER_ARMSONLY
};
class cOptions
{
public:
	struct 
	{
		struct
		{
			bool Enabled;
			int 	Mode;
			bool	XQZ;
			float 	TeamColor[3];
			float 	TeamColorWall[3];
			float  	EnemyColor[3];
			float 	EnemyColorWall[3];
		}Chams;
		struct
		{
			bool	Hands;
			bool	WireframeHands;
			bool	Weapon;
			bool	WireframeWep;
			bool	VisualRecoil;
			bool	Flash;
			bool    Smoke;
			bool	Sky;
			bool    Recoil;
		} Removals;
		struct
		{
			bool    Enabled;
			bool    EnemyOnly;
			bool    D3D;
			int     Mode;
			bool    Box;
			bool    Health;
			bool    Name;
			bool	Hitmarker;
			bool    Weapon;
			bool    Bone;
			bool    Barrel;
			bool    AimPoint;
			bool	RecoilCrosshair;
			bool	AutoAccept;
			bool	Glow;
			int     IsVisible;
			int		FOV;
			int     FOV2;
			bool    ThirdPerson;
			bool    bVisibleOnly;
			float 	TeamColor[3];
			float 	TeamColorWall[3];
			float  	EnemyColor[3];
			float 	EnemyColorWall[3];
			bool DLight;
			bool LocationSpam;
			bool RankESP;
			int DLightRadius;
		}ESP;
	}Visuals;
	struct
	{
		struct
		{
			bool Enabled;			
			bool TriggerFriends;
			int Filter;
			int Key;
			int Delay;
		}Trigger;

		struct
		{
			bool Enabled;
			float Fov;
			int Bone;
			float Smooth[2];
			float lSmooth;
			bool SilentAim;
			bool PerfectSilentAim;
			bool RCS;
			bool rRCS;
			bool pRCS;
			bool WeaponConfigs;
			int LFOV;
			int AimSpeed;
			int MultiplySpeed;
			int FOVBOOST;
			bool StandaloneRCS;
			bool EnemyOnly;
			struct
			{		
				struct
				{
					bool Trigger;
					bool Enabled;
					float Fov;
					int Bone;
					float Smooth[2];
					bool SilentAim;
					bool PerfectSilentAim;
					bool RCS;
					bool rRCS;
					bool pRCS;
					float lSmooth;
					int LFOV;
					int AimSpeed;
					int MultiplySpeed;
					int FOVBOOST;
				}Pistols;
				struct
				{
					bool Trigger;
					bool Enabled;
					float Fov;
					int Bone;
					float Smooth[2];
					bool SilentAim;
					bool PerfectSilentAim;
					bool RCS;
					bool rRCS;
					bool pRCS;
					float lSmooth;
					int LFOV;
					int AimSpeed;
					int MultiplySpeed;
					int FOVBOOST;
				}Rifles;
				struct
				{
					bool Trigger;
					bool Enabled;
					float Fov;
					int Bone;
					float Smooth[2];
					bool SilentAim;
					bool PerfectSilentAim;
					bool RCS;
					bool rRCS;
					bool pRCS;
					float lSmooth;
					int LFOV;
					int AimSpeed;
					int MultiplySpeed;
					int FOVBOOST;
				}Snipers;
				struct
				{
					bool Trigger;
					bool Enabled;
					float Fov;
					int Bone;
					float Smooth[2];
					bool SilentAim;
					bool PerfectSilentAim;
					bool RCS;
					bool rRCS;
					bool pRCS;
					float lSmooth;
					int LFOV;
					int AimSpeed;
					int MultiplySpeed;
					int FOVBOOST;
				}Shotguns;
				struct
				{
					bool Trigger;
					bool Enabled;
					float Fov;
					int Bone;
					float Smooth[2];
					bool SilentAim;
					bool PerfectSilentAim;
					bool RCS;
					bool rRCS;
					bool pRCS;
					float lSmooth;
					int LFOV;
					int AimSpeed;
					int MultiplySpeed;
					int FOVBOOST;
				}Machineguns;
				struct
				{
					bool Trigger;
					bool Enabled;
					float Fov;
					int Bone;
					float Smooth[2];
					bool SilentAim;
					bool PerfectSilentAim;
					bool RCS;
					bool rRCS;
					bool pRCS;
					float lSmooth;
					int LFOV;
					int AimSpeed;
					int MultiplySpeed;
					int FOVBOOST;
				}SMGs;
			}Configs;
			float Human = 1;
			float HumanSpeed = 6;
		}Aimbot;
	}Legit;
	struct
	{
		struct
		{
			float MinDamage;
			int AutowallType;
		}AutoWall;
		struct
		{
			bool Enabled;
			int Hitbox;
			int Targeting;
			bool AimSmart;
			int iSmartShots;
			int HitScans;
			bool AutoShoot;
			bool AutoScope;
			bool AS1tap;
			bool bHitchanceSnipers;
			int CHitscans;
			bool bHitchance;
			int StopType;
			float Hitchance;
			bool EnemyOnly;
			bool PsuedoSpread;
			bool AntiAntiAim;
			bool SilentAim;
			struct
			{
			   int ResolverType;
			   QAngle oAngle[64];
	           QAngle CAngle[64];
			   bool Enemyonly;
			   int bone[64];
			   int Lisp[64];
			   bool bDisableHead[64];
		    }AAA;
			struct
			{
				int Point;
				bool Head;
				bool Neck;
				bool LowerNeck;
				bool Pelvis;
				bool Body;
				bool Thorax;
				bool Chest;
				bool UpperChest;
				bool RightThigh;
				bool LeftThigh;
				bool RightCalf;
				bool LeftCalf;
				bool RightFoot;
				bool LeftFoot;
				bool RightHand;
				bool LeftHand;
				bool RightUpperArm;
				bool RightForeArm;
				bool LeftUpperArm;
				bool LeftForeArm;
				bool Max;
			}Hitscan;
		}Aimbot;
		struct
		{
			bool Enabled;
			int Yaw;
			int Pitch;
		}AntiAim;
	}Rage;
	struct
	{
		struct
		{
			bool Enabled;
			int Send;
			int Choke;
		}FakeLag;
		struct
		{
			int Key;
			bool Enabled;
		}AirStuck;
		struct
		{
			bool Enabled;
		}bhop;
		struct
		{
			bool Enabled;
			bool Silent;
		}AutoStrafe;
	}PlayerMods;
	struct
	{
		bool Opened = false;
		bool Configs;
		bool WeaponConfigs;
		bool Skins;
		bool PlayerList;
		struct
		{
			bool MoreInfo;
		}pList;
		bool HitScans;
	}Menu;
	struct
	{
		bool MM;
		bool SMAC;
		bool CEVO;
		bool FACEIT;
		bool VAC;
		bool ESEA;
	}AntiCheat;
	struct
	{
		bool Enabled;
		bool NEnabled;
		int deagle;
		int cz75;
		int p2000;
		int elites;
		int p250;
		int fiveseven;
		int tec9;
		int glock;
		int aug;
		int galil;
		int usps;
		int ak47;
		int famas;
		int m4a4;
		int m4a1s;
		int bizon;
		int mac10;
		int mp7;
		int mp9;
		int p90;
		int m249;
		int ump45;
		int negev;
		int mag7;
		int nova;
		int sawedoff;
		int xm1014;
		int scar20;
		int awp;
		int ssg08;
		int g3sg1;
		int magnum;
		int sg556;
		int KnifeIDb;
		int KnifeIDf;
		int KnifeIDd;
		int KnifeIDg;
		int KnifeIDm;
		int KnifeIDk;
		int KnifeIDh;
		int KnifeIDbutter;
		int KnifeIDfal;
		int KnifeIDdag;
		int KnifeIDbow;
		char* buf;
		int StatTrak;
		int KnifeSelect;
		struct
		{
			bool Custom0;
			bool Custom1;
			bool Custom2;
			bool Custom3;
			float color0[3];
			float color1[3];
			float color2[3];
			float color3[3];

		}Color;
	}Skins;
	struct
	{
		int Current;
	}Config;
	struct
	{
		bool Uninject;
	}Cheat;
	struct
	{
		bool Enabled;
		char Message[255] = "";
	}IRC;
};
extern cOptions Options;
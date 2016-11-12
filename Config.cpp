#include "Config.h"

Config* ConSys = new Config();

inline bool Check(std::string File)
{
	struct stat buf;
	return (stat(File.c_str(), &buf) == 0);
}

char Pic1[255], Sound[255];

bool Config::CheckConfigs()
{
	/*=====================================*/
	strcat(Path, "C:\\Karma");
	HANDLE File1, File2, File3, File4;
	CreateDirectoryA(Path, nullptr);
	strcpy(Path2, Path);
	strcpy(Path3, Path);
	strcpy(Path4, Path);
	strcpy(Picture, Path);
	strcpy(Sound, Path);
	strcat(Picture, "\\Pictures");
	CreateDirectoryA(Picture, nullptr);
	strcpy(Pic1, Picture);
	
	strcat(Pic1, "\\Karma.png");
	strcat(Picture, "\\hitsound.wav");
	 URLDownloadToFile(nullptr, XorStr("http://karma.fyi/karmafiles/karma.png"), Pic1, 0, nullptr); Sleep(400);
	 URLDownloadToFile(nullptr, XorStr("http://karma.fyi/karmafiles/hitsound.wav"), Picture, 0, nullptr); Sleep(400);
	
	strcat(Path, "\\Rage.ini");
	strcat(Path2, "\\Legit.ini");
	strcat(Path3, "\\Default.ini");
	strcat(Path4, "\\League.ini");
	/*=====================================*/
	File1 = CreateFileA(Path, GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (File1 != INVALID_HANDLE_VALUE)
	{
		CloseHandle(File1);
	}
	
	File2 = CreateFileA(Path2, GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (File2 != INVALID_HANDLE_VALUE)
	{
		CloseHandle(File2);
	}
	
	File3 = CreateFileA(Path3, GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (File3 != INVALID_HANDLE_VALUE)
	{
		CloseHandle(File3);
	}
	
	File4 = CreateFileA(Path4, GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (File4 != INVALID_HANDLE_VALUE)
	{
		CloseHandle(File4);
	}
	return true;
}

char* Config::Handle()
{
	if (Options.Config.Current == 0)
	{
		ConSys->Legit = false;
		ConSys->Rage = false;
		ConSys->RageMM = false;
	}
	if (Options.Config.Current == 1)
	{
		ConSys->Legit = true;
		ConSys->Rage = false;
		ConSys->RageMM = false;
	}
	if (Options.Config.Current == 2)
	{
		ConSys->Legit = false;
		ConSys->Rage = true;
		ConSys->RageMM = false;
	}
	if (Options.Config.Current == 3)
	{
		ConSys->Legit = false;
		ConSys->Rage = false;
		ConSys->RageMM = true;
	}
	if (Rage)
		return Path;
	if (Legit)
		return Path2;
	if (RageMM)
		return Path4;
	return Path3;
}

int Config::ReadInt(char* Cata, char* Name, int DefaultVal)
{
	int iResult;
	iResult = GetPrivateProfileIntA(Cata, Name, DefaultVal, this->Handle());
	return iResult;
}

float Config::ReadFloat(char* Cata, char* Name, float DefaultVal)
{
	char result[255];
	char cDefault[255];
	float fresult;
	sprintf(cDefault, "%f", DefaultVal);
	GetPrivateProfileStringA(Cata, Name, cDefault, result, 255, this->Handle());
	fresult = atof(result);
	return fresult;
}

char* Config::ReadString(char* Cata, char* Name, char* DefaultVal)
{
	auto result = new char[255];
	DWORD oProtection;
	VirtualProtect(reinterpret_cast<void*>(result), 4,PAGE_READWRITE, &oProtection);
	memset(result, 0x00, 255);
	VirtualProtect(reinterpret_cast<void*>(result), 4, oProtection, &oProtection);
	GetPrivateProfileStringA(Cata, Name, DefaultVal, result, 255, this->Handle());
	return result;
}

void Config::WriteFloat(char* Cata, char* Name, float SetVal)
{
	char buf[255];
	sprintf(buf, "%f", SetVal);
	WritePrivateProfileStringA(Cata, Name, buf, this->Handle());
}

void Config::WriteInt(char* Cata, char* Name, int SetVal)
{
	char buf[255];
	sprintf(buf, "%d", SetVal);
	WritePrivateProfileStringA(Cata, Name, buf, this->Handle());
}

void Config::WriteString(char* Cata, char* Name, char* SetVal)
{
	WritePrivateProfileStringA(Cata, Name, SetVal, this->Handle());
}


void Config::SaveConfig()
{
	//Visuals

	// Standard Visuals

	//:::::::::::::/”\ Truix kill your self for making me do configs :)
	//::::::::::::|\:/|
    //::::::::::::|:::|
    //::::::::::::|:~:|
    //::::::::::::|:::|
    //:::::::::/’\|:::|/’\::
    //:::::/”\|:::|:::|:::|:\
    //::::|:::[@]:::|:::|::::\
    //::::|:::|:::|:::|:::|:::\
    //::::|:~:~::~::~:|:::::::)
    //::::|:::::::::::::::::::/
    //:::::\:::::::::::::::::/
    //::::::\:::::::::::::::/


	WriteInt(XorStr("Visuals"), XorStr("Enabled"), Options.Visuals.ESP.Enabled);
	WriteInt(XorStr("Visuals"), XorStr("Visualize Aim Point"), Options.Visuals.ESP.AimPoint);
	WriteInt(XorStr("Visuals"), XorStr("EnemyOnly"), Options.Visuals.ESP.EnemyOnly);
	WriteInt(XorStr("Visuals"), XorStr("VisualDetection"), Options.Visuals.ESP.IsVisible);
	WriteInt(XorStr("Visuals"), XorStr("VisualOnly"), Options.Visuals.ESP.bVisibleOnly);
	WriteInt(XorStr("Visuals"), XorStr("Box"), Options.Visuals.ESP.Box);
	WriteInt(XorStr("Visuals"), XorStr("Health"), Options.Visuals.ESP.Health);
	WriteInt(XorStr("Visuals"), XorStr("Name"), Options.Visuals.ESP.Name);
	WriteInt(XorStr("Visuals"), XorStr("Weapon"), Options.Visuals.ESP.Weapon);
	WriteInt(XorStr("Visuals"), XorStr("Bone"), Options.Visuals.ESP.Bone);
	WriteInt(XorStr("Visuals"), XorStr("Barrel"), Options.Visuals.ESP.Barrel);
	WriteInt(XorStr("Visuals"), XorStr("FOV"), Options.Visuals.ESP.FOV);
	WriteInt(XorStr("Visuals"), XorStr("ThirdPerson"), Options.Visuals.ESP.ThirdPerson);
	WriteInt(XorStr("Visuals"), XorStr("Hitmarker"), Options.Visuals.ESP.Hitmarker);
	WriteInt(XorStr("Visuals"), XorStr("Recoil Crosshair"), Options.Visuals.ESP.RecoilCrosshair);
	WriteInt(XorStr("Visuals"), XorStr("Auto Accept"), Options.Visuals.ESP.AutoAccept);
	WriteInt(XorStr("Visuals"), XorStr("Lights"), Options.Visuals.ESP.DLight);
	WriteInt(XorStr("Visuals"), XorStr("Multiply Light Radius"), Options.Visuals.ESP.DLightRadius);
	WriteInt(XorStr("Visuals"), XorStr("LocationSpam"), Options.Visuals.ESP.LocationSpam);
	WriteInt(XorStr("Visuals"), XorStr("RankESP"), Options.Visuals.ESP.RankESP);

	/*Colors*/
	WriteFloat(XorStr("Colors"), XorStr("ESP Team Vis Red"), Options.Visuals.ESP.TeamColor[0]);
	WriteFloat(XorStr("Colors"), XorStr("ESP Team Vis Green"), Options.Visuals.ESP.TeamColor[1]);
	WriteFloat(XorStr("Colors"), XorStr("ESP Team Vis Blue"), Options.Visuals.ESP.TeamColor[2]);
	//Team Vis
	WriteFloat(XorStr("Colors"), XorStr("ESP Team Red"), Options.Visuals.ESP.TeamColorWall[0]);
	WriteFloat(XorStr("Colors"), XorStr("ESP Team Green"), Options.Visuals.ESP.TeamColorWall[1]);
	WriteFloat(XorStr("Colors"), XorStr("ESP Team Blue"), Options.Visuals.ESP.TeamColorWall[2]);
	//Team notVis
	WriteFloat(XorStr("Colors"), XorStr("ESP Enemy Vis Red"), Options.Visuals.ESP.EnemyColor[0]);
	WriteFloat(XorStr("Colors"), XorStr("ESP Enemy Vis Green"), Options.Visuals.ESP.EnemyColor[1]);
	WriteFloat(XorStr("Colors"), XorStr("ESP Enemy Vis Blue"), Options.Visuals.ESP.EnemyColor[2]);
	//Enemy vis
	WriteFloat(XorStr("Colors"), XorStr("ESP Enemy Red"), Options.Visuals.ESP.EnemyColorWall[0]);
	WriteFloat(XorStr("Colors"), XorStr("ESP Enemy Green"), Options.Visuals.ESP.EnemyColorWall[1]);
	WriteFloat(XorStr("Colors"), XorStr("ESP Enemy Blue"), Options.Visuals.ESP.EnemyColorWall[2]);



	/*Chams*/
	WriteInt(XorStr("Visuals"), XorStr("Chams"), Options.Visuals.Chams.Enabled);
	WriteInt(XorStr("Visuals"), XorStr("Type"), Options.Visuals.Chams.Mode);
	WriteInt(XorStr("Visuals"), XorStr("XQZ"), Options.Visuals.Chams.XQZ);
	/*Colors*/
	WriteFloat(XorStr("Colors"), XorStr("Team Vis Red"), Options.Visuals.Chams.TeamColor[0]);
	WriteFloat(XorStr("Colors"), XorStr("Team Vis Green"), Options.Visuals.Chams.TeamColor[1]);
	WriteFloat(XorStr("Colors"), XorStr("Team Vis Blue"), Options.Visuals.Chams.TeamColor[2]);
	//Team Vis
	WriteFloat(XorStr("Colors"), XorStr("Team Red"), Options.Visuals.Chams.TeamColorWall[0]);
	WriteFloat(XorStr("Colors"), XorStr("Team Green"), Options.Visuals.Chams.TeamColorWall[1]);
	WriteFloat(XorStr("Colors"), XorStr("Team Blue"), Options.Visuals.Chams.TeamColorWall[2]);
	//Team notVis
	WriteFloat(XorStr("Colors"), XorStr("Enemy Vis Red"), Options.Visuals.Chams.EnemyColor[0]);
	WriteFloat(XorStr("Colors"), XorStr("Enemy Vis Green"), Options.Visuals.Chams.EnemyColor[1]);
	WriteFloat(XorStr("Colors"), XorStr("Enemy Vis Blue"), Options.Visuals.Chams.EnemyColor[2]);
	//Enemy vis
	WriteFloat(XorStr("Colors"), XorStr("Enemy Red"), Options.Visuals.Chams.EnemyColorWall[0]);
	WriteFloat(XorStr("Colors"), XorStr("Enemy Green"), Options.Visuals.Chams.EnemyColorWall[1]);
	WriteFloat(XorStr("Colors"), XorStr("Enemy Blue"), Options.Visuals.Chams.EnemyColorWall[2]);


	//Enemy nonvis
	//removals
	WriteInt(XorStr("Removals"), XorStr("Hands"), Options.Visuals.Removals.Hands);
	WriteInt(XorStr("Removals"), XorStr("WireFrameHands"), Options.Visuals.Removals.WireframeHands);
	WriteInt(XorStr("Removals"), XorStr("Weapon"), Options.Visuals.Removals.Weapon);
	WriteInt(XorStr("Removals"), XorStr("WireFrameWeapon"), Options.Visuals.Removals.WireframeWep);
	WriteInt(XorStr("Removals"), XorStr("Visual Recoil"), Options.Visuals.Removals.VisualRecoil);
	WriteInt(XorStr("Removals"), XorStr("Recoil"), Options.Visuals.Removals.Recoil);
	WriteInt(XorStr("Removals"), XorStr("Flash"), Options.Visuals.Removals.Flash);
	//Rage
	/*Aimbot*/
	WriteFloat(XorStr("AutoWall"), XorStr("MinDamage"), Options.Rage.AutoWall.MinDamage);

	WriteInt(XorStr("Aimbot"), XorStr("Enabled"), Options.Rage.Aimbot.Enabled);
	WriteInt(XorStr("Aimbot"), XorStr("Hitbox"), Options.Rage.Aimbot.Hitbox);
	WriteInt(XorStr("Aimbot"), XorStr("Autowall"), Options.Rage.AutoWall.AutowallType);
	WriteInt(XorStr("Aimbot"), XorStr("Targeting"), Options.Rage.Aimbot.Targeting);
	WriteInt(XorStr("Aimbot"), XorStr("HitScans"), Options.Rage.Aimbot.HitScans);
	WriteInt(XorStr("Aimbot"), XorStr("AutoShoot"), Options.Rage.Aimbot.AutoShoot);
	WriteInt(XorStr("Aimbot"), XorStr("AutoScope"), Options.Rage.Aimbot.AutoScope);
	WriteInt(XorStr("Aimbot"), XorStr("1Tap"), Options.Rage.Aimbot.AS1tap);
	WriteInt(XorStr("Aimbot"), XorStr("bHitChance"), Options.Rage.Aimbot.bHitchance);
	WriteInt(XorStr("Aimbot"), XorStr("bHitChanceSniper"), Options.Rage.Aimbot.bHitchanceSnipers);
	WriteInt(XorStr("Aimbot"), XorStr("StopType"), Options.Rage.Aimbot.StopType);
	WriteInt(XorStr("Aimbot"), XorStr("iSmartShots"), Options.Rage.Aimbot.iSmartShots);
	WriteFloat(XorStr("Aimbot"), XorStr("HitChance"), Options.Rage.Aimbot.Hitchance);
	WriteInt(XorStr("Aimbot"), XorStr("AimSmart"), Options.Rage.Aimbot.AimSmart);
	WriteInt(XorStr("Aimbot"), XorStr("SilentAim"), Options.Rage.Aimbot.SilentAim);

	WriteInt(XorStr("Aimbot"), XorStr("EnemyOnly"), Options.Rage.Aimbot.EnemyOnly);

	WriteInt(XorStr("AntiAim"), XorStr("Enabled"), Options.Rage.AntiAim.Enabled);
	WriteInt(XorStr("AntiAim"), XorStr("Yaw"), Options.Rage.AntiAim.Yaw);
	WriteInt(XorStr("AntiAim"), XorStr("Pitch"), Options.Rage.AntiAim.Pitch);
	//Legit
	/*Trigger*/
	WriteInt(XorStr("Trigger"), XorStr("Enabled"), Options.Legit.Trigger.Enabled);
	WriteInt(XorStr("Trigger"), XorStr("Enemy Only"), Options.Legit.Trigger.TriggerFriends);
	WriteInt(XorStr("Trigger"), XorStr("Filter"), Options.Legit.Trigger.Filter);
	WriteInt(XorStr("Trigger"), XorStr("Key"), Options.Legit.Trigger.Key);
	WriteInt(XorStr("Trigger"), XorStr("Delay"), Options.Legit.Trigger.Delay);
	/*Aimbot*/
	WriteInt(XorStr("Legit"), XorStr("Enabled"),Options.Legit.Aimbot.Enabled);
	WriteInt(XorStr("Legit"), XorStr("Bone"), Options.Legit.Aimbot.Bone);
	WriteFloat(XorStr("Legit"), XorStr("FOV"), Options.Legit.Aimbot.Fov);
	WriteFloat(XorStr("Legit"), XorStr("SmoothX"), Options.Legit.Aimbot.Smooth[0]);
	WriteFloat(XorStr("Legit"), XorStr("SmoothY"), Options.Legit.Aimbot.Smooth[1]);
	WriteInt(XorStr("Legit"), XorStr("SilentAim"), Options.Legit.Aimbot.SilentAim);
	WriteInt(XorStr("Legit"), XorStr("PSilent"), Options.Legit.Aimbot.PerfectSilentAim);
	WriteInt(XorStr("Legit"), XorStr("RCS"), Options.Legit.Aimbot.RCS);
	WriteInt(XorStr("Legit"), XorStr("WeaponConfigs"), Options.Legit.Aimbot.WeaponConfigs);
	WriteInt(XorStr("Legit"), XorStr("LeagueFOV"), Options.Legit.Aimbot.LFOV);
	WriteInt(XorStr("Legit"), XorStr("AimSpeed"), Options.Legit.Aimbot.AimSpeed);
	WriteInt(XorStr("Legit"), XorStr("MultiplySpeed"), Options.Legit.Aimbot.MultiplySpeed);
	WriteInt(XorStr("Legit"), XorStr("FOVBOOST"), Options.Legit.Aimbot.FOVBOOST);
	WriteInt(XorStr("Legit"), XorStr("EnemyOnly"), Options.Legit.Aimbot.EnemyOnly);
	/*PlayerMods*/
	WriteInt(XorStr("FakeLag"),XorStr("Enabled"),Options.PlayerMods.FakeLag.Enabled);
	WriteInt(XorStr("FakeLag"), XorStr("Send"), Options.PlayerMods.FakeLag.Send);
	WriteInt(XorStr("FakeLag"), XorStr("Choke"), Options.PlayerMods.FakeLag.Choke);
	/*AirStuck*/
	WriteInt(XorStr("AirStuck"), XorStr("Enabled"), Options.PlayerMods.AirStuck.Enabled);
	WriteInt(XorStr("AirStuck"), XorStr("Key"), Options.PlayerMods.AirStuck.Key);
	/*Jump*/
	WriteInt(XorStr("Jump"), XorStr("BHOP"), Options.PlayerMods.bhop.Enabled);
	WriteInt(XorStr("Jump"), XorStr("AutoStrafe"), Options.PlayerMods.AutoStrafe.Enabled);
    WriteInt(XorStr("Jump"), XorStr("Silent"), Options.PlayerMods.AutoStrafe.Silent);
	/*Anti-Cheats*/
	WriteInt(XorStr("Anti-Cheat"), XorStr("MM"), Options.AntiCheat.MM);
	WriteInt(XorStr("Anti-Cheat"), XorStr("SMAC"), Options.AntiCheat.SMAC);
	WriteInt(XorStr("Anti-Cheat"), XorStr("CEVO"), Options.AntiCheat.CEVO);
	WriteInt(XorStr("Anti-Cheat"), XorStr("FACEIT"), Options.AntiCheat.FACEIT);
	WriteInt(XorStr("Anti-Cheat"), XorStr("VAC"), Options.AntiCheat.VAC);
	WriteInt(XorStr("Anti-Cheat"), XorStr("ESEA"), Options.AntiCheat.ESEA);
	/* Custom Hitscans*/
	WriteInt(XorStr("CHitScans"), XorStr("Multipoint"), Options.Rage.Aimbot.Hitscan.Point);
	WriteInt(XorStr("CHitScans"), XorStr("Head"), Options.Rage.Aimbot.Hitscan.Head);
	WriteInt(XorStr("CHitScans"), XorStr("Neck"), Options.Rage.Aimbot.Hitscan.Neck);
	WriteInt(XorStr("CHitScans"), XorStr("LowerNeck"), Options.Rage.Aimbot.Hitscan.LowerNeck);
	WriteInt(XorStr("CHitScans"), XorStr("Pelvis"), Options.Rage.Aimbot.Hitscan.Pelvis);
	WriteInt(XorStr("CHitScans"), XorStr("Body"), Options.Rage.Aimbot.Hitscan.Body);
	WriteInt(XorStr("CHitScans"), XorStr("Thorax"), Options.Rage.Aimbot.Hitscan.Thorax);
	WriteInt(XorStr("CHitScans"), XorStr("Chest"), Options.Rage.Aimbot.Hitscan.Chest);
	WriteInt(XorStr("CHitScans"), XorStr("UpperChest"), Options.Rage.Aimbot.Hitscan.UpperChest);
	WriteInt(XorStr("CHitScans"), XorStr("RightThigh"), Options.Rage.Aimbot.Hitscan.RightThigh);
	WriteInt(XorStr("CHitScans"), XorStr("LeftThigh"), Options.Rage.Aimbot.Hitscan.LeftThigh);
	WriteInt(XorStr("CHitScans"), XorStr("RightCalf"), Options.Rage.Aimbot.Hitscan.RightCalf);
	WriteInt(XorStr("CHitScans"), XorStr("LeftCalf"), Options.Rage.Aimbot.Hitscan.LeftCalf);
	WriteInt(XorStr("CHitScans"), XorStr("RightFoot"), Options.Rage.Aimbot.Hitscan.RightFoot);
	WriteInt(XorStr("CHitScans"), XorStr("LeftFoot"), Options.Rage.Aimbot.Hitscan.LeftFoot);
	WriteInt(XorStr("CHitScans"), XorStr("RightHand"), Options.Rage.Aimbot.Hitscan.RightHand);
	WriteInt(XorStr("CHitScans"), XorStr("LeftHand"), Options.Rage.Aimbot.Hitscan.LeftHand);
	WriteInt(XorStr("CHitScans"), XorStr("RightUpperArm"), Options.Rage.Aimbot.Hitscan.RightUpperArm);
	WriteInt(XorStr("CHitScans"), XorStr("RightForeArm"), Options.Rage.Aimbot.Hitscan.RightForeArm);
	WriteInt(XorStr("CHitScans"), XorStr("LeftUpperArm"), Options.Rage.Aimbot.Hitscan.LeftUpperArm);
	WriteInt(XorStr("CHitScans"), XorStr("LeftForeArm"), Options.Rage.Aimbot.Hitscan.LeftForeArm);





	/*Weapon Configs*/
	WriteInt(XorStr("Rifle"), XorStr("TrigEnabled"), Options.Legit.Aimbot.Configs.Rifles.Trigger);
	WriteInt(XorStr("Rifle"), XorStr("Enabled"), Options.Legit.Aimbot.Configs.Rifles.Enabled);
	WriteInt(XorStr("Rifle"), XorStr("Bone"), Options.Legit.Aimbot.Configs.Rifles.Bone);
	WriteFloat(XorStr("Rifle"), XorStr("FOV"), Options.Legit.Aimbot.Configs.Rifles.Fov);
	WriteFloat(XorStr("Rifle"), XorStr("Smooth"), Options.Legit.Aimbot.Configs.Rifles.lSmooth);
	WriteFloat(XorStr("Rifle"), XorStr("SmoothX"), Options.Legit.Aimbot.Configs.Rifles.Smooth[0]);
	WriteFloat(XorStr("Rifle"), XorStr("SmoothY"), Options.Legit.Aimbot.Configs.Rifles.Smooth[1]);
	WriteInt(XorStr("Rifle"), XorStr("SilentAim"), Options.Legit.Aimbot.Configs.Rifles.SilentAim);
	WriteInt(XorStr("Rifle"), XorStr("RCS"), Options.Legit.Aimbot.Configs.Rifles.RCS);
	WriteInt(XorStr("Rifle"), XorStr("pSilent"), Options.Legit.Aimbot.Configs.Rifles.PerfectSilentAim);
	WriteInt(XorStr("Rifle"), XorStr("LeagueFOV"), Options.Legit.Aimbot.Configs.Rifles.LFOV);
	WriteInt(XorStr("Rifle"), XorStr("AimSpeed"), Options.Legit.Aimbot.Configs.Rifles.AimSpeed);
	WriteInt(XorStr("Rifle"), XorStr("MultiplySpeed"), Options.Legit.Aimbot.Configs.Rifles.MultiplySpeed);
	WriteInt(XorStr("Rifle"), XorStr("FOVBOOST"), Options.Legit.Aimbot.Configs.Rifles.FOVBOOST);
	//
	WriteInt(XorStr("Pistol"), XorStr("TrigEnabled"), Options.Legit.Aimbot.Configs.Pistols.Trigger);
	WriteInt(XorStr("Pistol"), XorStr("Enabled"), Options.Legit.Aimbot.Configs.Pistols.Enabled);
	WriteInt(XorStr("Pistol"), XorStr("Bone"), Options.Legit.Aimbot.Configs.Pistols.Bone);
	WriteFloat(XorStr("Pistol"), XorStr("FOV"), Options.Legit.Aimbot.Configs.Pistols.Fov);
	WriteFloat(XorStr("Pistol"), XorStr("Smooth"), Options.Legit.Aimbot.Configs.Snipers.lSmooth);
	WriteFloat(XorStr("Pistol"), XorStr("SmoothX"), Options.Legit.Aimbot.Configs.Pistols.Smooth[0]);
	WriteFloat(XorStr("Pistol"), XorStr("SmoothY"), Options.Legit.Aimbot.Configs.Pistols.Smooth[1]);
	WriteInt(XorStr("Pistol"), XorStr("SilentAim"), Options.Legit.Aimbot.Configs.Pistols.SilentAim);
	WriteInt(XorStr("Pistol"), XorStr("RCS"), Options.Legit.Aimbot.Configs.Pistols.RCS);
	WriteInt(XorStr("Pistol"), XorStr("pSilent"), Options.Legit.Aimbot.Configs.Pistols.PerfectSilentAim);
	WriteInt(XorStr("Pistol"), XorStr("LeagueFOV"), Options.Legit.Aimbot.Configs.Pistols.LFOV);
	WriteInt(XorStr("Pistol"), XorStr("AimSpeed"), Options.Legit.Aimbot.Configs.Pistols.AimSpeed);
	WriteInt(XorStr("Pistol"), XorStr("MultiplySpeed"), Options.Legit.Aimbot.Configs.Pistols.MultiplySpeed);
	WriteInt(XorStr("Pistol"), XorStr("FOVBOOST"), Options.Legit.Aimbot.Configs.Pistols.FOVBOOST);
	//
	WriteInt(XorStr("Shotgun"), XorStr("TrigEnabled"), Options.Legit.Aimbot.Configs.Shotguns.Trigger);
	WriteInt(XorStr("Shotgun"), XorStr("Enabled"), Options.Legit.Aimbot.Configs.Shotguns.Enabled);
	WriteInt(XorStr("Shotgun"), XorStr("Bone"), Options.Legit.Aimbot.Configs.Shotguns.Bone);
	WriteFloat(XorStr("Shotgun"), XorStr("FOV"), Options.Legit.Aimbot.Configs.Shotguns.Fov);
	WriteFloat(XorStr("Shotgun"), XorStr("Smooth"), Options.Legit.Aimbot.Configs.Snipers.lSmooth);
	WriteFloat(XorStr("Shotgun"), XorStr("SmoothX"), Options.Legit.Aimbot.Configs.Shotguns.Smooth[0]);
	WriteFloat(XorStr("Shotgun"), XorStr("SmoothY"), Options.Legit.Aimbot.Configs.Shotguns.Smooth[1]);
	WriteInt(XorStr("Shotgun"), XorStr("SilentAim"), Options.Legit.Aimbot.Configs.Shotguns.SilentAim);
	WriteInt(XorStr("Shotgun"), XorStr("RCS"), Options.Legit.Aimbot.Configs.Shotguns.RCS);
	WriteInt(XorStr("Shotgun"), XorStr("pSilent"), Options.Legit.Aimbot.Configs.Shotguns.PerfectSilentAim);
	WriteInt(XorStr("Shotgun"), XorStr("LeagueFOV"), Options.Legit.Aimbot.Configs.Shotguns.LFOV);
	WriteInt(XorStr("Shotgun"), XorStr("AimSpeed"), Options.Legit.Aimbot.Configs.Shotguns.AimSpeed);
	WriteInt(XorStr("Shotgun"), XorStr("MultiplySpeed"), Options.Legit.Aimbot.Configs.Shotguns.MultiplySpeed);
	WriteInt(XorStr("Shotgun"), XorStr("FOVBOOST"), Options.Legit.Aimbot.Configs.Shotguns.FOVBOOST);
    //
	WriteInt(XorStr("Sniper"), XorStr("TrigEnabled"), Options.Legit.Aimbot.Configs.Snipers.Trigger);
	WriteInt(XorStr("Sniper"), XorStr("Enabled"), Options.Legit.Aimbot.Configs.Snipers.Enabled);
	WriteInt(XorStr("Sniper"), XorStr("Bone"), Options.Legit.Aimbot.Configs.Snipers.Bone);
	WriteFloat(XorStr("Sniper"), XorStr("FOV"), Options.Legit.Aimbot.Configs.Snipers.Fov);
	WriteFloat(XorStr("Sniper"), XorStr("Smooth"), Options.Legit.Aimbot.Configs.Snipers.lSmooth);
	WriteFloat(XorStr("Sniper"), XorStr("SmoothX"), Options.Legit.Aimbot.Configs.Snipers.Smooth[0]);
	WriteFloat(XorStr("Sniper"), XorStr("SmoothY"), Options.Legit.Aimbot.Configs.Snipers.Smooth[1]);
	WriteInt(XorStr("Sniper"), XorStr("SilentAim"), Options.Legit.Aimbot.Configs.Snipers.SilentAim);
	WriteInt(XorStr("Sniper"), XorStr("RCS"), Options.Legit.Aimbot.Configs.Snipers.RCS);
	WriteInt(XorStr("Sniper"), XorStr("pSilent"), Options.Legit.Aimbot.Configs.Snipers.PerfectSilentAim);
	WriteInt(XorStr("Sniper"), XorStr("LeagueFOV"), Options.Legit.Aimbot.Configs.Snipers.LFOV);
	WriteInt(XorStr("Sniper"), XorStr("AimSpeed"), Options.Legit.Aimbot.Configs.Snipers.AimSpeed);
	WriteInt(XorStr("Sniper"), XorStr("MultiplySpeed"), Options.Legit.Aimbot.Configs.Snipers.MultiplySpeed);
	WriteInt(XorStr("Sniper"), XorStr("FOVBOOST"), Options.Legit.Aimbot.Configs.Snipers.FOVBOOST);
	//
	WriteInt(XorStr("SMG"), XorStr("TrigEnabled"), Options.Legit.Aimbot.Configs.SMGs.Trigger);
	WriteInt(XorStr("SMG"), XorStr("Enabled"), Options.Legit.Aimbot.Configs.SMGs.Enabled);
	WriteInt(XorStr("SMG"), XorStr("Bone"), Options.Legit.Aimbot.Configs.SMGs.Bone);
	WriteFloat(XorStr("SMG"), XorStr("FOV"), Options.Legit.Aimbot.Configs.SMGs.Fov);
	WriteFloat(XorStr("SMG"), XorStr("Smooth"), Options.Legit.Aimbot.Configs.SMGs.lSmooth);
	WriteFloat(XorStr("SMG"), XorStr("SmoothX"), Options.Legit.Aimbot.Configs.SMGs.Smooth[0]);
	WriteFloat(XorStr("SMG"), XorStr("SmoothY"), Options.Legit.Aimbot.Configs.SMGs.Smooth[1]);
	WriteInt(XorStr("SMG"), XorStr("SilentAim"), Options.Legit.Aimbot.Configs.SMGs.SilentAim);
	WriteInt(XorStr("SMG"), XorStr("RCS"), Options.Legit.Aimbot.Configs.SMGs.RCS);
	WriteInt(XorStr("SMG"), XorStr("pSilent"), Options.Legit.Aimbot.Configs.SMGs.PerfectSilentAim);
	WriteInt(XorStr("SMG"), XorStr("LeagueFOV"), Options.Legit.Aimbot.Configs.SMGs.LFOV);
	WriteInt(XorStr("SMG"), XorStr("AimSpeed"), Options.Legit.Aimbot.Configs.SMGs.AimSpeed);
	WriteInt(XorStr("SMG"), XorStr("MultiplySpeed"), Options.Legit.Aimbot.Configs.SMGs.MultiplySpeed);
	WriteInt(XorStr("SMG"), XorStr("FOVBOOST"), Options.Legit.Aimbot.Configs.SMGs.FOVBOOST);
	//
	WriteInt(XorStr("MachineGun"), XorStr("TrigEnabled"), Options.Legit.Aimbot.Configs.Machineguns.Trigger);
	WriteInt(XorStr("MachineGun"), XorStr("Enabled"), Options.Legit.Aimbot.Configs.Machineguns.Enabled);
	WriteInt(XorStr("MachineGun"), XorStr("Bone"), Options.Legit.Aimbot.Configs.Machineguns.Bone);
	WriteFloat(XorStr("MachineGun"), XorStr("FOV"), Options.Legit.Aimbot.Configs.Machineguns.Fov);
	WriteFloat(XorStr("MachineGun"), XorStr("Smooth"), Options.Legit.Aimbot.Configs.Machineguns.lSmooth);
	WriteFloat(XorStr("MachineGun"), XorStr("SmoothX"), Options.Legit.Aimbot.Configs.Machineguns.Smooth[0]);
	WriteFloat(XorStr("MachineGun"), XorStr("SmoothY"), Options.Legit.Aimbot.Configs.Machineguns.Smooth[1]);
	WriteInt(XorStr("MachineGun"), XorStr("SilentAim"), Options.Legit.Aimbot.Configs.Machineguns.SilentAim);
	WriteInt(XorStr("MachineGun"), XorStr("RCS"), Options.Legit.Aimbot.Configs.Machineguns.RCS);
	WriteInt(XorStr("MachineGun"), XorStr("pSilent"), Options.Legit.Aimbot.Configs.Machineguns.PerfectSilentAim);
	WriteInt(XorStr("MachineGun"), XorStr("LeagueFOV"), Options.Legit.Aimbot.Configs.Machineguns.LFOV);
	WriteInt(XorStr("MachineGun"), XorStr("AimSpeed"), Options.Legit.Aimbot.Configs.Machineguns.AimSpeed);
	WriteInt(XorStr("MachineGun"), XorStr("MultiplySpeed"), Options.Legit.Aimbot.Configs.Machineguns.MultiplySpeed);
	WriteInt(XorStr("MachineGun"), XorStr("FOVBOOST"), Options.Legit.Aimbot.Configs.Machineguns.FOVBOOST);


	// Skin Changer zzz
	WriteInt(XorStr("Skins"), XorStr("Enabled"), Options.Skins.Enabled);
	WriteInt(XorStr("Skins"), XorStr("Deagle"), Options.Skins.deagle);
	WriteInt(XorStr("Skins"), XorStr("CZ75"), Options.Skins.cz75);
	WriteInt(XorStr("Skins"), XorStr("P2000"), Options.Skins.p2000);
	WriteInt(XorStr("Skins"), XorStr("Elites"),Options.Skins.elites);
	WriteInt(XorStr("Skins"), XorStr("P250"), Options.Skins.p250);
	WriteInt(XorStr("Skins"), XorStr("Fiveseven"), Options.Skins.fiveseven);
	WriteInt(XorStr("Skins"), XorStr("TEC9"), Options.Skins.tec9);
	WriteInt(XorStr("Skins"), XorStr("Glock"), Options.Skins.glock);
	WriteInt(XorStr("Skins"), XorStr("AUG"), Options.Skins.aug);
	WriteInt(XorStr("Skins"), XorStr("Galil"), Options.Skins.galil);
	WriteInt(XorStr("Skins"), XorStr("USPS"), Options.Skins.usps);
	WriteInt(XorStr("Skins"), XorStr("AK47"), Options.Skins.ak47);
	WriteInt(XorStr("Skins"), XorStr("Famas"), Options.Skins.famas);
	WriteInt(XorStr("Skins"), XorStr("M4A4"), Options.Skins.m4a4);
	WriteInt(XorStr("Skins"), XorStr("M4A1S"), Options.Skins.m4a1s);
	WriteInt(XorStr("Skins"), XorStr("Bizon"), Options.Skins.bizon);
	WriteInt(XorStr("Skins"), XorStr("MAC10"), Options.Skins.mac10);
	WriteInt(XorStr("Skins"), XorStr("MP7"), Options.Skins.mp7);
	WriteInt(XorStr("Skins"), XorStr("MP9"), Options.Skins.mp9);
	WriteInt(XorStr("Skins"), XorStr("P90"), Options.Skins.p90);
	WriteInt(XorStr("Skins"), XorStr("M249"), Options.Skins.m249);
	WriteInt(XorStr("Skins"), XorStr("UMP45"), Options.Skins.ump45);
	WriteInt(XorStr("Skins"), XorStr("NEGEV"), Options.Skins.negev);
	WriteInt(XorStr("Skins"), XorStr("MAG7"), Options.Skins.mag7);
	WriteInt(XorStr("Skins"), XorStr("NOVA"), Options.Skins.nova);
	WriteInt(XorStr("Skins"), XorStr("SawedOff"), Options.Skins.sawedoff);
	WriteInt(XorStr("Skins"), XorStr("XM1014"), Options.Skins.xm1014);
	WriteInt(XorStr("Skins"), XorStr("SCAR20"), Options.Skins.scar20);
	WriteInt(XorStr("Skins"), XorStr("AWP"), Options.Skins.awp);
	WriteInt(XorStr("Skins"), XorStr("SSG08"), Options.Skins.ssg08);
	WriteInt(XorStr("Skins"), XorStr("G3SG1"), Options.Skins.g3sg1);
	WriteInt(XorStr("Skins"), XorStr("MAGNUM"), Options.Skins.magnum);
	WriteInt(XorStr("Skins"), XorStr("SG556"), Options.Skins.sg556);
	WriteInt(XorStr("Skins"), XorStr("Knife"), Options.Skins.KnifeSelect);
	WriteInt(XorStr("Skins"), XorStr("M9 Skin"), Options.Skins.KnifeIDm);
	WriteInt(XorStr("Skins"), XorStr("Butterfly Skin"), Options.Skins.KnifeIDbutter);
	WriteInt(XorStr("Skins"), XorStr("Falchion Skin"), Options.Skins.KnifeIDfal);
	WriteInt(XorStr("Skins"), XorStr("Flip Skin"), Options.Skins.KnifeIDf);
	WriteInt(XorStr("Skins"), XorStr("Bayonet Skin"), Options.Skins.KnifeIDb);
	WriteInt(XorStr("Skins"), XorStr("Karambit Skin"), Options.Skins.KnifeIDk);
	WriteInt(XorStr("Skins"), XorStr("Huntsman Skin"), Options.Skins.KnifeIDh);
	WriteInt(XorStr("Skins"), XorStr("Gut Knife"), Options.Skins.KnifeIDg);
	WriteInt(XorStr("Skins"), XorStr("Bowie Knife"), Options.Skins.KnifeIDbow);
	WriteInt(XorStr("Skins"), XorStr("Shadow Daggers Knife"), Options.Skins.KnifeIDdag);
//	WriteInt(XorStr("Skins"), XorStr("KnifePaint"), Options.Skins.KnifeID);
	WriteInt(XorStr("Skins"), XorStr("StatTrak"), Options.Skins.StatTrak);

}

void Config::LoadConfig()
{
	//Visuals
	Options.Visuals.ESP.Enabled = ReadInt(XorStr("Visuals"), XorStr("Enabled"), 0);
	Options.Visuals.ESP.AimPoint = ReadInt(XorStr("Visuals"), XorStr("Visualize Aim Point"), 0);
	Options.Visuals.ESP.Box = ReadInt(XorStr("Visuals"), XorStr("Box"), 0);
	Options.Visuals.ESP.Health = ReadInt(XorStr("Visuals"), XorStr("Health"), 0);
	Options.Visuals.ESP.Weapon = ReadInt(XorStr("Visuals"), XorStr("Weapon"), 0);
	Options.Visuals.ESP.Name = ReadInt(XorStr("Visuals"), XorStr("Name"), 0);
	Options.Visuals.ESP.EnemyOnly = ReadInt(XorStr("Visuals"), XorStr("EnemyOnly"), 0);
	Options.Visuals.ESP.bVisibleOnly = ReadInt(XorStr("Visuals"), XorStr("VisualDetection"), 0);
    Options.Visuals.ESP.Bone = ReadInt(XorStr("Visuals"), XorStr("Bone"), 0);
	Options.Visuals.ESP.Barrel = ReadInt(XorStr("Visuals"), XorStr("Barrel"), 0);
	Options.Visuals.ESP.FOV = ReadInt(XorStr("Visuals"), XorStr("FOV"), 0);
	Options.Visuals.ESP.ThirdPerson = ReadInt(XorStr("Visuals"), XorStr("ThirdPerson"), 0);
	Options.Visuals.ESP.Hitmarker = ReadInt(XorStr("Visuals"), XorStr("Hitmarker"), 0);
	Options.Visuals.ESP.RecoilCrosshair = ReadInt(XorStr("Visuals"), XorStr("Recoil Crosshair"), 0);
	Options.Visuals.ESP.AutoAccept = ReadInt(XorStr("Visuals"), XorStr("Auto Accept"), 0);
	Options.Visuals.ESP.DLight = ReadInt(XorStr("Visuals"), XorStr("Lights"), 0);
	Options.Visuals.ESP.DLightRadius = ReadInt(XorStr("Visuals"), XorStr("Multiply Light Radius"), 1);
	Options.Visuals.ESP.LocationSpam = ReadInt(XorStr("Visuals"), XorStr("LocationSpam"), 0);
	Options.Visuals.ESP.RankESP = ReadInt(XorStr("Visuals"), XorStr("RankESP"), 0);


	Options.Visuals.ESP.TeamColor[0] = ReadFloat(XorStr("Colors"), XorStr("ESP Team Vis Red"), 0);
	Options.Visuals.ESP.TeamColor[1] = ReadFloat(XorStr("Colors"), XorStr("ESP Team Vis Green"), 1.f);
	Options.Visuals.ESP.TeamColor[2] = ReadFloat(XorStr("Colors"), XorStr("ESP Team Vis Blue"), 1.f);

	Options.Visuals.ESP.TeamColorWall[0] = ReadFloat(XorStr("Colors"), XorStr("ESP Team Red"), 0);
	Options.Visuals.ESP.TeamColorWall[1] = ReadFloat(XorStr("Colors"), XorStr("ESP Team Green"),0);
	Options.Visuals.ESP.TeamColorWall[2] = ReadFloat(XorStr("Colors"), XorStr("ESP Team Blue"), 1.f);

	Options.Visuals.ESP.EnemyColor[0] = ReadFloat(XorStr("Colors"), XorStr("ESP Enemy Vis Red"), 1.f);
	Options.Visuals.ESP.EnemyColor[1] = ReadFloat(XorStr("Colors"), XorStr("ESP Enemy Vis Green"), 0);
	Options.Visuals.ESP.EnemyColor[2] = ReadFloat(XorStr("Colors"), XorStr("ESP Enemy Vis Blue"), 0);

	Options.Visuals.ESP.EnemyColorWall[0] = ReadFloat(XorStr("Colors"), XorStr("ESP Enemy Red"), 1.f);
	Options.Visuals.ESP.EnemyColorWall[1] = ReadFloat(XorStr("Colors"), XorStr("ESP Enemy Green"), 1.f);
	Options.Visuals.ESP.EnemyColorWall[2] = ReadFloat(XorStr("Colors"), XorStr("ESP Enemy Blue"), 0);

	/*Chams*/
	Options.Visuals.Chams.Enabled = ReadInt(XorStr("Visuals"), XorStr("Chams"), 0);
	Options.Visuals.Chams.Mode = ReadInt(XorStr("Visuals"), XorStr("Type"), 0);
	Options.Visuals.Chams.XQZ =	ReadInt(XorStr("Visuals"), XorStr("XQZ"), 0);
	/*Colors*/
	Options.Visuals.Chams.TeamColor[0] = ReadFloat(XorStr("Colors"), XorStr("Team Vis Red"), 0);
	Options.Visuals.Chams.TeamColor[1]  = ReadFloat(XorStr("Colors"), XorStr("Team Vis Green"), 1.f);
	Options.Visuals.Chams.TeamColor[2] = ReadFloat(XorStr("Colors"), XorStr("Team Vis Blue"), 1.f);
	//Team Vis
	Options.Visuals.Chams.TeamColorWall[0] = ReadFloat(XorStr("Colors"), XorStr("Team Red"), 0);
	Options.Visuals.Chams.TeamColorWall[1] = ReadFloat(XorStr("Colors"), XorStr("Team Green"), 0);
	Options.Visuals.Chams.TeamColorWall[2] = ReadFloat(XorStr("Colors"), XorStr("Team Blue"), 1.f);
	//Team notVis
	Options.Visuals.Chams.EnemyColor[0] = ReadFloat(XorStr("Colors"), XorStr("Enemy Vis Red"), 1.f);
	Options.Visuals.Chams.EnemyColor[1] = ReadFloat(XorStr("Colors"), XorStr("Enemy Vis Green"), 0);
	Options.Visuals.Chams.EnemyColor[2] = ReadFloat(XorStr("Colors"), XorStr("Enemy Vis Blue"), 0);
	//Enemy vis
	Options.Visuals.Chams.EnemyColorWall[0] = ReadFloat(XorStr("Colors"), XorStr("Enemy Red"), 1.f);
	Options.Visuals.Chams.EnemyColorWall[1] = ReadFloat(XorStr("Colors"), XorStr("Enemy Green"), 1.f);
	Options.Visuals.Chams.EnemyColorWall[2] = ReadFloat(XorStr("Colors"), XorStr("Enemy Blue"), 0);
	//Enemy nonvis
	//removals
	Options.Visuals.Removals.Hands = ReadInt(XorStr("Removals"), XorStr("Hands"), 0);
	Options.Visuals.Removals.WireframeHands = ReadInt(XorStr("Removals"), XorStr("WireFrameHands"), 0);
	Options.Visuals.Removals.Weapon = ReadInt(XorStr("Removals"), XorStr("Weapon"), 0);
	Options.Visuals.Removals.WireframeWep = ReadInt(XorStr("Removals"), XorStr("WireFrameWeapon"), 0);
	Options.Visuals.Removals.VisualRecoil = ReadInt(XorStr("Removals"), XorStr("Visual Recoil"), 0);
	Options.Visuals.Removals.Recoil = ReadInt(XorStr("Removals"), XorStr("Recoil"), 0);
	Options.Visuals.Removals.Flash = ReadInt(XorStr("Removals"), XorStr("Flash"), 0);
	//Rage
	/*Aimbot*/
	Options.Rage.AutoWall.MinDamage = ReadFloat(XorStr("AutoWall"), XorStr("MinDamage"), 1.f);

	Options.Rage.Aimbot.Enabled = ReadInt(XorStr("Aimbot"), XorStr("Enabled"), 0);
	Options.Rage.Aimbot.Hitbox = ReadInt(XorStr("Aimbot"), XorStr("Hitbox"), 0);
	Options.Rage.AutoWall.AutowallType = ReadInt(XorStr("Aimbot"), XorStr("Autowall"), 0);
	Options.Rage.Aimbot.Targeting = ReadInt(XorStr("Aimbot"), XorStr("Targeting"), 0);
	Options.Rage.Aimbot.HitScans = ReadInt(XorStr("Aimbot"), XorStr("HitScans"), 0);
	Options.Rage.Aimbot.AutoShoot = ReadInt(XorStr("Aimbot"), XorStr("AutoShoot"), 0);
	Options.Rage.Aimbot.AutoScope =	ReadInt(XorStr("Aimbot"), XorStr("AutoScope"), 0);
	Options.Rage.Aimbot.AS1tap = ReadInt(XorStr("Aimbot"), XorStr("1Tap"), 0);
	Options.Rage.Aimbot.bHitchance = ReadInt(XorStr("Aimbot"), XorStr("bHitChance"), 0);
	Options.Rage.Aimbot.bHitchanceSnipers = ReadInt(XorStr("Aimbot"), XorStr("bHitChanceSniper"), 0);
	Options.Rage.Aimbot.StopType = ReadInt(XorStr("Aimbot"), XorStr("StopType"), 0);
	Options.Rage.Aimbot.Hitchance = ReadFloat(XorStr("Aimbot"), XorStr("HitChance"), 1.f);
	Options.Rage.Aimbot.AimSmart = ReadInt(XorStr("Aimbot"), XorStr("AimSmart"), 0);
	Options.Rage.Aimbot.iSmartShots = ReadInt(XorStr("Aimbot"), XorStr("iSmartShots"), 0);
	Options.Rage.Aimbot.EnemyOnly = ReadInt(XorStr("Aimbot"), XorStr("EnemyOnly"), 0);
	Options.Rage.Aimbot.SilentAim =	ReadInt(XorStr("Aimbot"), XorStr("SilentAim"), 0);
	Options.Rage.AntiAim.Enabled = ReadInt(XorStr("AntiAim"), XorStr("Enabled"), 0);
	Options.Rage.AntiAim.Yaw = ReadInt(XorStr("AntiAim"), XorStr("Yaw"), 0);
	Options.Rage.AntiAim.Pitch = ReadInt(XorStr("AntiAim"), XorStr("Pitch"), 0);
	//Legit
	/*Trigger*/
	Options.Legit.Trigger.Enabled = ReadInt(XorStr("Trigger"), XorStr("Enabled"),0);
	Options.Legit.Trigger.TriggerFriends = ReadInt(XorStr("Trigger"), XorStr("Enemy Only"), 0);
	Options.Legit.Trigger.Filter = ReadInt(XorStr("Trigger"), XorStr("Filter"), 0);
	Options.Legit.Trigger.Key = ReadInt(XorStr("Trigger"), XorStr("Key"), 0);
	Options.Legit.Trigger.Delay = ReadInt(XorStr("Trigger"), XorStr("Delay"), 0);
	/*Aimbot*/
	Options.Legit.Aimbot.Enabled = ReadInt(XorStr("Legit"), XorStr("Enabled"), 0);
	Options.Legit.Aimbot.Bone = ReadInt(XorStr("Legit"), XorStr("Bone"), 0);
	Options.Legit.Aimbot.Fov = ReadFloat(XorStr("Legit"), XorStr("FOV"), 0);
	Options.Legit.Aimbot.lSmooth = ReadFloat(XorStr("Legit"), XorStr("Smooth"), 1);
	Options.Legit.Aimbot.Smooth[0] = ReadFloat(XorStr("Legit"), XorStr("SmoothX"), 1);
	Options.Legit.Aimbot.Smooth[1] = ReadFloat(XorStr("Legit"), XorStr("SmoothY"), 1);
	Options.Legit.Aimbot.SilentAim = ReadInt(XorStr("Legit"), XorStr("SilentAim"), 0);
	Options.Legit.Aimbot.PerfectSilentAim = ReadInt(XorStr("Legit"), XorStr("PSilent"), 0);
	Options.Legit.Aimbot.RCS = ReadInt(XorStr("Legit"), XorStr("RCS"), 0);
	Options.Legit.Aimbot.LFOV = ReadInt(XorStr("Legit"), XorStr("LeagueFOV"), 0);
	Options.Legit.Aimbot.AimSpeed = ReadInt(XorStr("Legit"), XorStr("AimSpeed"), 0);
	Options.Legit.Aimbot.MultiplySpeed = ReadInt(XorStr("Legit"), XorStr("MultiplySpeed"), 0);
	Options.Legit.Aimbot.FOVBOOST = ReadInt(XorStr("Legit"), XorStr("FOVBOOST"), 0);
	Options.Legit.Aimbot.EnemyOnly = ReadInt(XorStr("Legit"), XorStr("EnemyOnly"), 0);

	/*PlayerMods*/
	Options.PlayerMods.FakeLag.Enabled = ReadInt(XorStr("FakeLag"), XorStr("Enabled"),0);
	Options.PlayerMods.FakeLag.Send = ReadInt(XorStr("FakeLag"), XorStr("Send"), 0);
	Options.PlayerMods.FakeLag.Choke = ReadInt(XorStr("FakeLag"), XorStr("Choke"), 0);
	/*AirStuck*/
	Options.PlayerMods.AirStuck.Enabled = ReadInt(XorStr("AirStuck"), XorStr("Enabled"), 0);
	Options.PlayerMods.AirStuck.Key = ReadInt(XorStr("AirStuck"), XorStr("Key"), 0);
	/*Jump*/
	Options.PlayerMods.bhop.Enabled = ReadInt(XorStr("Jump"), XorStr("BHOP"), 0);
	Options.PlayerMods.AutoStrafe.Enabled = ReadInt(XorStr("Jump"), XorStr("AutoStrafe"), 0);
	Options.PlayerMods.AutoStrafe.Silent = ReadInt(XorStr("Jump"), XorStr("Silent"), 0);
	/*Anti-Cheats*/
	Options.AntiCheat.MM = ReadInt(XorStr("Anti-Cheat"), XorStr("MM"), 0);
	Options.AntiCheat.SMAC = ReadInt(XorStr("Anti-Cheat"), XorStr("SMAC"),0);
	Options.AntiCheat.CEVO = ReadInt(XorStr("Anti-Cheat"), XorStr("CEVO"), 0);
	Options.AntiCheat.FACEIT = ReadInt(XorStr("Anti-Cheat"), XorStr("FACEIT"), 0);
	Options.AntiCheat.VAC = ReadInt(XorStr("Anti-Cheat"), XorStr("VAC"), 0);
	Options.AntiCheat.ESEA = ReadInt(XorStr("Anti-Cheat"), XorStr("ESEA"), 0);

	/* Custom Hitscans*/
	Options.Rage.Aimbot.Hitscan.Point = ReadInt(XorStr("CHitScans"), XorStr("Multipoint"), 0);
	Options.Rage.Aimbot.Hitscan.Head = ReadInt(XorStr("CHitScans"), XorStr("Head"), 0);
	Options.Rage.Aimbot.Hitscan.Neck = ReadInt(XorStr("CHitScans"), XorStr("Neck"), 0);
	Options.Rage.Aimbot.Hitscan.LowerNeck = ReadInt(XorStr("CHitScans"), XorStr("LowerNeck"), 0);
	Options.Rage.Aimbot.Hitscan.Pelvis = ReadInt(XorStr("CHitScans"), XorStr("Pelvis"), 0);
	Options.Rage.Aimbot.Hitscan.Body = ReadInt(XorStr("CHitScans"), XorStr("Body"), 0);
	Options.Rage.Aimbot.Hitscan.Thorax = ReadInt(XorStr("CHitScans"), XorStr("Thorax"), 0);
	Options.Rage.Aimbot.Hitscan.Chest = ReadInt(XorStr("CHitScans"), XorStr("Chest"), 0);
	Options.Rage.Aimbot.Hitscan.UpperChest = ReadInt(XorStr("CHitScans"), XorStr("UpperChest"), 0);
	Options.Rage.Aimbot.Hitscan.RightThigh = ReadInt(XorStr("CHitScans"), XorStr("RightThigh"), 0);
	Options.Rage.Aimbot.Hitscan.LeftThigh = ReadInt(XorStr("CHitScans"), XorStr("LeftThigh"), 0);
	Options.Rage.Aimbot.Hitscan.RightCalf = ReadInt(XorStr("CHitScans"), XorStr("RightCalf"), 0);
	Options.Rage.Aimbot.Hitscan.LeftCalf = ReadInt(XorStr("CHitScans"), XorStr("LeftCalf"), 0);
	Options.Rage.Aimbot.Hitscan.RightFoot = ReadInt(XorStr("CHitScans"), XorStr("RightFoot"), 0);
	Options.Rage.Aimbot.Hitscan.LeftFoot = ReadInt(XorStr("CHitScans"), XorStr("LeftFoot"), 0);
	Options.Rage.Aimbot.Hitscan.RightHand = ReadInt(XorStr("CHitScans"), XorStr("RightHand"), 0);
	Options.Rage.Aimbot.Hitscan.LeftHand = ReadInt(XorStr("CHitScans"), XorStr("LeftHand"), 0);
	Options.Rage.Aimbot.Hitscan.RightUpperArm =	ReadInt(XorStr("CHitScans"), XorStr("RightUpperArm"), 0);
	Options.Rage.Aimbot.Hitscan.RightForeArm = ReadInt(XorStr("CHitScans"), XorStr("RightForeArm"), 0);
	Options.Rage.Aimbot.Hitscan.LeftUpperArm = ReadInt(XorStr("CHitScans"), XorStr("LeftUpperArm"), 0);
	Options.Rage.Aimbot.Hitscan.LeftForeArm = ReadInt(XorStr("CHitScans"), XorStr("LeftForeArm"), 0);





	/*Weapon Configs*/ //How to double a configs size lmao
	Options.Legit.Aimbot.WeaponConfigs = ReadInt(XorStr("Legit"), XorStr("WeaponConfigs"), 0);
	Options.Legit.Aimbot.Configs.Rifles.Trigger = ReadInt(XorStr("Rifle"), XorStr("TrigEnabled"), 0);
	Options.Legit.Aimbot.Configs.Rifles.Enabled = ReadInt(XorStr("Rifle"), XorStr("Enabled"), 0);
	Options.Legit.Aimbot.Configs.Rifles.Bone = ReadInt(XorStr("Rifle"), XorStr("Bone"), 0);
	Options.Legit.Aimbot.Configs.Rifles.Fov = ReadFloat(XorStr("Rifle"), XorStr("FOV"), 0);
	Options.Legit.Aimbot.Configs.Rifles.Smooth[0] = ReadFloat(XorStr("Rifle"), XorStr("SmoothX"), 1);
	Options.Legit.Aimbot.Configs.Rifles.Smooth[1] = ReadFloat(XorStr("Rifle"), XorStr("SmoothY"), 1);
	Options.Legit.Aimbot.Configs.Rifles.SilentAim = ReadInt(XorStr("Rifle"), XorStr("SilentAim"), 0);
	Options.Legit.Aimbot.Configs.Rifles.RCS = ReadInt(XorStr("Rifle"), XorStr("RCS"), 0);
	Options.Legit.Aimbot.Configs.Rifles.PerfectSilentAim = ReadInt(XorStr("Rifle"), XorStr("pSilent"), 0);
	Options.Legit.Aimbot.Configs.Rifles.LFOV = ReadInt(XorStr("Rifle"), XorStr("LeagueFOV"), 0);
	Options.Legit.Aimbot.Configs.Rifles.AimSpeed = ReadInt(XorStr("Rifle"), XorStr("AimSpeed"), 0);
	Options.Legit.Aimbot.Configs.Rifles.MultiplySpeed = ReadInt(XorStr("Rifle"), XorStr("MultiplySpeed"), 0);
	Options.Legit.Aimbot.Configs.Rifles.FOVBOOST = ReadInt(XorStr("Rifle"), XorStr("FOVBOOST"), 0);
	//
	Options.Legit.Aimbot.Configs.Pistols.Trigger = ReadInt(XorStr("Pistol"), XorStr("TrigEnabled"), 0);
	Options.Legit.Aimbot.Configs.Pistols.Enabled = ReadInt(XorStr("Pistol"), XorStr("Enabled"), 0);
	Options.Legit.Aimbot.Configs.Pistols.Bone = ReadInt(XorStr("Pistol"), XorStr("Bone"), 0);
	Options.Legit.Aimbot.Configs.Pistols.Fov = ReadFloat(XorStr("Pistol"), XorStr("FOV"), 0);
	Options.Legit.Aimbot.Configs.Pistols.Smooth[0] = ReadFloat(XorStr("Pistol"), XorStr("SmoothX"), 1);
	Options.Legit.Aimbot.Configs.Pistols.Smooth[1] = ReadFloat(XorStr("Pistol"), XorStr("SmoothY"), 1);
	Options.Legit.Aimbot.Configs.Pistols.SilentAim = ReadInt(XorStr("Pistol"), XorStr("SilentAim"), 0);
	Options.Legit.Aimbot.Configs.Pistols.RCS = ReadInt(XorStr("Pistol"), XorStr("RCS"), 0);
	Options.Legit.Aimbot.Configs.Pistols.PerfectSilentAim = ReadInt(XorStr("Pistol"), XorStr("pSilent"), 0);
	Options.Legit.Aimbot.Configs.Pistols.LFOV = ReadInt(XorStr("Pistol"), XorStr("LeagueFOV"), 0);
	Options.Legit.Aimbot.Configs.Pistols.AimSpeed = ReadInt(XorStr("Pistol"), XorStr("AimSpeed"), 0);
	Options.Legit.Aimbot.Configs.Pistols.MultiplySpeed = ReadInt(XorStr("Pistol"), XorStr("MultiplySpeed"), 0);
	Options.Legit.Aimbot.Configs.Pistols.FOVBOOST = ReadInt(XorStr("Pistol"), XorStr("FOVBOOST"), 0);
	//
	Options.Legit.Aimbot.Configs.Shotguns.Trigger = ReadInt(XorStr("Shotgun"), XorStr("TrigEnabled"), 0);
	Options.Legit.Aimbot.Configs.Shotguns.Enabled = ReadInt(XorStr("Shotgun"), XorStr("Enabled"), 0);
	Options.Legit.Aimbot.Configs.Shotguns.Bone = ReadInt(XorStr("Shotgun"), XorStr("Bone"), 0);
	Options.Legit.Aimbot.Configs.Shotguns.Fov = ReadFloat(XorStr("Shotgun"), XorStr("FOV"), 0);
	Options.Legit.Aimbot.Configs.Shotguns.Smooth[0] = ReadFloat(XorStr("Shotgun"), XorStr("SmoothX"), 1);
	Options.Legit.Aimbot.Configs.Shotguns.Smooth[1] = ReadFloat(XorStr("Shotgun"), XorStr("SmoothY"), 1);
	Options.Legit.Aimbot.Configs.Shotguns.SilentAim = ReadInt(XorStr("Shotgun"), XorStr("SilentAim"), 0);
	Options.Legit.Aimbot.Configs.Shotguns.RCS = ReadInt(XorStr("Shotgun"), XorStr("RCS"), 0);
	Options.Legit.Aimbot.Configs.Shotguns.PerfectSilentAim = ReadInt(XorStr("Shotgun"), XorStr("pSilent"), 0);
	Options.Legit.Aimbot.Configs.Shotguns.LFOV = ReadInt(XorStr("Shotgun"), XorStr("LeagueFOV"), 0);
	Options.Legit.Aimbot.Configs.Shotguns.AimSpeed = ReadInt(XorStr("Shotgun"), XorStr("AimSpeed"), 0);
	Options.Legit.Aimbot.Configs.Shotguns.MultiplySpeed = ReadInt(XorStr("Shotgun"), XorStr("MultiplySpeed"), 0);
	Options.Legit.Aimbot.Configs.Shotguns.FOVBOOST = ReadInt(XorStr("Shotgun"), XorStr("FOVBOOST"), 0);
	//
	Options.Legit.Aimbot.Configs.Snipers.Trigger = ReadInt(XorStr("Sniper"), XorStr("TrigEnabled"), 0);
	Options.Legit.Aimbot.Configs.Snipers.Enabled = ReadInt(XorStr("Sniper"), XorStr("Enabled"), 0);
	Options.Legit.Aimbot.Configs.Snipers.Bone = ReadInt(XorStr("Sniper"), XorStr("Bone"), 0);
	Options.Legit.Aimbot.Configs.Snipers.Fov = ReadFloat(XorStr("Sniper"), XorStr("FOV"), 0);
	Options.Legit.Aimbot.Configs.Snipers.Smooth[0] = ReadFloat(XorStr("Sniper"), XorStr("SmoothX"), 1);
	Options.Legit.Aimbot.Configs.Snipers.Smooth[1] = ReadFloat(XorStr("Sniper"), XorStr("SmoothY"), 1);
	Options.Legit.Aimbot.Configs.Snipers.SilentAim = ReadInt(XorStr("Sniper"), XorStr("SilentAim"), 0);
	Options.Legit.Aimbot.Configs.Snipers.RCS = ReadInt(XorStr("Sniper"), XorStr("RCS"), 0);
	Options.Legit.Aimbot.Configs.Snipers.PerfectSilentAim = ReadInt(XorStr("Sniper"), XorStr("pSilent"), 0);
	Options.Legit.Aimbot.Configs.Snipers.LFOV = ReadInt(XorStr("Sniper"), XorStr("LeagueFOV"), 0);
	Options.Legit.Aimbot.Configs.Snipers.AimSpeed = ReadInt(XorStr("Sniper"), XorStr("AimSpeed"), 0);
	Options.Legit.Aimbot.Configs.Snipers.MultiplySpeed = ReadInt(XorStr("Sniper"), XorStr("MultiplySpeed"), 0);
	Options.Legit.Aimbot.Configs.Snipers.FOVBOOST = ReadInt(XorStr("Sniper"), XorStr("FOVBOOST"), 0);
   //
	Options.Legit.Aimbot.Configs.SMGs.Trigger = ReadInt(XorStr("SMG"), XorStr("TrigEnabled"), 0);
	Options.Legit.Aimbot.Configs.SMGs.Enabled = ReadInt(XorStr("SMG"), XorStr("Enabled"), 0);
	Options.Legit.Aimbot.Configs.SMGs.Bone = ReadInt(XorStr("SMG"), XorStr("Bone"), 0);
	Options.Legit.Aimbot.Configs.SMGs.Fov = ReadFloat(XorStr("SMG"), XorStr("FOV"), 0);
	Options.Legit.Aimbot.Configs.SMGs.Smooth[0] = ReadFloat(XorStr("SMG"), XorStr("SmoothX"), 1);
	Options.Legit.Aimbot.Configs.SMGs.Smooth[1] = ReadFloat(XorStr("SMG"), XorStr("SmoothY"), 1);
	Options.Legit.Aimbot.Configs.SMGs.SilentAim = ReadInt(XorStr("SMG"), XorStr("SilentAim"), 0);
	Options.Legit.Aimbot.Configs.SMGs.RCS = ReadInt(XorStr("SMG"), XorStr("RCS"), 0);
	Options.Legit.Aimbot.Configs.SMGs.PerfectSilentAim = ReadInt(XorStr("SMG"), XorStr("pSilent"), 0);
	Options.Legit.Aimbot.Configs.SMGs.LFOV = ReadInt(XorStr("SMG"), XorStr("LeagueFOV"), 0);
	Options.Legit.Aimbot.Configs.SMGs.AimSpeed = ReadInt(XorStr("SMG"), XorStr("AimSpeed"), 0);
	Options.Legit.Aimbot.Configs.SMGs.MultiplySpeed = ReadInt(XorStr("SMG"), XorStr("MultiplySpeed"), 0);
	Options.Legit.Aimbot.Configs.SMGs.FOVBOOST = ReadInt(XorStr("SMG"), XorStr("FOVBOOST"), 0);
	//
	Options.Legit.Aimbot.Configs.Machineguns.Trigger = ReadInt(XorStr("MachineGun"), XorStr("TrigEnabled"), 0);
	Options.Legit.Aimbot.Configs.Machineguns.Enabled = ReadInt(XorStr("MachineGun"), XorStr("Enabled"), 0);
	Options.Legit.Aimbot.Configs.Machineguns.Bone = ReadInt(XorStr("MachineGun"), XorStr("Bone"), 0);
	Options.Legit.Aimbot.Configs.Machineguns.Fov = ReadFloat(XorStr("MachineGun"), XorStr("FOV"), 0);
	Options.Legit.Aimbot.Configs.Machineguns.Smooth[0] = ReadFloat(XorStr("MachineGun"), XorStr("SmoothX"), 1);
	Options.Legit.Aimbot.Configs.Machineguns.Smooth[1] = ReadFloat(XorStr("MachineGun"), XorStr("SmoothY"), 1);
	Options.Legit.Aimbot.Configs.Machineguns.SilentAim = ReadInt(XorStr("MachineGun"), XorStr("SilentAim"), 0);
	Options.Legit.Aimbot.Configs.Machineguns.RCS = ReadInt(XorStr("MachineGun"), XorStr("RCS"), 0);
	Options.Legit.Aimbot.Configs.Machineguns.PerfectSilentAim = ReadInt(XorStr("MachineGun"), XorStr("pSilent"), 0);
	Options.Legit.Aimbot.Configs.Machineguns.LFOV = ReadInt(XorStr("MachineGun"), XorStr("LeagueFOV"), 0);
	Options.Legit.Aimbot.Configs.Machineguns.AimSpeed = ReadInt(XorStr("MachineGun"), XorStr("AimSpeed"), 0);
	Options.Legit.Aimbot.Configs.Machineguns.MultiplySpeed = ReadInt(XorStr("MachineGun"), XorStr("MultiplySpeed"), 0);
	Options.Legit.Aimbot.Configs.Machineguns.FOVBOOST = ReadInt(XorStr("MachineGun"), XorStr("FOVBOOST"), 0);


	// Skin Changer read meme

	Options.Skins.Enabled = ReadInt(XorStr("Skins"), XorStr("Enabled"), 0);
	Options.Skins.deagle = ReadInt(XorStr("Skins"), XorStr("Deagle"), 0);
	Options.Skins.cz75 = ReadInt(XorStr("Skins"), XorStr("CZ75"), 0);
	Options.Skins.p2000 = ReadInt(XorStr("Skins"), XorStr("P2000"), 0);
	Options.Skins.elites = ReadInt(XorStr("Skins"), XorStr("Elites"), 0);
	Options.Skins.p250 = ReadInt(XorStr("Skins"), XorStr("P250"), 0);
	Options.Skins.fiveseven = ReadInt(XorStr("Skins"), XorStr("Fiveseven"), 0);
	Options.Skins.tec9 = ReadInt(XorStr("Skins"), XorStr("TEC9"), 0);
	Options.Skins.glock = ReadInt(XorStr("Skins"), XorStr("Glock"), 0);
	Options.Skins.aug = ReadInt(XorStr("Skins"), XorStr("AUG"), 0);
	Options.Skins.galil = ReadInt(XorStr("Skins"), XorStr("Galil"), 0);
	Options.Skins.usps = ReadInt(XorStr("Skins"), XorStr("USPS"), 0);
	Options.Skins.ak47 = ReadInt(XorStr("Skins"), XorStr("AK47"), 0);
	Options.Skins.famas = ReadInt(XorStr("Skins"), XorStr("Famas"), 0);
	Options.Skins.m4a4 = ReadInt(XorStr("Skins"), XorStr("M4A4"), 0);
	Options.Skins.m4a1s = ReadInt(XorStr("Skins"), XorStr("M4A1S"), 0);
	Options.Skins.bizon = ReadInt(XorStr("Skins"), XorStr("Bizon"), 0);
	Options.Skins.mac10 = ReadInt(XorStr("Skins"), XorStr("MAC10"), 0);
	Options.Skins.mp7 = ReadInt(XorStr("Skins"), XorStr("MP7"), 0);
	Options.Skins.mp9 = ReadInt(XorStr("Skins"), XorStr("MP9"), 0);
	Options.Skins.p90 = ReadInt(XorStr("Skins"), XorStr("P90"), 0);
	Options.Skins.m249 = ReadInt(XorStr("Skins"), XorStr("M249"), 0);
	Options.Skins.ump45 = ReadInt(XorStr("Skins"), XorStr("UMP45"), 0);
	Options.Skins.negev = ReadInt(XorStr("Skins"), XorStr("NEGEV"), 0);
	Options.Skins.mag7 = ReadInt(XorStr("Skins"), XorStr("MAG7"), 0);
	Options.Skins.nova = ReadInt(XorStr("Skins"), XorStr("NOVA"), 0);
	Options.Skins.sawedoff = ReadInt(XorStr("Skins"), XorStr("SawedOff"), 0);
	Options.Skins.xm1014 = ReadInt(XorStr("Skins"), XorStr("XM1014"), 0);
	Options.Skins.scar20 = ReadInt(XorStr("Skins"), XorStr("SCAR20"), 0);
	Options.Skins.awp = ReadInt(XorStr("Skins"), XorStr("AWP"), 0);
	Options.Skins.ssg08 = ReadInt(XorStr("Skins"), XorStr("SSG08"), 0);
	Options.Skins.g3sg1 = ReadInt(XorStr("Skins"), XorStr("G3SG1"), 0);
	Options.Skins.magnum = ReadInt(XorStr("Skins"), XorStr("MAGNUM"), 0);
	Options.Skins.sg556 = ReadInt(XorStr("Skins"), XorStr("SG556"), 0);
	Options.Skins.KnifeSelect = ReadInt(XorStr("Skins"), XorStr("Knife"), 0);
	Options.Skins.KnifeIDm= ReadInt(XorStr("Skins"), XorStr("M9 Skin"), 0);
	Options.Skins.KnifeIDbutter= ReadInt(XorStr("Skins"), XorStr("Butterfly Skin"), 0);
	Options.Skins.KnifeIDfal= ReadInt(XorStr("Skins"), XorStr("Falchion Skin"), 0);
	Options.Skins.KnifeIDf = ReadInt(XorStr("Skins"), XorStr("Flip Skin"), 0);
	Options.Skins.KnifeIDb = ReadInt(XorStr("Skins"), XorStr("Bayonet Skin"), 0);
	Options.Skins.KnifeIDk = ReadInt(XorStr("Skins"), XorStr("Karambit Skin"), 0);
	Options.Skins.KnifeIDh = ReadInt(XorStr("Skins"), XorStr("Huntsman Skin"), 0);
	Options.Skins.KnifeIDg = ReadInt(XorStr("Skins"), XorStr("Gut Knife"), 0);
	Options.Skins.KnifeIDbow = ReadInt(XorStr("Skins"), XorStr("Bowie Knife"), 0);
	Options.Skins.KnifeIDdag = ReadInt(XorStr("Skins"), XorStr("Shadow Daggers Knife"), 0);
	//Options.Skins.KnifeID = ReadInt(XorStr("Skins"), XorStr("KnifePaint"), 0);
	Options.Skins.StatTrak = ReadInt(XorStr("Skins"), XorStr("StatTrak"), 0);
}


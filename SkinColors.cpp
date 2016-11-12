#include "Accessors.h"
/*I Grabbed the sigs this morning for this*/
//Imprement a menu for every gun please format it with seperators
void ChangeKnifeColor(CBaseCombatWeapon* pWeapon, int nBayonet, int nFlip, int nGut, int nKarambit, int nM9Bayonet, int nHuntsman, int nButterfly, int nFalchion,int nDagger, int nBowie)// gay ass code dont judge
{
	typedef DWORD(__cdecl* oGetItemSchema)();
	static oGetItemSchema GetItemSchema = reinterpret_cast<oGetItemSchema>(Memory::FindPatternAlt(XorStr("Client.dll"),reinterpret_cast<PBYTE>(XorStr("\xA1\x00\x00\x00\x00\x85\xC0\x75\x43")),XorStr("x????xxxx"),0,0));

	typedef CPaintKit*(__thiscall* oGetPaintKitDefinition)(DWORD, int);
	static oGetPaintKitDefinition GetPaintKitDefinition = reinterpret_cast<oGetPaintKitDefinition>(Memory::FindPatternAlt(XorStr("Client.dll"),
		reinterpret_cast<PBYTE>(XorStr("\x00\xCC\xCC\xCC\xCC\x55\x8B\xEC\x53\x56\x57\x8B\xF9")), XorStr("xxxxxxxxxxxxx"),0,0) + 5);

	if (Options.Skins.KnifeSelect == 1)
	{
		auto pKit = GetPaintKitDefinition(GetItemSchema() + 4, Options.Skins.KnifeIDb);
		if (Options.Skins.Color.Custom0)
			pKit->color0 = Color(Options.Skins.Color.color0[0] * 255, Options.Skins.Color.color0[1] * 255, Options.Skins.Color.color0[2] * 255, 255);
		if (Options.Skins.Color.Custom1)
			pKit->color1 = Color(Options.Skins.Color.color1[0] * 255, Options.Skins.Color.color1[1] * 255, Options.Skins.Color.color1[2] * 255, 255);
		if (Options.Skins.Color.Custom2)
			pKit->color2 = Color(Options.Skins.Color.color2[0] * 255, Options.Skins.Color.color2[1] * 255, Options.Skins.Color.color2[2] * 255, 255);
		if (Options.Skins.Color.Custom3)
			pKit->color3 = Color(Options.Skins.Color.color3[0] * 255, Options.Skins.Color.color3[1] * 255, Options.Skins.Color.color3[2] * 255, 255);
	}
	else if (Options.Skins.KnifeSelect == 2)
	{
		auto pKit = GetPaintKitDefinition(GetItemSchema() + 4, Options.Skins.KnifeIDf);
		if (Options.Skins.Color.Custom0)
			pKit->color0 = Color(Options.Skins.Color.color0[0] * 255, Options.Skins.Color.color0[1] * 255, Options.Skins.Color.color0[2] * 255, 255);
		if (Options.Skins.Color.Custom1)
			pKit->color1 = Color(Options.Skins.Color.color1[0] * 255, Options.Skins.Color.color1[1] * 255, Options.Skins.Color.color1[2] * 255, 255);
		if (Options.Skins.Color.Custom2)
			pKit->color2 = Color(Options.Skins.Color.color2[0] * 255, Options.Skins.Color.color2[1] * 255, Options.Skins.Color.color2[2] * 255, 255);
		if (Options.Skins.Color.Custom3)
			pKit->color3 = Color(Options.Skins.Color.color3[0] * 255, Options.Skins.Color.color3[1] * 255, Options.Skins.Color.color3[2] * 255, 255);
	}
	else if (Options.Skins.KnifeSelect == 3)
	{
		auto pKit = GetPaintKitDefinition(GetItemSchema() + 4, Options.Skins.KnifeIDg);
		if (Options.Skins.Color.Custom0)
			pKit->color0 = Color(Options.Skins.Color.color0[0] * 255, Options.Skins.Color.color0[1] * 255, Options.Skins.Color.color0[2] * 255, 255);
		if (Options.Skins.Color.Custom1)
			pKit->color1 = Color(Options.Skins.Color.color1[0] * 255, Options.Skins.Color.color1[1] * 255, Options.Skins.Color.color1[2] * 255, 255);
		if (Options.Skins.Color.Custom2)
			pKit->color2 = Color(Options.Skins.Color.color2[0] * 255, Options.Skins.Color.color2[1] * 255, Options.Skins.Color.color2[2] * 255, 255);
		if (Options.Skins.Color.Custom3)
			pKit->color3 = Color(Options.Skins.Color.color3[0] * 255, Options.Skins.Color.color3[1] * 255, Options.Skins.Color.color3[2] * 255, 255);
	}
	else if (Options.Skins.KnifeSelect == 4)
	{
		auto pKit = GetPaintKitDefinition(GetItemSchema() + 4, Options.Skins.KnifeIDk);
		if (Options.Skins.Color.Custom0)
			pKit->color0 = Color(Options.Skins.Color.color0[0] * 255, Options.Skins.Color.color0[1] * 255, Options.Skins.Color.color0[2] * 255, 255);
		if (Options.Skins.Color.Custom1)
			pKit->color1 = Color(Options.Skins.Color.color1[0] * 255, Options.Skins.Color.color1[1] * 255, Options.Skins.Color.color1[2] * 255, 255);
		if (Options.Skins.Color.Custom2)
			pKit->color2 = Color(Options.Skins.Color.color2[0] * 255, Options.Skins.Color.color2[1] * 255, Options.Skins.Color.color2[2] * 255, 255);
		if (Options.Skins.Color.Custom3)
			pKit->color3 = Color(Options.Skins.Color.color3[0] * 255, Options.Skins.Color.color3[1] * 255, Options.Skins.Color.color3[2] * 255, 255);
	}
	else if (Options.Skins.KnifeSelect == 5)
	{
		auto pKit = GetPaintKitDefinition(GetItemSchema() + 4, Options.Skins.KnifeIDm);
		if (Options.Skins.Color.Custom0)
			pKit->color0 = Color(Options.Skins.Color.color0[0] * 255, Options.Skins.Color.color0[1] * 255, Options.Skins.Color.color0[2] * 255, 255);
		if (Options.Skins.Color.Custom1)
			pKit->color1 = Color(Options.Skins.Color.color1[0] * 255, Options.Skins.Color.color1[1] * 255, Options.Skins.Color.color1[2] * 255, 255);
		if (Options.Skins.Color.Custom2)
			pKit->color2 = Color(Options.Skins.Color.color2[0] * 255, Options.Skins.Color.color2[1] * 255, Options.Skins.Color.color2[2] * 255, 255);
		if (Options.Skins.Color.Custom3)
			pKit->color3 = Color(Options.Skins.Color.color3[0] * 255, Options.Skins.Color.color3[1] * 255, Options.Skins.Color.color3[2] * 255, 255);
	}
	else if (Options.Skins.KnifeSelect == 6)
	{
		auto pKit = GetPaintKitDefinition(GetItemSchema() + 4, Options.Skins.KnifeIDh);
		if (Options.Skins.Color.Custom0)
			pKit->color0 = Color(Options.Skins.Color.color0[0] * 255, Options.Skins.Color.color0[1] * 255, Options.Skins.Color.color0[2] * 255, 255);
		if (Options.Skins.Color.Custom1)
			pKit->color1 = Color(Options.Skins.Color.color1[0] * 255, Options.Skins.Color.color1[1] * 255, Options.Skins.Color.color1[2] * 255, 255);
		if (Options.Skins.Color.Custom2)
			pKit->color2 = Color(Options.Skins.Color.color2[0] * 255, Options.Skins.Color.color2[1] * 255, Options.Skins.Color.color2[2] * 255, 255);
		if (Options.Skins.Color.Custom3)
			pKit->color3 = Color(Options.Skins.Color.color3[0] * 255, Options.Skins.Color.color3[1] * 255, Options.Skins.Color.color3[2] * 255, 255);
	}
	else if (Options.Skins.KnifeSelect == 7)
	{
		auto pKit = GetPaintKitDefinition(GetItemSchema() + 4, Options.Skins.KnifeIDbutter);
		if (Options.Skins.Color.Custom0)
			pKit->color0 = Color(Options.Skins.Color.color0[0] * 255, Options.Skins.Color.color0[1] * 255, Options.Skins.Color.color0[2] * 255, 255);
		if (Options.Skins.Color.Custom1)
			pKit->color1 = Color(Options.Skins.Color.color1[0] * 255, Options.Skins.Color.color1[1] * 255, Options.Skins.Color.color1[2] * 255, 255);
		if (Options.Skins.Color.Custom2)
			pKit->color2 = Color(Options.Skins.Color.color2[0] * 255, Options.Skins.Color.color2[1] * 255, Options.Skins.Color.color2[2] * 255, 255);
		if (Options.Skins.Color.Custom3)
			pKit->color3 = Color(Options.Skins.Color.color3[0] * 255, Options.Skins.Color.color3[1] * 255, Options.Skins.Color.color3[2] * 255, 255);
	}
	else if (Options.Skins.KnifeSelect == 8)
	{
		auto pKit = GetPaintKitDefinition(GetItemSchema() + 4, Options.Skins.KnifeIDfal);
		if (Options.Skins.Color.Custom0)
			pKit->color0 = Color(Options.Skins.Color.color0[0] * 255, Options.Skins.Color.color0[1] * 255, Options.Skins.Color.color0[2] * 255, 255);
		if (Options.Skins.Color.Custom1)
			pKit->color1 = Color(Options.Skins.Color.color1[0] * 255, Options.Skins.Color.color1[1] * 255, Options.Skins.Color.color1[2] * 255, 255);
		if (Options.Skins.Color.Custom2)
			pKit->color2 = Color(Options.Skins.Color.color2[0] * 255, Options.Skins.Color.color2[1] * 255, Options.Skins.Color.color2[2] * 255, 255);
		if (Options.Skins.Color.Custom3)
			pKit->color3 = Color(Options.Skins.Color.color3[0] * 255, Options.Skins.Color.color3[1] * 255, Options.Skins.Color.color3[2] * 255, 255);
	}
	else if (Options.Skins.KnifeSelect == 9)
	{
		auto pKit = GetPaintKitDefinition(GetItemSchema() + 4, Options.Skins.KnifeIDdag);
		if (Options.Skins.Color.Custom0)
			pKit->color0 = Color(Options.Skins.Color.color0[0] * 255, Options.Skins.Color.color0[1] * 255, Options.Skins.Color.color0[2] * 255, 255);
		if (Options.Skins.Color.Custom1)
			pKit->color1 = Color(Options.Skins.Color.color1[0] * 255, Options.Skins.Color.color1[1] * 255, Options.Skins.Color.color1[2] * 255, 255);
		if (Options.Skins.Color.Custom2)
			pKit->color2 = Color(Options.Skins.Color.color2[0] * 255, Options.Skins.Color.color2[1] * 255, Options.Skins.Color.color2[2] * 255, 255);
		if (Options.Skins.Color.Custom3)
			pKit->color3 = Color(Options.Skins.Color.color3[0] * 255, Options.Skins.Color.color3[1] * 255, Options.Skins.Color.color3[2] * 255, 255);
	}
	else if (Options.Skins.KnifeSelect == 10)
	{
		auto pKit = GetPaintKitDefinition(GetItemSchema() + 4, Options.Skins.KnifeIDbow);
		if (Options.Skins.Color.Custom0)
			pKit->color0 = Color(Options.Skins.Color.color0[0] * 255, Options.Skins.Color.color0[1] * 255, Options.Skins.Color.color0[2] * 255, 255);
		if (Options.Skins.Color.Custom1)
			pKit->color1 = Color(Options.Skins.Color.color1[0] * 255, Options.Skins.Color.color1[1] * 255, Options.Skins.Color.color1[2] * 255, 255);
		if (Options.Skins.Color.Custom2)
			pKit->color2 = Color(Options.Skins.Color.color2[0] * 255, Options.Skins.Color.color2[1] * 255, Options.Skins.Color.color2[2] * 255, 255);
		if (Options.Skins.Color.Custom3)
			pKit->color3 = Color(Options.Skins.Color.color3[0] * 255, Options.Skins.Color.color3[1] * 255, Options.Skins.Color.color3[2] * 255, 255);
	}
		if (Options.Skins.KnifeSelect == 1)
		{
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.ViewModelIndex) = nBayonet;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.WorldModelIndex) = nBayonet + 1;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iItemDefinitionIndex) = 500;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.KnifeIDb;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 3;

			if (Options.Skins.NEnabled)
			{
				sprintf_s(reinterpret_cast<char*>(DWORD(pWeapon) + offsets.m_szCustomName), 32, "%s", Options.Skins.buf);
			}
		}
		else if (Options.Skins.KnifeSelect == 2)
		{
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.ViewModelIndex) = nFlip;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.WorldModelIndex) = nFlip + 1;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iItemDefinitionIndex) = 505;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.KnifeIDf;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 3;
			if (Options.Skins.NEnabled)
			{
				sprintf_s(reinterpret_cast<char*>(DWORD(pWeapon) + offsets.m_szCustomName), 32, "%s", Options.Skins.buf);
			}
		}
		else if (Options.Skins.KnifeSelect == 3)
		{
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.ViewModelIndex) = nGut;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.WorldModelIndex) = nGut + 1;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iItemDefinitionIndex) = 506;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.KnifeIDg;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 3;
			if (Options.Skins.NEnabled)
			{
				sprintf_s(reinterpret_cast<char*>(DWORD(pWeapon) + offsets.m_szCustomName), 32, "%s", Options.Skins.buf);
			}
		}
		else if (Options.Skins.KnifeSelect == 4)
		{
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.ViewModelIndex) = nKarambit;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.WorldModelIndex) = nKarambit + 1;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iItemDefinitionIndex) = 507;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.KnifeIDk;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 3;
			if (Options.Skins.NEnabled)
			{
				sprintf_s(reinterpret_cast<char*>(DWORD(pWeapon) + offsets.m_szCustomName), 32, "%s", Options.Skins.buf);
			}
		}
		else if (Options.Skins.KnifeSelect == 5)
		{
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.ViewModelIndex) = nM9Bayonet;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.WorldModelIndex) = nM9Bayonet + 1;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iItemDefinitionIndex) = 508;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.KnifeIDm;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 3;
			if (Options.Skins.NEnabled)
			{
				sprintf_s(reinterpret_cast<char*>(DWORD(pWeapon) + offsets.m_szCustomName), 32, "%s", Options.Skins.buf);
			}
		}
		else if (Options.Skins.KnifeSelect == 6)
		{
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.ViewModelIndex) = nHuntsman;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.WorldModelIndex) = nHuntsman + 1;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iItemDefinitionIndex) = 509;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.KnifeIDh;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 3;
			if (Options.Skins.NEnabled)
			{
				sprintf_s(reinterpret_cast<char*>(DWORD(pWeapon) + offsets.m_szCustomName), 32, "%s", Options.Skins.buf);
			}
		}
		else if (Options.Skins.KnifeSelect == 7)
		{
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.ViewModelIndex) = nButterfly;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.WorldModelIndex) = nButterfly + 1;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iItemDefinitionIndex) = 515;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.KnifeIDbutter;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 3;
			if (Options.Skins.NEnabled)
			{
				sprintf_s(reinterpret_cast<char*>(DWORD(pWeapon) + offsets.m_szCustomName), 32, "%s", Options.Skins.buf);
			}
		}
		else if (Options.Skins.KnifeSelect == 8)
		{
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.ViewModelIndex) = nFalchion;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.WorldModelIndex) = nFalchion + 1;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iItemDefinitionIndex) = 512;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.KnifeIDfal;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 3;
			if (Options.Skins.NEnabled)
			{
				sprintf_s(reinterpret_cast<char*>(DWORD(pWeapon) + offsets.m_szCustomName), 32, "%s", Options.Skins.buf);
			}
		}
		else if (Options.Skins.KnifeSelect == 9)
		{
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.ViewModelIndex) = nDagger;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.WorldModelIndex) = nDagger + 1;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iItemDefinitionIndex) = 516;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.KnifeIDdag;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 3;
			if (Options.Skins.NEnabled)
			{
				sprintf_s(reinterpret_cast<char*>(DWORD(pWeapon) + offsets.m_szCustomName), 32, "%s", Options.Skins.buf);
			}
		}
		else if (Options.Skins.KnifeSelect == 10)
		{
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.ViewModelIndex) = nBowie;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.WorldModelIndex) = nBowie + 1;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iItemDefinitionIndex) = 514;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.KnifeIDbow;
			*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 3;
			if (Options.Skins.NEnabled)
			{
				sprintf_s(reinterpret_cast<char*>(DWORD(pWeapon) + offsets.m_szCustomName), 32, "%s", Options.Skins.buf);
			}
		}
}


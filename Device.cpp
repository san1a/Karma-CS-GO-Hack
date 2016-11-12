#include "SDK.h"
#include "Globals.h"
#include "Config.h"
#include "IRC.h"
#include "Accessors.h"

extern IMGUI_API LRESULT ImGui_ImplDX9_WndProcHandler(HWND, UINT msg, WPARAM wParam, LPARAM lParam);
bool CurKey[256] = {};
void GUI_Init(IDirect3DDevice9* pDevice);
tReset oResetScene;
tEndScene oEndScene;
cOptions Options;
LRESULT __stdcall Game::hkdWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//Captures the keys states
	auto& io = ImGui::GetIO();
	switch (uMsg)
	{

	case WM_LBUTTONDOWN:
		CurKey[VK_LBUTTON] = true;
		break;
	case WM_LBUTTONUP:
		CurKey[VK_LBUTTON] = false;
		break;
	case WM_RBUTTONDOWN:
		CurKey[VK_RBUTTON] = true;
		break;
	case WM_RBUTTONUP:
		CurKey[VK_RBUTTON] = false;
		break;
	case WM_KEYDOWN:
		CurKey[wParam] = true;
		break;
	case WM_KEYUP:
		CurKey[wParam] = false;
		break;
	case WM_MOUSEMOVE:
		io.MousePos.x = static_cast<signed short>(lParam);
		io.MousePos.y = static_cast<signed short>(lParam >> 16);
		break;
	default: break;
	}
	{
		static auto isDown = false;
		static auto isClicked = false;
		if (CurKey[VK_INSERT])
		{
			isClicked = false;
			isDown = true;
		}
		else if (!CurKey[VK_INSERT] && isDown)
		{
			isClicked = true;
			isDown = false;
		}
		else
		{
			isClicked = false;
			isDown = false;
		}
		if (isClicked)
		{
			Options.Menu.Opened = !Options.Menu.Opened;

			static auto cl_mouseenable = Cvar->FindVar(XorStr("cl_mouseenable"));

			cl_mouseenable->SetValue(!Options.Menu.Opened);

		}

	}
	if (Global::Init && Options.Menu.Opened && ImGui_ImplDX9_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;
	return CallWindowProc(Global::oWndProc, hWnd, uMsg, wParam, lParam);
}

#pragma region Arrays
const char* ChamsType[] =
{
	"Flat",
	"Textured"
};
const char* Keys[] =
{
	"",
	"Mouse 1",
	"Mouse 2",
	"Cancel",
	"Middle Mouse",
	"Mouse 4",
	"Mouse 5",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",

};
const char* Filter[] = 
{
	"None",
	"Most Damage",
	"Body Only",
	"No Arms or Head",
	"Head Only",
	"Arms Only"
};

const char* Bones[] =
{
	"Pelvis",
	"Lower Body",
	"Crotch",
	"Stomach",
	"Chest",
	"Neck",
	"Head"
};

const char* Knifes[] =
{
	"No Knife",
	"Bayonet",
	"Flip Knife",
	"Gut Knife",
	"Karambit",
	"M9 Bayonet",
	"Huntsman Knife",
	"Butterfly Knife",
	"Falchion Knife",
	"Shadow Daggers",
	"Bowie Knife"
};
#pragma endregion 


HRESULT __stdcall Game::hkdEndScene(IDirect3DDevice9* pDevice)
{
	
	if (!Global::Init)
		GUI_Init(pDevice);
	else
	{
		
		if (Engine->IsInGame() && Engine->IsConnected())
			ImGui::GetIO().MouseDrawCursor = Options.Menu.Opened;
		else
			ImGui::GetIO().MouseDrawCursor = true;
		ImGui_ImplDX9_NewFrame();
		ImVec2 Pos;
		if (Options.Menu.Opened)
		{

			ImGui::Begin(XorStr("Karma - CSGO"), &Options.Menu.Opened, ImVec2(400, 500), 1.f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
			{
				Pos = ImGui::GetWindowPos();
				if (ImGui::CollapsingHeader(XorStr("RageBot")))
				{
					ImGui::Text(XorStr("Ragebot"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Ragebot"), &Options.Rage.Aimbot.Enabled);
					ImGui::Combo(XorStr("HitBox"), &Options.Rage.Aimbot.Hitbox, Bones, ARRAYSIZE(Bones));
					ImGui::Combo(XorStr("AutoWall"), &Options.Rage.AutoWall.AutowallType, XorStr("Un-Invasive\0Invasive\0"));
					ImGui::Combo(XorStr("HitScans"), &Options.Rage.Aimbot.HitScans, XorStr("Aim At Bones\0HitScan-MultiPoint\0HitScan Hitboxs\0Hitscan-Extreme\0Custom-Hitscans\0"));
					ImGui::Combo(XorStr("Targeting"), &Options.Rage.Aimbot.Targeting, XorStr("FOV\0Healt h\0Distance\0First-Valid\0NextShot(Broken)\0Threat\0Visible Bones\0Damage\0"));
					ImGui::Combo(XorStr("StopType"), &Options.Rage.Aimbot.StopType, XorStr("None\0Stop\0StopCrouch\0Full-Stop\0Full-StopCrouch\0"));
					ImGui::SliderFloat(XorStr("Min-Damage"), &Options.Rage.AutoWall.MinDamage, 1.f, 100.f);
					ImGui::Checkbox(XorStr("Auto-Shoot"), &Options.Rage.Aimbot.AutoShoot);
					ImGui::Checkbox(XorStr("1Tap mode"), &Options.Rage.Aimbot.AS1tap);
					ImGui::Checkbox(XorStr("AutoScope"), &Options.Rage.Aimbot.AutoScope);
					ImGui::Checkbox(XorStr("Enemy Only"), &Options.Rage.Aimbot.EnemyOnly);
					ImGui::Checkbox(XorStr("Hitchance"), &Options.Rage.Aimbot.bHitchance);
					ImGui::Checkbox(XorStr("Hitchance Snipers"), &Options.Rage.Aimbot.bHitchanceSnipers);
					ImGui::Checkbox(XorStr("Psuedo Nospread(!)"), &Options.Rage.Aimbot.PsuedoSpread);
					ImGui::Checkbox(XorStr("pSilent(Turn off Wepconfigs)"), &Options.Legit.Aimbot.PerfectSilentAim);
					ImGui::Checkbox(XorStr("SilentAim"), &Options.Rage.Aimbot.SilentAim);
					ImGui::SliderFloat(XorStr("HitChance"), &Options.Rage.Aimbot.Hitchance, 1.f, 100.f);
					ImGui::Checkbox(XorStr("AimSmart"), &Options.Rage.Aimbot.AimSmart);
					ImGui::SameLine();
					ImGui::InputInt(XorStr("Smart Shots"), &Options.Rage.Aimbot.iSmartShots);
					ImGui::Text(XorStr("AA"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Anti-Aims"), &Options.Rage.AntiAim.Enabled);
					ImGui::Combo(XorStr("Pitch"), &Options.Rage.AntiAim.Pitch, XorStr("None\0Emotion\0Hide\0"));
					ImGui::Combo(XorStr("Yaw"), &Options.Rage.AntiAim.Yaw, XorStr("None\0F-Jitter\0Back-Jitter-Target\0Element\0F-Staic\0Back-Target\0Fire-Object\0"));
					if (ImGui::Button(XorStr("PlayerList"))) Options.Menu.PlayerList ^= 1;
					if (ImGui::Button(XorStr("Custom Hitscans"))) Options.Menu.HitScans ^= 1;
				}
				if (ImGui::CollapsingHeader(XorStr("Legitbot")))
				{
					bool lCheck = Options.AntiCheat.FACEIT;

					ImGui::Text(XorStr("Aimbot"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("LegitBot"), &Options.Legit.Aimbot.Enabled);
					if (!lCheck)
					{
						ImGui::Checkbox(XorStr("SilentAim"), &Options.Legit.Aimbot.SilentAim);
						ImGui::Checkbox(XorStr("RCS"), &Options.Legit.Aimbot.RCS);
						ImGui::SliderFloat(XorStr("FOV"), &Options.Legit.Aimbot.Fov, 0.f, 180.f, "%.1f");
					}
					if (lCheck)
					{
						ImGui::SliderInt(XorStr("League FOV"), &Options.Legit.Aimbot.LFOV, 1, 180);
						ImGui::SliderInt(XorStr("Aim Speed"), &Options.Legit.Aimbot.AimSpeed, 1, 300);
						ImGui::SliderInt(XorStr("Multiply Speed"), &Options.Legit.Aimbot.MultiplySpeed, 1, 10);
						ImGui::SliderInt(XorStr("FOV Boost"), &Options.Legit.Aimbot.FOVBOOST, 1, 10);
					}
					if (!lCheck)
					{
						ImGui::SliderFloat(XorStr("Smooth X"), &Options.Legit.Aimbot.Smooth[0], 1.f, 100.f, "%.1f");
						ImGui::SliderFloat(XorStr("Smooth Y"), &Options.Legit.Aimbot.Smooth[1], 1.f, 100.f, "%.1f");
					}
					ImGui::Combo(XorStr("Bone"), &Options.Legit.Aimbot.Bone, Bones, ARRAYSIZE(Bones));
					ImGui::Checkbox(XorStr("Enemy Only"), &Options.Legit.Aimbot.EnemyOnly);
				}
				if (ImGui::CollapsingHeader(XorStr("Visuals")))
				{
					ImGui::Text(XorStr("ESP"));
					ImGui::Separator();
				    ImGui::Checkbox(XorStr("ESP"), &Options.Visuals.ESP.Enabled);
					ImGui::Checkbox(XorStr("Visualize Aim Point"), &Options.Visuals.ESP.AimPoint);
					ImGui::Checkbox(XorStr("Enemy-Only"), &Options.Visuals.ESP.EnemyOnly); // ??
					ImGui::Combo(XorStr("Visual Detection"), &Options.Visuals.ESP.IsVisible, XorStr("Basic\0Advanced\0"));
					ImGui::Checkbox(XorStr("Visual Only"), &Options.Visuals.ESP.bVisibleOnly);
					ImGui::Checkbox(XorStr("Box"), &Options.Visuals.ESP.Box);
					ImGui::Checkbox(XorStr("Health"), &Options.Visuals.ESP.Health);
					ImGui::Checkbox(XorStr("Name"), &Options.Visuals.ESP.Name);
					ImGui::Checkbox(XorStr("Weapon"), &Options.Visuals.ESP.Weapon);
					ImGui::Checkbox(XorStr("Bone"), &Options.Visuals.ESP.Bone);
					ImGui::Checkbox(XorStr("Barrel"), &Options.Visuals.ESP.Barrel);
					ImGui::Checkbox(XorStr("ThirdPerson"), &Options.Visuals.ESP.ThirdPerson);
					ImGui::Checkbox(XorStr("Hitmarker"), &Options.Visuals.ESP.Hitmarker);
					ImGui::Checkbox(XorStr("Recoil Crosshair"), &Options.Visuals.ESP.RecoilCrosshair);
					ImGui::Checkbox(XorStr("Auto Accept"), &Options.Visuals.ESP.AutoAccept);
					ImGui::Checkbox(XorStr("Rank"), &Options.Visuals.ESP.RankESP);
					ImGui::Checkbox(XorStr("Location Spam"), &Options.Visuals.ESP.LocationSpam);
					ImGui::SliderInt(XorStr("Debug FOV"), &Options.Visuals.ESP.FOV, 0, 40);
					ImGui::Text(XorStr("Chams"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Chams"), &Options.Visuals.Chams.Enabled);
					ImGui::Combo(XorStr("Type"), &Options.Visuals.Chams.Mode, ChamsType, ARRAYSIZE(ChamsType));
					ImGui::Checkbox(XorStr("XQZ"), &Options.Visuals.Chams.XQZ);
					ImGui::Text(XorStr("DLights"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Lights"), &Options.Visuals.ESP.DLight);
					ImGui::SliderInt(XorStr("Multiply Light"), &Options.Visuals.ESP.DLightRadius, 1, 10);
				}
				if (ImGui::CollapsingHeader(XorStr("Player Mods")))
				{
					ImGui::Text(XorStr("Jump"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("BHOP"), &Options.PlayerMods.bhop.Enabled);
					ImGui::Checkbox(XorStr("AutoStrafe"), &Options.PlayerMods.AutoStrafe.Enabled);
					ImGui::SameLine();
					ImGui::Checkbox(XorStr("Silent"), &Options.PlayerMods.AutoStrafe.Silent);
					ImGui::Text(XorStr("Command Forcing"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("AirStuck"), &Options.PlayerMods.AirStuck.Enabled);
					ImGui::Combo(XorStr("Airstuck Key"), &Options.PlayerMods.AirStuck.Key, Keys, ARRAYSIZE(Keys));
					ImGui::Text(XorStr("FakeLag"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Fakelag"), &Options.PlayerMods.FakeLag.Enabled);
					ImGui::InputInt(XorStr("Send"), &Options.PlayerMods.FakeLag.Send);
					ImGui::InputInt(XorStr("Choke"), &Options.PlayerMods.FakeLag.Choke);

				}
				if (ImGui::CollapsingHeader(XorStr("Removals")))
				{
					ImGui::Text(XorStr("PlayerRemovals"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("No-Hands"), &Options.Visuals.Removals.Hands);
					ImGui::Checkbox(XorStr("WireFrame Hands"), &Options.Visuals.Removals.WireframeHands);
					ImGui::Checkbox(XorStr("No-Weapon"), &Options.Visuals.Removals.Weapon);
					ImGui::Checkbox(XorStr("WireFrame Weapons"), &Options.Visuals.Removals.WireframeWep);
					ImGui::Checkbox(XorStr("No Vis Recoil"), &Options.Visuals.Removals.VisualRecoil);
					ImGui::Checkbox(XorStr("No Recoil"), &Options.Visuals.Removals.Recoil);
					ImGui::Checkbox(XorStr("No-Flash"), &Options.Visuals.Removals.Flash);
				}
				if (ImGui::CollapsingHeader(XorStr("Trigger")))
				{
					ImGui::Text(XorStr("TriggerBot"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("TriggerBot"), &Options.Legit.Trigger.Enabled);
					ImGui::Combo(XorStr("Key"), &Options.Legit.Trigger.Key, Keys, ARRAYSIZE(Keys));
					ImGui::Checkbox(XorStr("EnemyOnly"), &Options.Legit.Trigger.TriggerFriends);
					ImGui::Combo(XorStr("Filter"), &Options.Legit.Trigger.Filter, Filter, ARRAYSIZE(Filter));
					ImGui::InputInt(XorStr("Delay"), &Options.Legit.Trigger.Delay);

				}
				if (ImGui::CollapsingHeader(XorStr("Visual Colors")))
				{
					ImGui::Text(XorStr("Cham Color"));
					ImGui::Separator();
					ImGui::ColorEdit3(XorStr("Chams Enemy"), Options.Visuals.Chams.EnemyColor);
					ImGui::ColorEdit3(XorStr("Chams Enemy NonVis"), Options.Visuals.Chams.EnemyColorWall);
					ImGui::ColorEdit3(XorStr("Chams Team"), Options.Visuals.Chams.TeamColor);
					ImGui::ColorEdit3(XorStr("Chams Team NonVis"), Options.Visuals.Chams.TeamColorWall);
					ImGui::Text(XorStr("ESP Color"));
					ImGui::Separator();
					ImGui::ColorEdit3(XorStr("ESP Enemy"), Options.Visuals.ESP.EnemyColor);
					ImGui::ColorEdit3(XorStr("ESP Enemy NonVis"), Options.Visuals.ESP.EnemyColorWall);
					ImGui::ColorEdit3(XorStr("ESP Team"), Options.Visuals.ESP.TeamColor);
					ImGui::ColorEdit3(XorStr("ESP Team NonVis"), Options.Visuals.ESP.TeamColorWall);
				}
				if (ImGui::CollapsingHeader(XorStr("Anti-Anti-Cheats")))
				{
					ImGui::Checkbox(XorStr("Match-Making(UNTRUSTED)"), &Options.AntiCheat.MM);
					ImGui::Checkbox(XorStr("Source Mod Anti-Cheat(SMAC)"), &Options.AntiCheat.SMAC);
					ImGui::Checkbox(XorStr("FACEIT Anti-Cheat"), &Options.AntiCheat.FACEIT);
					ImGui::Checkbox(XorStr("Cyber-Evolution Anti-Cheat(CEVO)"), &Options.AntiCheat.CEVO);
					ImGui::Checkbox(XorStr("Valve Anti-Cheat(VAC)"), &Options.AntiCheat.VAC);
					ImGui::Checkbox(XorStr("E-Sports Entertainment Association(ESEA)"), &Options.AntiCheat.ESEA);
				}
			}
			if (ImGui::CollapsingHeader(XorStr("Settings")))
			{
				if (ImGui::Button(XorStr("Config Manager"))) Options.Menu.Configs ^= 1;
				if (ImGui::Button(XorStr("Skinchanger"))) Options.Menu.Skins ^= 1;
				ImGui::Text(XorStr("Weapon Settings"));
				ImGui::Separator();
				ImGui::Checkbox(XorStr("Weapon Configs"), &Options.Legit.Aimbot.WeaponConfigs);
				if (ImGui::Button(XorStr("Weapon-Configs"))) Options.Menu.WeaponConfigs ^= 1;
			}
			ImGui::Text(XorStr("FrameTime : %.3f ms/frame (%.1f FPS)"), 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			if (ImGui::Button(XorStr("Reflect-Injection"))) Options.Cheat.Uninject ^= 1;
			if (ImGui::Button(XorStr("Open IRC"))) Options.IRC.Enabled ^= 1;
			ImGui::End();

			if (Options.Menu.HitScans)
			{
				ImGui::Begin(XorStr("CHitscans"), &Options.Menu.HitScans, ImVec2(400, 400));
				ImGui::Text(XorStr("HitScan Options"));
				ImGui::Separator();
				ImGui::SliderInt(XorStr("MultiPoint"), &Options.Rage.Aimbot.Hitscan.Point, 0, 9);
				ImGui::CollapsingHeader(XorStr("HitBoxes"));
				{
					ImGui::Checkbox(XorStr("Head"), &Options.Rage.Aimbot.Hitscan.Head);
					ImGui::Checkbox(XorStr("Neck"), &Options.Rage.Aimbot.Hitscan.Neck);
					ImGui::Checkbox(XorStr("LowerNeck"), &Options.Rage.Aimbot.Hitscan.LowerNeck);
					ImGui::Checkbox(XorStr("Pelvis"), &Options.Rage.Aimbot.Hitscan.Pelvis);
					ImGui::Checkbox(XorStr("Body"), &Options.Rage.Aimbot.Hitscan.Body);
					ImGui::Checkbox(XorStr("Thorax"), &Options.Rage.Aimbot.Hitscan.Thorax);
					ImGui::Checkbox(XorStr("Chest"), &Options.Rage.Aimbot.Hitscan.Chest);
					ImGui::Checkbox(XorStr("UpperChest"), &Options.Rage.Aimbot.Hitscan.UpperChest);
					ImGui::Checkbox(XorStr("RightThigh"), &Options.Rage.Aimbot.Hitscan.RightThigh);
					ImGui::Checkbox(XorStr("LeftThigh"), &Options.Rage.Aimbot.Hitscan.LeftThigh);
					ImGui::Checkbox(XorStr("RightCalf"), &Options.Rage.Aimbot.Hitscan.RightCalf);
					ImGui::Checkbox(XorStr("LeftCalf"), &Options.Rage.Aimbot.Hitscan.LeftCalf);
					ImGui::Checkbox(XorStr("RightFoot"), &Options.Rage.Aimbot.Hitscan.RightFoot);
					ImGui::Checkbox(XorStr("LeftFoot"), &Options.Rage.Aimbot.Hitscan.LeftFoot);
					ImGui::Checkbox(XorStr("RightHand"), &Options.Rage.Aimbot.Hitscan.RightHand);
					ImGui::Checkbox(XorStr("LeftHand"), &Options.Rage.Aimbot.Hitscan.LeftHand);
					ImGui::Checkbox(XorStr("RightUpperArm"), &Options.Rage.Aimbot.Hitscan.RightUpperArm);
					ImGui::Checkbox(XorStr("RightForeArm"), &Options.Rage.Aimbot.Hitscan.RightForeArm);
					ImGui::Checkbox(XorStr("LeftUpperArm"), &Options.Rage.Aimbot.Hitscan.LeftUpperArm);
					ImGui::Checkbox(XorStr("LeftForeArm"), &Options.Rage.Aimbot.Hitscan.LeftForeArm);
					ImGui::Checkbox(XorStr("Max"), &Options.Rage.Aimbot.Hitscan.Max);
				}
				ImGui::End();

			}
			if (Options.Menu.Skins)
			{
				// Still WIP - 6/28/16
				ImGui::Begin(XorStr("Skin Changer (WIP)"), &Options.Menu.Skins, ImVec2(690, 408));
				ImGui::Checkbox(XorStr("Enabled"), &Options.Skins.Enabled);
				ImGui::Checkbox(XorStr("Enable Name Changer"), &Options.Skins.NEnabled);
				ImGui::Separator();
				if (Engine->IsInGame() && Engine->IsConnected() && Global::LocalPlayer->GetHealth() > 0)
				{
					auto pWeapon = Global::LocalPlayer->GetWeapon();
					if (pWeapon->GetWeaponID() == 1)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.deagle);
					}
					if (pWeapon->GetWeaponID() == 7)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.ak47);
					}
					if (pWeapon->GetWeaponID() == 8)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.aug);
					}
					if (pWeapon->GetWeaponID() == 9)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.awp);
					}
					if (pWeapon->GetWeaponID() == 26)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.bizon);
					}
					if (pWeapon->GetWeaponID() == 63)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.cz75);
					}
					if (pWeapon->GetWeaponID() == 2)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.elites);
					}
					if (pWeapon->GetWeaponID() == 10)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.famas);
					}
					if (pWeapon->GetWeaponID() == 3)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.fiveseven);
					}
					if (pWeapon->GetWeaponID() == 11)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.g3sg1);
					}
					if (pWeapon->GetWeaponID() == 13)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.galil);
					}
					if (pWeapon->GetWeaponID() == 4)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.glock);
					}
					if (pWeapon->GetWeaponID() == 14)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.m249);
					}
					if (pWeapon->GetWeaponID() == 60)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.m4a1s);
					}
					if (pWeapon->GetWeaponID() == 16)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.m4a4);
					}
					if (pWeapon->GetWeaponID() == 17)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.mac10);
					}
					if (pWeapon->GetWeaponID() == 27)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.mag7);
					}
					if (pWeapon->GetWeaponID() == 64)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.magnum);
					}
					if (pWeapon->GetWeaponID() == 33)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.mp7);
					}
					if (pWeapon->GetWeaponID() == 34)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.mp9);
					}
					if (pWeapon->GetWeaponID() == 28)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.negev);
					}
					if (pWeapon->GetWeaponID() == 35)
					{ 
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.nova);
					}
					if (pWeapon->GetWeaponID() == 32)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.p2000);
					}
					if (pWeapon->GetWeaponID() == 61)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.usps);
					}
					if (pWeapon->GetWeaponID() == 19)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.p90);
					}
					if (pWeapon->GetWeaponID() == 36)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.p250);
					}
					if (pWeapon->GetWeaponID() == 29)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.sawedoff);
					}
					if (pWeapon->GetWeaponID() == 38)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.scar20);
					}
					if (pWeapon->GetWeaponID() == 39)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.sg556);
					}
					if (pWeapon->GetWeaponID() == 40)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.ssg08);
					}
					if (pWeapon->GetWeaponID() == 30)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.tec9);
					}
					if (pWeapon->GetWeaponID() == 24)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.ump45);
					}
					if (pWeapon->GetWeaponID() == 25)
					{
						ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.xm1014);
					}
					ImGui::InputInt(XorStr("StatTrak Amount"), &Options.Skins.StatTrak);
					ImGui::Separator();
					ImGui::Combo(XorStr("Select a knife"), &Options.Skins.KnifeSelect, Knifes, ARRAYSIZE(Knifes));
					if (Options.Skins.KnifeSelect == 1)
						ImGui::InputInt(XorStr("Bayonet Paint"), &Options.Skins.KnifeIDb);
					if (Options.Skins.KnifeSelect == 2)
						ImGui::InputInt(XorStr("Flip Knife Paint"), &Options.Skins.KnifeIDf);
					if (Options.Skins.KnifeSelect == 3)
						ImGui::InputInt(XorStr("Gut Knife Paint"), &Options.Skins.KnifeIDg);
					if (Options.Skins.KnifeSelect == 4)
						ImGui::InputInt(XorStr("Karambit Paint"), &Options.Skins.KnifeIDk);
					if (Options.Skins.KnifeSelect == 5)
						ImGui::InputInt(XorStr("M9 Bayonet Paint"), &Options.Skins.KnifeIDm);
					if (Options.Skins.KnifeSelect == 6)
						ImGui::InputInt(XorStr("Huntsman Knife Paint"), &Options.Skins.KnifeIDh);
					if (Options.Skins.KnifeSelect == 7)
						ImGui::InputInt(XorStr("Butterfly Knife Paint"), &Options.Skins.KnifeIDb);
					if (Options.Skins.KnifeSelect == 8)
						ImGui::InputInt(XorStr("Falchion Knife Paint"), &Options.Skins.KnifeIDf);
					if (Options.Skins.KnifeSelect == 9)
						ImGui::InputInt(XorStr("Shadow Daggers Paint"), &Options.Skins.KnifeIDdag);
					if (Options.Skins.KnifeSelect == 10)
						ImGui::InputInt(XorStr("Bowie Knife Paint"), &Options.Skins.KnifeIDbow);
					static char KnifeBuf[64] = ""; ImGui::InputText(XorStr("KnifeName"), KnifeBuf, 64);
					Options.Skins.buf = KnifeBuf;
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Skin Color 0"), &Options.Skins.Color.Custom0);
					ImGui::ColorEdit3(XorStr("Color0"), Options.Skins.Color.color0);
					ImGui::Checkbox(XorStr("Skin Color 1"), &Options.Skins.Color.Custom1);
					ImGui::ColorEdit3(XorStr("Color1"), Options.Skins.Color.color1);
					ImGui::Checkbox(XorStr("Skin Color 2"), &Options.Skins.Color.Custom2);
					ImGui::ColorEdit3(XorStr("Color2"), Options.Skins.Color.color2);
					ImGui::Checkbox(XorStr("Skin Color 3"), &Options.Skins.Color.Custom3);
					ImGui::ColorEdit3(XorStr("Color3"), Options.Skins.Color.color3);
					ImGui::Text(XorStr("HOME KEY = Apply Skins"));
				}
				else
				{
					if (Engine->IsInGame() && Engine->IsConnected() && !Global::LocalPlayer->GetHealth() > 0)
					{
						ImGui::Text(XorStr("You must be alive to change skins."));
					}
					else
					{
						ImGui::Text(XorStr("You must be ingame to change skins."));
					}
				}
				ImGui::End();
			}
			if (Options.Menu.Configs)
			{
				ImGui::Begin(XorStr("Configs"), &Options.Menu.Configs, ImVec2(200, 200));
				ImGui::Combo(XorStr("Config"), &Options.Config.Current, XorStr("Default\0Legit\0Rage\0League\0"));
				if (ImGui::Button(XorStr("Load-Config")))ConSys->LoadConfig();
				if (ImGui::Button(XorStr("Save-Config")))ConSys->SaveConfig();
				ImGui::End();
			}
			if(Options.Menu.WeaponConfigs)
			{
				bool lCheck = Options.AntiCheat.FACEIT;
				ImGui::Begin(XorStr("Weapon Config"),&Options.Menu.WeaponConfigs, ImVec2(400, 400),1.f);
				ImGui::Text(XorStr("Rifles"));
				ImGui::Separator();
				/*Rifles*/
				if (ImGui::CollapsingHeader(XorStr("Rifles")))
				{

					ImGui::Checkbox(XorStr("Rifle TriggerBot"), &Options.Legit.Aimbot.Configs.Rifles.Trigger);
					ImGui::Checkbox(XorStr("Rifle LegitBot"), &Options.Legit.Aimbot.Configs.Rifles.Enabled);
					if (!lCheck)
					{
						ImGui::Checkbox(XorStr("Rifle SilentAim"), &Options.Legit.Aimbot.Configs.Rifles.SilentAim);
						ImGui::Checkbox(XorStr("Rifle pSilentAim"), &Options.Legit.Aimbot.Configs.Rifles.PerfectSilentAim);
						ImGui::Checkbox(XorStr("Rifle RCS"), &Options.Legit.Aimbot.Configs.Rifles.RCS);
					}
					if (!lCheck)
					{   ImGui::SliderFloat(XorStr("Rifle FOV"), &Options.Legit.Aimbot.Configs.Rifles.Fov, 0.f, 180.f, "%.1f");
						ImGui::SliderFloat(XorStr("Rifle Smooth X"), &Options.Legit.Aimbot.Configs.Rifles.Smooth[0], 1.f, 100.f, "%.1f");
						ImGui::SliderFloat(XorStr("Rifle Smooth Y"), &Options.Legit.Aimbot.Configs.Rifles.Smooth[1], 1.f, 100.f, "%.1f");
					}
					ImGui::Combo(XorStr("Rifle Bone"), &Options.Legit.Aimbot.Configs.Rifles.Bone, Bones, ARRAYSIZE(Bones));
					if (lCheck)
					{
						ImGui::SliderInt(XorStr("Rifle League FOV"), &Options.Legit.Aimbot.Configs.Rifles.LFOV, 1, 300);
						ImGui::SliderInt(XorStr("Rifle Aim Speed"), &Options.Legit.Aimbot.Configs.Rifles.AimSpeed, 1, 300);
						ImGui::SliderInt(XorStr("Rifle Multiply Speed"), &Options.Legit.Aimbot.Configs.Rifles.MultiplySpeed, 1, 10);
						ImGui::SliderInt(XorStr("Rifle FOV Boost"), &Options.Legit.Aimbot.Configs.Rifles.FOVBOOST, 1, 10);
					}
				}
				ImGui::Text(XorStr("Pistols"));
				ImGui::Separator();
				/*Pistols*/
				if (ImGui::CollapsingHeader(XorStr("Pistols")))
				{
					ImGui::Checkbox(XorStr("Pistol TriggerBot"), &Options.Legit.Aimbot.Configs.Pistols.Trigger);
					ImGui::Checkbox(XorStr("Pistol LegitBot"), &Options.Legit.Aimbot.Configs.Pistols.Enabled);
					if (!lCheck)
					{
						ImGui::Checkbox(XorStr("Pistol SilentAim"), &Options.Legit.Aimbot.Configs.Pistols.SilentAim);
						ImGui::Checkbox(XorStr("Pistol pSilentAim"), &Options.Legit.Aimbot.Configs.Pistols.PerfectSilentAim);
						ImGui::Checkbox(XorStr("Pistol RCS"), &Options.Legit.Aimbot.Configs.Pistols.RCS);
					}
					if (!lCheck)
					{
						ImGui::SliderFloat(XorStr("Pistol FOV"), &Options.Legit.Aimbot.Configs.Pistols.Fov, 0.f, 180.f, "%.1f");
						ImGui::SliderFloat(XorStr("Pistol Smooth X"), &Options.Legit.Aimbot.Configs.Pistols.Smooth[0], 1.f, 100.f, "%.1f");
						ImGui::SliderFloat(XorStr("Pistol Smooth Y"), &Options.Legit.Aimbot.Configs.Pistols.Smooth[1], 1.f, 100.f, "%.1f");
					}
					ImGui::Combo(XorStr("Pistol Bone"), &Options.Legit.Aimbot.Configs.Pistols.Bone, Bones, ARRAYSIZE(Bones));
					if (lCheck)
					{
						ImGui::SliderInt(XorStr("Pistol League FOV"), &Options.Legit.Aimbot.Configs.Pistols.LFOV, 1, 300);
						ImGui::SliderInt(XorStr("Pistol Aim Speed"), &Options.Legit.Aimbot.Configs.Pistols.AimSpeed, 1, 300);
						ImGui::SliderInt(XorStr("Pistol Multiply Speed"), &Options.Legit.Aimbot.Configs.Pistols.MultiplySpeed, 1, 10);
						ImGui::SliderInt(XorStr("Pistol FOV Boost"), &Options.Legit.Aimbot.Configs.Pistols.FOVBOOST, 1, 10);
					}
				}
				ImGui::Text(XorStr("Sniper"));
				ImGui::Separator();
				/*Snipers*/
				if (ImGui::CollapsingHeader(XorStr("Sniper")))
				{
					ImGui::Checkbox(XorStr("Sniper TriggerBot"), &Options.Legit.Aimbot.Configs.Snipers.Trigger);
					ImGui::Checkbox(XorStr("Sniper LegitBot"), &Options.Legit.Aimbot.Configs.Snipers.Enabled);
					if (!lCheck)
					{
						ImGui::Checkbox(XorStr("Sniper SilentAim"), &Options.Legit.Aimbot.Configs.Snipers.SilentAim);
						ImGui::Checkbox(XorStr("Sniper pSilentAim"), &Options.Legit.Aimbot.Configs.Snipers.PerfectSilentAim);
						ImGui::Checkbox(XorStr("Sniper RCS"), &Options.Legit.Aimbot.Configs.Snipers.RCS);
					}
					if (!lCheck)
					{
						ImGui::SliderFloat(XorStr("Sniper FOV"), &Options.Legit.Aimbot.Configs.Snipers.Fov, 0.f, 180.f, "%.1f");
						ImGui::SliderFloat(XorStr("Sniper Smooth X"), &Options.Legit.Aimbot.Configs.Snipers.Smooth[0], 1.f, 100.f, "%.1f");
						ImGui::SliderFloat(XorStr("Sniper Smooth Y"), &Options.Legit.Aimbot.Configs.Snipers.Smooth[1], 1.f, 100.f, "%.1f");
					}
					ImGui::Combo(XorStr("Sniper Bone"), &Options.Legit.Aimbot.Configs.Snipers.Bone, Bones, ARRAYSIZE(Bones));
					if (lCheck)
					{

						ImGui::SliderInt(XorStr("Sniper League FOV"), &Options.Legit.Aimbot.Configs.Snipers.LFOV, 1, 300);
						ImGui::SliderInt(XorStr("Sniper Aim Speed"), &Options.Legit.Aimbot.Configs.Snipers.AimSpeed, 1, 300);
						ImGui::SliderInt(XorStr("Sniper Multiply Speed"), &Options.Legit.Aimbot.Configs.Snipers.MultiplySpeed, 1, 10);
						ImGui::SliderInt(XorStr("Sniper FOV Boost"), &Options.Legit.Aimbot.Configs.Snipers.FOVBOOST, 1, 10);
					}
				}
				
					ImGui::Text(XorStr("Shotgun"));
					ImGui::Separator();
					/*Shotguns*/
				if (ImGui::CollapsingHeader(XorStr("Shotgun")))
				{
					ImGui::Checkbox(XorStr("Shotgun TriggerBot"), &Options.Legit.Aimbot.Configs.Shotguns.Trigger);
					ImGui::Checkbox(XorStr("Shotgun LegitBot"), &Options.Legit.Aimbot.Configs.Shotguns.Enabled);
					if (!lCheck)
					{
						ImGui::Checkbox(XorStr("Shotgun SilentAim"), &Options.Legit.Aimbot.Configs.Shotguns.SilentAim);
						ImGui::Checkbox(XorStr("Shotgun pSilentAim"), &Options.Legit.Aimbot.Configs.Shotguns.PerfectSilentAim);
						ImGui::Checkbox(XorStr("Shotgun RCS"), &Options.Legit.Aimbot.Configs.Shotguns.RCS);
					}
					if (!lCheck)
					{
						ImGui::SliderFloat(XorStr("Shotgun FOV"), &Options.Legit.Aimbot.Configs.Shotguns.Fov, 0.f, 180.f, "%.1f");
						ImGui::SliderFloat(XorStr("Shotgun Smooth X"), &Options.Legit.Aimbot.Configs.Shotguns.Smooth[0], 1.f, 100.f, "%.1f");
						ImGui::SliderFloat(XorStr("Shotgun Smooth Y"), &Options.Legit.Aimbot.Configs.Shotguns.Smooth[1], 1.f, 100.f, "%.1f");
					}
					ImGui::Combo(XorStr("Shotgun Bone"), &Options.Legit.Aimbot.Configs.Shotguns.Bone, Bones, ARRAYSIZE(Bones));
					if (lCheck)
					{


						ImGui::SliderInt(XorStr("Shotgun League FOV"), &Options.Legit.Aimbot.Configs.Shotguns.LFOV, 1, 300);
						ImGui::SliderInt(XorStr("ShotgunAim Speed"), &Options.Legit.Aimbot.Configs.Shotguns.AimSpeed, 1, 300);
						ImGui::SliderInt(XorStr("Shotgun Multiply Speed"), &Options.Legit.Aimbot.Configs.Shotguns.MultiplySpeed, 1, 10);
						ImGui::SliderInt(XorStr("Shotgun FOV Boost"), &Options.Legit.Aimbot.Configs.Shotguns.FOVBOOST, 1, 10);
					}
				}
					ImGui::Text(XorStr("Sub-Machine-Guns"));
					ImGui::Separator();
					/*SubMachineGuns*/
				if (ImGui::CollapsingHeader(XorStr("Sub-Machine-Guns")))
				{
					ImGui::Checkbox(XorStr("SMG TriggerBot"), &Options.Legit.Aimbot.Configs.SMGs.Trigger);
					ImGui::Checkbox(XorStr("SMG LegitBot"), &Options.Legit.Aimbot.Configs.SMGs.Enabled);
					if (!lCheck)
					{
						ImGui::Checkbox(XorStr("SMG SilentAim"), &Options.Legit.Aimbot.Configs.SMGs.SilentAim);
						ImGui::Checkbox(XorStr("SMG pSilentAim"), &Options.Legit.Aimbot.Configs.SMGs.PerfectSilentAim);
						ImGui::Checkbox(XorStr("SMG RCS"), &Options.Legit.Aimbot.Configs.SMGs.RCS);
					}
					if (!lCheck)
					{
						ImGui::SliderFloat(XorStr("SMG FOV"), &Options.Legit.Aimbot.Configs.SMGs.Fov, 0.f, 180.f, "%.1f");
						ImGui::SliderFloat(XorStr("SMG Smooth X"), &Options.Legit.Aimbot.Configs.SMGs.Smooth[0], 1.f, 100.f, "%.1f");
						ImGui::SliderFloat(XorStr("SMG Smooth Y"), &Options.Legit.Aimbot.Configs.SMGs.Smooth[1], 1.f, 100.f, "%.1f");
					}
					ImGui::Combo(XorStr("SMG Bone"), &Options.Legit.Aimbot.Configs.SMGs.Bone, Bones, ARRAYSIZE(Bones));
					if (lCheck)
					{

						ImGui::SliderInt(XorStr("SMG League FOV"), &Options.Legit.Aimbot.Configs.SMGs.LFOV, 1, 300);
						ImGui::SliderInt(XorStr("SMG Aim Speed"), &Options.Legit.Aimbot.Configs.SMGs.AimSpeed, 1, 300);
						ImGui::SliderInt(XorStr("SMG Multiply Speed"), &Options.Legit.Aimbot.Configs.SMGs.MultiplySpeed, 1, 10);
						ImGui::SliderInt(XorStr("SMG FOV Boost"), &Options.Legit.Aimbot.Configs.SMGs.FOVBOOST, 1, 10);
					}
				}
					ImGui::Text(XorStr("Machine-Guns"));
					ImGui::Separator();
					/*Machine Guns*/
			if (ImGui::CollapsingHeader(XorStr("Machine-Guns")))
				{
					ImGui::Checkbox(XorStr("MG TriggerBot"), &Options.Legit.Aimbot.Configs.Machineguns.Trigger);
					ImGui::Checkbox(XorStr("MG LegitBot"), &Options.Legit.Aimbot.Configs.Machineguns.Enabled);
					if (!lCheck)
					{
						ImGui::Checkbox(XorStr("MG SilentAim"), &Options.Legit.Aimbot.Configs.Machineguns.SilentAim);
						ImGui::Checkbox(XorStr("MG pSilentAim"), &Options.Legit.Aimbot.Configs.Machineguns.PerfectSilentAim);
						ImGui::Checkbox(XorStr("MG RCS"), &Options.Legit.Aimbot.Configs.Machineguns.RCS);
					}
					if (!lCheck)
					{
						ImGui::SliderFloat(XorStr("MG FOV"), &Options.Legit.Aimbot.Configs.Machineguns.Fov, 0.f, 180.f, "%.1f");
						ImGui::SliderFloat(XorStr("MG Smooth X"), &Options.Legit.Aimbot.Configs.Machineguns.Smooth[0], 1.f, 100.f, "%.1f");
						ImGui::SliderFloat(XorStr("MG Smooth Y"), &Options.Legit.Aimbot.Configs.Machineguns.Smooth[1], 1.f, 100.f, "%.1f");
					}
					ImGui::Combo(XorStr("MG Bone"), &Options.Legit.Aimbot.Configs.Machineguns.Bone, Bones, ARRAYSIZE(Bones));
					if (lCheck)
					{

						ImGui::SliderInt(XorStr("MG League FOV"), &Options.Legit.Aimbot.Configs.Machineguns.LFOV, 1, 300);
						ImGui::SliderInt(XorStr("MG Aim Speed"), &Options.Legit.Aimbot.Configs.Machineguns.AimSpeed, 1, 300);
						ImGui::SliderInt(XorStr("MG Multiply Speed"), &Options.Legit.Aimbot.Configs.Machineguns.MultiplySpeed, 1, 10);
						ImGui::SliderInt(XorStr("MG FOV Boost"), &Options.Legit.Aimbot.Configs.Machineguns.FOVBOOST, 1, 10);
					}
				}
			ImGui::End();
			}
			
		}
		if (Options.IRC.Enabled)
		{
			if (ImGui::Begin(XorStr("IRC"), &Options.IRC.Enabled,ImVec2(400,400)));
			{
				g_pIRC->Invoke();
			}
			ImGui::End();
		}
		if (Options.Menu.PlayerList)
		{
			static const char* team[4] = { "None","Spec","T","CT" };
			static const char* IsSpec[2] = { "No","Yes" };
			//ImGui::SetNextWindowSize(ImVec2(625, 400), ImGuiSetCond_Appearing);
			if (ImGui::Begin(XorStr("Player List"), &Options.Menu.PlayerList))
			{
				ImGui::Checkbox(XorStr("AntiAntiAim"), &Options.Rage.Aimbot.AntiAntiAim);
				ImGui::Checkbox(XorStr("More Info"), &Options.Menu.pList.MoreInfo); 
				ImGui::SameLine(); 
				ImGui::Checkbox(XorStr("Hide Enemy's"), &Options.Rage.Aimbot.AAA.Enemyonly);
				///ImGui::Combo(XorStr("AAA Type"), &Options.Rage.Aimbot.AAA.ResolverType, XorStr("None\0Dynamic\0"));
				if (Options.Menu.pList.MoreInfo && !Options.Rage.Aimbot.AAA.Enemyonly)
				ImGui::Columns(11, "PlayerList");
				else if (Options.Menu.pList.MoreInfo && Options.Rage.Aimbot.AAA.Enemyonly)
					ImGui::Columns(10, "PlayerList");
				else if (!Options.Menu.pList.MoreInfo && Options.Rage.Aimbot.AAA.Enemyonly)
					ImGui::Columns(6, "PlayerList");
				else if (!Options.Menu.pList.MoreInfo && !Options.Rage.Aimbot.AAA.Enemyonly)
					ImGui::Columns(7, "PlayerList");
				ImGui::Separator();
				ImGui::Text(XorStr("Name"));                 ImGui::NextColumn();
				if (!Options.Rage.Aimbot.AAA.Enemyonly)
				{
					ImGui::Text(XorStr("Team"));                 ImGui::NextColumn();
				}
				if (Options.Menu.pList.MoreInfo)
				{
					ImGui::Text(XorStr("Index"));                ImGui::NextColumn();
					ImGui::Text(XorStr("Spectating Player"));    ImGui::NextColumn();
					ImGui::Text(XorStr("Pitch"));                ImGui::NextColumn();
					ImGui::Text(XorStr("Yaw"));                  ImGui::NextColumn();
				}
				ImGui::Text(XorStr("Custom Yaw Resolve"));   ImGui::NextColumn();
				ImGui::Text(XorStr("Custom Pitch Resolve")); ImGui::NextColumn();
				ImGui::Text(XorStr("Bone Correction")); ImGui::NextColumn();
				ImGui::Text(XorStr("Anti-Aimbot Correction")); ImGui::NextColumn();
				ImGui::Text(XorStr("Disable Head")); ImGui::NextColumn();
				ImGui::Separator();
				if (Engine->IsInGame() && Engine->IsConnected())
				{
					for (auto i = 0; i < ClientEntList->GetHighestEntityIndex(); i++)
					{
						auto plClient = ClientEntList->GetClientEntity(i);
						player_info_t plInfo;
						if (plClient == Global::LocalPlayer)
							continue;
					
						if (plClient && Engine->GetPlayerInfo(i, &plInfo))
						{
							if (Options.Rage.Aimbot.AAA.Enemyonly)
							{
								if (plClient->GetTeam() == Global::LocalPlayer->GetTeam())
									continue;
								if (plClient->GetTeam() == 1 || plClient->GetTeam() == 0)
									continue;
							}
							ImGui::Text(plInfo.name);
							ImGui::NextColumn();
							bool bIsSpec = 0;
							DWORD hSpecTarget;
							auto iTeamNum = plClient->GetTeam();
							if ((!Options.Rage.Aimbot.AAA.Enemyonly))
							{
								if (iTeamNum == 1)
								{
									hSpecTarget = *reinterpret_cast<DWORD*>(reinterpret_cast<DWORD>(plClient) + offsets.m_hObserverTarget);
									if (hSpecTarget)
										bIsSpec = ClientEntList->GetClientEntityFromHandle(hSpecTarget) == Global::LocalPlayer;
								}
							}
							auto oAngle = Options.Rage.Aimbot.AAA.oAngle[i];
							if (iTeamNum > 3) 
								iTeamNum = 0;

							
							if (!Options.Rage.Aimbot.AAA.Enemyonly)
							{
								ImGui::Text(team[iTeamNum]);              
								ImGui::NextColumn();
							}
							if (Options.Menu.pList.MoreInfo)
							{
								ImGui::Text("%i", i);                     ImGui::NextColumn();
								ImGui::Text(IsSpec[bIsSpec]);             ImGui::NextColumn();
								ImGui::Text("%.3f", oAngle.x);            ImGui::NextColumn();
								ImGui::Text("%.3f", oAngle.y);            ImGui::NextColumn();
							}// these only display if mor info
							char Yaw[255] = ""; char Pitch[255] = ""; char Bone[255] = ""; char Lisp[255] = ""; char Head[255] = "";
							sprintf(Yaw, "%s %s", plInfo.name, "Yaw");
							ImGui::InputFloat(Yaw, &Options.Rage.Aimbot.AAA.CAngle[i].y);
							ImGui::NextColumn();//yaw
							sprintf(Pitch, "%s %s", plInfo.name, "Pitch");
							ImGui::InputFloat(Pitch, &Options.Rage.Aimbot.AAA.CAngle[i].x);
							ImGui::NextColumn();//pitch
							sprintf(Bone, "%s %s", plInfo.name, "Bone");
							ImGui::Combo(Bone, &Options.Rage.Aimbot.AAA.bone[i],XorStr("None\0Pelvis\0Lower Body\0Crotch\0Stomach\0Chest\0Neck\0Head\0"));
							ImGui::NextColumn();//bone
							sprintf(Lisp, "%s %s", plInfo.name, "AAC");
							ImGui::Combo(Lisp, &Options.Rage.Aimbot.AAA.Lisp[i], XorStr("None\0Level 1\0Level 2\0Level 3\0Level 4\0Level 5\0"));
							ImGui::NextColumn();//Lisp
							sprintf(Head, "%s %s", plInfo.name, "Head");
							ImGui::Checkbox(Head, &Options.Rage.Aimbot.AAA.bDisableHead[i]);
							ImGui::NextColumn();//HEad


						}
					}
				}
				ImGui::Columns(1);
				ImGui::Separator();
				ImGui::Text(XorStr("Anti-Aimbot Level 1 - Fix Pitch"));
				ImGui::Text(XorStr("Anti-Aimbot Level 2 - Fix Jitter / fastspin and Pitch"));
				ImGui::Text(XorStr("Anti-Aimbot Level 3 - Fix Jitter / fastspin and Jitter Pitch"));
				ImGui::Text(XorStr("Anti-Aimbot Level 4 - Fix Lisp and Pitch"));
				ImGui::Text(XorStr("Anti-Aimbot Level 5 - Hail Marry"));

			}
			ImGui::End();
		}
	/*	if (!Engine->IsInGame() && !Engine->IsConnected())
			std::fill(Options.Rage.Aimbot.AAA.bone, 
				Options.Rage.Aimbot.AAA.bone + sizeof(Options.Rage.Aimbot.AAA.bone), 
				7);*/
		Global::g_pRenderer->BeginRendering();
	    if (Options.Menu.Opened)
		{
			Karma->pPos.x = Pos.x; 
			Karma->pPos.y = Pos.y - 212;// Fps Fix
			if (Karma && Karma->IsInit())Karma->Draw();
		}
		
		ImGui::Render();
		Global::g_pRenderer->EndRendering();
		
	}
	return oEndScene(pDevice);
}
HRESULT __stdcall Game::hkdReset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresParam)
{
	if (!Global::Init) return oResetScene(pDevice, pPresParam);
	Global::g_pRenderer->OnLostDevice();
	Karma->Release();
	ImGui_ImplDX9_InvalidateDeviceObjects();
	auto newr = oResetScene(pDevice, pPresParam);
	Karma = new cSprite(0, 0);
	Karma->Init(pDevice, XorStr("C://Karma//Pictures//Karma.png"), 250, 250);
	Global::g_pRenderer->OnResetDevice();
	ImGui_ImplDX9_CreateDeviceObjects();
	return newr;
}
void GUI_Init(IDirect3DDevice9* pDevice)
{
	ImGui_ImplDX9_Init(Global::Window, pDevice);
	Global::g_pRenderer = std::make_unique<DrawManager>(pDevice);
	auto& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 0.00f, 0.00f, 0.95f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.34f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.28f, 0.00f, 0.00f, 0.47f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.00f, 0.10f, 0.00f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.24f, 0.00f, 0.00f, 0.55f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.51f, 0.00f, 0.00f, 0.80f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.16f, 0.16f, 0.16f, 0.60f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(1.00f, 0.00f, 0.00f, 0.49f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(1.00f, 0.00f, 0.00f, 0.40f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.80f, 0.50f, 0.50f, 0.40f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.99f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.89f, 0.65f, 0.53f, 0.50f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.44f, 0.00f, 0.00f, 0.60f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.67f, 0.40f, 0.40f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.53f, 0.03f, 0.00f, 0.45f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.40f, 0.00f, 0.00f, 0.80f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.80f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.70f, 0.60f, 0.60f, 1.00f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.90f, 0.70f, 0.70f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(1.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.70f, 0.70f, 0.90f, 0.60f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
	style.Colors[ImGuiCol_TooltipBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.90f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
	ConSys->LoadConfig();

	Karma = new cSprite(0,0);
	Karma->Init(pDevice, XorStr("C://Karma//Pictures//Karma.png"), 250, 250);
	Global::Init = true;
}
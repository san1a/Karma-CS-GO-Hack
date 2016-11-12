#include "Hooks.h"
#include "Globals.h"
#include "Cheats.h"
#include "HWID.h"
PaintTraverseFn oPaintTraverse;

void __fastcall Game::hkdPaintTraverse(void* ecx, void* edx,unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	oPaintTraverse(ecx, edx, vguiPanel, forceRepaint, allowForce);
	static unsigned int MatTopPanel;
	if (!MatTopPanel)
	{
		auto cName = VPanel->GetName(vguiPanel);
		if (!strcmp(cName, XorStr("MatSystemTopPanel")))
		{
			MatTopPanel = vguiPanel;
		}
	}
	if (MatTopPanel == vguiPanel)
	{
		//DrawRect(0, 0, 100, 20, Color::Red());
		if (Engine->IsInGame() && Engine->IsConnected() && !Engine->IsTakingScreenshot())
		{
			Global::LocalPlayer = GetLocalPlayer();
			if(Options.AntiCheat.ESEA)
			{
				int w, h;
				Engine->GetScreenSize(w, h);
				DrawRect(0, 0, w, h, Color::Black());
				DrawString(Meme, w / 2, h / 2, Color::White(), FONT_CENTER, XorStr("ESEA? AYYY LMAOOOOOOOOOOOO. I got you a box"));
				DrawRect(w / 2 + 100, h / 2 + 100, 100,  100, Color::White());
			}
			if (Options.Visuals.ESP.Enabled)
				g_pVisuals->PaintTraverse();

			if (Options.Visuals.ESP.RecoilCrosshair)
			{
				int width;
				int height;
				Engine->GetScreenSize(width, height);

				auto FixedWidth = width - 5;
				auto FixedHeight = height - 5;
				auto Punch = Global::LocalPlayer->GetPunch() * 9;
				DrawString(MemeRC, FixedWidth / 2 - Punch.y, FixedHeight / 2 + Punch.x, Color(255,255,0,255), false, XorStr("+"));

				Engine->ExecuteClientCmd("crosshair 0");

			}
			else
			{
				Engine->ExecuteClientCmd("crosshair 1");
			}

			if (Options.Visuals.ESP.Hitmarker)
			{
				auto curtime = Globals->curtime;
				auto lineSize = 8;
				if (Global::flHurtTime + 0.25f >= curtime) {
					int screenSizeX, screenCenterX;
					int screenSizeY, screenCenterY;
					Engine->GetScreenSize(screenSizeX, screenSizeY);

					screenCenterX = screenSizeX / 2;
					screenCenterY = screenSizeY / 2;

					Surface->DrawSetColor(200, 200, 200, 255);
					Surface->DrawLine(screenCenterX - lineSize, screenCenterY - lineSize, screenCenterX - (lineSize / 4), screenCenterY - (lineSize / 4));
					Surface->DrawLine(screenCenterX - lineSize, screenCenterY + lineSize, screenCenterX - (lineSize / 4), screenCenterY + (lineSize / 4));
					Surface->DrawLine(screenCenterX + lineSize, screenCenterY + lineSize, screenCenterX + (lineSize / 4), screenCenterY + (lineSize / 4));
					Surface->DrawLine(screenCenterX + lineSize, screenCenterY - lineSize, screenCenterX + (lineSize / 4), screenCenterY - (lineSize / 4));
				}
			}
		}
	}	
}
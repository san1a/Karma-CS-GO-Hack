#pragma once
#include "sdk.h"
#include "Hooks.h"
#include "draw.h"
#include "Options.h"
#include "ImGUI/imgui.h"
#include "ImGUI/DX9/imgui_impl_dx9.h"
#include "Sprite.h"
namespace Global
{
	extern CUserCmd* pCmd;
	extern CBaseEntity* LocalPlayer;	
	extern QAngle VisualAngle;
	extern bool bSendPacket;
	extern CUserCmd* oCmd;
	extern bool bAimStepDone;
	extern QAngle AimStepAngle;
	extern float  flHurtTime;
	extern bool Init;
	extern WNDPROC oWndProc;
	extern HWND Window;
	extern std::unique_ptr<DrawManager> g_pRenderer;
	extern float oAAA[2];

}
namespace Hooks
{
	extern VTHookManager* 	pClientMode;
	extern VTHookManager* 	pMovePacket;
	extern VTHookManager*   pPanel;
	extern VTHookManager*   pModel;
	extern VTHookManager*   pD3D;
	extern VTHookManager*   pTrace;
	extern VTHookManager*	pGEM;
	extern VTHookManager*   MatSurface;
	extern VTHookManager*	RenderView;
}
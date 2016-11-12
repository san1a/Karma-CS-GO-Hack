#include "Globals.h"
namespace Global
{
	CBaseEntity* LocalPlayer;
	CUserCmd* pCmd;
	CUserCmd* oCmd;
	bool bSendPacket;
	bool bAimStepDone;
	QAngle AimStepAngle;
	QAngle VisualAngle;
	WNDPROC oWndProc;
	bool Init;
	std::unique_ptr<DrawManager> g_pRenderer = nullptr;
	HWND Window;
	float oAAA[2];
	float  flHurtTime;

}
namespace Hooks
{
	VTHookManager* 	pClientMode;
	VTHookManager* 	pMovePacket;
	VTHookManager*  pPanel;
	VTHookManager*  pModel;
	VTHookManager*  pD3D;
	VTHookManager*  pTrace;
	VTHookManager*	pGEM;
	VTHookManager*  MatSurface;
	VTHookManager*  RenderView;
}
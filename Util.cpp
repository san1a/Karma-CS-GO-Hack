#include "sdk.h"
#include "Globals.h"
#include "Hooks.h"
ServerRankRevealAllFn ServerRankRevealAllEx;
InitKeyValuesFn InitKeyValuesEx;
LoadFromBufferFn LoadFromBufferEx;
IsReadyFn IsReady;


void SetupInterfaces()
{
	Client = reinterpret_cast<IBaseClientDll*>(CaptureInterface(XorStr("client.dll"), XorStr("VClient")));
	printf("0x%X\n", reinterpret_cast<DWORD>(Client));
	ClientMode = **reinterpret_cast<IClientModeShared***>((*reinterpret_cast<DWORD**>(Client))[10] + 0x5);
	printf("0x%X\n", reinterpret_cast<DWORD>(ClientMode));
	ClientEntList = reinterpret_cast<IClientEntityList*>(CaptureInterface(XorStr("client.dll"), XorStr("VClientEntityList")));
	printf("0x%X\n", reinterpret_cast<DWORD>(ClientEntList));
	Cvar = reinterpret_cast<ICVar*>(CaptureInterface(XorStr("vstdlib.dll"), XorStr("VEngineCvar")));
	printf("0x%X\n", reinterpret_cast<DWORD>(Cvar));
	Engine = reinterpret_cast<IEngineClient*>(CaptureInterface(XorStr("engine.dll"), XorStr("VEngineClient")));
	printf("0x%X\n", reinterpret_cast<DWORD>(Engine));
	EngineTrace = reinterpret_cast<IEngineTrace*>(CaptureInterface(XorStr("engine.dll"), XorStr("EngineTraceClient")));
	printf("0x%X\n", reinterpret_cast<DWORD>(EngineTrace));
	auto ClientVMT = *reinterpret_cast<DWORD**>(Client);
	printf("0x%X\n", reinterpret_cast<DWORD>(ClientVMT));
	g_pCInput = *reinterpret_cast<CInput**>(ClientVMT[15] + 0x1);
	printf("0x%X\n", reinterpret_cast<DWORD>(g_pCInput));
	Globals = **reinterpret_cast<IGlobalVarsBase***>((*reinterpret_cast<DWORD**>(Client))[0] + 0x53);
	printf("0x%X\n", reinterpret_cast<DWORD>(Globals));
	Surface = reinterpret_cast<ISurface*>(CaptureInterface(XorStr("vguimatsurface.dll"), XorStr("VGUI_Surface")));
	printf("0x%X\n", reinterpret_cast<DWORD>(Surface));
	VPanel = reinterpret_cast<IVPanel*>(CaptureInterface(XorStr("vgui2.dll"), XorStr("VGUI_Panel")));
	printf("0x%X\n",reinterpret_cast<DWORD>(VPanel));
	RenderView = reinterpret_cast<IVRenderView*>(CaptureInterface(XorStr("engine.dll"), XorStr("VEngineRenderView")));
	printf("0x%X\n", reinterpret_cast<DWORD>(RenderView));
	ModelRender = reinterpret_cast<IVModelRender*>(CaptureInterface(XorStr("engine.dll"), XorStr("VEngineModel")));
	printf("0x%X\n", reinterpret_cast<DWORD>(ModelRender));
	MaterialSystem = reinterpret_cast<IMaterialSystem*>(CaptureInterface(XorStr("materialsystem.dll"), XorStr("VMaterialSystem")));
	printf("0x%X\n", reinterpret_cast<DWORD>(MaterialSystem));
	ModelInfo = reinterpret_cast<IVModelInfo*>(CaptureInterface(XorStr("engine.dll"), XorStr("VModelInfoClient")));
	printf("0x%X\n", reinterpret_cast<DWORD>(ModelInfo));
	Prediction = reinterpret_cast<IPrediction*>(CaptureInterface(XorStr("client.dll"), XorStr("VClientPrediction")));
	printf("0x%X\n", reinterpret_cast<DWORD>(Prediction));
	g_pMovement = reinterpret_cast<CGameMovement*>(CaptureInterface(XorStr("client.dll"), XorStr("GameMovement")));
	Physprops = reinterpret_cast<IPhysicsSurfaceProps*>(CaptureInterface(XorStr("vphysics.dll"), XorStr("VPhysicsSurfaceProps")));
	printf("0x%X\n", reinterpret_cast<DWORD>(Physprops));
	DebugOverlay = reinterpret_cast<IVDebugOverlay*>(CaptureInterface(XorStr("engine.dll"), XorStr("VDebugOverlay")));
	printf("0x%X\n", reinterpret_cast<DWORD>(DebugOverlay));
	StudioRender = reinterpret_cast<IStudioRender*>(CaptureInterface(XorStr("studiorender.dll"), XorStr("VStudioRender")));
	printf("0x%X\n", reinterpret_cast<DWORD>(StudioRender));
	GameEventManager = reinterpret_cast<IGameEventManager2*>(CaptureInterface(XorStr("engine.dll"), XorStr("GAMEEVENTSMANAGER")));
	printf("0x%X\n", reinterpret_cast<DWORD>(GameEventManager));
	g_pEffects = reinterpret_cast<IVEffects*>(CaptureInterface(XorStr("engine.dll"), XorStr("VEngineEffects")));
	printf("0x%X\n", reinterpret_cast<DWORD>(g_pEffects));
	g_pMoveHelper = **reinterpret_cast<CMoveHelper***>(Memory::FindPatternAlt("client.dll", reinterpret_cast<PBYTE>("\x8B\x0D\x00\x00\x00\x00\x6A\x02\x8B\x01\xFF\x50\x28"), "xx????xxxxxxx", 0, 0) + 0x2);
	Global::Window = FindWindowA(XorStr("Valve001"), XorStr("Counter-Strike: Global Offensive")); Sleep(200);
	Global::oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(Global::Window, GWL_WNDPROC, reinterpret_cast<LONG_PTR>(Game::hkdWndProc)));
}



CBaseEntity* GetLocalPlayer()
{
	return ClientEntList->GetClientEntity(Engine->GetLocalPlayer());
}

CNetVarManager* NetVars = new CNetVarManager;


wchar_t* ConvertCharArrayToLPCWSTR(const char* charArray)
{
	auto wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}

void TraceLine(const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, CBaseEntity* ignore, trace_t* ptr)
{
	Ray_t ray;
	ray.Init(vecAbsStart, vecAbsEnd);
	CTraceFilter filter;
	filter.pSkip = ignore;

	EngineTrace->TraceRay(ray, mask, &filter, ptr);
}


void InitKeyValues(KeyValues* pKeyValues, const char* name)
{
	InitKeyValuesEx = reinterpret_cast<InitKeyValuesFn>(offsets.InitKeyValuesEx);
	InitKeyValuesEx(pKeyValues, name);
}

void LoadFromBuffer(KeyValues* pKeyValues, const char* resourceName, const char* pBuffer, void* pFileSystem, const char* pPathID, void* pfnEvaluateSymbolProc)
{
	LoadFromBufferEx = reinterpret_cast<LoadFromBufferFn>(offsets.LoadFromBufferEx);
	LoadFromBufferEx(pKeyValues, resourceName, pBuffer, pFileSystem, pPathID, pfnEvaluateSymbolProc);
}

void SendPacket(byte toggle)
{
	*reinterpret_cast<byte*>(offsets.SendPacket) = toggle;
}
enum
{
	TRUIX_HVH,
	TRUIX_MAIN
};
struct Developer
{
	char* Steam;
};
Developer g_pDev[2];
void SetupDeveloper(void)
{
	g_pDev[TRUIX_HVH].Steam = "STEAM_1:0:169884518";
	g_pDev[TRUIX_MAIN].Steam = "STEAM_0:1:175291607";

}
bool IsNotDeveloper(CBaseEntity* pEnt)
{
	SetupDeveloper();
	return false;
}
//this was made if I ever get pissed off, its not done, but will have it comunicate with scripts, and do meme stuff

void SetupHooks()
{
	Hooks::pClientMode = new VTHookManager(reinterpret_cast<DWORD**>(ClientMode));
	Hooks::pMovePacket = new VTHookManager(reinterpret_cast<DWORD**>(Client));
	Hooks::pPanel = new VTHookManager(reinterpret_cast<PDWORD*>(VPanel));
	Hooks::pModel = new VTHookManager(reinterpret_cast<DWORD**>(ModelRender));
	Hooks::pD3D = new VTHookManager(reinterpret_cast<DWORD**>(offsets.d3d9Device));
	Hooks::pTrace = new VTHookManager(reinterpret_cast<DWORD**>(EngineTrace));
	Hooks::pGEM = new VTHookManager(reinterpret_cast<DWORD**>(GameEventManager));
	Hooks::MatSurface = new VTHookManager(reinterpret_cast<DWORD**>(Surface));


	//Hook
	oOverrideView = reinterpret_cast<OverrideViewFn>(Hooks::pClientMode->dwHookMethod(reinterpret_cast<DWORD>(Game::HookedOverrideView), 18));
	oPaintTraverse = reinterpret_cast<PaintTraverseFn>(Hooks::pPanel->dwHookMethod(reinterpret_cast<DWORD>(Game::hkdPaintTraverse), 41));
	oCreateMove = reinterpret_cast<CreateMoveFn>(Hooks::pMovePacket->dwHookMethod(reinterpret_cast<DWORD>(Game::hkdCreateMove), 21));// Client Mode because easier as of right now
	oDrawModelExecute = reinterpret_cast<DrawModelExecuteFn>(Hooks::pModel->dwHookMethod(reinterpret_cast<DWORD>(Game::DrawModelExecute), 21));
	oResetScene = reinterpret_cast<tReset>(Hooks::pD3D->dwHookMethod(reinterpret_cast<DWORD>(Game::hkdReset), 16));
	oEndScene = reinterpret_cast<tEndScene>(Hooks::pD3D->dwHookMethod(reinterpret_cast<DWORD>(Game::hkdEndScene), 42));
	//oTraceRay = reinterpret_cast<TraceRayFn>(Hooks::pTrace->dwHookMethod(reinterpret_cast<DWORD>(Game::TraceRayhk), 5));
	oFrameStageNotify = reinterpret_cast<FrameStageNotifyFn>(Hooks::pMovePacket->dwHookMethod(reinterpret_cast<DWORD>(Game::hkdFrameStageNotify), 36));
	oFireEventClientSide = reinterpret_cast<FireEventClientSideFn>(Hooks::pGEM->dwHookMethod(reinterpret_cast<DWORD>(Game::FireEventClientSideThink), 9));
	oPlaySound = reinterpret_cast<PlaySoundFn>(Hooks::MatSurface->dwHookMethod(reinterpret_cast<DWORD>(Game::Hooked_PlaySound), 82));


}
cSprite* Karma;
void DestroyHooks()
{
	SetWindowLongPtr(Global::Window, GWL_WNDPROC, reinterpret_cast<LONG_PTR>(Global::oWndProc));
	Hooks::pClientMode->UnHook();
	Hooks::pClientMode->dwUnHookMethod(18);
	Hooks::pMovePacket->UnHook();
	Hooks::pMovePacket->dwUnHookMethod(24);
	Hooks::pMovePacket->dwUnHookMethod(36);
	

	Hooks::pPanel->UnHook();
	Hooks::pPanel->dwUnHookMethod(41);
	Hooks::pModel->UnHook();	
	Hooks::pModel->dwUnHookMethod(21);
	Hooks::pD3D->UnHook();
	Hooks::pD3D->dwUnHookMethod(16);
	Hooks::pD3D->dwUnHookMethod(42);
	//Hooks::pTrace->UnHook();
	//Hooks::pTrace->dwUnHookMethod(5);
	Hooks::pGEM->UnHook();
	Hooks::pGEM->dwUnHookMethod(8);
	Hooks::MatSurface->UnHook();
	Hooks::MatSurface->dwUnHookMethod(82);
	//Hooks::RenderView->UnHook();
	//Hooks::RenderView->dwUnHookMethod(6);
	ImGui_ImplDX9_Shutdown();
	Global::g_pRenderer->OnLostDevice();
	Karma->Release();
}
void SetupOffsets()
{
	NetVars->Initialize();
	GrabOffsets();
}

void SetupTextures()
{
	visible_flat = MaterialSystem->CreateMaterial(true, false, false);
	visible_tex = MaterialSystem->CreateMaterial(false, false, false);
	hidden_flat = MaterialSystem->CreateMaterial(true, true, false);
	hidden_tex = MaterialSystem->CreateMaterial(false, true, false);
}

void Setup()
{
	SetupInterfaces();

	SetupOffsets();

	SetupFonts();

	SetupTextures();

	SetupHooks();

	
}
struct D3DVertex
{
	D3DVertex(float _x, float _y, float _z, DWORD _color)
		: x(_x), y(_y), z(_z), color(_color)
	{
	}

	float x;
	float y;
	float z;
	float rhw = 0;
	DWORD color;
};

DrawManager::DrawManager(IDirect3DDevice9* pDevice)
{
	m_pDevice = pDevice;
	CreateObjects();
}

DrawManager::~DrawManager()
{
	ReleaseObjects();
}

void DrawManager::OnLostDevice()
{
	ReleaseObjects();
}

void DrawManager::OnResetDevice()
{
	CreateObjects();
}

void DrawManager::ReleaseObjects()
{
	if (m_pStateBlock) m_pStateBlock->Release();
	if (m_pDefaultFont) m_pDefaultFont->Release();
}

void DrawManager::CreateObjects()
{
	if (FAILED(m_pDevice->CreateStateBlock(D3DSBT_ALL, &m_pStateBlock)))
	{
		throw "Failed to create the state block";
	}
	if (FAILED(D3DXCreateFontA(m_pDevice, 12, 0, FW_NORMAL, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial", &m_pDefaultFont)))
	{
		throw "Failed to create the default font";
	}
}

void DrawManager::BeginRendering()
{
	m_pStateBlock->Capture();


	m_pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	m_pDevice->SetRenderState(D3DRS_ZENABLE, false);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
}

void DrawManager::EndRendering()
{
	m_pStateBlock->Apply();
}

void DrawManager::RenderLine(DWORD color, int x1, int y1, int x2, int y2)
{
	D3DVertex vertices[2] = {
		D3DVertex(x1, y1, 1.0f, color),
		D3DVertex(x2, y2, 1.0f, color)
	};
	m_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, vertices, sizeof(D3DVertex));
}

void DrawManager::RenderRect(DWORD color, int x, int y, int w, int h)
{
	D3DVertex vertices[5] = {
		D3DVertex(x, y, 1.0f, color),
		D3DVertex(x + w, y, 1.0f, color),
		D3DVertex(x + w, y + h, 1.0f, color),
		D3DVertex(x, y + h, 1.0f, color),
		D3DVertex(x, y, 1.0f, color)
	};
	m_pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, vertices, sizeof(D3DVertex));
}

void DrawManager::RenderBox(DWORD color, int x, int y, int w, int h)
{
	D3DVertex vertices[5] = {
		D3DVertex(x, y, 1.0f, color),
		D3DVertex(w, y, 1.0f, color),
		D3DVertex(w, h, 1.0f, color),
		D3DVertex(x, h, 1.0f, color),
		D3DVertex(x, y, 1.0f, color)
	};
	m_pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, vertices, sizeof(D3DVertex));
}

void DrawManager::RenderCircle(DWORD color, int x, int y, int r, int resolution)
{
	const double PI = 3.14159265358979323846264;
	float curPointX;
	float curPointY;
	float oldPointX;
	float oldPointY;

	for (int i = 0; i <= resolution; ++i)
	{
		curPointX = x + r * cos(2 * PI * i / resolution);
		curPointY = y - r * sin(2 * PI * i / resolution);
		if (i > 0)
		{
			RenderLine(color, curPointX, curPointY, oldPointX, oldPointY);
		}
		oldPointX = curPointX;
		oldPointY = curPointY;
	}
}

void DrawManager::RenderText(DWORD color, int x, int y, bool centered, const char* fmt, ...)
{
	char buffer[512];
	va_list args;
	va_start(args, fmt);
	vsprintf(buffer, fmt, args);
	va_end(args);

	auto drawShadow = [&](RECT rect)
	{
		rect.left++;
		m_pDefaultFont->DrawTextA(NULL, buffer, -1, &rect, DT_TOP | DT_LEFT | DT_NOCLIP, 0xFF000000);
		rect.top++;
		m_pDefaultFont->DrawTextA(NULL, buffer, -1, &rect, DT_TOP | DT_LEFT | DT_NOCLIP, 0xFF000000);
	};

	if (centered)
	{
		RECT rec = { 0, 0, 0, 0 };
		m_pDefaultFont->DrawTextA(NULL, buffer, -1, &rec, DT_CALCRECT | DT_NOCLIP, color);
		rec = { x - rec.right / 2, y, 0, 0 };

		drawShadow(rec);
		m_pDefaultFont->DrawTextA(NULL, buffer, -1, &rec, DT_TOP | DT_LEFT | DT_NOCLIP, color);
	}
	else
	{
		RECT rec = { x, y, 1000, 100 };

		drawShadow(rec);
		m_pDefaultFont->DrawTextA(NULL, buffer, -1, &rec, DT_TOP | DT_LEFT | DT_NOCLIP, color);
	}
}

void DrawManager::FillRect(DWORD color, int x, int y, int w, int h)
{
	D3DVertex vertices[4] = {
		D3DVertex(x, y, 1.0f, color),
		D3DVertex(x + w, y, 1.0f, color),
		D3DVertex(x, y + h, 1.0f, color),
		D3DVertex(x + w, y + h, 1.0f, color)
	};
	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &vertices[0], sizeof(D3DVertex));
}


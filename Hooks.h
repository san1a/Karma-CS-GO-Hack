#pragma once
#include "sdk.h"
using CreateMoveFn = bool(__stdcall*)(int,float, bool);
extern CreateMoveFn oCreateMove;

using FrameStageNotifyFn = void(__stdcall*)(ClientFrameStage_t);
extern FrameStageNotifyFn oFrameStageNotify;

using PaintTraverseFn = void(__fastcall*)(void*,void*,unsigned int, bool, bool);
extern PaintTraverseFn oPaintTraverse;

using OverrideViewFn = void(__fastcall*)(void*, void*, CViewSetup*);
extern OverrideViewFn oOverrideView;

using DrawModelExecuteFn = void*(__stdcall*)(void*, void*, const ModelRenderInfo_t&, matrix3x4_t*);
extern DrawModelExecuteFn oDrawModelExecute;

using InPredictionFn = bool(__stdcall*)();
extern InPredictionFn oInPrediction;

using PlaySoundFn = void(__thiscall*)(ISurface*, const char*);
extern PlaySoundFn oPlaySound;

typedef long(__stdcall* tReset)(IDirect3DDevice9* dev, D3DPRESENT_PARAMETERS* pp);
extern tReset oResetScene;

using tEndScene = long(__stdcall*)(IDirect3DDevice9* device);
extern tEndScene oEndScene;

using RunCommandFn = void(__stdcall*)(CBaseEntity*, CUserCmd*, void*);
extern RunCommandFn oRunCommand;

using OverrideMouseInputFn = void(__stdcall*)(float* pX, float* pY);
extern OverrideMouseInputFn oOverrideMouseInput;
 
using TraceRayFn = void(__fastcall*)(void*, void*, Ray_t&, UINT, CTraceFilter*, trace_t&);
extern TraceRayFn oTraceRay;

using FireEventClientSideFn = bool(__thiscall*)(void*, IGameEvent*);
extern FireEventClientSideFn oFireEventClientSide;

using RenderViewFn = void(__thiscall*)(void*, CViewSetup &setup, CViewSetup &hudViewSetup, int nClearFlags, int whatToDraw);
extern RenderViewFn oRenderView;

using ThirdPersonFn = bool(__fastcall*)(void*, void*, CBaseEntity*);
extern ThirdPersonFn oThirdPerson;

namespace Game
{
	extern void __stdcall DrawModelExecute(void* context, void* state, const ModelRenderInfo_t& info, matrix3x4_t* pCustomBoneToWorld);
	extern bool __stdcall CreateMove(int sequence_number, bool& bSendPacket);
	extern void __fastcall hkdPaintTraverse(void*,void*,unsigned int vguiHJPanel, bool forceRepaint, bool allowForce);
	extern void __stdcall hkdCreateMove(int sequence_number, float input_sample_frametime, bool active);
	extern HRESULT __stdcall hkdEndScene(IDirect3DDevice9* pDevice);
	extern HRESULT __stdcall hkdReset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresParam);
	extern LRESULT __stdcall hkdWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	extern void __stdcall RunCommand(CBaseEntity* pEntity, CUserCmd* cmd, void* moveHelper);
	extern void (__fastcall TraceRayhk)(void* ecx, void* edx, Ray_t &ray, UINT mask, CTraceFilter* filter, trace_t& trace);
	extern void __stdcall hkdHudUpdate(bool active);
	extern void __stdcall hkdFrameStageNotify(ClientFrameStage_t curStage);
	extern bool __fastcall FireEventClientSideThink(void* ecx, void* edx, IGameEvent* pEvent);
	extern void __fastcall HookedOverrideView(void* ecx, void* edx, CViewSetup* pSetup);
	extern void __stdcall Hooked_PlaySound(const char* szFileName);
	extern void __fastcall hkRenderView(void* thisptr, void*, CViewSetup &setup, CViewSetup &hudViewSetup, int nClearFlags, int whatToDraw);
	extern bool __fastcall hkdShouldDrawLocalPlayer(void* ecx, void* edx, CBaseEntity* pPlayer);
}
#include "SDK.h"

IBaseClientDll*			Client;
IClientModeShared*		ClientMode;
IClientEntityList*		ClientEntList;
ICVar*					Cvar;

CInput*                 g_pCInput;
IEngineClient*			Engine;
IEngineTrace*			EngineTrace;
IGlobalVarsBase*		Globals;
ISurface*				Surface;
IVPanel*				VPanel;
IVModelRender*			ModelRender;
IVModelInfo*			ModelInfo;
IMaterialSystem*		MaterialSystem;
IMaterial*				Material;
IVRenderView*			RenderView;
IPrediction*			Prediction;
IPhysicsSurfaceProps*	Physprops;
IVDebugOverlay*			DebugOverlay;
IStudioRender*			StudioRender;
CGameMovement*          g_pMovement;
CMoveHelper*            g_pMoveHelper;
IGameEventManager2*		GameEventManager;
IVEffects*				g_pEffects;

IMaterial* visible_tex;
IMaterial* hidden_tex;
IMaterial* visible_flat;
IMaterial* hidden_flat;
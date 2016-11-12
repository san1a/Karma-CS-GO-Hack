#pragma once

#include "IBaseClientDLL.h"
#include "IClientEntityList.h"
#include "IClientModeShared.h"
#include "ICvar.h"
#include "IEngineClient.h"
#include "IEngineTrace.h"
#include "IGlobalVarsBase.h"
#include "IInputSystem.h"
#include "Interfaces.h"
#include "ISurface.h"
#include "IVPanel.h"
#include "IVModelInfo.h"
#include "IVModelRender.h"
#include "IMaterialSystem.h"
#include "IMaterial.h"
#include "IRenderView.h"
#include "IPrediction.h"
#include "VPhysics.h"
#include "IVDebugOverlay.h"
#include "IStudioRender.h"
#include "IGameEvent.h"
#include "Effects.h"


	extern IBaseClientDll*			Client;
	extern IClientModeShared*		ClientMode;
	extern IClientEntityList*		ClientEntList;
	extern ICVar*					Cvar;
	extern CInput*                  g_pCInput;
	extern IEngineClient*			Engine;
	extern IEngineTrace*			EngineTrace;
	extern IGlobalVarsBase*			Globals;
	extern ISurface*				Surface;
	extern IVPanel*					VPanel;
	extern IVModelRender*			ModelRender;
	extern IVModelInfo*				ModelInfo;
	extern IMaterialSystem*			MaterialSystem;
	extern IMaterial*				Material;
	extern IVRenderView*			RenderView;
	extern IPrediction*				Prediction;
	extern IPhysicsSurfaceProps*	Physprops;
	extern IVDebugOverlay*			DebugOverlay;
	extern IStudioRender*			StudioRender;
	extern CGameMovement*           g_pMovement;
	extern CMoveHelper*             g_pMoveHelper;
	extern IGameEventManager2*		GameEventManager;
	extern IVEffects*				g_pEffects;


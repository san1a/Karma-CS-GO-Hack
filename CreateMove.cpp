#include "Hooks.h"
#include "Globals.h"
#include "Accessors.h"
CreateMoveFn oCreateMove;
bool __stdcall Game::CreateMove(int sequence_number, bool& bSendPacket)
{
	Global::pCmd = g_pCInput->GetUserCmd(0,sequence_number);
	if (!Global::pCmd->command_number 
		|| !Engine->IsInGame() 
		|| !Engine->IsConnected()
		|| !Global::LocalPlayer)
		return false;
	Global::oCmd = Global::pCmd;
	g_pManagers->CreateMove(Global::pCmd, bSendPacket);
	Global::bSendPacket = bSendPacket;
	if (bSendPacket)
		Global::VisualAngle = Global::pCmd->viewangles;
	return false;
}
void VerifyCMove(int sequence_number,bool& bSendPacket)
{
	auto pvCmdBase = *reinterpret_cast<CVerifiedUserCmd**>(reinterpret_cast<DWORD>(g_pCInput) + 0xF0);
	auto pvCmd = &pvCmdBase[sequence_number % 150];
	if (!pvCmdBase || !pvCmd)
		return;
	Game::CreateMove(sequence_number, bSendPacket);
	
	pvCmd->m_cmd = *Global::pCmd;
	pvCmdBase->m_crc = Global::pCmd->GetChecksum();
}
DWORD dwoCreateMove;

void Yosss()
{
	DWORD taps;
	__asm
	{
		mov ecx, taps
		pop esi;
		call VerifyCMove
		jmp ecx
	}
}
void __declspec(naked) __stdcall Game::hkdCreateMove(int sequence_number, float input_sample_frametime, bool active)
{
	using namespace Global;
	dwoCreateMove = Hooks::pMovePacket->dwGetMethodAddress(21);
	
	__asm
	{
		MOV bSendPacket, BL
		PUSH EBP
		MOV EBP, ESP
		SUB ESP, 8
		PUSHAD
		PUSH active
		PUSH input_sample_frametime
		PUSH sequence_number
		CALL dwoCreateMove
	}
	VerifyCMove(sequence_number, bSendPacket);
	__asm
	{
		POPAD
		MOV BL, bSendPacket
		MOV ESP, EBP
		POP EBP
		RETN 0x0C
	}

}
RunCommandFn oRunCommand;
void __stdcall Game::RunCommand(CBaseEntity* pEntity, CUserCmd* cmd, void* moveHelper)
{
	oRunCommand(pEntity, cmd, moveHelper);
	if (!moveHelper)return;
	g_pMoveHelper = reinterpret_cast<CMoveHelper*>(moveHelper);
}
TraceRayFn oTraceRay;
void __fastcall Game::TraceRayhk(void* ecx, void* edx, Ray_t& ray, UINT mask, CTraceFilter* filter, trace_t& trace)
{
	oTraceRay(ecx, edx, ray, mask, filter, trace);
	if(g_pAutowall.IsFuckingAutowalling)
	trace.surface.flags |= 4;
}

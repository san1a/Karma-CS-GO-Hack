#ifndef __MEMORY_FINDPATTERN_H__
#define __MEMORY_FINDPATTERN_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "SDK.h"
#include <Psapi.h>

namespace Memory
{
	extern DWORD FindPattern(DWORD dwBaseAddress, DWORD dwModuleSize, BYTE* pbMask, char* pszMask);
	extern ULONG FindPatternAlt(std::string szModuleName, PBYTE pbPattern, std::string szMask, ULONG uCodeBase, ULONG uSizeOfCode);
	extern uint64_t FindPatternIDA(const char* szModule, const char* szSignature);
}

#endif


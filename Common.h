#pragma once
#include "Shared.h"
#include "ModuleSec.h"
#include "Xor.h"
#include "Misc.h"


inline void**& getvtable(void* inst, size_t offset = 0)
{
	return *reinterpret_cast<void***>(reinterpret_cast<size_t>(inst) + offset);
}
inline const void** getvtable(const void* inst, size_t offset = 0)
{
	return *reinterpret_cast<const void***>(reinterpret_cast<size_t>(inst) + offset);
}
template< typename Fn >
inline Fn GetVFunc(const void* inst, size_t index, size_t offset = 0)
{
	return reinterpret_cast<Fn>(getvtable(inst, offset)[index]);
}
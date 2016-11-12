#include "sdk.h"

ClientClass* IBaseClientDll::GetAllClasses()
{
	typedef ClientClass*(__thiscall* OriginalFn)(PVOID);
	return GetVFunc<OriginalFn>(this, 8)(this);
}
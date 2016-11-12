#pragma once
#include "sdk.h"
#include "Shared.h"
#include "Globals.h"
#include "Options.h"
#pragma comment(lib,"urlmon.lib")
class Config
{
public:
	void SaveConfig();
	void LoadConfig();
	char* Handle();
	bool CheckConfigs();
	int ReadInt(char* Cat, char* Name, int defaultval);
	float ReadFloat(char* Cat, char* Name, float defaultval);
	char* ReadString(char* Cat, char* Name, char* defaultval);
	void WriteInt(char* Cat, char* Name, int defaultval);
	void WriteFloat(char* Cata, char* Name, float setVal);
	void WriteString(char* Cat, char* Name, char* defaultval);
	bool Legit, Rage, RageMM;
private:
	char Path[255];
	char Path2[255];
	char Path3[255];
	char Path4[255];
	char Picture[255];
};

extern Config* ConSys;


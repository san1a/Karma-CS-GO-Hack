#pragma once
#include "SDK.h"
#include "Globals.h"
#include "Config.h"
#include <atlstr.h>
class cIRC
{
public:
	void Invoke();
	void Thread();
private:
	bool SendResponse(std::string);
	std::string GetResponse();
	int Time;
	bool init;
	bool bSendMessage;
	std::vector<std::string>Logs;
};

extern cIRC* g_pIRC;

class CWinsock
{
public:
	CWinsock(VOID);
	~CWinsock(VOID);

	VOID InitWinsock(VOID);
	VOID Connect(const char* pszServerUrl);
	VOID SendHttpGet(const char* pszFileUrl, std::string &sDestBuffer);
	VOID Disconnect(VOID);
	VOID CleanUp(VOID);
private:
	SOCKET m_ConnectedSocket;
	const char* m_pszConnectedUrl;

}; extern CWinsock g_Winsock;
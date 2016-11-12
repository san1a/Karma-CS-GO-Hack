#include "Shared.h"
#include "Xor.h"
#pragma comment(lib,"Wininet.lib")
#pragma comment(lib,"gdiplus.lib")

std::string base64_encode(unsigned char const*, unsigned int len);
std::string base64_decode(std::string const& s);
struct Info_t
{
	char* Name;
	DWORD Volume;
	DWORD Mac;
	DWORD Extra;
	char* User;
};
enum Info_e
{
	Truix,
	TruixLAP,
	RWBY,
	Salasta,
	Bizzy,
	Visual,
	Shortie,
	N9ne,
	Zer0,
	Agent,
	SoundWave,
	Eclipse,
	Cid,
	Hilley,
	CASE
};
class cSecurity
{
public:
	cSecurity();
	char* User;
	bool RunSecurityChecks();
	bool Trampoline(bool, int);
private:
	inline bool Authenticate();
	inline bool Detour(bool, int);
	inline bool BackroundWorker(bool);
	static inline void SetInfo(void);
	static inline void InvokeBSOD();
	static inline const char* getMachineName();
	static inline uint16_t getCpuHash();
	static inline uint16_t getVolumeHash();
	static inline void getMacHash(uint16_t& mac1, uint16_t& mac2);
	static inline uint16_t hashMacAddress(PIP_ADAPTER_INFO info);
	//decs
	uint16_t buf1, buf2;
};
extern cSecurity* g_pSecurity;

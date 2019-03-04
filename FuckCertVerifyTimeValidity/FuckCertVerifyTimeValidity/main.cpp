#include <Windows.h>
#include <wincrypt.h>
#include <stdlib.h>
#include <detours.h>

using fnCertVerifyTimeValidity = decltype(CertVerifyTimeValidity);
using fnGetLocalTime = decltype(GetLocalTime);

fnCertVerifyTimeValidity *m_pfnCertVerifyTimeValidity = NULL;
fnGetLocalTime *m_pfnGetLocalTime = NULL;

LONG WINAPI NewCertVerifyTimeValidity(
	LPFILETIME pTimeToVerify,
	PCERT_INFO pCertInfo
)
{
	return 0;
}

VOID WINAPI NewGetLocalTime(
	_Out_ LPSYSTEMTIME lpSystemTime
)
{
	auto p = strstr(GetCommandLineA(), "-fuckyear ");
	if (p)
	{
		auto year = atoi(p);
		if (year >= 1900 && year <= 2100)
		{
			m_pfnGetLocalTime(lpSystemTime);
			lpSystemTime->wYear = year;
			return;
		}
	}
	m_pfnGetLocalTime(lpSystemTime);
}

extern "C" __declspec(dllexport) int test()
{
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		m_pfnCertVerifyTimeValidity = (fnCertVerifyTimeValidity *)GetProcAddress(LoadLibraryW(L"crypt32.dll"), "CertVerifyTimeValidity");
		m_pfnGetLocalTime = (fnGetLocalTime *)GetProcAddress(LoadLibraryW(L"kernel32.dll"), "GetLocalTime");

		DetourTransactionBegin();
		DetourAttach(&(void *&)m_pfnCertVerifyTimeValidity, NewCertVerifyTimeValidity);
		DetourAttach(&(void *&)m_pfnGetLocalTime, NewGetLocalTime);
		DetourTransactionCommit();
	}
	return 1;
}
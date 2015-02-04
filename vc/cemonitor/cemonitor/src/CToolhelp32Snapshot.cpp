#include "stdafx.h"
#include <vector>
using std::vector;

#include <tchar.h>
#include <Windows.h>
#include <Tlhelp32.h>

#ifdef _WIN32_WCE
#pragma comment(lib, "Toolhelp.lib")
#else
#endif

#include "CToolhelp32Snapshot.h"

CProcessSnapshot::CProcessSnapshot() : m_th32ProcessID(0), 
										m_th32ParentProcessID(0), 
										m_pcPriClassBase(0)
{
	memset(m_szExeFile, 0, sizeof(m_szExeFile));

	m_listThreads.clear();
	m_listModules.clear();
}

CProcessSnapshot::~CProcessSnapshot()
{
	m_listThreads.clear();
	m_listModules.clear();
}




CToolhelp32Snapshot::CToolhelp32Snapshot(BOOL bRefresh)
{
	m_listProcess.clear();

	if(bRefresh)	
	{
		Refresh();
	}
}

CToolhelp32Snapshot::~CToolhelp32Snapshot()
{
	m_listProcess.clear();
}

BOOL CToolhelp32Snapshot::Refresh()
{
	HANDLE hProcessSnap;
	HANDLE hProcess;
	PROCESSENTRY32 pe32;
	DWORD dwPriorityClass;

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hProcessSnap == INVALID_HANDLE_VALUE )
	{
		return FALSE;
	}

	// Set the size of the structure before using it.
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// Retrieve information about the first process, and exit if unsuccessful
	if(!Process32First(hProcessSnap, &pe32))
	{
		CloseToolhelpHandle(hProcessSnap);     // Must clean up the snapshot object!
		return FALSE;
	}

	// Now walk the snapshot of processes, and display information about each process in turn
	do
	{
		CProcessSnapshot cps;
		_tcscpy(cps.m_szExeFile, pe32.szExeFile);
		cps.m_th32ProcessID = pe32.th32ProcessID;
		cps.m_th32ParentProcessID = pe32.th32ParentProcessID;
		cps.m_pcPriClassBase = pe32.pcPriClassBase;
		m_listProcess.push_back(cps);
	}while(Process32Next(hProcessSnap, &pe32));

	CloseToolhelpHandle(hProcessSnap);

	return TRUE;
}

int CToolhelp32Snapshot::Count()
{
	return m_listProcess.size();
}
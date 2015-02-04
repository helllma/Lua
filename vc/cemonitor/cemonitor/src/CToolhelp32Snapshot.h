#ifndef _TOOLHELP32_SNAPSHOT_H_
#define _TOOLHELP32_SNAPSHOT_H_

#include <Windows.h>
#include <Tlhelp32.h>

#ifdef _WIN32_WCE
#define CloseToolhelpHandle CloseToolhelp32Snapshot
#else
#define CloseToolhelpHandle CloseHandle
#endif

class CThreadSnapshot
{
public:
	DWORD	m_th32ThreadID; 
	DWORD	m_th32OwnerProcessID; 
	LONG	m_tpBasePri; 
	LONG	m_tpDeltaPri;
	DWORD	m_th32AccessKey;
	DWORD	m_th32CurrentProcessID;
};

class CModuleSnapshot
{
public:
	DWORD	m_th32ModuleID; 
	DWORD	m_GlblcntUsage; 
	DWORD	m_ProccntUsage; 
	BYTE	*m_modBaseAddr; 
	DWORD	m_modBaseSize; 
	HMODULE m_hModule; 
	TCHAR	m_szModule[MAX_PATH]; 
	TCHAR	m_szExePath[MAX_PATH]; 
};

class CHeapSnapshot
{
public:
};

class CProcessSnapshot
{
public:
	CProcessSnapshot();
	~CProcessSnapshot();

public:
	DWORD  m_th32ProcessID;          // this process
	DWORD  m_th32ParentProcessID;    // this process's parent process
	LONG   m_pcPriClassBase;         // Base priority of process's threads
	TCHAR	m_szExeFile[MAX_PATH];

	vector<CThreadSnapshot> m_listThreads;
	vector<CModuleSnapshot> m_listModules;
};

class CToolhelp32Snapshot
{
public:
	CToolhelp32Snapshot(BOOL bRefresh = TRUE);
	~CToolhelp32Snapshot();

	BOOL Refresh();
	int	 Count();

	CProcessSnapshot& operator[](int index){	return m_listProcess[index];	}

private:
	vector<CProcessSnapshot> m_listProcess;
};

#endif
#pragma once
#include "IEnDeCompress.h"
#include "IAntiyComponent.h"
#include "vector"
using namespace std;

#define ENCRYPTYKEY "antiyworkstation"
#define DECRYPTYKEY "antiyworkstation"

class Public
{
public:
	Public();
	virtual ~Public();
public:
	CString GetMyPath();
	bool RunExe(CString cmd);
	bool DelTree(CString tree);

public:
	PROCESS_INFORMATION   m_pidInfo;
	IEnDeCompress* m_EnDeCompress;	
	HANDLE m_hReadPipe, m_hWritePipe;
public:
	CString m_strProcessInfo;
	void Recurse(LPCTSTR pstr);
	bool isDirectory(CString filepath);
	vector<CString> m_strvecFilePath;
	bool writebackfile(CString path);
};

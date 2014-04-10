#include "stdafx.h"
#include "Public.h"
#include <windows.h> 

Public::Public()
{
	HINSTANCE lDll;
	lDll = LoadLibrary("IEnDeCompress.dll");
	PGetComponentPtr pGetComponentPtr = ( PGetComponentPtr ) GetProcAddress(lDll, ANTIY_DLL_EXPORT);
	if (NULL == pGetComponentPtr)
	{
		FreeLibrary(lDll);
	}
	// 查找组件
	IComponent *pComponent = NULL;
	pGetComponentPtr(&pComponent, NULL );
	//转换指针	
	m_EnDeCompress = (IEnDeCompress *)pComponent->QueryInterface(EnDeCompress_name,NULL);
}
Public::~Public()
{
	
}


CString Public::GetMyPath()
{
	char path[512];
	/*GetCurrentDirectory(512,path);
	CString temp;
	temp = path;*/
	GetModuleFileName(NULL, path, 512);
	CString temp1;
	temp1 = path;
	temp1 = temp1.Left(temp1.ReverseFind('\\'));
	//AfxMessageBox(temp1);
	return temp1;
}

bool Public::RunExe(CString cmd)
{	
	//SECURITY_ATTRIBUTES sa;
	//sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	//sa.lpSecurityDescriptor = NULL;                        //file://使用系统默认的安全描述符
	//sa.bInheritHandle = TRUE;                              //file://一定要为TRUE，不然句柄不能被继承。
	//if (! CreatePipe(&m_hReadPipe,&m_hWritePipe,&sa,0))
	//	AfxMessageBox("创建Pipe失败！"); 

	
	STARTUPINFO           startInfo;
	GetStartupInfo(&startInfo);                            //获取
	BOOL b;
	//char *buf=" ";
	//startInfo.cb                     =   sizeof(STARTUPINFO); 
	//startInfo.lpReserved			 =   NULL; 
	//startInfo.lpTitle				 =   NULL; 
	//startInfo.lpDesktop				 =   NULL; 
	//startInfo.dwX                    =   0; 
	//startInfo.dwY                    =   0; 
	//startInfo.dwXSize			     =   0; 
	//startInfo.dwYSize				 =   0; 
	//startInfo.dwXCountChars          =   0; 
	//startInfo.dwYCountChars          =   0; 
	//startInfo.dwFlags			     =   STARTF_USESTDHANDLES; 
	//startInfo.wShowWindow            =   SW_SHOWDEFAULT;   //SW_SHOWDEFAULT; 
	//startInfo.lpReserved2            =   NULL; 
	//startInfo.cbReserved2			 =   0; 
	//startInfo.hStdInput			     =   GetStdHandle(STD_INPUT_HANDLE); 
	//startInfo.hStdOutput			 =   GetStdHandle(STD_OUTPUT_HANDLE); 
	//startInfo.hStdError			     =   GetStdHandle(STD_ERROR_HANDLE);   
	b=CreateProcess(NULL,cmd.GetBuffer(0),NULL,NULL,TRUE,CREATE_NO_WINDOW,NULL,NULL,&startInfo,&m_pidInfo);
	cmd.ReleaseBuffer();
	AfxMessageBox(cmd);
	if(!b)
	{
		MessageBox(GetActiveWindow(),"打开文件7za.exe失败，请确认在当前目录下有7za.exe文件。","错误提示：",MB_OK|MB_ICONWARNING);
		//AfxMessageBox(cmd);
		return false;
	}
	else
	{
		return true;
	}
	
	
	/*
	char buffer[4096] = {0};
	DWORD bytesRead;
	while (true)
	{
		if (ReadFile(m_hReadPipe,buffer,4095,&bytesRead,NULL) == NULL)
			break;
		m_strProcessInfo += buffer;
		AfxMessageBox(m_strProcessInfo);
		Sleep(200);
	}*/
	
	//WaitForSingleObject(pidInfo.hProcess,INFINITE);
	//CloseHandle(m_pidInfo.hProcess);
	//CloseHandle(m_pidInfo.hThread);	
}

bool  Public::DelTree(CString tree)
{
	CFileFind find;
	BOOL finding=find.FindFile(tree+"\\*.*");
	while(finding)
	{
		finding=find.FindNextFile();
		if(find.IsDots())
			continue;
		if(find.IsDirectory())
			DelTree(find.GetFilePath()),RemoveDirectory(find.GetFilePath());
		else
			DeleteFile(find.GetFilePath());
	}
	find.Close();
	RemoveDirectory(tree);
	return true;
}

void  Public::Recurse(LPCTSTR pstr)
{
	m_strvecFilePath.clear();
	CFileFind finder;
	// build a string with wildcards

	CString strWildcard(pstr);	
	strWildcard += _T("\\*.*");

	// start working for files
	BOOL bWorking = finder.FindFile(strWildcard);

	while (bWorking)
	{
		bWorking = finder.FindNextFile();

		// skip . and .. files; otherwise, we'd
		// recur infinitely!

		if (finder.IsDots())
			continue;

		// if it's a directory, recursively search it

		if (!finder.IsDirectory())
		{
			CString str = finder.GetFilePath();			
			m_strvecFilePath.push_back(str);
			//cout << (LPCTSTR) str << endl;
			//Recurse(str);
		}
		else
		{
			CString strPath = finder.GetFilePath();
			Recurse(strPath);
		}
	}

	finder.Close();
}

bool Public::isDirectory(CString filepath)
{	
	CFileFind cfind;
	cfind.FindFile(filepath);
	cfind.FindNextFile();
	if(cfind.IsDirectory())
		return true;	
	else		
		return false;
}

bool Public::writebackfile(CString path)
{
	CFile writefile;
	BYTE it;
	it = 0x55;
	writefile.Open(path, CFile::modeReadWrite|CFile::modeCreate|CFile::typeBinary);
	writefile.Write(&it, sizeof(it));
	writefile.Close();
	return true;
}
// myTable4.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Update.h"
#include "myTable4.h"
#include "myTable1.h"
#include "shlwapi.h"

// CmyTable4 �Ի���

IMPLEMENT_DYNAMIC(CmyTable4, CDialog)

CmyTable4::CmyTable4(CWnd* pParent /*=NULL*/)
	: CDialog(CmyTable4::IDD, pParent)
{

}

CmyTable4::~CmyTable4()
{
}

void CmyTable4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ADDSOFT, m_list);	
}


BEGIN_MESSAGE_MAP(CmyTable4, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SOFTADD, &CmyTable4::OnBnClickedButtonSoftadd)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &CmyTable4::OnBnClickedButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_MAKING, &CmyTable4::OnBnClickedButtonMaking)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CmyTable4 ��Ϣ�������


BOOL CmyTable4::OnInitDialog()
{
	CDialog::OnInitDialog();	

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_list.SetHorizontalExtent(800);
	m_strFileName = "softwareUpdata.7z";

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CmyTable4::OnBnClickedButtonSoftadd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
	//CString strtempPath;
	m_strPath = BrowseFolder(NULL,"��ѡ���������������ļ��У�");
	if (m_strPath == "")
		return;
	m_list.AddString(m_strPath);
	
	Recurse(m_strPath);
	for (int i=0;i<m_strvecFilePath.size();i++)
	{
		m_list.AddString(m_strvecFilePath[i]);
	}
}

void CmyTable4::OnBnClickedButtonRemove()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	while(m_list.GetCount()!=0)
		m_list.DeleteString(0);
	m_strvecFilePath.clear();
	
}

void CmyTable4::OnBnClickedButtonMaking()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_strvecFilePath.size()==0)
	{
		MessageBox("��û�����Ŀ¼","������ʾ��",MB_OK|MB_ICONWARNING);
		return;
	}
	while(m_list.GetCount()!=0)
	{
		m_list.DeleteString(0);
	}
	m_list.AddString("��ʼ�������������...");
	m_list.AddString("��ʼ��������...");
	MakingList(m_strPath);
	m_strvecFilePath.clear();
	m_list.AddString("��ʼ��������ϣ�");	
	
	m_strProcessCMD   =  GetMyPath()+'\\';
	m_strCompressFilePath = m_strProcessCMD;
	m_strProcessCMD   +=  "7za a " +m_strFileName+" \"" + m_strPath+'\"';
	//AfxMessageBox(m_strPath);
	m_strCompressFilePath  +=  m_strFileName;
	m_list.AddString("��ʼѹ����...");	
	AfxBeginThread(SoftPackMakingThread,this);
}

CString  CmyTable4::BrowseFolder(HWND hWnd, LPCTSTR lpTitle)
{    
	char szPath[MAX_PATH] = {0};
	BROWSEINFO m_bi;
	m_bi.ulFlags = BIF_RETURNONLYFSDIRS  | BIF_STATUSTEXT;
	m_bi.hwndOwner = hWnd;
	m_bi.pidlRoot = NULL;
	m_bi.lpszTitle = lpTitle;
	m_bi.lpfn = NULL;
	m_bi.lParam = NULL;
	m_bi.pszDisplayName = szPath;

	LPITEMIDLIST pidl = ::SHBrowseForFolder( &m_bi );
	if ( pidl )
			{
			if( !::SHGetPathFromIDList ( pidl, szPath ) )  szPath[0]=0;

			IMalloc * pMalloc = NULL;
			if ( SUCCEEDED ( ::SHGetMalloc( &pMalloc ) ) )  // ȡ��IMalloc�������ӿ�
			{
					pMalloc->Free( pidl );    // �ͷ��ڴ�
					pMalloc->Release();       // �ͷŽӿ�
			}
	}
	return szPath;
}
void CmyTable4::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	char *lpszFileName=new char[512];	
	int nFileCount,i; 
	nFileCount=::DragQueryFile (hDropInfo, 0xFFFFFFFF, NULL, 512); 
	m_strvecFilePath.clear();
	for (i=0; i< nFileCount; i++) 
	{ 		
		UINT nChars=::DragQueryFile (hDropInfo,i,&lpszFileName[0], 512);	    
		m_strPath = &lpszFileName[0];
		//�ж����ļ��л����ļ�		  
		if(isDirectory(m_strPath))
		{
			m_list.AddString(m_strPath);
			Recurse(m_strPath);
			for (int i=0;i<m_strvecFilePath.size();i++)
			{
				m_list.AddString(m_strvecFilePath[i]);
			}
		}
		else
		{
			MessageBox("��ȷ������ק�����ļ��У�","������ʾ��",MB_OK|MB_ICONWARNING);
		}
	} 	
	::DragFinish (hDropInfo);   // �� �� �� �� 	
	delete []lpszFileName;

	

	CDialog::OnDropFiles(hDropInfo);
}

void CmyTable4::Recurse(LPCTSTR pstr)
{
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

bool CmyTable4::MakingList(CString filepath)
{
	//Recurse(filepath);
	CString strtempOpenfile;
	strtempOpenfile = GetMyPath() + "\\softwareUpdata.dat";
	CString strtempOpenLastFile;
	strtempOpenLastFile = filepath + "\\endUpdata.dat";
	CStdioFile writefile;	
	writefile.Open(strtempOpenfile,CFile::modeCreate | CFile::modeReadWrite);
	CString strFormatOut;
	filepath = filepath.Left(filepath.ReverseFind('\\'));
	filepath+='\\';
	CString strtemp;
	CString strFileType;
	for (int i=0;i<m_strvecFilePath.size();i++)
	{	
		strtemp = m_strvecFilePath[i];
		strtemp.Replace(filepath,"");
		strtemp.Replace('\\','/');
		if (strtemp.ReverseFind('.')!=-1 && strtemp.ReverseFind('.')>strtemp.ReverseFind('/'))
		{
			strFileType = strtemp.Right(strtemp.GetLength()-strtemp.ReverseFind('.')-1);
		}
		else
		{
			strFileType = "NULL";
		}
		
		strFormatOut.Format("%d\t%s\t%s\n",i+1, strtemp, strFileType);
		writefile.WriteString(strFormatOut);
	}
	//д�����ļ�
	/*strFormatOut.Format("%d\t%s\t%s",m_strvecFilePath.size()+1, "endUpdata.dat", "end");
	writefile.WriteString(strFormatOut);
	CStdioFile WriteEndFile;	
	WriteEndFile.Open(strtempOpenLastFile,CFile::modeCreate | CFile::modeReadWrite);
	WriteEndFile.Write("0x55",4);
	WriteEndFile.Close();*/
	writefile.Close();
	return true;
}

UINT CmyTable4::SoftPackMakingThread(void *para)
{
	CmyTable4* pthis=reinterpret_cast<CmyTable4*>(para);
	if (PathFileExists(pthis->GetMyPath()+"\\"+pthis->m_strFileName))
	{
		DeleteFile(pthis->GetMyPath()+"\\"+pthis->m_strFileName);
	}
	pthis->RunExe(pthis->m_strProcessCMD);
	WaitForSingleObject(pthis->m_pidInfo.hProcess,INFINITE);
	CloseHandle(pthis->m_pidInfo.hProcess);
	CloseHandle(pthis->m_pidInfo.hThread);
	//���softwareUpdata.dat����Ŀ¼��
	CString strtempCMd;
	strtempCMd = pthis->GetMyPath()+"\\7za a "+pthis->m_strFileName+" \""+pthis->GetMyPath() + "\\softwareUpdata.dat" +"\"";
	pthis->RunExe(strtempCMd);	
	WaitForSingleObject(pthis->m_pidInfo.hProcess,INFINITE);
	CloseHandle(pthis->m_pidInfo.hProcess);
	CloseHandle(pthis->m_pidInfo.hThread);
	DeleteFile(pthis->GetMyPath() + "\\softwareUpdata.dat");
	pthis->m_list.AddString("���������ѹ����ϣ�");
	pthis->m_list.AddString("���ڼ������������...");
	if(pthis->m_EnDeCompress->AESCrptFile(pthis->m_strCompressFilePath, pthis->m_strCompressFilePath, ENCRYPTYKEY))
	{
		pthis->m_list.AddString("���������������ϣ�");
	}
	else
	{
		pthis->m_list.AddString("�������������ʧ�ܣ�");
		return 1;
	}
	pthis->m_list.AddString("���������������ϣ�");
	return 0;
}

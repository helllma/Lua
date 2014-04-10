// cemonitorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cemonitor.h"
#include "cemonitorDlg.h"

#define CURL_STATICLIB
long CcemonitorDlg::timeout=10;
long CcemonitorDlg::error=0;
curl_proxytype CcemonitorDlg::proxyType;
const TCHAR* CcemonitorDlg::proxy = NULL;
long CcemonitorDlg::proxyPort;
const TCHAR* CcemonitorDlg::usrAndPswd = NULL;
long CcemonitorDlg::tryTimes=7;

#include "src/WMHTTPSocket.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif




// CcemonitorDlg �Ի���

CcemonitorDlg::CcemonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CcemonitorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcemonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_CHECK, m_CheckProgress);
}

BEGIN_MESSAGE_MAP(CcemonitorDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_CHECK, &CcemonitorDlg::OnBnClickedButtonCheck)
END_MESSAGE_MAP()


// CcemonitorDlg ��Ϣ�������

BOOL CcemonitorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CcemonitorDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_CEMONITOR_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_CEMONITOR_DIALOG));
	}
}
#endif


void CcemonitorDlg::OnBnClickedButtonCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str_url = _T("http://10.111.34.243:8080");
	CString S_Buff;
	/*CInternetSession Sess;
	CHttpFile* cFile = (CHttpFile*)Sess.OpenURL(str_url,1,INTERNET_FLAG_TRANSFER_ASCII||INTERNET_FLAG_RELOAD||INTERNET_FLAG_DONT_CACHE,NULL ,0);
	DWORD dw_StatusCode = -1;
	if (cFile)
	{
		cFile->QueryInfoStatusCode(dw_StatusCode);
		S_Buff.Format(_T("%d"),dw_StatusCode);
		AfxMessageBox(S_Buff);
	}else{
		AfxMessageBox(_T("�õ�ַ�����쳣:")+str_url);
	}*/
	LONGLONG d_result = GetLength(str_url);
	S_Buff.Format(_T("%d"),d_result);
	AfxMessageBox(S_Buff);

}

CString GetRandomName(CString para)
{
	CString sendinfo;
	srand(GetTickCount());
	sendinfo.Format(_T("%s?%X%X%X%X%X%X%X%X%X"),para,rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand(),rand());
	return sendinfo;
}

LONGLONG CcemonitorDlg::GetLength( CString url )
{
	//CURLOPT_PUT;
	CURL *curl=NULL;
	curl = curl_easy_init();
	CString strUrl;
	strUrl = UnicodeToAnsi(/*GetRandomName(url)*/url);
	curl_easy_setopt(curl, CURLOPT_URL ,strUrl);
	curl_easy_setopt(curl, CURLOPT_NOBODY , 1);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);
	if(proxy!=NULL)
	{
		switch(proxyType)
		{
		case CURLPROXY_HTTP:
		case CURLPROXY_SOCKS4:
		case CURLPROXY_SOCKS5:
			curl_easy_setopt(curl, CURLOPT_PROXYTYPE,proxyType);
			break;
		}
		curl_easy_setopt(curl, CURLOPT_PROXY,CW2A(proxy));
		curl_easy_setopt(curl, CURLOPT_PROXYPORT,proxyPort);
		if(usrAndPswd!=NULL)
		{
			curl_easy_setopt(curl, CURLOPT_PROXYAUTH,CURLAUTH_ANY);
			curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD,CW2A(usrAndPswd));
		}
	}
	//curl_easy_setopt(curl, CURLOPT_RANGE,"0-");
	//CURL_CONTENT_LENGTH length={curl,0.0};
	CURLcode err=CURLE_OK;
	long code;
	LONGLONG len=0;
	long tr=0;
	err=curl_easy_perform(curl); /* ignores error */
	while (err==CURLE_OPERATION_TIMEDOUT&&tr++<tryTimes)
	{
		//AfxMessageBox("retry");
		curl_easy_perform(curl);
	}
	//if(err!=CURLE_OK)
	//{
	//	switch (err)
	//	{
	//	case CURLE_COULDNT_RESOLVE_HOST:
	//		TRACE("�޷����ӷ�����");
	//		//throw "�޷����ӷ�����";
	//		break;
	//	case CURLE_OPERATION_TIMEDOUT:
	//		TRACE("��ʱ");
	//		//throw "��ʱ";
	//		break;
	//	case CURLE_COULDNT_RESOLVE_PROXY:
	//		TRACE("�������������");
	//		//throw "�������������";
	//		break;
	//	//case CURLE_REMOTE_FILE_NOT_FOUND:
	//	//	TRACE("�ļ�������");
	//	//	break;
	//	case CURLE_OK:
	//		break;
	//	default:
	//		{
	//			CString s;
	//			s.Format("%d",err);
	//			TRACE(s);
	//		}
	//		break;
	//	}
	//}
	curl_easy_getinfo(curl,CURLINFO_RESPONSE_CODE,&code);
	curl_easy_getinfo(curl,CURLINFO_CONTENT_LENGTH_DOWNLOAD,&len);
	curl_easy_cleanup(curl);
	if(code!=200)
		return -code;
	return len;
}

char* CcemonitorDlg::UnicodeToAnsi(const TCHAR *sz)
{  

	DWORD dwNum = WideCharToMultiByte(CP_OEMCP,NULL,sz,-1,NULL,0,NULL,FALSE);
	char *szANSIString;
	szANSIString = new char[dwNum];
	if(!szANSIString)
	{
		delete []szANSIString;
	}
	WideCharToMultiByte (CP_OEMCP,NULL,sz,-1,szANSIString,dwNum,NULL,FALSE);
	return szANSIString;
}

CString CcemonitorDlg::AnsiToUnicodeT(char *sz)
{  

	DWORD dwMinSize;
	dwMinSize = MultiByteToWideChar (CP_ACP, 0, sz, -1, NULL, 0);
	TCHAR *szWideProgID =new TCHAR[dwMinSize];
	long    lLen    =    MultiByteToWideChar(CP_ACP,0,sz,(int)strlen(sz),szWideProgID,dwMinSize);   
	szWideProgID[lLen]    =    '\0'; 
	CString str;
	str.Format(L"%s",szWideProgID);
	return str;
}

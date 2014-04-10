// myTable1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Update.h"
#include "myTable1.h"
#include "UpdateDlg.h"
#include "Public.h"
#include "shlwapi.h"
  
// CmyTable1 �Ի���

IMPLEMENT_DYNAMIC(CmyTable1, CDialog)

CmyTable1::CmyTable1(CWnd* pParent /*=NULL*/)
: CDialog(CmyTable1::IDD, pParent)
{

}

CmyTable1::~CmyTable1()
{
}

void CmyTable1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_BIOS, m_combBios);
	DDX_Control(pDX, IDC_COMBO_SOFT, m_combSoft);
	DDX_Control(pDX, IDC_LIST_UPDATEINFO, m_list);
}


BEGIN_MESSAGE_MAP(CmyTable1, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_BIOS, &CmyTable1::OnBnClickedButtonBios)
	ON_BN_CLICKED(IDC_BUTTON_SOFT, &CmyTable1::OnBnClickedButtonSoft)
	ON_BN_CLICKED(IDC_BUTTON_BEGIN, &CmyTable1::OnBnClickedButtonBegin)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CmyTable1::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CmyTable1 ��Ϣ�������

void CmyTable1::OnBnClickedButtonBios()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString filetype;
	filetype = "*.dat(*.dat)|*.dat|all(*.*)|*.*|";
	CFileDialog dlg(TRUE,NULL,"firmwareUpdata.dat",OFN_OVERWRITEPROMPT,filetype);
	if(dlg.DoModal() == IDOK)
	{	
		m_strBiosUpdateFilePath = dlg.GetPathName();
		m_combBios.SetWindowText(m_strBiosUpdateFilePath);
		UpdateData(false);
		m_strBiosUpdateFilePath = m_strBiosUpdateFilePath.Left(m_strBiosUpdateFilePath.ReverseFind('\\')+1);
		int strLength = m_strBiosUpdateFilePath.GetLength() + 1;
		m_strFileName = new char[strLength];
		strncpy(m_strFileName, m_strBiosUpdateFilePath, strLength);	

		m_strSoftUpdateFilePath = "";
		m_combSoft.SetWindowText(m_strSoftUpdateFilePath);
		UpdateData(false);
		m_list.DeleteString(0);
		m_list.AddString("�̼���������ѡ��");

		//����tftp����
		//AfxBeginThread(StartTftpServerThread,this);	
		//AfxMessageBox("tftp�����������ļ�·����"+m_strBiosUpdateFilePath);
		
	}
	//delete dlg;
}

void CmyTable1::OnBnClickedButtonSoft()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString filetype;
	filetype = "all(*.*)|*.*|";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_OVERWRITEPROMPT,filetype);
	if(dlg.DoModal() == IDOK)
	{	
		CString strTempTftpPath;
		m_strSoftUpdateFilePath = dlg.GetPathName();
		m_combSoft.SetWindowText(m_strSoftUpdateFilePath);
		UpdateData(false);		
        m_strProcessCMD   =  GetMyPath()+"\\7za x \"";		
		m_strProcessCMD += m_strSoftUpdateFilePath + ".tmp\" -otemp";		
		strTempTftpPath = m_strSoftUpdateFilePath.Left(m_strSoftUpdateFilePath.ReverseFind('\\')+1);		
		strTempTftpPath += "temp\\";
		//m_strFileName = temp.GetBuffer(temp.GetLength()+1);
		//���ļ�·������tftp�����̡߳�
		int strLength = strTempTftpPath.GetLength() + 1;
		m_strFileName = new char[strLength];
		strncpy(m_strFileName, strTempTftpPath, strLength);	
		//ȷ��BIOS���������ֻ��ѡ��һ��
		m_strBiosUpdateFilePath = "";
		m_combBios.SetWindowText(m_strBiosUpdateFilePath);
		UpdateData(false);
		m_list.DeleteString(0);
		m_list.AddString("�����������ѡ��");
		//AfxMessageBox(m_strSoftUpdateFilePath+"\n"+strTempTftpPath);		 
		
		//����tftp����
		/*AfxBeginThread(StartTftpServerThread,dynamic_cast<CmyTftpServer*>(this));
		m_list.AddString("tftp�����������ļ�·����");
		m_list.AddString(strTempTftpPath);*/
		//AfxMessageBox("tftp�����������ļ�·����"+strTempTftpPath);
	}
	//delete dlg;
}

void CmyTable1::OnBnClickedButtonBegin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_strLimiteIP =="")
	{
		MessageBox("�������ò�����","������ʾ��",MB_OK|MB_ICONWARNING);
		return;
	}
	if (m_strSoftUpdateFilePath!="")
	{
		m_list.AddString("���ڳ�ʼ����������...");
		DelTree(m_strFileName);
		AfxBeginThread(SoftUpdateThread,this);		
	}
	else if (m_strBiosUpdateFilePath!="")
	{
		AfxBeginThread(StartTftpServerThread, this);
		//m_list.AddString("tftp�����������ļ�·����");
		//m_list.AddString(m_strBiosUpdateFilePath);
	}
		
}

UINT CmyTable1::SoftUpdateThread(void *para)
{
	CmyTable1* pthis=reinterpret_cast<CmyTable1*>(para);
	pthis->m_list.AddString("���ڽ������������...");
	pthis->m_strDecryptPath = pthis->m_strSoftUpdateFilePath+".tmp";
	if(pthis->m_EnDeCompress->AESEncrptFile(pthis->m_strSoftUpdateFilePath, pthis->m_strDecryptPath,DECRYPTYKEY))
	{
		if (pthis->IsEmptyFile(pthis->m_strDecryptPath))
		{
			pthis->m_list.AddString("�������������ʧ��,��ȷ��ѡ������ȷ�������ļ���");
			return 1;
		}
		else
		{
			pthis->m_list.AddString("���������������ϣ�");
		}
		
	}
	else
	{
		pthis->m_list.AddString("�������������ʧ��,��ȷ��ѡ������ȷ�������ļ���");
		return 1;
	}
	pthis->m_list.AddString("���ڽ�ѹ���������...");
	pthis->RunExe(pthis->m_strProcessCMD);
	WaitForSingleObject(pthis->m_pidInfo.hProcess,INFINITE);
	CloseHandle(pthis->m_pidInfo.hProcess);
	CloseHandle(pthis->m_pidInfo.hThread);	
	pthis->m_list.AddString("�����������ѹ��ϣ�");
	DeleteFile(pthis->m_strDecryptPath);
	AfxBeginThread(pthis->StartTftpServerThread, pthis);
	
	/*pthis->m_list.AddString("tftp�����������ļ�·����");
	pthis->m_list.AddString(pthis->m_strFileName);*/
	return 0;
}


void CmyTable1::OnBnClickedButtonClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_strSoftUpdateFilePath = "";
	m_strBiosUpdateFilePath = "";
	m_combBios.SetWindowText(m_strBiosUpdateFilePath);
	m_combSoft.SetWindowText(m_strSoftUpdateFilePath);
	UpdateData(false);
	while(m_list.GetCount()!=0)
	{
		m_list.DeleteString(0);
	}
}

bool  CmyTable1::IsEmptyFile(CString path)
{
	CFile Readfile;
	Readfile.Open(path,CFile::readOnly);
	if (Readfile.GetLength() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
	Readfile.Close();
}

UINT CmyTable1::StartTftpServerThread(void* para)
{
	CmyTable1 *pthis=reinterpret_cast<CmyTable1*>(para);

	struct sockaddr_in adresse;
	int lg=sizeof(adresse),n;
	int desc_socket;
	char   buf[PKTSIZE];
	struct tftphdr *tp=(tftphdr *)buf;	

	pthis->m_nTimeOut=3;
	pthis->m_nNumberTimeOut=7;	
	pthis->m_nPortTFTP = 19191; 
	WSADATA wsaData;
	WSAStartup( MAKEWORD( 2, 1 ), &wsaData );
	if ((desc_socket=pthis->creer_socket(SOCK_DGRAM, &pthis->m_nPortTFTP, NULL)) == -1)
	{
		//	    syslog(LOG_ERR,"creation socket serveur: %m.\n");
		//printf("creation socket serveur: error.\n");
		pthis->m_list.AddString("����tftp����ʧ�ܣ�");
		WSACleanup();
		return 2;
	}

	//    syslog(LOG_DAEMON,"standard_tftp_server launched on port %i.\n", PortTFTP);
	//printf("standard_tftp_server launched on port %i.\n",pthis->m_nPortTFTP);
	pthis->m_list.AddString("����tftp����ɹ���");
	CString tempadd;
	tempadd.Format("%s%s","·����",pthis->m_strFileName);
	pthis->m_list.AddString(tempadd);
	
	while (1)
	{
		do
		{
			n=recvfrom(desc_socket,(char *)tp,PKTSIZE,0,(sockaddr *)&adresse,(int*)&lg);
			if(pthis->m_bExitFlag)
			{
				pthis->m_list.AddString("����ֹͣ��");
				return 2;
			}
		}
		while (n<0);
		ULONG getip = adresse.sin_addr.S_un.S_addr;
		/*ULONG t = ntohl(getip);
		CString tempadd1;
		tempadd1.Format("%d",t);
		pthis->m_list.AddString(tempadd1);*/
		//pthis->m_strLimiteIP = "10.0.14.152";
		CString diplayip;
		diplayip = inet_ntoa(adresse.sin_addr);
		pthis->m_list.AddString("�û���"+diplayip+"���ӵ���������");
		//AfxMessageBox(pthis->m_strLimiteIP);
		if(inet_addr(pthis->m_strLimiteIP)==getip)
		{
			pthis->m_list.AddString("�û�IPУ����ȷ��");
			//fprintf(stderr,"connection.\n");
			CString temp = &tp->th_stuff[0];
			pthis->m_list.AddString("���ڴ��䣺"+temp);
			//temp.Format("%s",tp->tu_stuff);
			tp->th_opcode=htons((u_short)tp->th_opcode);
			if ((tp->th_opcode == WRQ)||(tp->th_opcode == RRQ))
				pthis->tftp_connection(adresse,tp->th_opcode,&tp->th_stuff[0]);
			if ((tp->th_opcode == RRQ) && temp.CompareNoCase("endUpdata.dat")==0)
			{
				pthis->writebackfile(pthis->GetMyPath()+'\\'+"endUpdata.dat");
				pthis->m_list.AddString("������ϣ�");
				/*WSACleanup();
				return 0;*/
			}
		}
		else
		{
			pthis->m_list.AddString("���û�IPδͨ����֤��");
		}		
	}
}

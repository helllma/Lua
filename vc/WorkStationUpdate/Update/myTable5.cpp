// myTable5.cpp : 实现文件
//

#include "stdafx.h"
#include "Update.h"
#include "myTable5.h"
#include "map"
using namespace std;


// CmyTable5 对话框

IMPLEMENT_DYNAMIC(CmyTable5, CDialog)

CmyTable5::CmyTable5(CWnd* pParent /*=NULL*/)
	: CDialog(CmyTable5::IDD, pParent)
{
}

CmyTable5::~CmyTable5()
{
}

void CmyTable5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);	
	DDX_Control(pDX, IDC_LIST_CHECK, m_list);
}


BEGIN_MESSAGE_MAP(CmyTable5, CDialog)
	ON_BN_CLICKED(IDC_BUTTONT_BEGIN, &CmyTable5::OnBnClickedButtontBegin)
	ON_BN_CLICKED(IDC_BUTTONT_RESET, &CmyTable5::OnBnClickedButtontReset)
	ON_BN_CLICKED(IDC_BUTTONT_END, &CmyTable5::OnBnClickedButtontEnd)
END_MESSAGE_MAP()


// CmyTable5 消息处理程序

BOOL CmyTable5::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化	
	CString strSignal;
	CString strState;
	CString strIniPath = GetMyPath();
	for (int i=0;strSignal!=_T("READ FILE FAILE!!")|| strState!=_T("READ FILE FAILE!!");i++)
	{
		CString strCheckName = _T("CHECK");
		int j = i + 1;
		char num[128];
		itoa(j, num, 10);
		strCheckName+=num;
		GetPrivateProfileString(strCheckName, _T("signal"), _T("READ FILE FAILE!!"), strSignal.GetBuffer(128), 128, strIniPath + _T("\\setinfo.ini"));
		strSignal.ReleaseBuffer();
		GetPrivateProfileString(strCheckName, _T("state"),  _T("READ FILE FAILE!!"), strState.GetBuffer(512), 512, strIniPath + _T("\\setinfo.ini"));
		strState.ReleaseBuffer();
		m_vecSignal.push_back(strSignal);
		m_vecState.push_back(strState);
		if (m_vecSignal.size()!=m_vecState.size())
		{
			if(MessageBox(strIniPath + _T("\\setinfo.ini")+"文件配置错误，请重新配置，继续运行可能会导致错误，继续吗?","错误提示：",MB_YESNO|MB_ICONWARNING)!=IDYES)
			{
				exit(1);
			}
		}		
	}
	m_strFileName = new char[GetMyPath().GetLength()+1];
	strncpy(m_strFileName, GetMyPath(), GetMyPath().GetLength()+1);
	strcat(m_strFileName, "\\");
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

UINT CmyTable5::StartTftpServerThread(void* para)
{
	CmyTable5 *pthis=reinterpret_cast<CmyTable5*>(para);

	struct sockaddr_in adresse;
	int lg=sizeof(adresse),n;
	int desc_socket;
	char   buf[PKTSIZE];
	struct tftphdr *tp=(tftphdr *)buf;	

	pthis->m_nTimeOut=3;
	pthis->m_nNumberTimeOut=7;	
	pthis->m_nPortTFTP = 69; 
	WSADATA wsaData;
	WSAStartup( MAKEWORD( 2, 1 ), &wsaData );
	if ((desc_socket=pthis->creer_socket(SOCK_DGRAM, &pthis->m_nPortTFTP, NULL)) == -1)
	{
		//	    syslog(LOG_ERR,"creation socket serveur: %m.\n");
		//printf("creation socket serveur: error.\n");
		pthis->m_list.AddString("启动tftp服务失败！");
		WSACleanup();
		return 2;
	}

	//    syslog(LOG_DAEMON,"standard_tftp_server launched on port %i.\n", PortTFTP);
	//printf("standard_tftp_server launched on port %i.\n",pthis->m_nPortTFTP);
	pthis->m_list.AddString("启动tftp服务成功！");
	CString tempadd;
	tempadd.Format("%s%s","路径：",pthis->m_strFileName);
	pthis->m_list.AddString(tempadd);
	CString tempcomp;
	while (1)
	{		
		do
		{
			n=recvfrom(desc_socket,(char *)tp,PKTSIZE,0,(sockaddr *)&adresse,(int*)&lg);
			if(pthis->m_bExitFlag)
			{
				pthis->m_list.AddString("服务停止！");
				return 2;
			}
			
		}
		while (n<0);
		tp->th_opcode=htons((u_short)tp->th_opcode);
		ULONG getip = adresse.sin_addr.S_un.S_addr;
	/*	ULONG t = ntohl(getip);
		CString tempadd1;
		tempadd1.Format("%d",t);
		pthis->m_list.AddString(tempadd1);*/
		//pthis->m_strLimiteIP = "10.0.14.152";
		CString diplayip;
		diplayip = inet_ntoa(adresse.sin_addr);
		pthis->m_list.AddString("用户："+diplayip+"连接到服务器！");
		//AfxMessageBox(pthis->m_strLimiteIP);
		if(inet_addr(pthis->m_strLimiteIP)==getip)
		{			
			//fprintf(stderr,"connection.\n");
			CString temp = &tp->th_stuff[0];			
			if (temp!=tempcomp)
			{
				tempcomp = temp;
				//pthis->m_list.AddString("用户IP校验正确。");
				pthis->m_list.AddString("正在传输："+temp);
				//temp.Format("%s",tp->tu_stuff);				
				if (tp->th_opcode == RRQ)
				{
					for (int i=0;i<pthis->m_vecSignal.size();i++)
					{
						if (temp.CompareNoCase(pthis->m_vecSignal[i])==0)
						{
							pthis->m_list.AddString(pthis->m_vecState[i]);						
							pthis->writebackfile(pthis->GetMyPath()+'\\'+pthis->m_vecSignal[i]);
							if(pthis->m_vecState[i].Find("确认")==0)
							{
								pthis->MessageBox(pthis->m_vecState[i],"确认：",MB_OK|MB_ICONINFORMATION);
							}
							
						}						
					}
					if (temp.CompareNoCase("endUpdata.dat")==0)
						{
							pthis->writebackfile(pthis->GetMyPath()+'\\'+"endUpdata.dat");
							pthis->m_list.AddString("校验完毕！");
							/*WSACleanup();
							return 0;*/
						}
				}					
			}
		}
		else
		{
			pthis->m_list.AddString("该用户IP未通过验证。");
		}		
		if ((tp->th_opcode == WRQ)||(tp->th_opcode == RRQ))
		{
			pthis->tftp_connection(adresse,tp->th_opcode,&tp->th_stuff[0]);
		}
			
	}
}
void CmyTable5::OnBnClickedButtontBegin()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxBeginThread(StartTftpServerThread,this);	
}

void CmyTable5::OnBnClickedButtontReset()
{
	// TODO: 在此添加控件通知处理程序代码
	while(m_list.GetCount()!=0)
		m_list.DeleteString(0);
	EndThread();
	AfxBeginThread(StartTftpServerThread,this);
}

void CmyTable5::OnBnClickedButtontEnd()
{
	// TODO: 在此添加控件通知处理程序代码
	EndThread();
}


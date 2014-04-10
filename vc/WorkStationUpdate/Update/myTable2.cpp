// myTable2.cpp : 实现文件
//

#include "stdafx.h"
#include "Update.h"
#include "myTable2.h"
#include "atlimage.h"



// CmyTable2 对话框

IMPLEMENT_DYNAMIC(CmyTable2, CDialog)

CmyTable2::CmyTable2(CWnd* pParent /*=NULL*/)
	: CDialog(CmyTable2::IDD, pParent)
{

}

CmyTable2::~CmyTable2()
{
}

void CmyTable2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_SetType);
	DDX_Control(pDX, IDC_STATIC_PIC, m_pic);
	DDX_Control(pDX, IDC_IPADDRESS_SETIP, m_IP);
}


BEGIN_MESSAGE_MAP(CmyTable2, CDialog)
//	ON_CBN_SELENDOK(IDC_COMBO1, &CmyTable2::OnCbnSelendokCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CmyTable2::OnCbnSelchangeCombo1)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_SET, &CmyTable2::OnBnClickedButtonSet)
END_MESSAGE_MAP()


// CmyTable2 消息处理程序

BOOL CmyTable2::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化	
	
	CString strIniPath;
	CString strSetTypeName;	
	CString strTempSetPicPath;	
	strIniPath = GetMyPath();
	//读取.ini文件配置--------------------------------------------------------------------------
	int i = 0;
	while(strSetTypeName != _T("READ FILE FAILE!!") || strTempSetPicPath == _T("READ FILE FAILE!!"))
	{	  
		CString strSetName;
		int j = i + 1;
		strSetName = _T("SET");
		char num[128];
		itoa(j, num, 10);
		strSetName+=num;
		//strSetName.Format(_T("%s%d"), strSetName, j);
		GetPrivateProfileString(strSetName, _T("SETTYPENAME"), _T("READ FILE FAILE!!"), strSetTypeName.GetBuffer(128), 128, strIniPath + _T("\\setinfo.ini"));
		strSetTypeName.ReleaseBuffer();
		GetPrivateProfileString(strSetName, _T("SETTYPEPICPATH"), _T("READ FILE FAILE!!"), strTempSetPicPath.GetBuffer(512), 512, strIniPath + _T("\\setinfo.ini"));
		strTempSetPicPath.ReleaseBuffer();
		if (strSetTypeName == _T("READ FILE FAILE!!") || strTempSetPicPath == _T("READ FILE FAILE!!"))
		{
			if (i==0)
			{
				MessageBox("读取setinfo.ini文件失败！程序即将退出。","错误提示：",MB_OK|MB_ICONWARNING);
				exit(1);
			}			
			break;
		}
		strTempSetPicPath = strIniPath +strTempSetPicPath;	
		if(PathFileExists(strTempSetPicPath))
			m_strSetPicPath.push_back(strTempSetPicPath);		
		m_SetType.InsertString(i, strSetTypeName);		
		i++;
	}
	/*m_SetType.InsertString(0,"型号1");
	m_SetType.InsertString(1,"型号2");
	m_SetType.InsertString(2,"型号3");*/
	m_SetType.SetCurSel(0);
	if(m_strSetPicPath.size() != 0)
	{
		m_strPicPath = m_strSetPicPath[0];	
		ShowPic(m_strPicPath);
	}
	else
	{
		MessageBox("未找到设备图片，请检查setinfo.ini确认图片存在。","错误提示：",MB_OK|MB_ICONWARNING);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

//void CmyTable2::OnCbnSelendokCombo1()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	
//	
//}

void CmyTable2::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	int nselect = m_SetType.GetCurSel();
	if (m_strSetPicPath.size()!=0)
	{
		m_strPicPath = m_strSetPicPath[nselect];
		ShowPic(m_strPicPath);
	}
	else
	{
		MessageBox("未找到设备图片，请检查setinfo.ini确认图片存在。","错误提示：",MB_OK|MB_ICONWARNING);
	}
	
	/*switch (nselect)
	{
	case 0:
		{
			m_strPicPath = ".\\pic\\pic01.jpg";
			ShowPic(m_strPicPath);
		}
		 
		break;
	case 1:
		m_strPicPath = ".\\pic\\pic02.jpg";
		ShowPic(m_strPicPath);
		break;
	case 2:
		m_strPicPath = ".\\pic\\pic03.jpg";
		ShowPic(m_strPicPath);
		break;
	default:
		break;
	}*/
}

void CmyTable2::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	CDialog::OnPaint();     //重绘对话框
	CDialog::UpdateWindow(); //更新windows窗口，如果无这步调用，图片显示还会出现问题
	if (PathFileExists(m_strPicPath))
		ShowPic(m_strPicPath);   //重绘图片函数
}

void CmyTable2::ShowPic(CString picpath)
{	
	CRect rect;
	m_pic.GetClientRect(&rect);     
	CImage image; 
	image.Load(picpath); 
	CDC* pDC = m_pic.GetWindowDC();
	image.Draw( pDC -> m_hDC,rect);
	ReleaseDC(pDC);
}


CString CmyTable2::GetLocalIP(BOOL OnlyFirst)
{
	WORD wVersionRequested;
	WSADATA wsaData;
	char name[MAX_PATH];
	CString ip="";
	PHOSTENT hostinfo;
	wVersionRequested = MAKEWORD( 2, 2 );

	if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
	{
		if( gethostname ( name, sizeof(name)) == 0)
		{
			if((hostinfo = gethostbyname(name)) != NULL)
			{
				for(int i = 0; hostinfo!= NULL && hostinfo->h_addr_list[i]!= NULL; i++ )  
				{
					ip+=inet_ntoa (*(struct in_addr *)hostinfo->h_addr_list[i]); 
					if(OnlyFirst) break;
					if(hostinfo->h_addr_list[i+1]!=NULL)  ip+=",";
				} 
			}
		}

		WSACleanup( );
	} 

	return ip;
}


void CmyTable2::OnBnClickedButtonSet()
{
	// TODO: 在此添加控件通知处理程序代码
	BYTE para1,para2,para3,para4;
	m_IP.GetAddress(para1,para2,para3,para4);
	m_strLimiteIP.Format("%d.%d.%d.%d",para1,para2,para3,para4);
	//MessageBox(m_strLimiteIP,"错误提示：",MB_OK|MB_ICONWARNING);
	AfxMessageBox(m_strLimiteIP);
}

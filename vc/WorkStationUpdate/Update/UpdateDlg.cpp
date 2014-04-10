// UpdateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Update.h"
#include "UpdateDlg.h"
#include "MyTable.h"
#include "Iphlpapi.h"
#pragma comment(lib,"Iphlpapi.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CUpdateDlg 对话框




CUpdateDlg::CUpdateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUpdateDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_myTable);
}

BEGIN_MESSAGE_MAP(CUpdateDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CUpdateDlg::OnTcnSelchangeTab1)
	//ON_BN_CLICKED(IDOK, &CUpdateDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CUpdateDlg 消息处理程序

BOOL CUpdateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetWorkStationIP("");
	
	//m_strFileName = "e:\\";
	//启动tftp服务
	//AfxBeginThread(StartTftpServerThread,this);


	m_myTable.InsertItem(0,"升级选择");
	m_myTable.InsertItem(1,"参数选择");
#ifndef __PUBLIC
	m_myTable.InsertItem(2,"固件升级包制作");
	m_myTable.InsertItem(3,"软件升级包制作");
	m_myTable.InsertItem(4,"设备自检");
#endif
	m_myTable1.Create(IDD_TABLE1, GetDlgItem(IDC_TAB1));
	m_myTable2.Create(IDD_TABLE2, GetDlgItem(IDC_TAB1));
#ifndef __PUBLIC
	m_myTable3.Create(IDD_TABLE3, GetDlgItem(IDC_TAB1));
	m_myTable4.Create(IDD_TABLE4, GetDlgItem(IDC_TAB1));
	m_myTable5.Create(IDD_TABLE5, GetDlgItem(IDC_TAB1));
#endif

	CRect rs;
	m_myTable.GetClientRect(&rs);
	rs.top+=22;
	rs.bottom-=20;
	rs.left+=3;
	rs.right-=3;
	m_myTable1.MoveWindow(&rs);
	m_myTable2.MoveWindow(&rs);
#ifndef __PUBLIC
	m_myTable3.MoveWindow(&rs);
	m_myTable4.MoveWindow(&rs);
	m_myTable5.MoveWindow(&rs);
#endif

	m_myTable1.ShowWindow(false);
	m_myTable2.ShowWindow(true);
#ifndef __PUBLIC
	m_myTable3.ShowWindow(false);
	m_myTable4.ShowWindow(false);
	m_myTable5.ShowWindow(false);
#endif
	m_myTable.SetCurSel(1);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUpdateDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUpdateDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CUpdateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CUpdateDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int CerSel = m_myTable.GetCurSel();
	switch (CerSel)
	{
	case 0 :
		m_myTable1.ShowWindow(true);
		m_myTable2.ShowWindow(false);
		m_myTable3.ShowWindow(false);
		m_myTable4.ShowWindow(false);
		m_myTable5.ShowWindow(false);
		break;
	case 1 :
		m_myTable1.ShowWindow(false);
		m_myTable2.ShowWindow(true);
		m_myTable3.ShowWindow(false);
		m_myTable4.ShowWindow(false);
		m_myTable5.ShowWindow(false);
		break;
	case 2:
		m_myTable1.ShowWindow(false);
		m_myTable2.ShowWindow(false);
		m_myTable3.ShowWindow(true);
		m_myTable4.ShowWindow(false);
		m_myTable5.ShowWindow(false);
		break;
	case 3:
		m_myTable1.ShowWindow(false);
		m_myTable2.ShowWindow(false);
		m_myTable3.ShowWindow(false);
		m_myTable4.ShowWindow(true);
		m_myTable5.ShowWindow(false);
		break;
	case 4:
		m_myTable1.ShowWindow(false);
		m_myTable2.ShowWindow(false);
		m_myTable3.ShowWindow(false);
		m_myTable4.ShowWindow(false);
		m_myTable5.ShowWindow(true);
		break;
	default :
		;
	}

	*pResult = 0;
}

void CUpdateDlg::SetWorkStationIP(CString IP)
{
	return;
	ULONG ulAdapterInfoSize = sizeof(IP_ADAPTER_INFO);
	IP_ADAPTER_INFO *pAdapterInfoBkp, *pAdapterInfo = (IP_ADAPTER_INFO*)new char[ulAdapterInfoSize];
	if( GetAdaptersInfo(pAdapterInfo, &ulAdapterInfoSize) == ERROR_BUFFER_OVERFLOW ) // 缓冲区不够大
	{
		delete pAdapterInfo;
		pAdapterInfo = (IP_ADAPTER_INFO*)new char[ulAdapterInfoSize];
		pAdapterInfoBkp = pAdapterInfo;
	}
	if( GetAdaptersInfo(pAdapterInfo, &ulAdapterInfoSize) == ERROR_SUCCESS )
	{
		do{ // 遍历所有适配器
			if(pAdapterInfo->Type == MIB_IF_TYPE_ETHERNET)	// 判断是否为以太网接口
			{
				// pAdapterInfo->Description 是适配器描述
				// pAdapterInfo->AdapterName 是适配器名称
				CString tmp;
				tmp.Format("%s\t%s",pAdapterInfo->AdapterName,pAdapterInfo->Description);
				AfxMessageBox(tmp);
			}
			pAdapterInfo = pAdapterInfo->Next;
		}while(pAdapterInfo);
	}
	delete pAdapterInfoBkp;
}

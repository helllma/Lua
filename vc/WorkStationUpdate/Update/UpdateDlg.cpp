// UpdateDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CUpdateDlg �Ի���




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


// CUpdateDlg ��Ϣ�������

BOOL CUpdateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetWorkStationIP("");
	
	//m_strFileName = "e:\\";
	//����tftp����
	//AfxBeginThread(StartTftpServerThread,this);


	m_myTable.InsertItem(0,"����ѡ��");
	m_myTable.InsertItem(1,"����ѡ��");
#ifndef __PUBLIC
	m_myTable.InsertItem(2,"�̼�����������");
	m_myTable.InsertItem(3,"�������������");
	m_myTable.InsertItem(4,"�豸�Լ�");
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CUpdateDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CUpdateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CUpdateDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	if( GetAdaptersInfo(pAdapterInfo, &ulAdapterInfoSize) == ERROR_BUFFER_OVERFLOW ) // ������������
	{
		delete pAdapterInfo;
		pAdapterInfo = (IP_ADAPTER_INFO*)new char[ulAdapterInfoSize];
		pAdapterInfoBkp = pAdapterInfo;
	}
	if( GetAdaptersInfo(pAdapterInfo, &ulAdapterInfoSize) == ERROR_SUCCESS )
	{
		do{ // ��������������
			if(pAdapterInfo->Type == MIB_IF_TYPE_ETHERNET)	// �ж��Ƿ�Ϊ��̫���ӿ�
			{
				// pAdapterInfo->Description ������������
				// pAdapterInfo->AdapterName ������������
				CString tmp;
				tmp.Format("%s\t%s",pAdapterInfo->AdapterName,pAdapterInfo->Description);
				AfxMessageBox(tmp);
			}
			pAdapterInfo = pAdapterInfo->Next;
		}while(pAdapterInfo);
	}
	delete pAdapterInfoBkp;
}

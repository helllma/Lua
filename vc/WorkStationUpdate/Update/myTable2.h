#pragma once
#include "afxwin.h"
#include "vector"
#include<winsock2.h>
#include "afxcmn.h"
#include "CmyTftpServer.h"
#include "public.h"
#pragma comment(lib,"Wsock32.lib")
using namespace std;


// CmyTable2 �Ի���

class CmyTable2 : public CDialog, public CmyTftpServer, public Public
{
	DECLARE_DYNAMIC(CmyTable2)

public:
	CmyTable2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CmyTable2();

// �Ի�������
	enum { IDD = IDD_TABLE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_SetType;
	virtual BOOL OnInitDialog();
//	afx_msg void OnCbnSelendokCombo1();
	afx_msg void OnCbnSelchangeCombo1();
	CStatic m_pic;
	afx_msg void OnPaint();
	void ShowPic(CString picpath);
	CString m_strPicPath;
	CString GetLocalIP(BOOL OnlyFirst=TRUE);
	vector<CString> m_strSetPicPath;
	CIPAddressCtrl m_IP;
	afx_msg void OnBnClickedButtonSet();
};

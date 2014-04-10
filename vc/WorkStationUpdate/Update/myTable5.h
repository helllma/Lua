#pragma once
#include "afxwin.h"
#include "CmyTftpServer.h"
#include "Public.h"
#include "vector"
using namespace std;


// CmyTable5 对话框

class CmyTable5 : public CDialog, public CmyTftpServer, public Public
{
	DECLARE_DYNAMIC(CmyTable5)

public:
	CmyTable5(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CmyTable5();

// 对话框数据
	enum { IDD = IDD_TABLE5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	static UINT StartTftpServerThread(void* para);
	CListBox m_list;
	afx_msg void OnBnClickedButtontBegin();
	afx_msg void OnBnClickedButtontReset();
private:
	vector<CString> m_vecSignal;
	vector<CString> m_vecState;	
public:
	afx_msg void OnBnClickedButtontEnd();
};

// UpdateDlg.h : 头文件
//

#pragma once
#include "myTable1.h"
#include "myTable2.h"
#include "myTable3.h"
#include "myTable4.h"
#include "myTable5.h"
#include "public.h"

// CUpdateDlg 对话框
class CUpdateDlg : public CDialog, public Public
{
// 构造
public:
	CUpdateDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_UPDATE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_myTable;
	CmyTable1 m_myTable1;
	CmyTable2 m_myTable2;
	CmyTable3 m_myTable3;
	CmyTable4 m_myTable4;
	CmyTable5 m_myTable5;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	void SetWorkStationIP(CString IP);
};

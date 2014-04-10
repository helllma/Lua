#pragma once


// CMyTable 对话框

class CMyTable : public CDialog
{
	DECLARE_DYNAMIC(CMyTable)

public:
	CMyTable(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyTable();

// 对话框数据
	enum { IDD = IDD_UPDATE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};

#pragma once

#include "CmyTftpServer.h"
#include "afxwin.h"
#include "Public.h"
// CmyTable1 对话框

class CmyTable1 : public CDialog, public CmyTftpServer, public Public
{
	DECLARE_DYNAMIC(CmyTable1)

public:
	CmyTable1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CmyTable1();

// 对话框数据
	enum { IDD = IDD_TABLE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonBios();
	afx_msg void OnBnClickedButtonSoft();
	CComboBox m_combBios;
	CComboBox m_combSoft;	
	// /static UINT CheckCompressProcess(void *para);

public:
	CListBox m_list;
	static UINT SoftUpdateThread(void *para) ;                     //解密文件
	afx_msg void OnBnClickedButtonBegin();
	afx_msg void OnBnClickedButtonClear();
	bool IsEmptyFile(CString path);
	static UINT StartTftpServerThread(void* para);
private:
	CString m_strSoftUpdateFilePath;
	CString m_strBiosUpdateFilePath;
	CString m_strDecryptPath;
	CString m_strProcessCMD;	
};

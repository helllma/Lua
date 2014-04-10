// cemonitorDlg.h : 头文件
//

#include "curl/curl.h"
#include "curl/easy.h"
#pragma once#include "afxcmn.h"


// CcemonitorDlg 对话框
class CcemonitorDlg : public CDialog
{
// 构造
public:
	CcemonitorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CEMONITOR_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCheck();
	LONGLONG GetLength( CString url );
	char* UnicodeToAnsi(const TCHAR *sz);
	CString AnsiToUnicodeT(char *sz);


	static long timeout;
	static long error;
	static curl_proxytype proxyType;
	static const TCHAR* proxy;
	static long proxyPort;
	static const TCHAR* usrAndPswd;
	static long tryTimes;
	CProgressCtrl m_CheckProgress;
};


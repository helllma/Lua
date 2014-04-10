#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Public.h"


// CmyTable4 对话框

class CmyTable4 : public CDialog, public Public
{
	DECLARE_DYNAMIC(CmyTable4)

public:
	CmyTable4(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CmyTable4();

// 对话框数据
	enum { IDD = IDD_TABLE4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSoftadd();
	afx_msg void OnBnClickedButtonRemove();
	afx_msg void OnBnClickedButtonMaking();
	virtual BOOL OnInitDialog();
	CString BrowseFolder(HWND hWnd, LPCTSTR lpTitle);     //生成浏览文件夹对话框
	CListBox m_list;
	afx_msg void OnDropFiles(HDROP hDropInfo);            //拖拽文件夹处理
	CString m_strPath;                                    //保存拖拽或者打开的路径
	void Recurse(LPCTSTR pstr);
	//vector<CString> m_strvecFilePath;
	bool MakingList(CString filepath);	
	static UINT SoftPackMakingThread(void *para);          //软件升级包制作主线程	
private:
	CString m_strCompressFilePath;                         //生成压缩文件的路径
	CString m_strProcessCMD;                               //进程传入CMD参数
	CString m_strFileName;
};

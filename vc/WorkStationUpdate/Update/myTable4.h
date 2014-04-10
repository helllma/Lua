#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Public.h"


// CmyTable4 �Ի���

class CmyTable4 : public CDialog, public Public
{
	DECLARE_DYNAMIC(CmyTable4)

public:
	CmyTable4(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CmyTable4();

// �Ի�������
	enum { IDD = IDD_TABLE4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSoftadd();
	afx_msg void OnBnClickedButtonRemove();
	afx_msg void OnBnClickedButtonMaking();
	virtual BOOL OnInitDialog();
	CString BrowseFolder(HWND hWnd, LPCTSTR lpTitle);     //��������ļ��жԻ���
	CListBox m_list;
	afx_msg void OnDropFiles(HDROP hDropInfo);            //��ק�ļ��д���
	CString m_strPath;                                    //������ק���ߴ򿪵�·��
	void Recurse(LPCTSTR pstr);
	//vector<CString> m_strvecFilePath;
	bool MakingList(CString filepath);	
	static UINT SoftPackMakingThread(void *para);          //����������������߳�	
private:
	CString m_strCompressFilePath;                         //����ѹ���ļ���·��
	CString m_strProcessCMD;                               //���̴���CMD����
	CString m_strFileName;
};

#pragma once


// CMyTable �Ի���

class CMyTable : public CDialog
{
	DECLARE_DYNAMIC(CMyTable)

public:
	CMyTable(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyTable();

// �Ի�������
	enum { IDD = IDD_UPDATE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};

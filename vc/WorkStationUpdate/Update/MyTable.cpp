// MyTable.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Update.h"
#include "MyTable.h"


// CMyTable �Ի���

IMPLEMENT_DYNAMIC(CMyTable, CDialog)

CMyTable::CMyTable(CWnd* pParent /*=NULL*/)
	: CDialog(CMyTable::IDD, pParent)
{

}

CMyTable::~CMyTable()
{
}

void CMyTable::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyTable, CDialog)
END_MESSAGE_MAP()



// myTable3.cpp : 实现文件
//

#include "stdafx.h"
#include "Update.h"
#include "myTable3.h"

// CmyTable3 对话框

IMPLEMENT_DYNAMIC(CmyTable3, CDialog)

CmyTable3::CmyTable3(CWnd* pParent /*=NULL*/)
	: CDialog(CmyTable3::IDD, pParent)
	, m_iSetFileSize(0)
{

}

CmyTable3::~CmyTable3()
{
}

void CmyTable3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ADDBIOS, m_list);
	DDX_Control(pDX, IDC_EDIT_SETFILESIZE, m_stSetFileSize);
}


BEGIN_MESSAGE_MAP(CmyTable3, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADDBIOS, &CmyTable3::OnBnClickedButtonAddbios)
	ON_BN_CLICKED(IDC_BUTTON_REMOVEBIOS, &CmyTable3::OnBnClickedButtonRemovebios)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON_MAKINGBIOS, &CmyTable3::OnBnClickedButtonMakingbios)
	ON_BN_CLICKED(IDC_BUTTON_SETFILESIZE, &CmyTable3::OnBnClickedButtonSetfilesize)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CmyTable3::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CmyTable3 消息处理程序

BOOL CmyTable3::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化	
	/*m_list.InsertString(0,"c:\\test\\test\\test\\u-boot.bin");
	m_list.InsertString(1,"c:\\test\\test\\test\\uImage");
	m_list.InsertString(2,"c:\\test\\test\\test\\filesystem.yaffs");*/
	m_iSetFileSize = SPLITFILESIZE*60;
	GetDlgItem(IDC_EDIT_SETFILESIZE)->SetWindowText("60");
	m_list.SetHorizontalExtent(800);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CmyTable3::OnBnClickedButtonAddbios()
{
	// TODO: 在此添加控件通知处理程序代码
	/*CString strtempPath;
	strtempPath = BrowseFolder(NULL,"请选择升级包制作的文件夹！");
	m_list.AddString(strtempPath);	*/
	CString filetype;
	filetype = "all(*.*)|*.*|";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_OVERWRITEPROMPT,filetype);
	if(dlg.DoModal() == IDOK)
	{	
		CString temp;
		CString tempname;		
		temp.MakeLower();
		temp = dlg.GetPathName();
		tempname = temp.Right(temp.GetLength() - temp.ReverseFind('\\')-1);
		if (isBiosFile(temp))
		{
			if (m_list.FindString(-1, temp) == LB_ERR)
			{
				if (!IsExistFile(tempname))
				{
					m_list.AddString(temp);
				}
				
			}
			
		}
		else
			MessageBox("请确认你选取的是正确BIOS文件！","错误提示：",MB_OK|MB_ICONWARNING);
	}
	delete dlg;
}

void CmyTable3::OnBnClickedButtonRemovebios()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.GetSelCount();
	m_list.DeleteString(m_list.GetCurSel());
}

void CmyTable3::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	char *lpszFileName=new char[512];	
	int nFileCount,i; 
	nFileCount=::DragQueryFile (hDropInfo, 0xFFFFFFFF, NULL, 512); 
	for (i=0; i< nFileCount; i++) 
	{ 		
		UINT nChars=::DragQueryFile (hDropInfo,i,&lpszFileName[0], 512);	    
		m_strPath = &lpszFileName[0];
		CString temp;		
		if(!isDirectory(m_strPath))
		{
			temp = m_strPath;
			temp = temp.Right(temp.GetLength() - temp.ReverseFind('\\')-1);
			temp.MakeLower();
			if (m_list.FindString(-1, m_strPath) == LB_ERR)
			{				
				if (isBiosFile(m_strPath))
				{
					if (!IsExistFile(temp))
					{
						m_list.AddString(m_strPath);
					}
					
				}				
			}			
		}
		else
		{
			m_new.Recurse(m_strPath);
			for (int i=0;i<m_new.m_strvecFilePath.size();i++)
			{
				temp = m_new.m_strvecFilePath[i];
				temp = temp.Right(temp.GetLength() - temp.ReverseFind('\\')-1);
				temp.MakeLower();
				if (m_list.FindString(-1, m_new.m_strvecFilePath[i]) == LB_ERR)
				{	
					if (isBiosFile(m_new.m_strvecFilePath[i]))
					{
						if (!IsExistFile(temp))
						{
							m_list.AddString(m_new.m_strvecFilePath[i]);
						}
					}
				}
			}
		}
	} 	
	::DragFinish (hDropInfo);   // 释 放 内 存 	
	delete []lpszFileName;	
	
	


	CDialog::OnDropFiles(hDropInfo);
}

bool CmyTable3::isBiosFile(CString filepath)
{
	CString strtemp;
	strtemp = filepath;
	strtemp.MakeLower();	
	if(!isDirectory(filepath) && (strtemp.Find("u-boot.bin") != -1 || strtemp.Find("uimage") != -1 || strtemp.Find("filesystem.yaffs") != -1))
		return true;	
	else		
		return false;
}

void CmyTable3::OnBnClickedButtonMakingbios()
{
	// TODO: 在此添加控件通知处理程序代码
	/*"u-boot.bin";"uimage";"filesystem.yaffs";
	m_list.GetCount();*/
	if (m_list.GetCount()==0)
	{
		return;
	}
	if(OrderFile())
	{
		m_list.AddString("正在制作固件升级包文件...");
		MakingFile();
		m_list.AddString("固件升级包文件制作完成！");
	}	
}

bool CmyTable3::OrderFile()
{
	CString strTemp;
	CString strTempFind;
	m_vecGetListBox.clear();
	WriteBiosFile refurbish;
	m_biosinfo = refurbish;
	if (m_list.GetCount()>3)
	{
		MessageBox("您添加的BIOS制作文件信息不正确。","错误提示：",MB_OK|MB_ICONWARNING);		
		return false;
	}
	m_vecGetListBox.resize(3,"");
	for (int i=0;i<m_list.GetCount();i++)
	{
		m_list.GetText(i,strTemp);
		strTempFind=strTemp;
		strTempFind.MakeLower();
		if (strTempFind.Find("u-boot.bin")!=-1)
		{
			m_vecGetListBox[0] = strTemp;
		}
		else if (strTempFind.Find("uimage")!=-1)
		{
			m_vecGetListBox[1] = strTemp;
		}
		else if (strTempFind.Find("filesystem.yaffs")!=-1)
		{
			m_vecGetListBox[2] = strTemp;
		}		
	}
	/*vector<CString>::iterator startIterator;
	startIterator = m_vecGetListBox.begin();
	for (int i=0;i<m_vecGetListBox.size();i++)
	{
		if (m_vecGetListBox[i]=="")
		{
			m_vecGetListBox.erase(startIterator+i);
			i--;
		}
	}*/
	return true;
}

void CmyTable3::MakingFile(CString filepath)
{
	CFile writebios;		
	InitFileHead();	
	writebios.Open(filepath, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary);
	//writebios.Write(&m_biosinfo, sizeof(m_biosinfo));
	writebios.Seek(2048,CFile::begin);
	for (int i=0;i<m_vecGetListBox.size();i++)
	{
		if (m_vecGetListBox[i]!="")
		{
			CFile readfile;			
			readfile.Open(m_vecGetListBox[i],CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone);
			int filesize;		
			int needfill;
			filesize      = readfile.GetLength();		
			needfill      = LIMITEFILESIZE-filesize;
			
			if (i<2)
			{	
				char *pbuf;
				pbuf      = (char *)malloc(filesize);			
				readfile.Read(pbuf,filesize);				
				writebios.Write(pbuf,filesize);
				free(pbuf);
				char *fillzero;
				fillzero      = (char *)malloc(needfill);
				memset(fillzero,0,needfill);
				writebios.Write(fillzero,needfill);
				free(fillzero);	
				readfile.Close();
			}
			else
			{				
				if (!m_bIsSplitFile)
				{
					char *pbuf;
					pbuf      = (char *)malloc(filesize);	
					readfile.Read(pbuf,filesize);			
					writebios.Write(pbuf,filesize);
					free(pbuf);
					readfile.Close();
				}
				else
				{
					m_nBlockSize = m_iSetFileSize;//SPLITFILESIZE;
					for (int i=0;m_nFileSystemSize%m_nBlockSize<(LIMITEFILESIZE);i++)
					{
						m_nBlockSize-=i*1024;
					}
					char *pbuf;
					m_nBlockSize			   = m_nBlockSize-m_nBlockSize%(MOD);
					m_biosinfo.FileSystemSize  = m_nBlockSize;
					pbuf					   = (char *)malloc(m_nBlockSize);	
					readfile.Read(pbuf, m_nBlockSize);
					writebios.Write(pbuf, m_nBlockSize);
					readfile.Close();
					SplitFile(m_nBlockSize,m_vecGetListBox[2]);
				}
			}	
			
		}	
	}
	writebios.SeekToBegin();
	writebios.Write(&m_biosinfo, sizeof(m_biosinfo));
	writebios.Close();
}

bool CmyTable3::InitFileHead()
{
	//biosinfo->Verify[1024];预留校验信息	
	m_bIsSplitFile = isSplitFile();
	if(m_bIsSplitFile)
	{
		strcpy(m_biosinfo.ContinueFileName,"firmware1.dat");
		m_biosinfo.CoutinueExist     = 0x1;
	}
	else
	{
		memset(m_biosinfo.ContinueFileName,0,20);
		m_biosinfo.CoutinueExist     = 0;
	}
	
	
	if(m_vecGetListBox[0]!="")
	{	
		m_biosinfo.UbootExist        = 0x1;		
	}
	else
	{
		m_biosinfo.UbootExist        = 0;	
	}

	if(m_vecGetListBox[1]!="")
	{
		m_biosinfo.UImageExist        = 0x1;	
	}
	else
	{
		m_biosinfo.UImageExist        = 0;	
	}

	if(m_vecGetListBox[2]!="")
	{
		m_biosinfo.FileSystemExist         = 0x1;		
		m_biosinfo.FileSystemBeginAddress  = m_nFileSystemBeginAddress;
		m_biosinfo.FileSystemSize          = m_nFileSystemSize;
	}
	else
	{
		m_biosinfo.FileSystemExist         = 0;		
		m_biosinfo.FileSystemBeginAddress  = 0;
		m_biosinfo.FileSystemSize          = 0;
	}
	return true;
}

bool CmyTable3::isSplitFile() 
{
	CFile readfile;
	m_nTotalfileSize   = 0;
	m_nFileOffset      = 0;
	m_nFileSystemSize  = 0;
	if (m_vecGetListBox[0]!="")
	{
		readfile.Open(m_vecGetListBox[0],CFile::modeRead);
		m_nTotalfileSize += readfile.GetLength();
		m_nFileOffset       = LIMITEFILESIZE;
		readfile.Close();
	}
	if (m_vecGetListBox[1]!="")
	{
		readfile.Open(m_vecGetListBox[1],CFile::modeRead);
		m_nTotalfileSize += readfile.GetLength();
		m_nFileOffset      += LIMITEFILESIZE;
		readfile.Close();
	}
	m_nFileSystemBeginAddress = 2048+m_nFileOffset;      //获得filesystem.yaffs的起始地址
	if (m_vecGetListBox[2]!="")
	{
		readfile.Open(m_vecGetListBox[2],CFile::modeRead);
		m_nFileSystemSize = readfile.GetLength();
		m_nTotalfileSize  += m_nFileSystemSize;
		m_nFileOffset     += m_nFileSystemSize;
		readfile.Close();
	}
	if (m_nFileSystemSize>m_iSetFileSize/*SPLITFILESIZE*/)
	{
		m_biosinfo.CoutinueExist = 1;
		return true;
	}
	else
	{
		return false;
	}

}

bool CmyTable3::SplitFile(int offset, CString path)
{	
	char *pbuf;	
	CFile read;
	CFile write;	
	int memsize;	
	CString filename;
	CString nextfilename;
	int constoffset =offset;
	WriteContinueBiosFile writecontinue;
	int i = 0;
	do 
	{

		filename.Format("%s%d%s","firmware",i+1,".dat");
		nextfilename.Format("%s%d%s","firmware",i+2,".dat");
		m_list.AddString("正在分割文件："+filename);
		if(read.Open(path, CFile::modeRead | CFile::typeBinary))
		{			
			offset	  = constoffset*(i+1);
			if (m_nFileSystemSize-offset > constoffset)
			{
				memsize   = constoffset;
			}
			else
			{
				memsize	  = m_nFileSystemSize%constoffset;
			}			
			pbuf      = (char *)malloc(memsize);			
			read.Seek(offset, CFile::begin);
			read.Read(pbuf,memsize);
			write.Open(filename,CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary);
			if (m_nFileSystemSize-offset!=m_nFileSystemSize%constoffset)
			{
				strcpy(m_bioscontinueinfo.NextContinueFileName, nextfilename);
				m_bioscontinueinfo.NextContinueFlag     = 0x1;
				m_bioscontinueinfo.NextFileSize         = constoffset;
			}
			else
			{
				memset(m_bioscontinueinfo.NextContinueFileName,0,20);
				m_bioscontinueinfo.NextContinueFlag     = 0;
				m_bioscontinueinfo.NextFileSize         = m_nFileSystemSize%constoffset;
			}
			write.Write(&m_bioscontinueinfo,sizeof(writecontinue));
			write.Write(pbuf,memsize);
			write.Close();
			read.Close();
			i++;
		}
	} while (m_nFileSystemSize-offset!=m_nFileSystemSize%constoffset);	
	return true;
}

bool CmyTable3::IsExistFile(CString filename)
{
	CString temp;
	int k=0;
	for (int i=0;i<m_list.GetCount();i++)
	{
		m_list.GetText(i,temp);
		temp.MakeLower();
		if (temp.Find(filename)!=-1)
		{
			k++;
		}		
	}
	if (k>0)
	{
		return true;
	}
	else
	{
		return false;
	}	
}
void CmyTable3::OnBnClickedButtonSetfilesize()
{
	// TODO: 在此添加控件通知处理程序代码
	CString temp;
	m_stSetFileSize.GetWindowText(temp);
	m_iSetFileSize = atoi(temp);
	if (m_iSetFileSize==0)
	{
		AfxMessageBox("你没有设置文件大小！");
		return;
	}
	else if (m_iSetFileSize < 2 || m_iSetFileSize==2)
	{
		AfxMessageBox("文件必须大于2MB！");
		return;
	}
	m_iSetFileSize *= SPLITFILESIZE;
}

void CmyTable3::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	while(m_list.GetCount()!=0)
		m_list.DeleteString(0);
}

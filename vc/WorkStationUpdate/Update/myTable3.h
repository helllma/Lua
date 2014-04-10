#pragma once
#include "afxcmn.h"
#include "vector"
#include "Public.h"
#include "afxwin.h"
using namespace std;

#define SPLITFILESIZE   1024*1024		//分割文件每块大小
#define LIMITEFILESIZE	1024*1024*2		//最后一块最小值
#define MOD             1024*132		//每块必须得被它整除
// CmyTable3 对话框

class CmyTable3 : public CDialog, public Public
{
	DECLARE_DYNAMIC(CmyTable3)

public:
	CmyTable3(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CmyTable3();

// 对话框数据
	enum { IDD = IDD_TABLE3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_list;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAddbios();	
	afx_msg void OnBnClickedButtonRemovebios();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedButtonMakingbios();
	CString m_strPath;	
public:
	//--------------------------------------------按照文档firmwareUpdata.dat文件的结构定义变量：
#pragma pack(push)                               //压栈保存
#pragma pack(1)                                  // 设置1字节对齐
	typedef struct BiosFile
	{
		BiosFile()
		{
			memset(Verify,0,1024);memset(ContinueFileName,0,20);memset(ReserveZone,0,980);
			UbootExist=0;UImageExist=0;CoutinueExist=0;
			FileSystemExist=0;FileSystemBeginAddress=0;FileSystemSize=0;
		};
		char  Verify[1024];                      //antiy_loadimage 0	1024	主要是校验文件信息
		int   UbootExist;                        //存在标志位	1024	4	说明此次文件中是否包含u-boot.bin文件，包含文件为0x1,不包含为0.		
		int   UImageExist;				         //存在标志位	1028	4	说明此次文件中是否包含uImage文件，包含文件为0x1,不包含为0.
		int   FileSystemExist;				     //存在标志位	1032	4	说明此次文件中是否包含文件系统文件，包含文件为0x1,不包含为0.	
		char  ContinueFileName[20];              /*续传文件名	1036	20	如果存在续传，此处的名字为续传文件名字，文件名的最后一位为
												  *“\0”，如果不存在续传，直接填充为0 */
		int   CoutinueExist;                     //续传标志位	1056	4	存在续传文件为1，不存在为0		
		int   FileSystemBeginAddress;            //filesystem.yaffs的起始地址	1060	4	此偏移地址是只相对于文件头的偏移量
		int   FileSystemSize;				     //filesystem.yaffs的大小	1064	4	即filesystem.yaffs大小，也就是终止地址相对起始地址的偏移量
		char  ReserveZone[980];                  //保留区	1068	980	填充为0
	}WriteBiosFile;
#pragma pack(pop)                                // 恢复先前设置

#pragma pack(push)                               //压栈保存
#pragma pack(1)                                  // 设置1字节对齐
	//--------------------------------------------续传文件格式：
	typedef struct ContinueBiosFile
	{
		ContinueBiosFile()
		{
			memset(NextContinueFileName,0,20);
			NextContinueFlag=0;NextFileSize=0;
		};
		char  NextContinueFileName[20];          /*续传文件名	0	20	如果存在续传，此处的名字为续传文件名字，文件名的最后一位为“\0”，如果不存
												  *在续传，直接填充为0 */
		int   NextContinueFlag;                  //续传标志位	20	4	文件是否存在续传，存在续传为0x1，否为0		
		int   NextFileSize;                      //文件大小	24	4	本次所传文件数据区的大小		
	}WriteContinueBiosFile;
#pragma pack(pop)                                // 恢复先前设置

public:
	bool isBiosFile(CString filepath);			 //判断是不是制作BIOS文件所需要的文件
	bool OrderFile();                            //对列表控件中的文件排序	                        
	bool InitFileHead();						 //初始化文件头数据
	bool isSplitFile();							 //判断文件大小是否达到分割标准，并计算filesystem.yaffs的起始地址和大小
	bool SplitFile(int offset,CString path);							 //分割文件
	bool IsExistFile(CString filename);          //过滤listbox列表同名文件	
	WriteBiosFile m_biosinfo;
	WriteContinueBiosFile m_bioscontinueinfo;
public:
	void MakingFile(CString filepath="firmwareUpdata.dat");   //制作bios文件
	Public m_new;
private:
	vector<CString> m_vecGetListBox;			 //保存获取ListBox控件值
	int m_nFileSystemBeginAddress;				 //保存filesystem.yaffs的起始地址
	int m_nFileSystemSize;						 //保存filesystem.yaffs文件的大小
	int m_nTotalfileSize;                        //文件总大小
	int m_nFileOffset;							 //文件实际偏移量，不足2M补足2M后的大小
	int m_nBlockSize;							 //分割文件大小
	int m_nRemainSize;                           //分割后剩余的大小
	
public:
	int m_iSetFileSize;
	afx_msg void OnBnClickedButtonSetfilesize();
	CEdit m_stSetFileSize;
	bool m_bIsSplitFile;
	afx_msg void OnBnClickedButtonClear();
};

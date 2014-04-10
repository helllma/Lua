#pragma once
#include "afxcmn.h"
#include "vector"
#include "Public.h"
#include "afxwin.h"
using namespace std;

#define SPLITFILESIZE   1024*1024		//�ָ��ļ�ÿ���С
#define LIMITEFILESIZE	1024*1024*2		//���һ����Сֵ
#define MOD             1024*132		//ÿ�����ñ�������
// CmyTable3 �Ի���

class CmyTable3 : public CDialog, public Public
{
	DECLARE_DYNAMIC(CmyTable3)

public:
	CmyTable3(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CmyTable3();

// �Ի�������
	enum { IDD = IDD_TABLE3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	//--------------------------------------------�����ĵ�firmwareUpdata.dat�ļ��Ľṹ���������
#pragma pack(push)                               //ѹջ����
#pragma pack(1)                                  // ����1�ֽڶ���
	typedef struct BiosFile
	{
		BiosFile()
		{
			memset(Verify,0,1024);memset(ContinueFileName,0,20);memset(ReserveZone,0,980);
			UbootExist=0;UImageExist=0;CoutinueExist=0;
			FileSystemExist=0;FileSystemBeginAddress=0;FileSystemSize=0;
		};
		char  Verify[1024];                      //antiy_loadimage 0	1024	��Ҫ��У���ļ���Ϣ
		int   UbootExist;                        //���ڱ�־λ	1024	4	˵���˴��ļ����Ƿ����u-boot.bin�ļ��������ļ�Ϊ0x1,������Ϊ0.		
		int   UImageExist;				         //���ڱ�־λ	1028	4	˵���˴��ļ����Ƿ����uImage�ļ��������ļ�Ϊ0x1,������Ϊ0.
		int   FileSystemExist;				     //���ڱ�־λ	1032	4	˵���˴��ļ����Ƿ�����ļ�ϵͳ�ļ��������ļ�Ϊ0x1,������Ϊ0.	
		char  ContinueFileName[20];              /*�����ļ���	1036	20	��������������˴�������Ϊ�����ļ����֣��ļ��������һλΪ
												  *��\0�������������������ֱ�����Ϊ0 */
		int   CoutinueExist;                     //������־λ	1056	4	���������ļ�Ϊ1��������Ϊ0		
		int   FileSystemBeginAddress;            //filesystem.yaffs����ʼ��ַ	1060	4	��ƫ�Ƶ�ַ��ֻ������ļ�ͷ��ƫ����
		int   FileSystemSize;				     //filesystem.yaffs�Ĵ�С	1064	4	��filesystem.yaffs��С��Ҳ������ֹ��ַ�����ʼ��ַ��ƫ����
		char  ReserveZone[980];                  //������	1068	980	���Ϊ0
	}WriteBiosFile;
#pragma pack(pop)                                // �ָ���ǰ����

#pragma pack(push)                               //ѹջ����
#pragma pack(1)                                  // ����1�ֽڶ���
	//--------------------------------------------�����ļ���ʽ��
	typedef struct ContinueBiosFile
	{
		ContinueBiosFile()
		{
			memset(NextContinueFileName,0,20);
			NextContinueFlag=0;NextFileSize=0;
		};
		char  NextContinueFileName[20];          /*�����ļ���	0	20	��������������˴�������Ϊ�����ļ����֣��ļ��������һλΪ��\0�����������
												  *��������ֱ�����Ϊ0 */
		int   NextContinueFlag;                  //������־λ	20	4	�ļ��Ƿ������������������Ϊ0x1����Ϊ0		
		int   NextFileSize;                      //�ļ���С	24	4	���������ļ��������Ĵ�С		
	}WriteContinueBiosFile;
#pragma pack(pop)                                // �ָ���ǰ����

public:
	bool isBiosFile(CString filepath);			 //�ж��ǲ�������BIOS�ļ�����Ҫ���ļ�
	bool OrderFile();                            //���б�ؼ��е��ļ�����	                        
	bool InitFileHead();						 //��ʼ���ļ�ͷ����
	bool isSplitFile();							 //�ж��ļ���С�Ƿ�ﵽ�ָ��׼��������filesystem.yaffs����ʼ��ַ�ʹ�С
	bool SplitFile(int offset,CString path);							 //�ָ��ļ�
	bool IsExistFile(CString filename);          //����listbox�б�ͬ���ļ�	
	WriteBiosFile m_biosinfo;
	WriteContinueBiosFile m_bioscontinueinfo;
public:
	void MakingFile(CString filepath="firmwareUpdata.dat");   //����bios�ļ�
	Public m_new;
private:
	vector<CString> m_vecGetListBox;			 //�����ȡListBox�ؼ�ֵ
	int m_nFileSystemBeginAddress;				 //����filesystem.yaffs����ʼ��ַ
	int m_nFileSystemSize;						 //����filesystem.yaffs�ļ��Ĵ�С
	int m_nTotalfileSize;                        //�ļ��ܴ�С
	int m_nFileOffset;							 //�ļ�ʵ��ƫ����������2M����2M��Ĵ�С
	int m_nBlockSize;							 //�ָ��ļ���С
	int m_nRemainSize;                           //�ָ��ʣ��Ĵ�С
	
public:
	int m_iSetFileSize;
	afx_msg void OnBnClickedButtonSetfilesize();
	CEdit m_stSetFileSize;
	bool m_bIsSplitFile;
	afx_msg void OnBnClickedButtonClear();
};

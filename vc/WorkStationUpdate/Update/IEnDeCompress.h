// �ļ���;��ѹ�����ܽӿ�
//////////////////////////////////////////////////////////

#ifndef Antiy_EnDeCompressInterfaceDefine
#define Antiy_EnDeCompressInterfaceDefine

//�����԰�ʹ�ýӿ���
static LPCTSTR EnDeCompress_name = _T("EnDeCompress");  //L"EnDeCompress";
class IEnDeCompress
{
public:

	virtual bool AESCrptFile(LPCTSTR lpSourceFile, LPCTSTR lpDoFile, LPCTSTR lpDecrpt = NULL) = 0;//����
	virtual bool AESEncrptFile(LPCTSTR lpSourceFile, LPCTSTR lpDoFile, LPCTSTR lpDecrpt = NULL) = 0;//����
	virtual bool LzariArchieve(LPCTSTR lpSourceFile, LPCTSTR lpDoFile) = 0;
	virtual bool LzariUnArchieve(LPCTSTR lpSourceFile, LPCTSTR lpFilePath) = 0;

};


#endif 
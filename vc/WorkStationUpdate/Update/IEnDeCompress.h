// 文件用途：压缩加密接口
//////////////////////////////////////////////////////////

#ifndef Antiy_EnDeCompressInterfaceDefine
#define Antiy_EnDeCompressInterfaceDefine

//多语言包使用接口类
static LPCTSTR EnDeCompress_name = _T("EnDeCompress");  //L"EnDeCompress";
class IEnDeCompress
{
public:

	virtual bool AESCrptFile(LPCTSTR lpSourceFile, LPCTSTR lpDoFile, LPCTSTR lpDecrpt = NULL) = 0;//加密
	virtual bool AESEncrptFile(LPCTSTR lpSourceFile, LPCTSTR lpDoFile, LPCTSTR lpDecrpt = NULL) = 0;//解密
	virtual bool LzariArchieve(LPCTSTR lpSourceFile, LPCTSTR lpDoFile) = 0;
	virtual bool LzariUnArchieve(LPCTSTR lpSourceFile, LPCTSTR lpFilePath) = 0;

};


#endif 
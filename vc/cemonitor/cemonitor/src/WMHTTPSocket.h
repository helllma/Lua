#pragma once
#include <winsock2.h>

#define SEND					1
#define RECEIVE					0
#define SOCKET_WWW				1
#define SOCKET_IP				0
#define MAXHEADERSIZE			1024
#define AY_SOCKET_PORT			80
#define AY_SOCKET_DEFAULT_PORT	80
#define AY_SOCKET_NOLINK		-100
#define AY_PARAM_BUFF_NULL		-101
#define AY_PARAM_VALUE_ERR		-102

/*
	使用本类必须先调用InitSocketBase()成功才可调用Connect()发起连接,GPRS连接管理器已经包含其中,其存在生命期也相同
*/
class  CWMHTTPSocket  
{
public:

	CWMHTTPSocket(void);
	 ~CWMHTTPSocket(void);

	BOOL  InitSocketBase(void);									//初始化－装载Socket库，校验版本等
	BOOL  Connect(char* ip,int type=SOCKET_IP,int port=0);		//按指定地址和port建立Socket连接，type取SOCKET_IP或者SOCKET_WWW
	int   ServerUnblockSetWait(int sec=60);
	void  CloseSocket();										//关闭已打开的Socket连接
	int   Recv(char* pBuff,int len);							//接收网络信息到缓存内
	int   Send(char* pBuff);									//发送缓存内的信息
	int	  RecOrSdData(int SdOrRecFlg,char *pData,int len=0);	//接收和发送信息的统一接口函数
	char* FmtReqHead(char *pIpOrWWW,char *pPath,char *pLen,char *pPort=NULL);
	BOOL  SendReq(char* pRequestHeader=NULL);
	int   GetReqHead(char *pHeader,int len);
	char* GetRespHead(int &Length);								//获取完整的返回头
	int   GetRecvConLen(char* buff);

	
//	int ParseResp( char* buf,int* result,_bstr_t& paperxmlurl,_bstr_t& ppakxmlurl,_bstr_t& date,_bstr_t& configxml,int len);
//	int CreateAndConnect(char *pServer,//IP 项目提供
//		 	 char *pObject, //sevlet 项目提供
//			 char *pDatalength,//上传数据长度
//			 char *pPort);//端口
//	CWMGPRSConn* pGPRSConn;

private:	
	SOCKET  mySocket;
	char	*pcReqHead;					//存放Socket请求的头数据信息  
	char	*pcRespHead;				//存放Socket响应的头数据信息 
	int		iPort;						//Socket连接的端口号        
	char	*pcIPAddr;					//Socket连接的IP地址   
	BOOL	bConnected;					//标识Socket是否连接成功  
	int		iRespHeadLen;				//Socket响应的头数据信息长度
};


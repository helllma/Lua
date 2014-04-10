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
	ʹ�ñ�������ȵ���InitSocketBase()�ɹ��ſɵ���Connect()��������,GPRS���ӹ������Ѿ���������,�����������Ҳ��ͬ
*/
class  CWMHTTPSocket  
{
public:

	CWMHTTPSocket(void);
	 ~CWMHTTPSocket(void);

	BOOL  InitSocketBase(void);									//��ʼ����װ��Socket�⣬У��汾��
	BOOL  Connect(char* ip,int type=SOCKET_IP,int port=0);		//��ָ����ַ��port����Socket���ӣ�typeȡSOCKET_IP����SOCKET_WWW
	int   ServerUnblockSetWait(int sec=60);
	void  CloseSocket();										//�ر��Ѵ򿪵�Socket����
	int   Recv(char* pBuff,int len);							//����������Ϣ��������
	int   Send(char* pBuff);									//���ͻ����ڵ���Ϣ
	int	  RecOrSdData(int SdOrRecFlg,char *pData,int len=0);	//���պͷ�����Ϣ��ͳһ�ӿں���
	char* FmtReqHead(char *pIpOrWWW,char *pPath,char *pLen,char *pPort=NULL);
	BOOL  SendReq(char* pRequestHeader=NULL);
	int   GetReqHead(char *pHeader,int len);
	char* GetRespHead(int &Length);								//��ȡ�����ķ���ͷ
	int   GetRecvConLen(char* buff);

	
//	int ParseResp( char* buf,int* result,_bstr_t& paperxmlurl,_bstr_t& ppakxmlurl,_bstr_t& date,_bstr_t& configxml,int len);
//	int CreateAndConnect(char *pServer,//IP ��Ŀ�ṩ
//		 	 char *pObject, //sevlet ��Ŀ�ṩ
//			 char *pDatalength,//�ϴ����ݳ���
//			 char *pPort);//�˿�
//	CWMGPRSConn* pGPRSConn;

private:	
	SOCKET  mySocket;
	char	*pcReqHead;					//���Socket�����ͷ������Ϣ  
	char	*pcRespHead;				//���Socket��Ӧ��ͷ������Ϣ 
	int		iPort;						//Socket���ӵĶ˿ں�        
	char	*pcIPAddr;					//Socket���ӵ�IP��ַ   
	BOOL	bConnected;					//��ʶSocket�Ƿ����ӳɹ�  
	int		iRespHeadLen;				//Socket��Ӧ��ͷ������Ϣ����
};


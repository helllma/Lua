#include "stdafx.h"
#include "WMHTTPSocket.h"
#pragma comment(lib,"winsock.lib")

CWMHTTPSocket::CWMHTTPSocket(void){
//	this->pGPRSConn=NULL;
	this->mySocket=NULL;
	this->iPort=AY_SOCKET_DEFAULT_PORT;        
	this->bConnected=false;
	this->iRespHeadLen=-1;
	this->pcIPAddr=new char[MAXHEADERSIZE/4];
	this->pcReqHead=new char[MAXHEADERSIZE]; 
	this->pcRespHead=new char[MAXHEADERSIZE]; 
	memset(this->pcIPAddr,0,MAXHEADERSIZE/4);
	memset(this->pcReqHead,0,MAXHEADERSIZE);
	memset(this->pcRespHead,0,MAXHEADERSIZE);
}

CWMHTTPSocket::~CWMHTTPSocket(void){
	if(NULL!=this->pcIPAddr){delete[] this->pcIPAddr;this->pcIPAddr=NULL;}
	if(NULL!=this->pcReqHead){delete[] this->pcReqHead;this->pcReqHead=NULL;}
	if(NULL!=this->pcRespHead){delete[] this->pcRespHead;this->pcRespHead=NULL;}
	this->CloseSocket();
	WSACleanup();
//	if(NULL!=this->pGPRSConn){delete this->pGPRSConn; this->pGPRSConn=NULL;} 
}

BOOL CWMHTTPSocket::InitSocketBase(void){
	WSADATA WSAData;
	WORD wVersion=MAKEWORD(2,0);
	if(0!=WSAStartup(wVersion,&WSAData)){//无法装载Socket库 WSAGetLastError()
		return false;
	}else{
		if(2!=LOBYTE(WSAData.wVersion)){//无法找到合适的Socket库
			WSACleanup();
			return false;
		}
	}
	return true;
}

void CWMHTTPSocket::CloseSocket(void){
	if(NULL!=this->mySocket){
		if(SOCKET_ERROR==closesocket(this->mySocket)){}
		this->mySocket=NULL;
	}
	this->bConnected=false;
}

BOOL CWMHTTPSocket::Connect(char* iporwww,int type,int port){
	if(NULL==iporwww) return false;
	if(SOCKET_IP==type||SOCKET_WWW==type){}else return false;
	if(this->bConnected) this->CloseSocket();
	this->mySocket=socket(PF_INET,SOCK_STREAM,IPPROTO_IP);//设置SOCKET连接类型、字符流类型和协议类型
	if(INVALID_SOCKET==this->mySocket) return false;
	if(0==port) this->iPort=AY_SOCKET_DEFAULT_PORT;
	else this->iPort=port;
	struct in_addr ip_addr;
	memset(&ip_addr,0,sizeof(in_addr));
	if(SOCKET_IP==type){	
		ip_addr.S_un.S_addr=inet_addr(iporwww);
	}else{
		hostent* pHostent=gethostbyname(iporwww);
		if(NULL==pHostent)	return FALSE;
		memcpy(&ip_addr,pHostent->h_addr_list[0],4);///h_addr_list[0]里4个字节,每个字节8位
	}
	memset(this->pcIPAddr,0,MAXHEADERSIZE/4);
	sprintf(this->pcIPAddr,"%d.%d.%d.%d",ip_addr.S_un.S_un_b.s_b1,ip_addr.S_un.S_un_b.s_b2,ip_addr.S_un.S_un_b.s_b3,ip_addr.S_un.S_un_b.s_b4);
	struct sockaddr_in destaddr;
	memset((void *)&destaddr,0,sizeof(destaddr)); 
	destaddr.sin_family=AF_INET;
	destaddr.sin_port=htons(this->iPort);
	destaddr.sin_addr=ip_addr;
	if(0!=connect(this->mySocket,(struct sockaddr*)&destaddr,sizeof(destaddr))){this->CloseSocket();return false;}
	this->bConnected=true;
	return true;
}
//本函数未编写完成，不要使用
BOOL CWMHTTPSocket::ServerUnblockSetWait(int sec){
	if(!this->bConnected) return false;
	fd_set rfd;										// 描述符集 这个将用来测试有没有一个可用的连接
	FD_ZERO(&rfd);									//总是这样先清空一个描述符集
	struct timeval timeout;
	timeout.tv_sec=sec;								//秒
	timeout.tv_usec=0;								//微秒
	u_long ul=1;									//非阻塞为非0，阻塞为0
	if(0!=ioctlsocket(this->mySocket,FIONBIO,&ul)){	//设置非阻塞连接模式会失败，应该只会返回SOCKET_ERROR错误
	}
	//用select设置中断时间
	FD_SET(this->mySocket,&rfd);						//把sock放入要测试的描述符集 就是说把sock放入了rfd里面 这样下一步调用select对rfd进行测试的时候就会测试sock了(因为我们将sock放入的rdf) 一个描述符集可以包含多个被测试的描述符, 
	if(0>=select(this->mySocket+1,&rfd,0,0,&timeout)){//select的第一个参数是可以忽略的(这样写是为了保持和linux下一致) 第二个参数放入需要测试的读描述符集(也就是说如果这里面有一个描述符可以读取了,select就返回) 第三个放入需要测试的写描述符集,第四个放入"可执行描述符集"(??我也不知道) 第五个参数是超时时间(如果过了这个超时时间依然没有描述符准备好,select也返回.(如果为NULL,那就一直等到一个描述符集变成准备好的状态)
		//这个大括号接上面的,返回0那么就超过了timeout预定的时间设备还没准备好，如果-1是被其它事件中断 
		//this->CloseSocket();
		return false;
	};
	return true;
}

int CWMHTTPSocket::Recv(char* pBuff,int len){
	if(!this->bConnected) return AY_SOCKET_NOLINK;
	int iLen=recv(this->mySocket,pBuff,len,0);
	if(iLen<=0){
		int a=GetLastError();
		this->CloseSocket();
	}
	return iLen;

}

int CWMHTTPSocket::Send(char* pBuff){
	if(!this->bConnected) return AY_SOCKET_NOLINK;
	if(NULL==pBuff) return AY_PARAM_BUFF_NULL;
	int iLen=send(this->mySocket,pBuff,strlen(pBuff),0);
	if(iLen<=0){
//		unsigned long a=WSAGetLastError();
		this->CloseSocket();
	}
	return iLen;
}

int CWMHTTPSocket::RecOrSdData(int SdOrRecFlg,char *pData,int len){
	int nReceSize = 0;
	switch(SdOrRecFlg)
	{
		case SEND:
			nReceSize = this->Send(pData);
			if(nReceSize == 0){//服务器已经关闭连接
			}else if(nReceSize == -1){//发送数据超时
			}
			break;
		case RECEIVE:
			nReceSize = this->Recv(pData,len);
			if(nReceSize == 0){//服务器已经关闭连接
			}else if(nReceSize == -1){//接收数据超时
			}
			break;
		default: 
			break;
	}
	return nReceSize;
}
//根据请求的相对URL得出HTTP请求头,pIpOrWWW为网络地址,pPath为相对路径,pLen为数据长度,pPort为端口
char* CWMHTTPSocket::FmtReqHead(char *pIpOrWWW,char *pPath,char *pLen,char *pPort){
	memset(this->pcReqHead,'\0',MAXHEADERSIZE);
	strcat(this->pcReqHead,"GET ");
	if(NULL!=pPath) strcat(this->pcReqHead,pPath);
	strcat(this->pcReqHead," HTTP/1.1");
    strcat(this->pcReqHead,"\r\n");
    strcat(this->pcReqHead,"Host: ");
	if(NULL!=pIpOrWWW){ 
		strcat(this->pcReqHead,pIpOrWWW);
		if(NULL!=pPort && !strcmp("80",pPort)){
			strcat(this->pcReqHead,":"); 
			strcat(this->pcReqHead,pPort);
		}
	}
    strcat(this->pcReqHead,"\r\n");
	strcat(this->pcReqHead,"Accept: www/source; text/html; image/gif; image/png; image/jpeg; */*\r\n");
    strcat(this->pcReqHead,"Content-type: application/octet-stream\r\n"); 
    strcat(this->pcReqHead,"Content-Length: "); 
    if(NULL!=pLen) strcat(this->pcReqHead,pLen); 
    strcat(this->pcReqHead,"\r\n"); 
    strcat(this->pcReqHead,"Connection: close\r\n\r\n");
	int resultlen=strlen(this->pcReqHead)+1;
	char* result=new char[resultlen];
	memset(result,0,resultlen);
	memcpy(result,this->pcReqHead,resultlen-1);
	return result;
}
//发送请求头
BOOL CWMHTTPSocket::SendReq(char *pRequestHeader){
	if(!this->bConnected) return false;
	if(NULL==pRequestHeader) pRequestHeader=this->pcReqHead;
	if(NULL==pRequestHeader) return false;
	if(0>=this->Send(pRequestHeader)) return false;
	return true;
}
//服务器监听使用
int CWMHTTPSocket::GetReqHead(char *pHeader, int len){
	if(NULL==pHeader) return AY_PARAM_BUFF_NULL;
	if(len<=0) return AY_PARAM_VALUE_ERR;
	int iLen=strlen(this->pcReqHead);
	if(iLen>len) iLen=len;
	if(iLen>MAXHEADERSIZE) iLen=MAXHEADERSIZE;
	memcpy(pHeader,this->pcReqHead,iLen);
	return iLen;
}
//获取HTTP请求的返回头
char* CWMHTTPSocket::GetRespHead(int &iLen){
	char c = 0;
	int nIndex = 0;
	BOOL bEndResponse = FALSE;
	memset(this->pcRespHead,'\0',MAXHEADERSIZE);
	while(!bEndResponse && nIndex<MAXHEADERSIZE){
		iLen=this->Recv(&c,1);
		if(iLen<=0) return NULL;
		this->pcRespHead[nIndex++] = c;
		if(nIndex>=4){//判断是否到末尾了
			if('\r'==this->pcRespHead[nIndex-4]&&'\n'==this->pcRespHead[nIndex-3]&&'\r'==this->pcRespHead[nIndex-2]&&'\n'==this->pcRespHead[nIndex-1])
				bEndResponse = TRUE;
		}
	}
	this->iRespHeadLen=nIndex;
	iLen = this->iRespHeadLen;
	int resultlen=strlen(this->pcRespHead)+1;
	char* result=new char[resultlen];
	memset(result,0,resultlen);
	memcpy(result,this->pcRespHead,resultlen-1);
	return result;
}

int CWMHTTPSocket::GetRecvConLen(char* buff){
	if(NULL==buff) return AY_PARAM_BUFF_NULL;
	int len=strlen(buff);
	if(len<=16||NULL==strstr(buff,"OK")||*buff=='\0') return 0;

	for(int i=0;i<len;i++,buff++){
		if((*(buff)=='C')&&(*(buff+1)=='o')&&(*(buff+2)=='n')&&(*(buff+3)=='t')&&
			(*(buff+4)=='e')&&(*(buff+5)=='n')&&(*(buff+6)=='t')&&(*(buff+7)=='-')&&
			(*(buff+8)=='L')&&(*(buff+9)=='e')&&(*(buff+10)=='n')&&(*(buff+11)=='g')&&
			(*(buff+12)=='t')&&(*(buff+13)=='h')&&(*(buff+14)==':')&&(*(buff+15)==' '))
		{
			char temp[11];
			memset(temp,'\0',11);
			int i=0;
			while( ((*(buff+16+i)=='0')||
					(*(buff+16+i)=='1')||
					(*(buff+16+i)=='2')||
					(*(buff+16+i)=='3')||
					(*(buff+16+i)=='4')||
					(*(buff+16+i)=='5')||
					(*(buff+16+i)=='6')||
					(*(buff+16+i)=='7')||
					(*(buff+16+i)=='8')||
					(*(buff+16+i)=='9')) && i<11) temp[i]=*(buff+16+i++);
			temp[i]='\0';
			if(0==strlen(temp)) return 0;
			return atoi(temp);
		}
	}
	return 0;
}

/*
int CWMHTTPSocket::CreateAndConnect(char *pServer,//IP 项目提供
		 	 char *pObject, //sevlet 项目提供
			 char *pDatalength,//上传数据长度
			 char *pPort)//端口
{
	if(NULL!=this->pGPRSConn){
			
		delete this->pGPRSConn; this->pGPRSConn=NULL;
	} 

	if(myGprsConnection->ConnctGprs(MNS_SOCKET_URLWWWT)==MNS_ERR){MNSlog("connect gprs in CreateAndConnect fail");return MNS_ERR;}
	const char *pRequestHeader = NULL;
	pRequestHeader =FormatRequestHeader(pServer,pObject,pDatalength,pPort);	
	if(Socket()==MNS_ERR){ MNSlog("Socket in CreateAndConnect fail");return MNS_ERR;}
	if(Connect(pServer)==MNS_ERR){ MNSlog("Connect in CreateAndConnect fail");return MNS_ERR;}
	if(SendRequest()==MNS_ERR){ MNSlog("SendRequest in CreateAndConnect fail");return MNS_ERR;}
	return MNS_OK;
};

int CWMHTTPSocket::ResponseParse( char* buf,
							   int* result,
							   _bstr_t& paperxmlurl,
							   _bstr_t& ppakxmlurl,
							   _bstr_t& date,
							   _bstr_t& configxml,
							   int len
							   )
{
	GetPath* MNSpath= new GetPath;

	paperxmlurl="";
	ppakxmlurl="";
	date="";
	configxml="";

	WCHAR* wcharConnectResultBuf=(WCHAR*)malloc(sizeof(WCHAR)*(len+1));
	memset(wcharConnectResultBuf,0,sizeof(WCHAR)*(len+1));
	WCHAR* Tp=wcharConnectResultBuf;

	if(MultiByteToWideChar(CP_UTF8, 0, buf,len,wcharConnectResultBuf,len)==0) {MNSlog("transfer uft-8 configxml response to wchar fail");free(Tp);return MNS_ERR;}


	
	while(*wcharConnectResultBuf++!='=');
	if(result!=NULL) *result= *wcharConnectResultBuf-'0';

	

	WCHAR* temp=(WCHAR*)malloc(sizeof(WCHAR)*2);
	memset(temp,'\0',sizeof(WCHAR)*2);

	if((*result==-1)||(*result==0))
		goto Exit;
			if((*result==1)||(*result==3))//paper.xml
			{
				while((*wcharConnectResultBuf!='/')||
				(*(wcharConnectResultBuf-1)!='3')||
				(*(wcharConnectResultBuf-2)!='2')||
				(*(wcharConnectResultBuf-3)!='1')||
				(*(wcharConnectResultBuf-4)!='.'))
				wcharConnectResultBuf++;
				while(*wcharConnectResultBuf!=';')

				{
					
					*temp=*wcharConnectResultBuf;
					paperxmlurl=paperxmlurl+temp;
					wcharConnectResultBuf++;
				}
			}

			if((*result==2)||(*result==3))//ppak.xml
			{
				while((*wcharConnectResultBuf!='/')||
				(*(wcharConnectResultBuf-1)!='3')||
				(*(wcharConnectResultBuf-2)!='2')||
				(*(wcharConnectResultBuf-3)!='1')||
				(*(wcharConnectResultBuf-4)!='.'))
				wcharConnectResultBuf++;

				while(*wcharConnectResultBuf!=';')

				{
					*temp=*wcharConnectResultBuf;
					ppakxmlurl=ppakxmlurl+temp;
					wcharConnectResultBuf++;

				}
				if(*result==2)
					goto Exit;

			}

			if((*result==1)||(*result==3))//date
			{
				while(*wcharConnectResultBuf++!='=');
					while(*wcharConnectResultBuf!=';')
					{	
						*temp=*wcharConnectResultBuf;
						date=date+temp;
						wcharConnectResultBuf++;

					}
			}


			if(*result==3)//config
			{
				while(*wcharConnectResultBuf++!='=');
				

				char* Tp2=wcharConnectResultBuf-Tp+buf+2;
				FILE *configxmlfile=fopen(MNSpath->GetMNSPath(MNS_CONFIG_XML_FROMSERVER_PATH),"w");
				while((*(Tp2-1)!='>')||(*(Tp2-2)!='P')||(*(Tp2-3)!='N')||(*(Tp2-4)!='M')||(*(Tp2-5)!='B')||(*(Tp2-6)!='/'))
				{
					fwrite(Tp2,sizeof(char),1,configxmlfile);
					Tp2++;
				}
				fclose(configxmlfile);
				while((*(wcharConnectResultBuf-1)!='>')||(*(wcharConnectResultBuf-2)!='P')||(*(wcharConnectResultBuf-3)!='N')||(*(wcharConnectResultBuf-4)!='M')||(*(wcharConnectResultBuf-5)!='B')||(*(wcharConnectResultBuf-6)!='/'))
				{	
					*temp=*wcharConnectResultBuf;
					configxml=configxml+temp;
					wcharConnectResultBuf++;
				}
			}
Exit:   
	free(temp);
	free(Tp);
	return MNS_OK;
}
*/







// HttpSocket.cpp: implementation of the CHttpSocket class.
/*/
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MNSSocket.h"
#include "MNSlog.h"

#define MAXHEADERSIZE 1024
//extern GetPath* MNSpath;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHttpSocket::CHttpSocket()
{
	
	IniHttp();

	m_s=NULL;
	m_phostent=NULL;
	m_port=MNS_SOCKET_PORT;

	myGprsConnection=new CConnectManager();

	m_bConnected=FALSE;

	m_ipaddr=new char[MAXHEADERSIZE/4];
	m_requestheader=new char[MAXHEADERSIZE];
	m_ResponseHeader=new char[MAXHEADERSIZE];

	for(int i=0;i<(MAXHEADERSIZE/4);i++)
		m_ipaddr[i]='\0';
	memset(m_requestheader,0,MAXHEADERSIZE);
	memset(m_ResponseHeader,0,MAXHEADERSIZE);

	//m_nCurIndex = 0;		//
	//m_bResponsed = FALSE;
	m_nResponseHeaderSize = -1;
/*
	m_nBufferSize = nBufferSize;
	m_pBuffer = new char[nBufferSize];
	memset(m_pBuffer,0,nBufferSize);/
}

CHttpSocket::~CHttpSocket()
{
	if(m_ipaddr) delete []m_ipaddr;
	m_ipaddr=NULL;
	if(m_requestheader) delete []m_requestheader;
	m_requestheader=NULL;
	if(m_ResponseHeader) delete []m_ResponseHeader;
	m_ResponseHeader=NULL;
	CloseSocket();
	WSACleanup();


}

int CHttpSocket::Socket()
{
	if(m_bConnected){MNSlog("socket have connected");return MNS_ERR;}

	//struct protoent *ppe; 
	//ppe=getprotobyname("tcp"); 

	///创建SOCKET对象
	//m_s=socket(PF_INET,SOCK_STREAM,ppe->p_proto);//SOCKET PASCAL FAR socket( int af,int type,int protocol );
	//m_s=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);//parmeter 3:IPPROTO_IP   IPPROTO_ICMP   IPPROTO_IGMP   IPPROTO_TCP   IPPROTO_UDP   IPPROTO_RAW   
	//m_s=socket(PF_INET,SOCK_STREAM,SOL_SOCKET);
	//s=socket(PF_INET,SOCK_STREAM,0);
	//m_s=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
//m_s=WSASocket(AF_INET,SOCK_RAW,IPPROTO_IP,NULL,0,WSA_FLAG_OVERLAPPED);  
	m_s=socket(PF_INET,SOCK_STREAM,IPPROTO_IP);
	if(m_s==INVALID_SOCKET)
	{   
		//char ErMsg1[]="socket()函数执行失败!";
		//char ErMsg2[]="错误";
		//MessageBox(NULL,(const unsigned short *)&ErMsg1,(const unsigned short *)&ErMsg2,MB_OK);
		//MessageBox(NULL,"socket()函数执行失败!","错误",MB_OK);
		MNSlog("create socket fail");
		return MNS_ERR;
	}

	/*set the socket into reuse port
	int   opt=1;   
    int iret=setsockopt(m_s,SOL_SOCKET,SO_REUSEADDR,(const char *)&opt,sizeof(opt));   
    if(iret!=0)   
	{
		CloseSocket();
		return FALSE;
	}; /

	return MNS_OK;

}

//BOOL CHttpSocket::Connect(char *szHostName,int nPort)
int CHttpSocket::Connect(const char* IP,int nPort)
{
	//if(szHostName==NULL)
	//	return FALSE;

	///若已经连接,则先关闭
	if(m_bConnected)
	{
		CloseSocket();
	}

	///保存端口号
	m_port=nPort;

	///根据主机名获得IP地址
/*	m_phostent=gethostbyname(szHostName);
	if(m_phostent==NULL)
	{   
		char ErMsg1[]="gethostbyname()函数执行失败!";
		char ErMsg2[]="错误";
		MessageBox(NULL,(const unsigned short *)&ErMsg1,(const unsigned short *)&ErMsg2,MB_OK);
//		MessageBox(NULL,"gethostbyname()函数执行失败!","错误",MB_OK);
		return FALSE;
	}/


	


	///连接
	struct in_addr ip_addr;/*struct   in_addr   {   union   {   
	                                              struct   {   u_char   s_b1,s_b2,s_b3,s_b4;   }   S_un_b;   
	                                              struct   {   u_short   s_w1,s_w2;   }   S_un_w;   
	                                              u_long   S_addr;    } S_un}}/
	//memcpy(&ip_addr,m_phostent->h_addr_list[0],4);///h_addr_list[0]里4个字节,每个字节8位
	
	
	//memcpy(&ip_addr,IP,sizeof(ip_addr));
	memset(&ip_addr,0,sizeof(in_addr));
	ip_addr.S_un.S_addr=inet_addr(IP);
	struct sockaddr_in destaddr;
	memset((void *)&destaddr,0,sizeof(destaddr)); 
	destaddr.sin_family=AF_INET;
	destaddr.sin_port=htons(nPort);
	destaddr.sin_addr=ip_addr;
	



	///保存主机的IP地址字符串
	/*sprintf(m_ipaddr,"%d.%d.%d.%d",
		destaddr.sin_addr.S_un.S_un_b.s_b1,
		destaddr.sin_addr.S_un.S_un_b.s_b2,
		destaddr.sin_addr.S_un.S_un_b.s_b3,
		destaddr.sin_addr.S_un.S_un_b.s_b4);*/
	/*inet_addr();把带点的IP地址字符串转化为in_addr格式;
	  inet_ntoa();作用相反*/
	
	/*注意理解sturct in_addr 的结构:一个32位的数;一共同体的形式使用
	(1)每8位一个即s_b1~s_b4;
	(2)每16位一个即s_w1~s_w2;
	(3)32位s_addr
	struct   in_addr {
    union   {
			  struct{
				unsigned  char   s_b1,
								 s_b2,
								 s_b3,
								 s_b4;
					} S_un_b;
              struct{
				unsigned  short  s_w1,
                                 s_w2
			        }S_un_w;      
               unsigned long  S_addr;
			} S_un;
		};
	/


	if(connect(m_s,(struct sockaddr*)&destaddr,sizeof(destaddr))!=0)
//if(connect(m_s,(struct sockaddr*)&a,sizeof(a))!=0)
	{
		
		CloseSocket();
		m_s=NULL;
		//char ErMsg1[]="connect()函数执行失败!";
		//char ErMsg2[]="错误";
		//MessageBox(NULL,(const unsigned short *)&ErMsg1,(const unsigned short *)&ErMsg2,MB_OK);
		MNSlog("connect fail");
		return MNS_ERR;
	}

/*
	//test
	char pBuffer[10];
		long nLength;
	nLength=recv(m_s,pBuffer,10,0);/
	//test/


	///设置已经连接的标志
	m_bConnected=true;
	return MNS_OK;
}

///根据请求的相对URL输出HTTP请求头
const char *CHttpSocket::FormatRequestHeader(char *pServer,//IP 项目提供
											 char *pObject, //sevlet 项目提供
											 char *pDatalength,//上传数据长度
											  char *pPort)//端口
									         //char *pCookie,
									         //char *pReferer,
									         //long nFrom,
									         //long nTo,
									         //int nServerType)
{
	//char szPort[10];
	//char szTemp[20];
	//sprintf(szPort,"%d",m_port);
	memset(m_requestheader,'\0',1024);

	///第1行:方法,请求的路径,版本
	strcat(m_requestheader,"GET ");//"GET ");
	strcat(m_requestheader,pObject);
	strcat(m_requestheader," HTTP/1.1");
    strcat(m_requestheader,"\r\n");

	///第2行:主机
    strcat(m_requestheader,"Host: ");
	strcat(m_requestheader,pServer);
	//strcat(m_requestheader,MNS_SOCKET_URLWWW);
	//strcat(m_requestheader,":");
	//strcat(m_requestheader,pPort);
    strcat(m_requestheader,"\r\n");

	strcat(m_requestheader,"Accept: www/source; text/html; image/gif; image/png; image/jpeg; * /*\r\n");
	
    strcat(m_requestheader,"Content-type: application/octet-stream\r\n"); 
	//strcat(m_requestheader,"Content-Type: application/x-www-form-urlencoded\r\n"); 
    strcat(m_requestheader,"Content-Length: "); 
    strcat(m_requestheader,pDatalength); 
    strcat(m_requestheader,"\r\n"); 
    strcat(m_requestheader,"Connection: close\r\n\r\n"); 


	//test
	//strcat(m_requestheader,"xml=ccccccccccccccc");
	//test
/*
	///第3行:
	if(pReferer != NULL)
	{
		strcat(m_requestheader,"Referer:");
		strcat(m_requestheader,pReferer);
		strcat(m_requestheader,"\r\n");		
	}

	///第4行:接收的数据类型
      strcat(m_requestheader,"Accept:*/  //*");
      //strcat(m_requestheader,"\r\n");
/*
	///第5行:浏览器类型
    strcat(m_requestheader,"User-Agent:Mozilla/4.0 (compatible; MSIE 5.00; Windows 98)");
    strcat(m_requestheader,"\r\n");

	///第6行:连接设置,保持
	strcat(m_requestheader,"Connection:Keep-Alive");
	strcat(m_requestheader,"\r\n");

	///第7行:Cookie.
	if(pCookie != NULL)
	{
		strcat(m_requestheader,"Set Cookie:0");
		strcat(m_requestheader,pCookie);
		strcat(m_requestheader,"\r\n");
	}

	///第8行:请求的数据起始字节位置(断点续传的关键)
	if(nFrom > 0)
	{
		strcat(m_requestheader,"Range: bytes=");
		_ltoa(nFrom,szTemp,10);
		strcat(m_requestheader,szTemp);
		strcat(m_requestheader,"-");
		if(nTo > nFrom)
		{
			_ltoa(nTo,szTemp,10);
			strcat(m_requestheader,szTemp);
		}
		strcat(m_requestheader,"\r\n");
	}
	
	///最后一行:空行
	strcat(m_requestheader,"\r\n");
/
	///返回结果
	//Length=strlen(m_requestheader);
	return m_requestheader;
}

///发送请求头
int CHttpSocket::SendRequest(const char *pRequestHeader, long Length)
{
	if(!m_bConnected){MNSlog("not connect while sendrequest");return MNS_ERR;}

	if(pRequestHeader==NULL)
		pRequestHeader=m_requestheader;
	if(Length==0)
		Length=strlen(m_requestheader);

//test
	//strcat((char *)pRequestHeader,"\r\n");
	//strcat((char *)pRequestHeader,"aaaaaaaaaaa");
	//unsigned short *a=new unsigned short(200);
	//MultiByteToWideChar(CP_ACP, 0, m_requestheader,-1,a,200);
//	int b=send(m_s,(char *)a,500,0);
	//char c[]="aaaaaaaaaaaaaaaaaa";
	//b=send(m_s,c,10,strlen(c));
	//strcat((char *)pRequestHeader,"\r\n");
	//strcat((char *)pRequestHeader,"xml=aaaaaaaaaaa");
	//Length=strlen(pRequestHeader);
	//int a=send(m_s,pRequestHeader,Length,0);
	//char b[]="bbbbbbbbbbbbbbb";
//	a=send(m_s,b,strlen(b),0);

//test

	if(send(m_s,pRequestHeader,Length,0)==SOCKET_ERROR)
	{
//		MessageBox(NULL,"send()函数执行失败!","错误",MB_OK);
		MNSlog("send request fail");
		return MNS_ERR;
	}

		/*
		//test
			unsigned short *a=new unsigned short(200);
	MultiByteToWideChar(CP_ACP, 0, m_requestheader,-1,a,200);
	int b=send(m_s,(char *)a,Length,0);
	char c[]="aaaaaaaaaaaaaaaaaa";
	b=send(m_s,c,10,strlen(c));
		//test*/

	/*int nLength;
	GetResponseHeader(nLength);/
	return MNS_OK;
}

long CHttpSocket::Receive(char* pBuffer,long nMaxLength)
{
	if(!m_bConnected)return NULL;
/*	
		//set timeout
		fd_set rfd;                                   // 描述符集 这个将用来测试有没有一个可用的连接
		struct timeval timeout;

		FD_ZERO(&rfd);                     //总是这样先清空一个描述符集

		timeout.tv_sec=60;                //等下select用到这个
		timeout.tv_usec=0;

		u_long ul=1;

		ioctlsocket(m_s,FIONBIO,&ul);    //用非阻塞的连接

		//现在开始用select
		FD_SET(m_s,&rfd);    //把sock放入要测试的描述符集 就是说把sock放入了rfd里面 这样下一步调用select对rfd进行测试的时候就会测试sock了(因为我们将sock放入的rdf) 一个描述符集可以包含多个被测试的描述符, 
		if(select(m_s+1,&rfd,0,0, &timeout)==0)    // select的第一个参数是可以忽略的(这样写是为了保持和linux下一致) 第二个参数放入需要测试的读描述符集(也就是说如果这里面有一个描述符可以读取了,select就返回) 第三个放入需要测试的写描述符集,第四个放入"可执行描述符集"(??我也不知道) 第五个参数是超时时间(如果过了这个超时时间依然没有描述符准备好,select也返回.(如果为NULL,那就一直等到一个描述符集变成准备好的状态)
		{ //这个大括号接上面的,返回0那么就超过了timeout预定的时间 
			int a= GetLastError();
			CloseSocket();
			//处理....
			return NULL;
		};
		
		
*/	

	//test 
	//set the len of socke buf
	 /*  int   bufsize=65280;   
  
    setsockopt(   
          m_s,   
          SOL_SOCKET,   
          SO_RCVBUF,   
          (char*)&bufsize,   
          sizeof(bufsize)   
          );/
	//test

	///接收数据
	long nLength;
	nLength=recv(m_s,pBuffer,nMaxLength,0);
/*	ioctlsocket(m_s, FIONBIO, &ul); //设置为阻塞模式/
		//set timeout
	if(nLength <= 0)
	{
		int a=GetLastError();
		//MessageBox(NULL,"recv()函数执行失败!","错误",MB_OK);
		CloseSocket();
		MNSlog("receive() fail");
	}
	return nLength;

}

long CHttpSocket::Send(char* pBuffer,long nMaxLength)
{
	if(!m_bConnected)return NULL;

	///发送数据
	long nLength;
	nLength=send(m_s,pBuffer,nMaxLength,0);
	
	if(nLength <= 0)
	{
		unsigned long a=WSAGetLastError();//test
		//MessageBox(NULL,"send()函数执行失败!","错误",MB_OK);
		CloseSocket();
	}
	return nLength;
}

///关闭套接字
int CHttpSocket::CloseSocket()
{
	

	if(m_s != NULL)
	{
		if(closesocket(m_s)==SOCKET_ERROR)
		{
//			MessageBox(NULL,"closesocket()函数执行失败!","错误",MB_OK);
			MNSlog("close socket fail");
			return MNS_ERR;
		}
	}
	m_s = NULL;
	m_bConnected=FALSE;

	myGprsConnection->ReleaseConnection();

	return MNS_OK;
}

int CHttpSocket::GetRequestHeader(char *pHeader, int nMaxLength) const
{
	int nLength;
	if(int(strlen(m_requestheader))>nMaxLength)
	{
		nLength=nMaxLength;
	}
	else
	{
		nLength=strlen(m_requestheader);
	}
	memcpy(pHeader,m_requestheader,nLength);
	return nLength;
}

//设置接收或者发送的最长时间
int CHttpSocket::SetTimeout(int nTime, int nType)
{
	//vc ver
	/*if(nType == 0)
	{
		nType = SO_RCVTIMEO;
	}
	else
	{
		nType = SO_SNDTIMEO;
	}

	DWORD dwErr;
    dwErr=setsockopt(m_s,SOL_SOCKET,nType,(char*)&nTime,sizeof(nTime));  
	//dwErr=setsockopt(m_s,IPPROTO_TCP,nType,(char*)&nTime,sizeof(nTime));  

	unsigned long a=WSAGetLastError();//test

	if(dwErr)
	{
//		MessageBox(NULL,"setsockopt()函数执行失败!","错误",MB_OK);
		return FALSE;
	}
	return TRUE;/
//vc ver


		//set timeout
		fd_set rfd;                                   // 描述符集 这个将用来测试有没有一个可用的连接
		struct timeval timeout;

		FD_ZERO(&rfd);                     //总是这样先清空一个描述符集

		timeout.tv_sec=60;                //等下select用到这个
		timeout.tv_usec=0;

		u_long ul=1;

		ioctlsocket(m_s,FIONBIO,&ul);    //用非阻塞的连接

		//现在开始用select
		FD_SET(m_s,&rfd);    //把sock放入要测试的描述符集 就是说把sock放入了rfd里面 这样下一步调用select对rfd进行测试的时候就会测试sock了(因为我们将sock放入的rdf) 一个描述符集可以包含多个被测试的描述符, 
		if(select(m_s+1,&rfd,0,0, &timeout)==0)    // select的第一个参数是可以忽略的(这样写是为了保持和linux下一致) 第二个参数放入需要测试的读描述符集(也就是说如果这里面有一个描述符可以读取了,select就返回) 第三个放入需要测试的写描述符集,第四个放入"可执行描述符集"(??我也不知道) 第五个参数是超时时间(如果过了这个超时时间依然没有描述符准备好,select也返回.(如果为NULL,那就一直等到一个描述符集变成准备好的状态)
		{ //这个大括号接上面的,返回0那么就超过了timeout预定的时间 
			//CloseSocket();
			//处理....
			MNSlog("select while settime fail");
			return MNS_ERR;
		};
		return MNS_OK;
		//set timeout



}

//获取HTTP请求的返回头
const char* CHttpSocket::GetResponseHeader(int &nLength)
{
	/*test
	char c[300]="lllllll";
	send(m_s,c,300,0);
	recv(m_s,c,300,0);
	return c;
	//test/

	//if(!m_bResponsed)
	//{
		char c = 0;
		int nIndex = 0;
		BOOL bEndResponse = FALSE;
		while(!bEndResponse && nIndex < MAXHEADERSIZE)
		{
			recv(m_s,&c,1,0);
			m_ResponseHeader[nIndex++] = c;
			if(nIndex >= 4)
			{
				if(m_ResponseHeader[nIndex - 4] == '\r' && m_ResponseHeader[nIndex - 3] == '\n'
					&& m_ResponseHeader[nIndex - 2] == '\r' && m_ResponseHeader[nIndex - 1] == '\n')
				bEndResponse = TRUE;
			}
		}
		m_nResponseHeaderSize = nIndex;
		//m_bResponsed = TRUE;
	//}
	
	nLength = m_nResponseHeaderSize;
	return m_ResponseHeader;

}
/*
int CHttpSocket::ClipSpaceInXml(const char* buf,_bstr_t& xml,int len)
{

	WCHAR* wcharConnectResultBuf=(WCHAR*)malloc(sizeof(WCHAR)*len);
	memset(wcharConnectResultBuf,0,sizeof(WCHAR)*len);

	if(MultiByteToWideChar(CP_UTF8, 0, buf,-1,wcharConnectResultBuf,len)==0){MNSlog("transfer uft-8 xml to wchar fail");return MNS_ERR;}

	WCHAR* temp=(WCHAR*)malloc(sizeof(WCHAR)*2);
	memset(temp,'\0',sizeof(WCHAR)*2);

	while((*(wcharConnectResultBuf-1)!='>')||(*(wcharConnectResultBuf-2)!='P')||(*(wcharConnectResultBuf-3)!='N')||(*(wcharConnectResultBuf-4)!='M')||(*(wcharConnectResultBuf-5)!='B')||(*(wcharConnectResultBuf-6)!='/'))
	{	

		*temp=*wcharConnectResultBuf;
		xml=xml+temp;

		if(*wcharConnectResultBuf=='>')
		{
			bool isNail=false;
			int i=0;
			while(*(wcharConnectResultBuf-i)!='<')
			{
				if(*(wcharConnectResultBuf-i)=='/'){isNail==true;break;}
				i++;
			}
			
			i=0;
			if(isNail)
			{
				while(*(wcharConnectResultBuf+i++)!='<') wcharConnectResultBuf++;
			}
			else wcharConnectResultBuf++;

		}
		else wcharConnectResultBuf++;

	}

	free(temp);
	free(wcharConnectResultBuf);

	return MNS_OK;
}*/

/*
int CHttpSocket::ResponseParse( char* buf,
							   int* result,
							   _bstr_t& paperxmlurl,
							   _bstr_t& ppakxmlurl,
							   _bstr_t& date,
							   _bstr_t& configxml,
							   int len
							   )
{
	GetPath* MNSpath= new GetPath;

	paperxmlurl="";
	ppakxmlurl="";
	date="";
	configxml="";

	WCHAR* wcharConnectResultBuf=(WCHAR*)malloc(sizeof(WCHAR)*(len+1));
	memset(wcharConnectResultBuf,0,sizeof(WCHAR)*(len+1));
	WCHAR* Tp=wcharConnectResultBuf;

	if(MultiByteToWideChar(CP_UTF8, 0, buf,len,wcharConnectResultBuf,len)==0) {MNSlog("transfer uft-8 configxml response to wchar fail");free(Tp);return MNS_ERR;}


	
	while(*wcharConnectResultBuf++!='=');
	if(result!=NULL) *result= *wcharConnectResultBuf-'0';

	

	WCHAR* temp=(WCHAR*)malloc(sizeof(WCHAR)*2);
	memset(temp,'\0',sizeof(WCHAR)*2);

	if((*result==-1)||(*result==0))
	//{
	//	paperxmlurl="";
	//	ppakxmlurl="";
	//	date="";
	//	configxml="";
		goto Exit;
	//}
			/*while((*wcharConnectResultBuf!='/')||
			(*(wcharConnectResultBuf-1)!='m')||
			(*(wcharConnectResultBuf-2)!='o')||
			(*(wcharConnectResultBuf-3)!='c')||
			(*(wcharConnectResultBuf-4)!='.')) wcharConnectResultBuf++;/

			if((*result==1)||(*result==3))//paper.xml
			{
				while((*wcharConnectResultBuf!='/')||
				(*(wcharConnectResultBuf-1)!='3')||
				(*(wcharConnectResultBuf-2)!='2')||
				(*(wcharConnectResultBuf-3)!='1')||
				(*(wcharConnectResultBuf-4)!='.'))
				wcharConnectResultBuf++;

			//if(paperxmlurl!=NULL)
			//{

				while(*wcharConnectResultBuf!=';')

				{
					
					*temp=*wcharConnectResultBuf;
					paperxmlurl=paperxmlurl+temp;
					wcharConnectResultBuf++;
				}
				/*if(*result==1)
				{
					ppakxmlurl="";
					configxml="";
				}/

			}
	//}
	//else while(*buf++!=';');

			/*while((*wcharConnectResultBuf!='/')||
			(*(wcharConnectResultBuf-1)!='m')||
			(*(wcharConnectResultBuf-2)!='o')||
			(*(wcharConnectResultBuf-3)!='c')||
			(*(wcharConnectResultBuf-4)!='.')) wcharConnectResultBuf++;/

			if((*result==2)||(*result==3))//ppak.xml
			{
				while((*wcharConnectResultBuf!='/')||
				(*(wcharConnectResultBuf-1)!='3')||
				(*(wcharConnectResultBuf-2)!='2')||
				(*(wcharConnectResultBuf-3)!='1')||
				(*(wcharConnectResultBuf-4)!='.'))
				wcharConnectResultBuf++;

			//if(ppakxmlurl!=NULL)
			//{
				while(*wcharConnectResultBuf!=';')

				{
					*temp=*wcharConnectResultBuf;
					ppakxmlurl=ppakxmlurl+temp;
					wcharConnectResultBuf++;

				}
				if(*result==2)
				//{
				//	paperxmlurl="";
				//	date="";
				//	configxml="";
					goto Exit;

				//}
			}
	//}
	//else while(*buf++!=';');

			if((*result==1)||(*result==3))//date
			{
				while(*wcharConnectResultBuf++!='=');

				//if(date!=NULL)
				//{
				
					while(*wcharConnectResultBuf!=';')
					{	
						*temp=*wcharConnectResultBuf;
						date=date+temp;
						wcharConnectResultBuf++;

					}
				//}
				//else while(*buf++!=';');
				/*if(*result==1)
				{
					ppakxmlurl="";
					configxml="";
				}/

			}


			if(*result==3)//config
			{
				while(*wcharConnectResultBuf++!='=');
				

				char* Tp2=wcharConnectResultBuf-Tp+buf+2;
				FILE *configxmlfile=fopen(MNSpath->GetMNSPath(MNS_CONFIG_XML_FROMSERVER_PATH),"w");
				while((*(Tp2-1)!='>')||(*(Tp2-2)!='P')||(*(Tp2-3)!='N')||(*(Tp2-4)!='M')||(*(Tp2-5)!='B')||(*(Tp2-6)!='/'))
				{
					fwrite(Tp2,sizeof(char),1,configxmlfile);
					Tp2++;
				}
				fclose(configxmlfile);

			//if(configxml!=NULL)
			//{
				while((*(wcharConnectResultBuf-1)!='>')||(*(wcharConnectResultBuf-2)!='P')||(*(wcharConnectResultBuf-3)!='N')||(*(wcharConnectResultBuf-4)!='M')||(*(wcharConnectResultBuf-5)!='B')||(*(wcharConnectResultBuf-6)!='/'))
				{	

					*temp=*wcharConnectResultBuf;
					configxml=configxml+temp;

		/*
					if(*wcharConnectResultBuf=='>')
					{
						bool isNail=false;
						int i=0;
						while(*(wcharConnectResultBuf-i)!='<')
						{
							if(*(wcharConnectResultBuf-i)=='/'){isNail==true;break;}
							i++;
						}
						
						i=0;
						if(isNail)
						{
							while(*(wcharConnectResultBuf+i++)!='<') wcharConnectResultBuf++;
						}
						else wcharConnectResultBuf++;

					}
					else wcharConnectResultBuf++;/

					wcharConnectResultBuf++;

				}
			}
	//}


Exit:   
	free(temp);
	free(Tp);


	return MNS_OK;
}
int CHttpSocket::GetRevContentLength(const char* buf)
{
	if((NULL==buf)||(NULL==strstr(buf,"OK"))||(*buf=='\0')) return 0;

	while(true)
	{
		if((*(buf)=='C')&&(*(buf+1)=='o')&&(*(buf+2)=='n')&&(*(buf+3)=='t')&&
			(*(buf+4)=='e')&&(*(buf+5)=='n')&&(*(buf+6)=='t')&&(*(buf+7)=='-')&&
			(*(buf+8)=='L')&&(*(buf+9)=='e')&&(*(buf+10)=='n')&&(*(buf+11)=='g')&&
			(*(buf+12)=='t')&&(*(buf+13)=='h')&&(*(buf+14)==':')&&(*(buf+15)==' '))
		{
			char temp[10];
			int i=0;
			while(((*(buf+16+i)=='0')||
				 (*(buf+16+i)=='1')||
				 (*(buf+16+i)=='2')||
				 (*(buf+16+i)=='3')||
				 (*(buf+16+i)=='4')||
				 (*(buf+16+i)=='5')||
				 (*(buf+16+i)=='6')||
				 (*(buf+16+i)=='7')||
				 (*(buf+16+i)=='8')||
				 (*(buf+16+i)=='9'))&&
				 (i<10))temp[i]=*(buf+16+i++);

			temp[i]='\0';
			
			return atoi(temp);
		}

		buf++;

	}

}


/*
//返回HTTP响应头中的一行.
int CHttpSocket::GetResponseLine(char *pLine, int nMaxLength)
{
	if(m_nCurIndex >= m_nResponseHeaderSize)
	{
		m_nCurIndex = 0;
		return -1;
	}

	int nIndex = 0;
	char c = 0;
	do 
	{
		c = m_ResponseHeader[m_nCurIndex++];
		pLine[nIndex++] = c;
	} while(c != '\n' && m_nCurIndex < m_nResponseHeaderSize && nIndex < nMaxLength);
	
	return nIndex;
}*/
/*
int CHttpSocket::GetField(const char *szSession, char *szValue, int nMaxLength)
{
	//取得某个域值
	if(!m_bResponsed) return -1;
	
	CString strRespons;
	strRespons = m_ResponseHeader;
	int nPos = -1;
	nPos = strRespons.Find(szSession,0);
	if(nPos != -1)
	{
		nPos += strlen(szSession);
		nPos += 2;
		int nCr = strRespons.Find(L"\r\n",nPos);
		CString strValue = strRespons.Mid(nPos,nCr - nPos);
		strcpy(szValue,strValue);
		return (nCr - nPos);
	}
	else
	{
		return -1;
	}
}
*//*
int CHttpSocket::GetServerState()
{
	//若没有取得响应头,返回失败
	if(!m_bResponsed) return -1;
	
	char szState[3];
	szState[0] = m_ResponseHeader[9];
	szState[1] = m_ResponseHeader[10];
	szState[2] = m_ResponseHeader[11];

	return atoi(szState);
}/


int CHttpSocket::IniHttp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	///初始化Socket函数库
	int err;
	WORD wVersion;
	WSADATA WSAData;
	wVersion=MAKEWORD(2,0);
	err=WSAStartup(wVersion,&WSAData);
	
	if(err!=0)
	{
	unsigned long a=WSAGetLastError();//test
		//AfxMessageBox("无法装载Socket库.");
		MNSlog("WSAStartup fail");
		return MNS_ERR;
	}
	if(LOBYTE( WSAData.wVersion ) != 2)
	{
	
		//AfxMessageBox("无法找到合适的Socket库.");
		WSACleanup();
		MNSlog("can not find suit lib in WSAStartup");
		return MNS_ERR;
	}

	return MNS_OK;
}




int CHttpSocket::CreateAndConnect(char *pServer,//IP 项目提供
		 	 char *pObject, //sevlet 项目提供
			 char *pDatalength,//上传数据长度
			 char *pPort)//端口
{
//	CTestHttpDlg *pMainWnd = (CTestHttpDlg *)pArg;
//	CFileDialog FileDlg(FALSE);
//	CString strFileName;
//	if(FileDlg.DoModal() == IDOK)
//	{
//		strFileName = FileDlg.GetPathName();
//	}
//	else
//	{
//		return 0;
//	}

	if(myGprsConnection->ConnctGprs(MNS_SOCKET_URLWWWT)==MNS_ERR){MNSlog("connect gprs in CreateAndConnect fail");return MNS_ERR;}

	//CString strServer,strObject;
	//unsigned short nPort;
	//DWORD dwServiceType;
	//long nLength;
	const char *pRequestHeader = NULL;
	//char a[]="192.168.1.1";
	//char *strServer=a;
/*
	AfxParseURL(_T("125.34.53.238"),dwServiceType,strServer,strObject,nPort);//AfxParseURL(const unsigned short *,dwServiceType,strServer,strObject,nPort)
	
	pRequestHeader = HttpSocket.FormatRequestHeader((char *)(LPTSTR)(LPCTSTR)strServer,(char *)(LPTSTR)(LPCTSTR)strObject,nLength);	
	HttpSocket.Socket();
	HttpSocket.Connect((char *)(LPTSTR)(LPCTSTR)strServer);
	HttpSocket.SendRequest();
	HttpSocket.SetTimeout(10000,0);
/

//	AfxParseURL(_T("192.168.1.12"),dwServiceType,strServer,strObject,nPort);//AfxParseURL(const unsigned short *,dwServiceType,strServer,strObject,nPort)
//	pRequestHeader = sampSocket.FormatRequestHeader((char *)(LPTSTR)(LPCTSTR)strServer,(char *)(LPTSTR)(LPCTSTR)strObject,nLength);	
	pRequestHeader =FormatRequestHeader(pServer,pObject,pDatalength,pPort);	

	if(Socket()==MNS_ERR){ MNSlog("Socket in CreateAndConnect fail");return MNS_ERR;}
	//flag=StTmeOt(0);
	//if(flag==false) return false;
	//HttpSocket.Connect((char *)(LPTSTR)(LPCTSTR)strServer);
	
	if(Connect(pServer)==MNS_ERR){ MNSlog("Connect in CreateAndConnect fail");return MNS_ERR;}
	/*flag=StTmeOt(0);
	if(flag==false) 
	{
		//char ErMsg1[]="接收数据失败！";
		//MessageBox(NULL,(const unsigned short *)&ErMsg1,(const unsigned short *)&ErMsg2,MB_OK);
		//MessageBox((const unsigned short *)&ErMsg1);
		return false;
	};/
	
	if(SendRequest()==MNS_ERR){ MNSlog("SendRequest in CreateAndConnect fail");return MNS_ERR;}

	//Socket=&HttpSocket;
	return MNS_OK;

};

int CHttpSocket::StTmeOt(int flag)
{  
	if(SetTimeout(10000,flag)==MNS_ERR){ MNSlog("SetTimeout in StTmeOt fail");return MNS_ERR;}
	return MNS_OK;

};
 int CHttpSocket::RecOrSdData(int SdOrRecFlg,char *Data,int length,int CloseFlg)
{
//	CTestHttpDlg *pMainWnd = (CTestHttpDlg *)pArg;
//	CFileDialog FileDlg(FALSE);
//	CString strFileName;
//	if(FileDlg.DoModal() == IDOK)
//	{
//		strFileName = FileDlg.GetPathName();
//	}
//	else
//	{
//		return 0;
//	}
/*	CHttpSocket HttpSocket;
	CString strServer,strObject;
	unsigned short nPort;
	DWORD dwServiceType;
	long nLength;
	const char *pRequestHeader = NULL;
	AfxParseURL(serverURL,dwServiceType,strServer,strObject,nPort);
	
	pRequestHeader = HttpSocket.FormatRequestHeader((LPTSTR)(LPCTSTR)strServer,(LPTSTR)(LPCTSTR)strObject,nLength);	
	HttpSocket.Socket();
	HttpSocket.Connect((LPTSTR)(LPCTSTR)strServer);
	HttpSocket.SendRequest();
	HttpSocket.SetTimeout(10000,0);
/*
	int nSize;
	HttpSocket.GetResponseHeader(nSize);/
int nReceSize = 0;
switch(SdOrRecFlg)
{
case SEND:
	{
		nReceSize = Send(Data,length);
		//nReceSize = sampSocket.Send(Data,strlen(Data));
		if(nReceSize == 0)
		{
		//	AfxMessageBox("服务器已经关闭连接.");
			MNSlog("server closed while send data in RecOrSdData()");
			return MNS_ERR;
		}
		if(nReceSize == -1)
		{
		//	AfxMessageBox("发送数据超时.");
			MNSlog("timeout while send data in RecOrSdData()");
			return MNS_ERR;
		}

		
	 break;
	}
case RECEIVE:
	{
		//char szValue[30];
	//	HttpSocket.GetField("Content-Length",szValue,30);
		//int nSvrState = HttpSocket.GetServerState();
		//int nFileSize = atoi(szValue);
		
		//get responseheader
		//int nLength;
		//GetResponseHeader(nLength);

		
		nReceSize = Receive(Data,length);
		//*test
		nReceSize = sampSocket.Receive(Data,length);
		nReceSize = sampSocket.Receive(Data,length);
		nReceSize = sampSocket.Receive(Data,length);
		nReceSize = sampSocket.Receive(Data,length);
		nReceSize = sampSocket.Receive(Data,length);
		nReceSize = sampSocket.Receive(Data,length);
		nReceSize = sampSocket.Receive(Data,length);
		nReceSize = sampSocket.Receive(Data,length);/
		//test/
		if(nReceSize == 0)
		{
//			AfxMessageBox("服务器已经关闭连接.");
			MNSlog("server closed while receive data in RecOrSdData()");
			return MNS_ERR;
		}
		if(nReceSize == -1)
		{
//			AfxMessageBox("接收数据超时.");
			MNSlog("timeout while receive data in RecOrSdData()");
			return MNS_ERR;
		}

	
		
		/*test
		CString strFileName=_T("http://196.128.1.16/servlet/loginServlet?userName=123&userPass=456");
		CFile DownloadFile;
		DownloadFile.Open(strFileName,CFile::modeCreate | CFile::modeWrite);
		//test*/

		/*
		//char pData[1024];
		int nReceSize = 0;
		nReceSize = sampSocket.Receive(Data,length);
		if(nReceSize == 0)
		{
//			AfxMessageBox("服务器已经关闭连接.");
			return false;
		}
		if(nReceSize == -1)
		{
//			AfxMessageBox("接收数据超时.");
			return false;
		}*/

		
		//Data=XMLtoS(pData);
/*
	pMainWnd->m_edtEdit1.SetWindowText(pRequestHeader);
	int nLineSize = 0;
	char szLine[256];
	while(nLineSize != -1)
	{
		nLineSize = HttpSocket.GetResponseLine(szLine,256);
		if(nLineSize > -1)
		{
			szLine[nLineSize] = '\0';
			pMainWnd->m_ctrlList.AddString(szLine);
		}
	}
	char szValue[30];
	HttpSocket.GetField("Content-Length",szValue,30);
	int nSvrState = HttpSocket.GetServerState();
	int nFileSize = atoi(szValue);
	pMainWnd->m_ctrlProgress.ShowWindow(SW_SHOW);
	pMainWnd->m_ctrlProgress.SetRange(0,nFileSize / 1024);
	int nCompletedSize = 0;
	CFile DownloadFile;
	DownloadFile.Open(strFileName,CFile::modeCreate | CFile::modeWrite);
	char pData[1024];
	int nReceSize = 0;
	DWORD dwStartTime,dwEndTime;
	while(nCompletedSize < nFileSize)
	{
		dwStartTime = GetTickCount();
		nReceSize = HttpSocket.Receive(pData,1024);
		if(nReceSize == 0)
		{
			AfxMessageBox("服务器已经关闭连接.");
			break;
		}
		if(nReceSize == -1)
		{
			AfxMessageBox("接收数据超时.");
			break;
		}
		dwEndTime = GetTickCount();
		DownloadFile.Write(pData,nReceSize);
		nCompletedSize += nReceSize;
		pMainWnd->m_ctrlProgress.SetPos(nCompletedSize / 1024);
		
		//Speed
		CString strSpeed;
		//strSpeed.Format("%d",dwStartTime -dwEndTime);
		strSpeed.Format("%d",nReceSize);
		pMainWnd->m_stcSpeed.SetWindowText(strSpeed);
	}
	DownloadFile.Close();
	
	pMainWnd->m_ctrlProgress.ShowWindow(SW_HIDE);
	pMainWnd->m_ctrlProgress.SetPos(0);
	return 0;/
		break;
	}
default: 
	break;
}
	//if close the socket
	//if(CloseFlg==1) CloseSocket();

	return nReceSize;

}
*/
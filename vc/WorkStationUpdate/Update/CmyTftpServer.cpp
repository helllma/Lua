#include "StdAfx.h"
#include "CmyTftpServer.h"

CString CmyTftpServer::m_strLimiteIP="";
CmyTftpServer::CmyTftpServer(void)
{
	m_bExitFlag=false;
}

CmyTftpServer::~CmyTftpServer(void)
{
}
int CmyTftpServer::creer_socket(int type, int *ptr_port, struct sockaddr_in *ptr_adresse)
{
	//SOCKET desc; 					/* descripteur socket */
	unsigned int longueur=sizeof(struct sockaddr_in);	/* taille adresse */

	/* creation socket */
	if ((m_sDesc = socket(AF_INET, type, 0)) == INVALID_SOCKET)
	{
		//AfxMessageBox(" Creation socket impossible.\n ");
		return -1;
	}

	
	/* preparation de l'adresse d'attachement */
	adresse.sin_family=AF_INET;
	adresse.sin_addr.s_addr=htonl(INADDR_ANY);
	adresse.sin_port=htons(*ptr_port); /*numero du port en format reseau */

	/* demande d'attachement du socket */
	if (bind(m_sDesc,(sockaddr *)&adresse,longueur) == SOCKET_ERROR)
	{
		/*CString temp;
		temp.Format("Attachement socket impossible. AND the error is %d\n", WSAGetLastError());
		AfxMessageBox(temp);*/
		/*int enable = 1;
		setsockopt(m_sDesc, SOL_SOCKET, SO_REUSEADDR,  (char*)&enable, sizeof(int));
		closesocket(m_sDesc);*/
		//_endthread();
		return -1;
		
	}
	/* recuperation de l'adresse effective d'attachement */
	if (ptr_adresse!=NULL)
		getsockname(m_sDesc,(sockaddr *)ptr_adresse, (int *)&longueur);
	return m_sDesc;
}

void CmyTftpServer::tftpd_general(void *t)
{
	CmyTftpServer* pthis=reinterpret_cast<CmyTftpServer*>(t);
	connect_info_S *ci=(connect_info_S *)t;
	int factice=0;
	FILE *f;
	int r=255;

	if (ci->job==RRQ)
	{		
		char temp[512];
		strcpy(temp, ci->filepath);
		char *temp2 = strcat(temp, ci->name);
		//        f=fopen(ci->name,"rb");
		f = fopen(temp2, "rb");
		if (f)
		{
			r=pthis->tftp_send(&ci->adresse,ci->name,"octet",0,TFTPsread,f);
		}
		else
		{
			return;
		}		
		fclose(f);
	} 
	else
	{
		char temp[512];
		strcpy(temp, ci->filepath);
		char *temp2 = strcat(temp, ci->name);
		//        f=fopen(ci->name,"wb");
		f = fopen(temp2, "wb");	
		r=pthis->tftp_receive(&ci->adresse,ci->name,"octet",0,TFTPswrite,f);
		fclose(f);
	}

	if (r!=0) 
		fprintf(stderr,"error tftp.\n");

	free(ci->name);
	free(ci);

	//    pthread_detach(pthread_self());
	//    pthread_exit(&factice);    
	_endthread();
	//    return 0;
}

int CmyTftpServer::tftp_connection(struct sockaddr_in _adresse, short _job, char *_name)
{

	char *cp=_name;
	//    pthread_t pthread_ident;
	unsigned int hThread;
	connect_info_S *ci;

	while ((cp<_name+SEGSIZE-5)&&(*cp!=' ')&&(*cp!='\0')) cp++;
	if ((*cp!= ' ')&&(*cp!='\0')) 
	{
		return 255;
	}

	*cp='\0';
	ci=(connect_info_S*)malloc(sizeof(connect_info_S));
	ci->name=(char*)malloc(cp-_name+1);
	strcpy(ci->name,_name);	
	ci->filepath=(char*)malloc(MAX_PATH);
	strcpy(ci->filepath, m_strFileName);

	ci->adresse=_adresse; ci->job=_job; 

	//    tftpd_general(ci);
	//    pthread_create ( &pthread_ident, NULL,::tftpd_general, ci );
	hThread = _beginthread(tftpd_general, 0, ci);	
	return 0;
}

char CmyTftpServer::TFTPswrite(char *data,long n,char first,void *f)
{
	fwrite(data,n,1,(FILE *)f);
	return 0;
}

char CmyTftpServer::TFTPsread(char *data,long *n,char first,void *f)
{
	*n=fread(data,1,SEGSIZE,(FILE *)f);
	return 0;
}

char CmyTftpServer::TFTPsSendBuffer(char *data,long *s,char first,void *a)
{
	long size=MIN(PKTSIZE-4,((TFTParg_buffer *)a)->l);
	*s=size;
	memcpy(data,((TFTParg_buffer *)a)->dat,size);
	((TFTParg_buffer *)a)->l-=size; ((TFTParg_buffer *)a)->dat+=size;
	return 0;
}

int creer_socket(int type, int *ptr_port, struct sockaddr_in *ptr_adresse);

int CmyTftpServer::tftp_receive_ext(struct sockaddr_in *to1,char *name,char *mode,int InClient,                
					 char (*TFTPwrite)(char *,long ,char,void *),
					 void *argu,int vPKTSIZE)
{
	char *buf,*ackbuf,*dat,*cp;
	tftphdr *dp,*ap;
	int i,size,n,ntimeout;
	SOCKET peer;
	struct timeval tv;
	u_short nextBlockNumber;
	fd_set lecture;
	struct sockaddr_in from,to=*to1;
	size_t fromlen=sizeof(from),tolen=fromlen;

	buf=(char*)malloc(vPKTSIZE);
	if (buf==NULL)
	{
		fprintf(stderr,"TFTP: out of memory.\n");
		return 255;
	}
	ackbuf=(char*)malloc(vPKTSIZE);
	if (ackbuf==NULL)
	{
		fprintf(stderr,"TFTP: out of memory.\n");
		free(buf);
		return 255;
	}
	dp=(tftphdr *)buf;
	ap=(tftphdr *)ackbuf;
	dat=(char*)&dp->th_data[0];
	cp=(char*)&ap->th_stuff[0];

	i=0;
	if ((peer=creer_socket(SOCK_DGRAM, &i, NULL))<0)
	{
		//        syslog(LOG_ERR,"creation socket client: %m\n");
		free(buf); 
		free(ackbuf);
		return 255;
	}

	if (InClient)
	{
		ap->th_opcode=htons((u_short)RRQ);
		strcpy(cp, name);
		cp += strlen(name);
		*cp++ = '\0';
		strcpy(cp, mode);
		cp += strlen(mode);
		*cp++ = '\0';
		size=(DWORD)cp-(DWORD)ackbuf;
	} 
	else
	{
		ap->th_opcode=htons((u_short)ACK);
		ap->th_block=0;
		size=4;
	}
	nextBlockNumber=1;

	do 
	{    
		ntimeout=0;
		do
		{
			if (ntimeout==m_nNumberTimeOut) 
			{ 
				closesocket(peer); 
				free(buf); 
				free(ackbuf); 
				return 255;
		 }

			if (sendto(peer,(const char*)ap,size,0,(struct sockaddr *)&to,tolen)!=size)
			{
				//             syslog(LOG_ERR, "tftp: write: %m\n");
				closesocket(peer);  
				free(buf); 
				free(ackbuf);
				return 255;
			}

			do
			{
				n=-1;
				FD_ZERO(&lecture);
				FD_SET(peer,&lecture); 
				tv.tv_sec=m_nTimeOut; tv.tv_usec=0;
				if ((i=select(peer+1, &lecture, NULL, NULL, &tv))==-1)
				{
					//	            syslog(LOG_ERR,"erreur select.\n");
					closesocket(peer); 
					free(buf); 
					free(ackbuf);
					return 255;
				}
				if (i>0) 
					n=recvfrom(peer, (char *)dp, vPKTSIZE, 0,(struct sockaddr *)&from, (int *)&fromlen);
			} while ((n<0)&&(i>0));

			if (i>0)
			{
				to.sin_port=from.sin_port;
				dp->th_opcode = ntohs((u_short)dp->th_opcode);            
				dp->th_block = ntohs((u_short)dp->th_block);
				if (dp->th_opcode != DATA) 
				{
					closesocket(peer); 
					free(buf); 
					free(ackbuf);
					return 255;
				}

				if (dp->th_block != nextBlockNumber)
				{
					/* Re-synchronize with the other side */
					ioctlsocket(peer, FIONREAD, (u_long *)&i); //i=number of byte in read-buffer
					while (i)
					{
						recv(peer, (char *)dp, vPKTSIZE, 0);
						ioctlsocket(peer, FIONREAD, (u_long *)&i);
					}
					dp->th_block=nextBlockNumber+1;
				}
			}
			ntimeout++;
		} while (dp->th_block!=nextBlockNumber);

		ap->th_block=htons(nextBlockNumber);
		nextBlockNumber++;

		if (nextBlockNumber==2)
		{
			ap->th_opcode=htons((u_short)ACK); // seulement utile si InClient=1
			size=4;
		}

		// les donn閑s sont dans dat et leur longueur est de n-4
		if ( (n-4) > 0 )
		{
			if (nextBlockNumber==2) i=(*TFTPwrite)(dat,n-4,1,argu);
			else i=(*TFTPwrite)(dat,n-4,0,argu);
			if (i)
			{
				closesocket(peer); 
				free(buf); 
				free(ackbuf);
				return i;
			}
		}

	} while (n == vPKTSIZE);

	/* send the "final" ack */
	sendto(peer, (const char *)ap, 4, 0,(struct sockaddr *)&to,tolen);
	closesocket(peer); 
	free(buf); 
	free(ackbuf);
	return 0;
};

int CmyTftpServer::tftp_receive(struct sockaddr_in *to1,char *name,char *mode,int InClient,                
				 char (*TFTPwrite)(char *,long ,char,void *),
				 void *argu)
{
	return tftp_receive_ext(to1,name,mode,InClient,TFTPwrite,argu,PKTSIZE);
}

int CmyTftpServer::tftp_send_ext(struct sockaddr_in *to1,char *name,char *mode,int InClient,
				  char (*TFTPread)(char *,long *,char,void *),                
				  void *argu, int vPKTSIZE)
{
	char *buf,*ackbuf,*dat,*cp;
	tftphdr *dp,*ap;
	int i,size,Oldsize=vPKTSIZE,n,ntimeout,peer;
	unsigned short nextBlockNumber;
	struct timeval tv;
	fd_set lecture;
	struct sockaddr_in from,to=*to1;
	size_t fromlen=sizeof(from),tolen=fromlen;

	buf=(char*)malloc(vPKTSIZE);
	if (buf==NULL)
	{
		fprintf(stderr,"TFTP: out of memory.\n");
		return 255;
	}
	ackbuf=(char*)malloc(vPKTSIZE);
	if (ackbuf==NULL)
	{
		fprintf(stderr,"TFTP: out of memory.\n");
		free(buf); return 255;
	}
	dp=(tftphdr *)buf;
	ap=(tftphdr *)ackbuf;
	dat=(char*)&dp->th_data[0];
	cp=(char*)&dp->th_stuff[0];

	i=0;
	if ((peer=creer_socket(SOCK_DGRAM, &i, NULL))<0)
	{
		//       syslog(LOG_ERR,"creation socket client: %m\n");
		free(buf); 
		free(ackbuf);
		return 255;
	}

	if (InClient)
	{
		dp->th_opcode=htons((u_short)WRQ);
		strcpy(cp, name);
		cp += strlen(name);
		*cp++ = '\0';
		strcpy(cp, mode);
		cp += strlen(mode);
		*cp++ = '\0';
		size=(DWORD)cp-(DWORD)buf;
		nextBlockNumber=0;
	} 
	else
	{
		dp->th_opcode=htons((u_short)DATA);
		dp->th_block=htons((u_short)1);
		if ((*TFTPread)(dat,(long*)(&size),1,argu)!=0)
		{
			closesocket(peer); 
			free(buf); 
			free(ackbuf);
			return 255;
		} 
		size+=4;
		nextBlockNumber=1;
	}

	do 
	{    
		ntimeout=0;
		do
		{
			if (ntimeout==m_nNumberTimeOut) 
			{ 
				closesocket(peer); 
				free(buf); 
				free(ackbuf); 
				return 255;
		 }

			if (sendto(peer,(const char *)dp,size,0,(struct sockaddr *)&to,tolen)!=size)
			{
				//             syslog(LOG_ERR, "tftp: write: %m\n");
				closesocket(peer); 
				free(buf); 
				free(ackbuf);
				return 255;
			}

			do
			{
				n=-1;
				FD_ZERO(&lecture);
				FD_SET(peer,&lecture); 

				tv.tv_sec=m_nTimeOut; tv.tv_usec=0;
				if ((i=select(peer+1, &lecture, NULL, NULL, &tv))==-1)
				{
					//	            syslog(LOG_ERR,"erreur select.\n");
					closesocket(peer); 
					free(buf); 
					free(ackbuf);
					return 255;
				}

				if (i>0) // = time out not expired
					n=recvfrom(peer, (char*)ap, vPKTSIZE, 0,(struct sockaddr *)&from, (int *)&fromlen);                
			} while ((n<0)&&(i>0));

			if (i>0)
			{
				to.sin_port=from.sin_port;
				ap->th_opcode = ntohs((u_short)ap->th_opcode);
				ap->th_block = ntohs((u_short)ap->th_block);
				if (ap->th_opcode != ACK) 
				{ 
					closesocket(peer); 
					free(buf); 
					free(ackbuf); 
					return 255;
				}

				if (ap->th_block != nextBlockNumber)
				{
					/* Re-synchronize with the other side */
					ioctlsocket(peer, FIONREAD, (u_long *)&i); //i=number of byte in read-buffer
					while (i)
					{
						recv(peer, (char *)ap, vPKTSIZE, 0);
						ioctlsocket(peer, FIONREAD, (u_long *)&i);
					}
					ap->th_block=nextBlockNumber+1;
				}
			}
			ntimeout++;
		} while (ap->th_block!=nextBlockNumber);

		if ((size<vPKTSIZE)&&(nextBlockNumber!=0)) break; // tout a d閖?閠?envoy?dans le 1er packet de DATA
		//  attention pour ce test si on fait le "tour" du ushort !!

		nextBlockNumber++;
		dp->th_block=htons(nextBlockNumber);
		if (nextBlockNumber==1)
		{
			dp->th_opcode=htons((u_short)DATA); // seulement utile si InClient=1
			i=(*TFTPread)(dat,(long*)(&size),1,argu);
		} else 
		{
			Oldsize=size;
			if (Oldsize==vPKTSIZE) 
				i=(*TFTPread)(dat,(long*)(&size),0,argu);
			else 
				i=0;
		}
		if (i)
		{
			closesocket(peer); 
			free(buf); 
			free(ackbuf);
			return i;
		}

		size+=4;
	} while (Oldsize==vPKTSIZE);
	closesocket(peer); 
	free(buf); 
	free(ackbuf);
	return 0;
}

int CmyTftpServer::tftp_send(struct sockaddr_in *to1,char *name,char *mode,int InClient,
			  char (*TFTPread)(char *,long *,char,void *),                
			  void *argu)
{
	return tftp_send_ext(to1,name,mode,InClient,TFTPread,argu,PKTSIZE);
}

int CmyTftpServer::tftp_send_buffer(struct sockaddr_in *to,char *name,char *mode,char *datas,DWORD l)
{
	TFTParg_buffer a;
	a.dat=datas;
	a.l=l;
	return tftp_send(to,name,mode,1,TFTPsSendBuffer,&a);
}

void CmyTftpServer::EndThread()
{
	//设置结束线程标志	
	m_bExitFlag=true;
	int enable = 1;
	//关闭socket，port
	setsockopt(m_sDesc, SOL_SOCKET, SO_LINGER,  (char*)&enable, sizeof(int));
	closesocket(m_sDesc);
	//发空消息跳过recvfrom接收结束标志
	sendto(m_sDesc,NULL,NULL,NULL,NULL,NULL);
	//重置
	m_bExitFlag=false;
}

#pragma once


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <windows.h>
#include <winsock2.h>
#include <process.h>
//#include "tftp.h"

#pragma   comment(lib,   "ws2_32.lib") 

#ifndef __TFTP_H
#define	__TFTP_H 1
#pragma   pack(1)
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
#define	SEGSIZE	512 		/* data segment size */
#define PKTSIZE SEGSIZE+4   /* full packet size */
#define	RRQ	1				/* read request */
#define	WRQ	2				/* write request */
#define	DATA 3			    /* data packet */
#define	ACK	4				/* acknowledgement */
#define	TFTPERROR 5 		/* error code */
#define	th_block	th_u.tu_block
#define	th_code		th_u.tu_code
#define	th_stuff	th_u.tu_stuff
#define	th_msg		th_data
#define	EUNDEF		0		/* not defined */
#define	ENOTFOUND	1		/* file not found */
#define	EACCESS		2		/* access violation */
#define	ENOSPACE	3		/* disk full or allocation exceeded */
#define	EBADOP		4		/* illegal TFTP operation */
#define	EBADID		5		/* unknown transfer ID */
#define	EEXISTS		6		/* file already exists */
#define	ENOUSER		7		/* no such user */
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif /* tftp.h */

class CmyTftpServer
{
public:
	CmyTftpServer(void);
	~CmyTftpServer(void);

	typedef struct connect_info_tag_S 
	{		
		char *name;
		struct sockaddr_in adresse;
		short job;
		char *filepath;
	} connect_info_S;

	struct	tftphdr 
	{
		short	th_opcode;			/* packet type */
		union {
			unsigned short	tu_block;	/* block # */
			short	tu_code;		/* error code */
			char	tu_stuff[1];		/* request packet stuff */
		} th_u;
		char	th_data[1];			/* data or error string */
	} ;

	typedef struct TFTParg_buffer_tag
	{
		char *dat;
		long l;
	} TFTParg_buffer;	


public:
	int creer_socket(int type, int *ptr_port, struct sockaddr_in *ptr_adresse);

	int m_nTimeOut,m_nNumberTimeOut,m_nPortTFTP;
	char* m_strFileName;
	static CString m_strLimiteIP;
	inline void initPara(){m_nTimeOut=0;m_nNumberTimeOut=0;m_nPortTFTP=0;m_strLimiteIP = "";}

	static void tftpd_general(void *t);
	int tftp_connection(struct sockaddr_in _adresse, short _job, char *_name);
	static char TFTPswrite(char *data,long n,char first,void *f);
	static char TFTPsread(char *data,long *n,char first,void *f);
	static char TFTPsSendBuffer(char *data,long *s,char first,void *a);
	int tftp_receive_ext(struct sockaddr_in *to1,char *name,char *mode,int InClient,                
		char (*TFTPwrite)(char *,long ,char,void *),
		void *argu,int vPKTSIZE);
	int tftp_receive(struct sockaddr_in *to1,char *name,char *mode,int InClient,                
		char (*TFTPwrite)(char *,long ,char,void *),
		void *argu);
	int tftp_send_ext(struct sockaddr_in *to1,char *name,char *mode,int InClient,
		char (*TFTPread)(char *,long *,char,void *),                
		void *argu, int vPKTSIZE);
	int tftp_send(struct sockaddr_in *to1,char *name,char *mode,int InClient,
		char (*TFTPread)(char *,long *,char,void *),
		void *argu);
	int tftp_send_buffer(struct sockaddr_in *to,char *name,char *mode,char *datas,DWORD l);
public:
	SOCKET m_sDesc;
	struct sockaddr_in adresse;
	bool m_bExitFlag;
	void EndThread();//向tftp线程发送结束消息，关闭socket以及端口
};

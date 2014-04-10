/*
 * TFTP library 
 * copyright (c) 2004 Vanden Berghen Frank  
 *
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * 
 */

#ifndef __TFTP_H
#define	__TFTP_H 1
/*
 *custom declaration
 */
#pragma   pack(1)


typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
/*
 * Trivial File Transfer Protocol (IEN-133)
 */
#define	SEGSIZE	512 		/* data segment size */
#define PKTSIZE SEGSIZE+4   /* full packet size */

/*
 * Packet types.
 */
#define	RRQ	1				/* read request */
#define	WRQ	2				/* write request */
#define	DATA 3			    /* data packet */
#define	ACK	4				/* acknowledgement */
#define	ERROR 5 			/* error code */

struct	tftphdr {
	short	th_opcode;			/* packet type */
	union {
		unsigned short	tu_block;	/* block # */
		short	tu_code;		/* error code */
		char	tu_stuff[1];		/* request packet stuff */
	} th_u;
	char	th_data[1];			/* data or error string */
} ;

#define	th_block	th_u.tu_block
#define	th_code		th_u.tu_code
#define	th_stuff	th_u.tu_stuff
#define	th_msg		th_data


//void nak(int peer,struct sockaddr_in *to,int error,char *commentaire);


int tftp_receive(struct sockaddr_in *to, char *name, char *mode, int InClient,
                char (*TFTPwrite)(char *,long ,char,void *),
                void *argu);
int tftp_receive_ext(struct sockaddr_in *to1,char *name,char *mode,int InClient,                
                     char (*TFTPwrite)(char *,long ,char,void *),
                     void *argu,int vPKTSIZE);
int tftp_send(struct sockaddr_in *to,char *name,char *mode,int InClient,
              char (*TFTPread)(char *,long *,char,void *),
              void *argu);
int tftp_send_ext(struct sockaddr_in *to,char *name,char *mode,int InClient,
                  char (*TFTPread)(char *,long *,char,void *),
                  void *argu,int vPKTSIZE);

char TFTPswrite(char *data,long n,char first,void *f);
  // return 0 if no error.
char TFTPsread(char *data,long *n,char first,void *f);
  // return 0 if no error.

int tftp_send_buffer(struct sockaddr_in *to,char *name,char *mode,char *datas,DWORD l);

/*
 * Error codes.
 */
#define	EUNDEF		0		/* not defined */
#define	ENOTFOUND	1		/* file not found */
#define	EACCESS		2		/* access violation */
#define	ENOSPACE	3		/* disk full or allocation exceeded */
#define	EBADOP		4		/* illegal TFTP operation */
#define	EBADID		5		/* unknown transfer ID */
#define	EEXISTS		6		/* file already exists */
#define	ENOUSER		7		/* no such user */

#endif /* tftp.h */

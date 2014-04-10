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
/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <syslog.h>
#include <netinet/in.h>
#include <pthread.h>
#include "tftp.h" 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <windows.h>
#include <winsock2.h>
#include <process.h>
#include "tftp.h"

#pragma   comment(lib,   "ws2_32.lib") 

#ifdef __GNUG__
// #warning "Compiling under G++." 
#endif

int creer_socket(int type, int *ptr_port, struct sockaddr_in *ptr_adresse);

int TimeOut,NumberTimeOut,PortTFTP;

typedef struct connect_info_tag_S 
{
    char *name;
    struct sockaddr_in adresse;
    short job;
} connect_info_S;
       
void tftpd_general(void *t)
{
    connect_info_S *ci=(connect_info_S *)t;
    int factice=0;
    FILE *f;
    int r=255;
    
    if (ci->job==RRQ)
    {
		char temp[255];
		strcpy(temp, "d:\\");
		char *temp2 = strcat(temp, ci->name);
//        f=fopen(ci->name,"rb");
		f = fopen(temp2, "rb");  
		r=tftp_send(&ci->adresse,ci->name,"octet",0,TFTPsread,f);
        fclose(f);
    } 
	else
    {
		char temp[255];
		strcpy(temp, "d:\\");
		char *temp2 = strcat(temp, ci->name);
//        f=fopen(ci->name,"wb");
		f = fopen(temp2, "wb");	
		r=tftp_receive(&ci->adresse,ci->name,"octet",0,TFTPswrite,f);
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

int tftp_connection(struct sockaddr_in _adresse, short _job, char *_name)
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

    ci->adresse=_adresse; ci->job=_job; 

//    tftpd_general(ci);
//    pthread_create ( &pthread_ident, NULL,::tftpd_general, ci );
	hThread = _beginthread(tftpd_general, 0, ci);	
	return 0;
}

int main(int argc, char *argv[])
{
    struct sockaddr_in adresse;
    int lg=sizeof(adresse),n;
    int desc_socket;
    char   buf[PKTSIZE];
    struct tftphdr *tp=(tftphdr *)&buf;

	int tempDirectoryLength;
	char tempBuf[255];
	tempDirectoryLength = GetCurrentDirectory(255, tempBuf);
	printf("tempBuf is %s\n", tempBuf);
/*
    if (argc!=2)
    {
        printf("You must specify on the command line the number of the TFTP initial accept PORT.\n");
        exit(255);
    }
*/
    TimeOut=3;
    NumberTimeOut=7;

	if (argc < 2)
		PortTFTP = 69; //atol("69");
	else
	if (argc == 2)
		PortTFTP=atol(argv[1]);
	else{
		printf(" Too many arguments!\n ");
		exit(255);
	}

//	PortTFTP = atol();
    if (PortTFTP==0)
    {
        printf("invalid port number.");
        exit(254);
    }

  /* detachement du terminal 
  if (fork()!=0) exit(0);
  setsid(); */

  //  openlog("tftpd", LOG_PID||LOG_PERROR, LOG_DAEMON);

    /* creation et attachement du socket d'ecoute */
	WSADATA wsaData;
	WSAStartup( MAKEWORD( 2, 1 ), &wsaData );

    if ((desc_socket=creer_socket(SOCK_DGRAM, &PortTFTP, NULL)) == -1)
    {
//	    syslog(LOG_ERR,"creation socket serveur: %m.\n");
		printf("creation socket serveur: error.\n");
		WSACleanup();
		exit(2);
    }

//    syslog(LOG_DAEMON,"standard_tftp_server launched on port %i.\n", PortTFTP);
    printf("standard_tftp_server launched on port %i.\n",PortTFTP);

    while (1)
    {
        do
            n=recvfrom(desc_socket,(char *)tp,PKTSIZE,0,(sockaddr *)&adresse,(int*)&lg);
        while (n<0);
        fprintf(stderr,"connection.\n");
        tp->th_opcode=htons((u_short)tp->th_opcode);
        if ((tp->th_opcode == WRQ)||(tp->th_opcode == RRQ))
            tftp_connection(adresse,tp->th_opcode,&tp->th_stuff[0]);
    }
};

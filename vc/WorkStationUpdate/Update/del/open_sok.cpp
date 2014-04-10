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

#include <stdio.h>
//#include <unistd.h>
#include <stdlib.h>
//#include <windows.h>
#include <winsock2.h>

#pragma   comment(lib,   "ws2_32.lib") 
/*
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
*/
//#include "commun.h"

static struct sockaddr_in adresse;
int creer_socket(int type, int *ptr_port, struct sockaddr_in *ptr_adresse)
{
  SOCKET desc; 					/* descripteur socket */
  unsigned int longueur=sizeof(struct sockaddr_in);	/* taille adresse */
  
  /* creation socket */
  if ((desc = socket(AF_INET, type, 0)) == INVALID_SOCKET)
  {
	printf(" Creation socket impossible.\n ");
	return -1;
  }
  
  /* preparation de l'adresse d'attachement */
  adresse.sin_family=AF_INET;
  adresse.sin_addr.s_addr=htonl(INADDR_ANY);
  adresse.sin_port=htons(*ptr_port); /*numero du port en format reseau */

  /* demande d'attachement du socket */
  if (bind(desc,(sockaddr *)&adresse,longueur) == SOCKET_ERROR)
  {
	  
	  printf("Attachement socket impossible. AND the error is %d\n", WSAGetLastError());
      closesocket(desc);
	return -1;
  }
  
  /* recuperation de l'adresse effective d'attachement */
  if (ptr_adresse!=NULL)
     getsockname(desc,(sockaddr *)ptr_adresse, (int *)&longueur);
  return desc;
}

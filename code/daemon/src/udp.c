/*-
 * Copyright (c) 2013, mozgan.
 * All Rights Reserved with BSD License.
 * Read LICENSE file.
 */

/**
 * @file	udp.c
 * @brief	udp communication
 *
 * @author	M. Ozgan, <mozgan@mozgan.org>
 * @version	0.1
 * @date	23.08.2013 22:01:48
 * @internal
 *	$Compiler:	gcc (on Mac, and 4.4BSD) $
 *	$Company:	TU Wien $
 *
 *  @bug	none
 *  @todo	none
 */

/*
 *	@(#) src/udp.c	    TU Wien 23.08.2013
 *  $Id: udp.c,v 0.1 23.08.2013 22:01:48 mozgan Exp $
 */

#include "udp.h"
#include "error.h"

/**
 * @brief make the socket
 *
 * @param hostname get the hostname
 * @param port port number to connection
 */
void
make_socket(const char *hostname, unsigned int port)
{
	memset(&dest_addr, 0, sizeof(dest_addr));

	h_name = gethostbyname(hostname);

	dest_addr.sin_family = AF_INET;
	dest_addr.sin_addr.s_addr = *(u_long *)h_name->h_addr_list[0];
	dest_addr.sin_port = htons(port);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);
	memset(&serv_addr.sin_zero, 0, sizeof(serv_addr.sin_zero));
	
	if ((sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
		sys_err("creating socket failed");
}

/**
 * @brief bind to host
 */
void
binding(void)
{
	if (bind(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)))
		sys_err("bind socket failed");
}

/**
 * @brief make the communication with host (recv or send the datagrams)
 */
void
communication(void)
{
	int		len;
	char		buf[BUFSIZ];
	socklen_t	sin_size;
	

	/*** send to client ***/

	if (strcpy(buf, "start") == NULL)
		sys_err("copy the string to buffer failed");
	
	(void)fprintf(stdout, "sending: %s\n", buf);

	if (sendto(sock_fd, buf, strlen(buf), 0, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr)) == -1)
		sys_err("sendto failed");



	/*** receive from client ***/

	sin_size = (socklen_t)sizeof(struct sockaddr_in);
	(void)fprintf(stdout, "waiting for packet ...\n");

	if((len = recvfrom(sock_fd, buf, BUFSIZ, 0, (struct sockaddr *)&dest_addr, &sin_size)) == -1) 
		sys_err("recvfrom failed");
	
	(void)fprintf(stdout, "received packet from %s: ", inet_ntoa(dest_addr.sin_addr));

	buf[len] = '\0';
	(void)fprintf(stdout, "%s Hz\n", buf);

}

/**
 * @brief close the socket if not to use in future
 */
void
close_socket(void)
{
	if (close(sock_fd) == -1)
		sys_err("close socket failed");
}


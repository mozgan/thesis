/*-
 * Copyright (c) 2013, mozgan.
 * All Rights Reserved with BSD License.
 * Read LICENSE file.
 */

/**
 * @file	udp.h
 * @brief	header file for udp communication
 *
 * @author	M. Ozgan, <mozgan@mozgan.org>
 * @version	0.1
 * @date	23.08.2013 22:02:31
 * @internal
 *	$Compiler:	gcc (on Mac, and 4.4BSD) $
 *	$Company:	TU Wien $
 *
 *  @bug	none
 *  @todo	none
 */

/*
 *	@(#) src/udp.h		TU Wien 23.08.2013
 *  $Id: udp.h,v 0.1 23.08.2013 22:02:31 mozgan Exp $
 */

#ifndef __UDP_H__
#define __UDP_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

/*
 * many compiler do not know the type 'u_long'
 */
#ifndef	u_long
#define	u_long	unsigned long
#endif

/*
 * in many systems has not defined 'h_addr'
 */
#ifndef h_addr
#define h_addr h_addr_list[0]
#endif

struct hostent *h_name;			/**< real hostname */

struct sockaddr_in dest_addr;		/**< destination address */
struct sockaddr_in serv_addr;		/**< server address */

int		sock_fd;		/**< socket description */
unsigned int	port_nr;		/**< port number */

void		make_socket(const char *, unsigned int);  /**< make a socket */
void		binding(void);		/**< bind to the socket */
void		communication(void);	/**< communication */
void		close_socket(void);	/**< close the open socket */

#endif /* __UDP_H__ */


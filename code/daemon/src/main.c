/*-
 * Copyright (c) 2013, mozgan.
 * All Rights Reserved with BSD License.
 * Read LICENSE file.
 */

/**
 * @file	main.c
 * @brief	udp communication
 *
 * @author	M. Ozgan, <mozgan@mozgan.org>
 * @version	0.1
 * @date	23.08.2013 22:00:56
 * @internal
 *	$Compiler:	gcc (on Mac, and 4.4BSD) $
 *	$Company:	TU Wien $
 *
 *  @bug	none
 *  @todo	none
 */

/*
 *	@(#) src/main.c	    TU Wien 23.08.2013
 *  $Id: main.c,v 0.1 23.08.2013 22:00:56 mozgan Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "udp.h"
#include "error.h"

const char  *optstr = "h:p:";		    /**< options */
char	    *prg_name = "<not yet set>";    /**< program name */

/**
 * @brief usage of program how to call this
 */
void
usage(void)
{
	(void)fprintf(stdout, "Usage: \n");
	(void)fprintf(stdout, "\t%s -h <hostname> -p <port>\n", prg_name);
	(void)fprintf(stdout, "\tExample: %s -h FreeBSD.local -p 32000\n", prg_name);

	exit(EXIT_FAILURE);
}


/**
 * @brief main - start program
 *
 * @param argc count of arguments
 * @param argv vector of arguments
 *
 * @return int (if success returns EXIT_SUCCESS, otherwise returns EXIT_FAILURE)
 */
int
main(int argc, char *argv[])
{
	int		ch;
	int		opt_h, opt_p;
	char		*end_ptr;
	char		*hostname;	/**< hostname to bind */

	prg_name = argv[0];
	opt_h = opt_p = 0;

	/* it should be exactly 5 arguments */
	if (argc != 5)
		usage();

	/* parse arguments */
	while((ch = getopt(argc, argv, optstr)) != -1) {
		switch(ch) {
			case 'h':
				hostname = optarg;
				printf ("hostname: %s \n", hostname);
				opt_h = 1;
				break;
			case 'p':
				port_nr = (unsigned int)strtol(optarg, &end_ptr, 10);
				printf ("port number: %d\n", port_nr);
				opt_p = 1;
				break;
			case '?':
				usage();
				exit(EXIT_FAILURE);
			default:
				abort();
				exit(EXIT_FAILURE);
		}
	}
	
	/* check the options correct gived */
	if (!opt_h || !opt_p)
		usage();

	/* no more arguments accept */
	if (optind != argc)
		usage();
	
	make_socket(hostname, port_nr);	    /* make the socket */
	binding();			    /* bind to host */
	communication();		    /* send to host, recv from host */
	close_socket();			    /* close the socket */
	
	exit(EXIT_SUCCESS);
}


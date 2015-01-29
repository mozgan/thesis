/*-
 * Copyright (c) 2013, mozgan.
 * All Rights Reserved with BSD License.
 * Read LICENSE file.
 */

/**
 * @file	error.c
 * @brief	error handling
 *
 * @author	M. Ozgan, <mozgan@mozgan.org>
 * @version	0.1
 * @date	23.08.2013 22:21:22
 * @internal
 *	$Compiler:	gcc (on Mac, and 4.4BSD) $
 *	$Company:	TU Wien $
 *
 *  @bug	none
 *  @todo	none
 */

/*
 *	@(#) src/error.c	    TU Wien 23.08.2013
 *  $Id: error.c,v 0.1 23.08.2013 22:21:22 mozgan Exp $
 */

#include "error.h"

/**
 * @brief if an error occured then print the error message and exit from program
 *
 * @param msg programmer message to print
 */
void
sys_err(const char *msg)
{
	if (errno != 0)
		(void)fprintf(stderr, "Error: %s - %s\n", msg, strerror(errno));
	else
		(void)fprintf(stderr, "Error: %s\n", msg);

	exit(EXIT_FAILURE);
}


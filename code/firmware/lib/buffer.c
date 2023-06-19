/*-
 * Copyright (c) 2013, mozgan.
 * All Rights Reserved with BSD License.
 * Read LICENSE file.
 */

/**
 * @file	buffer.c
 * @brief	library for ring-buffer
 *
 * @author	M. Ozgan, <mozgan@mozgan.org>
 * @version	0.5
 * @date	20.08.2013 20:28:03
 * @internal
 *	$Compiler:	gcc (on Mac, and 4.4BSD) $
 *	$Company:	TU Wien $
 *
 *  @bug	none
 *  @todo	none
 */

/*
 *	@(#) lib/buffer.c	    TU Wien 20.08.2013
 *  $Id: buffer.c,v 0.5 20.08.2013 20:28:03 mozgan Exp $
 */

#include <lib/buffer.h>

/**
 * @brief initialize the ring buffer
 */
void
buffer_init(void)
{
	head = 0;
	tail = 0;
}

/**
 * @brief write the new data in ring buffer
 *
 * @param c new data to write in ring buffer
 */
void
buffer_write(uint16_t c)
{
	buffer[head] = c;

	if (++head >= LEN)
		head = 0;
}

/**
 * @brief calculate the medium of ring buffer
 *
 * @return 
 */
float
buffer_medium(void)
{
	uint8_t i;
	float sum = 0;

	for (i = 0; i < LEN; i++) {
		sum += buffer[i];
	}

	sum /= LEN;

	return sum;
}


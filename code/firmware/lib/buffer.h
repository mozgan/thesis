/*-
 * Copyright (c) 2013, mozgan.
 * All Rights Reserved with BSD License.
 * Read LICENSE file.
 */

/**
 * @file	buffer.h
 * @brief	header file for ring buffer
 *
 * @author	M. Ozgan, <mozgan@mozgan.org>
 * @version	0.5
 * @date	20.08.2013 20:24:11
 * @internal
 *	$Compiler:	gcc (on Mac, and 4.4BSD) $
 *	$Company:	TU Wien $
 *
 *  @bug	none
 *  @todo	none
 */

/*
 *	@(#) lib/buffer.h		TU Wien 20.08.2013
 *  $Id: buffer.h,v 0.5 20.08.2013 20:24:11 mozgan Exp $
 */

#ifndef __BUFFER_H__
#define __BUFFER_H__	1

#include <stdio.h>
#include <include/common.h>

#define	    LEN		10	/**< max. length of ring buffer */

volatile uint16_t buffer[LEN];	/**< ring buffer */
volatile uint8_t head;		/**< point the head of ring buffer */
volatile uint8_t tail;		/**< point the tail of ring buffer */


extern void	    buffer_init(void);
extern void	    buffer_write(uint16_t);
extern float	    buffer_medium(void);


#endif /* __BUFFER_H__ */


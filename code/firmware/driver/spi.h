/*-
 * Copyright (c) 2013, mozgan.
 * All Rights Reserved with BSD License.
 * Read LICENSE file.
 */

/**
 * @file	spi.h
 * @brief	header file for spi interface
 *
 * @author	M. Ozgan, <mozgan@mozgan.org>
 * @version	0.1
 * @date	20.08.2013 14:52:02
 * @internal
 *	$Compiler:	gcc (on Mac, GNU/Linux and 4.4BSD) $
 *	$Company:	TU Wien $
 *
 *  @bug	none
 *  @todo	none
 */

/*
 *	@(#) driver/spi.h		TU Wien 20.08.2013
 *  $Id: spi.h,v 0.1 20.08.2013 14:52:02 mozgan Exp $
 */

#ifndef __SPI_H__
#define __SPI_H__   1

#include <board/freq.h>
#include <device/atmega16.h>
#include <device/enc28j60.h>


extern void	    spi_init(void);
extern void	    spi_write_op(uint8_t, uint8_t);
extern void	    spi_write(uint8_t);
extern uint8_t	    spi_read_addr(uint8_t);
extern uint8_t	    spi_read(void);



#endif /* __SPI_H__ */


/*-
 * Copyright (c) 2013, mozgan.
 * All Rights Reserved with BSD License.
 * Read LICENSE file.
 */

/**
 * @file	freq.h
 * @brief	pin locations for "Frequenzmessung-Board"
 *
 * @author	M. Ozgan, <mozgan@mozgan.org>
 * @version	0.2
 * @date	19.08.2013 15:13:45
 * @internal
 *	$Compiler:	gcc (on Mac, GNU/Linux and 4.4BSD) $
 *	$Company:	TU Wien $
 *
 *  @bug	none
 *  @todo	none
 */

/*
 *	@(#) board/freq.h		TU Wien 19.08.2013
 *  $Id: freq.h,v 0.2 19.08.2013 15:13:45 mozgan Exp $
 */

#ifndef __FREQ_H__
#define __FREQ_H__  1

#include <device/atmega16.h>

/* LEDs for debuging */
#define	    LED_DDR	    DDRA
#define	    LED_PORT	    PORTA
#define	    LED_PIN	    PINA

#define	    LED0	    PA0
#define	    LED1	    PA1
#define	    LED2	    PA2
#define	    LED3	    PA3
#define	    LED4	    PA4
#define	    LED5	    PA5
#define	    LED6	    PA6
#define	    LED7	    PA7

#define	    LED_ALL	    0xFF
#define	    LED_OFF	    0x00

/* SPI */
#define	    SPI_DDR	    DDRB
#define	    SPI_PORT	    PORTB
#define	    SPI_SS	    PB4
#define	    SPI_MOSI	    PB5
#define	    SPI_MISO	    PB6
#define	    SPI_SCK	    PB7

/* ENC28J60 */
#define	    ENC_CTRL_DDR    DDRB
#define	    ENC_CTRL_PORT   PORTB
#define	    ENC_CTRL_CS	    PB3



#endif /* __FREQ_H__ */


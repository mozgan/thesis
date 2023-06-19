/*-
 * Copyright (c) 2013, mozgan.
 * All Rights Reserved with BSD License.
 * Read LICENSE file.
 */

/**
 * @file	atmega16.h
 * @brief	specific definitions for ATMega16 device
 *
 * @author	M. Ozgan, <mozgan@mozgan.org>
 * @version	0.3
 * @date	19.08.2013 15:18:15
 * @internal
 *	$Compiler:	gcc (on Mac, and 4.4BSD) $
 *	$Company:	TU Wien $
 *
 *  @bug	none
 *  @todo	none
 */

/*
 *	@(#) device/atmega16.h		TU Wien 19.08.2013
 *  $Id: atmega16.h,v 0.3 19.08.2013 15:18:15 mozgan Exp $
 */

#ifndef __ATMEGA16_H__
#define __ATMEGA16_H__	1

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <avr/iom16.h>		    /* avr-gcc library */

/*
 * If cpu freq. in Makefile not set, define it 16 MHz.
 * (Compiler option: -DF_CPU=16000000)
 */
#ifndef F_CPU
#warning    "F_CPU not yet set!"
#define F_CPU 16000000		    /* CPU FREQ: 16 MHz */
#endif	/* F_CPU */

/******************************************************************************
 *		Timer/Counter Registers
 *****************************************************************************/

/*
 * TIMSK - Timer/Counter Interrupt Mask Register
 * +------------------------------------------------------------------+
 * | OCIE2 | TOIE2 | TICIE1 | OCIE1A | OCIE1B | TOIE1 | OCIE0 | TOIE0 |
 * +------------------------------------------------------------------+
 */
#define	    TIMER_INT_MASK  TIMSK

/*
 * TIFR - Timer/Counter Interrupt Flag Register
 * +---------------------------------------------------------+
 * | OCF2 | TOV2 | ICF1 | OCF1A | OCF1B | TOV1 | OCF0 | TOV0 |
 * +---------------------------------------------------------+
 */
#define	    TIMER_INT_FLG   TIFR

/******************************************************************************
 * 8-bit Timer/Counter 0
 */

#define	    TIMER0_CNT	    TCNT0
#define	    TIMER0_OCR	    OCR0

/*
 * TCCR0 - Timer/Counter Control Register 
 * +-----------------------------------------------------------+
 * | FOC0 | WGM00 | COM01 | COM00 | WGM01 | CS02 | CS01 | CS00 |
 * +-----------------------------------------------------------+
 */
#define	    TIMER0_TCCR	    TCCR0

/*
 * Timer/Counter 0 Clock Select
 */
#define	    TIMER0_NO_CLK	(TIMER0_TCCR & 0xF8)    /*(~((1 << CS00) | (1 << CS01) | (1 << CS02)))*/
#define	    TIMER0_PRES_1	(TIMER0_NO_CLK | (1 << CS00))
#define	    TIMER0_PRES_8	(TIMER0_NO_CLK | (1 << CS01))
#define	    TIMER0_PRES_64	(TIMER0_NO_CLK | (1 << CS00) | (1 << CS01))
#define	    TIMER0_PRES_256	(TIMER0_NO_CLK | (1 << CS02))
#define	    TIMER0_PRES_1024	(TIMER0_NO_CLK | (1 << CS00) | (1 << CS02))
#define	    TIMER0_T0_FALL	(TIMER0_NO_CLK | (1 << CS01) | (1 << CS02))
#define	    TIMER0_T0_RIS	(TIMER0_NO_CLK | (1 << CS00) | (1 << CS01) | (1 << CS02))

/*
 * CTC-Mode & non-PWM
 */
#define	    TIMER0_NORMAL_P	(TIMER0_TCCR & 0x3F)
#define	    TIMER0_CTC		(TIMER0_NORMAL_P | (1 << WGM01))

/******************************************************************************
 * 16-bit Timer/Counter 1
 */
#define	    TIMER1_CNT	    TCNT1
#define	    TIMER1_OCRA	    OCR1A
#define	    TIMER1_ICR	    ICR1

/******************************************************************************
 * SPI
 */

#define	    MASTER	    0x01
#define	    SLAVE	    0x02

#define	    SPI_DATA_REG    SPDR

/*
 * SPRC - SPI Control Register
 * +------------------------------------------------------+
 * | SPIE | SPE | DORD | MSTR | CPOL | CPHA | SPR1 | SPR0 |
 * +------------------------------------------------------+
 */
#define	SPI_CONTROL_REG	    SPCR

#define	SPI_ENABLE	    SPE
#define	SPI_INT_ENABLE	    SPIE
#define	SPI_MASTER	    MSTR

/*
 * SPSR - SPI Status Register
 * +--------------------------------------------------------+
 * | SPIF | WCOL | ---- | ---- | ---- | ---- | ---- | SPI2X |
 * +--------------------------------------------------------+
 */
#define	SPI_STATUS_REG	    SPSR

#define	SPI_INT_FLAG	    SPIF
#define	SPI_DOUBLE_SPEED    SPI2X



#endif /* __ATMEGA16_H__ */


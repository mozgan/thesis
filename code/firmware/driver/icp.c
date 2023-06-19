/*-
 * Copyright (c) 2013, mozgan.
 * All Rights Reserved with BSD License.
 * Read LICENSE file.
 */

/**
 * @file	icp.c
 * @brief	driver for input capture pin operations
 *
 * @author	M. Ozgan, <mozgan@mozgan.org>
 * @version	0.1
 * @date	22.08.2013 15:57:28
 * @internal
 *	$Compiler:	gcc (on Mac, and 4.4BSD) $
 *	$Company:	TU Wien $
 *
 *  @bug	none
 *  @todo	none
 */

/*
 *	@(#) driver/icp.c	    TU Wien 22.08.2013
 *  $Id: icp.c,v 0.1 22.08.2013 15:57:28 mozgan Exp $
 */

#include <driver/leds.h>
#include <driver/icp.h>

/**
 * @brief initialize the input capture pin on timer 1
 *
 * @param call_back call back function from interrupt to call
 */
void
icp_init(void (*call_back)(uint16_t))
{
	uint32_t temp_ocr;

	if (call_back != NULL)
		icp_handler = call_back;

	TCNT1H = 0x00;
	TCNT1L = 0x00;

	TCCR1A = 0x00;

	/* CTC Mode - TOP: OCR1A */
	TCCR1B |= (1 << WGM12);
	/* Input Capture Noise Canceller on - Fallig Edge as trigger */
	TCCR1B |= (1 << ICNC1) | (1 << ICES1);

	/*
	 * Freq: 1 Hz
	 *
	 *                F_CPU
	 * OCR1A =  -------------------- - 1
	 *            2 * PRES * Freq
	 *
	 */

	temp_ocr = (uint32_t)(F_CPU / 2);
	temp_ocr /= 256;
	temp_ocr--;
	OCR1A = temp_ocr;

	/* Pres.: 256 */
	TCCR1B |= (1 << CS12);

	TIMSK |= (1 << TICIE1);
/*	TIMSK |= (1 << OCIE1A); */  /* not needed the compare interrupt */
}

/*
ISR(TIMER1_COMPA_vect)
{
//	led_toggle(0);
}
*/

/**
 * @brief Timer1 Input Capture Interrupt
 *
 * @param TIMER1_CAPT_vect interrupt name
 */
ISR(TIMER1_CAPT_vect)
{
	if (icp_handler != NULL)
		icp_handler(ICR1);
}


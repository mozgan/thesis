/*-
 * Copyright (c) 2013, mozgan.
 * All Rights Reserved with BSD License.
 * Read LICENSE file.
 */

/**
 * @file	timer0.c
 * @brief	driver of timer/counter 0
 *
 * @author	M. Ozgan, <mozgan@mozgan.org>
 * @version	0.2
 * @date	19.08.2013 15:55:03
 * @internal
 *	$Compiler:	gcc (on Mac, and 4.4BSD) $
 *	$Company:	TU Wien $
 *
 *  @bug	none
 *  @todo	none
 */

/*
 *	@(#) driver/timer0.c	    TU Wien 19.08.2013
 *  $Id: timer0.c,v 1.0 19.08.2013 15:55:03 mozgan Exp $
 */

#include <driver/timer0.h>
#include <driver/leds.h>

volatile int cnt0 = 0;

/**
 * @brief initialize timer/counter 0 with frequency
 *
 * @param freq timer frequency
 * @param call_back if timer interrupt request, returns to call_back function
 */
void
timer0_init_f(uint16_t freq, void (*call_back)(void))
{
	int temp_ocr0;

	temp_ocr0 = (uint16_t)(((uint32_t)(F_CPU) / (uint32_t)(2*256*freq)));
	temp_ocr0--;
	int_cnt0 = 0;

	timer0_handler = call_back;
	TIMER0_CNT = 0x00;

	/* if the OCR bigger as 255 then need the interrupt counter */
	if (temp_ocr0 > 255) {
		int_cnt0 = temp_ocr0 / 255;
		TIMER0_OCR = 0xFF;
	} else
		TIMER0_OCR = temp_ocr0;

	TIMER0_TCCR |= TIMER0_CTC;
	TIMER0_TCCR |= TIMER0_PRES_256;
	
	TIMER_INT_MASK |= (1 << OCIE0);
	TIMER_INT_FLG |= (1 << OCF0);
}

/**
 * @brief stop the timer 0
 */
void
timer0_stop(void)
{
	TIMER0_TCCR = TIMER0_NO_CLK;
}

/**
 * @brief Interrupt for timer/counter 0 of campare output match mode
 *
 * @param TIMER0_COMP_vect Interrupt vector
 */
ISR(TIMER0_COMP_vect)
{
	if (int_cnt0 == 0) {
		if (timer0_handler != NULL)
			timer0_handler();
	} else {
		if (cnt0 % int_cnt0 == 0) {
			if (timer0_handler != NULL)
				timer0_handler();
		}
		cnt0++;
	}
}


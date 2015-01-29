/*-
 * Copyright (c) 2013, mozgan.
 * All Rights Reserved with BSD License.
 * Read LICENSE file.
 */

/**
 * @file	leds.c
 * @brief	driver for leds (to use for debugging)
 *
 * @author	M. Ozgan, <mozgan@mozgan.org>
 * @version	1.0
 * @date	19.08.2013 15:27:38
 * @internal
 *	$Compiler:	gcc (on Mac, GNU/Linux, 4.4BSD) $
 *	$Company:	TU Wien $
 *
 *  @bug	none
 *  @todo	none
 */

/*
 *	@(#) driver/leds.c	    TU Wien 19.08.2013
 *  $Id: leds.c,v 1.0 19.08.2013 15:27:38 mozgan Exp $
 */

#include <driver/leds.h>

/**
 * @brief initialize all LEDs
 */
void
leds_init(void)
{
	LED_DDR	= LED_ALL;
	LED_PORT = LED_OFF;
}

/** 
 * @brief initialize a led
 *
 * @param led the number of led
 */
void
led_init(uint8_t led)
{
	LED_DDR |= (1 << led);
	LED_PORT &= ~(1 << led);
}

/**
 * @brief turn on all LEDs
 */
void
leds_on(void)
{
	LED_PORT = LED_ALL;
}

/**
 * @brief turn on a led
 *
 * @param led the number of led
 */
void
led_on(uint8_t led)
{
	LED_PORT |= (1 << led);
}

/**
 * @brief turn off all LEDs
 */
void
leds_off(void)
{
	LED_PORT = LED_OFF;
}

/**
 * @brief turn off a led
 *
 * @param led the number of led
 */
void
led_off(uint8_t led)
{
	LED_PORT &= ~(1 << led);
}

/**
 * @brief toggle all LEDs
 */
void
leds_toggle(void)
{
	LED_PORT ^= (LED_ALL);
}

/**
 * @brief toggle a led
 *
 * @param led the number of led
 */
void
led_toggle(uint8_t led)
{
	LED_PORT ^= (1 << led);
}


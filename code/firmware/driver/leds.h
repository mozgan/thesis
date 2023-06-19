/*-
 * Copyright (c) 2013, mozgan.
 * All Rights Reserved with BSD License.
 * Read LICENSE file.
 */

/**
 * @file	leds.h
 * @brief	specific header file for leds driver
 *
 * @author	M. Ozgan, <mozgan@mozgan.org>
 * @version	1.0
 * @date	19.08.2013 15:28:53
 * @internal
 *	$Compiler:	gcc (on Mac, and 4.4BSD) $
 *	$Company:	TU Wien $
 *
 *  @bug	none
 *  @todo	none
 */

/*
 *	@(#) driver/leds.h		TU Wien 19.08.2013
 *  $Id: leds.h,v 1.0 19.08.2013 15:28:53 mozgan Exp $
 */

#ifndef __LEDS_H__
#define __LEDS_H__  1

#include <board/freq.h>
#include <include/common.h>

extern void	    leds_init(void);
extern void	    led_init(uint8_t);

extern void	    leds_on(void);
extern void	    led_on(uint8_t);

extern void	    leds_off(void);
extern void	    led_off(uint8_t);

extern void	    leds_toggle(void);
extern void	    led_toggle(uint8_t);



#endif /* __LEDS_H__ */


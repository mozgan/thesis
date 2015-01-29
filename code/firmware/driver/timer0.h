/*-
 * Copyright (c) 2013, mozgan.
 * All Rights Reserved with BSD License.
 * Read LICENSE file.
 */

/**
 * @file	timer0.h
 * @brief	specific header file for timer/counter 0
 *
 * @author	M. Ozgan, <mozgan@mozgan.org>
 * @version	0.2
 * @date	19.08.2013 15:54:58
 * @internal
 *	$Compiler:	gcc (on Mac, and 4.4BSD) $
 *	$Company:	TU Wien $
 *
 *  @bug	none
 *  @todo	none
 */

/*
 *	@(#) driver/timer0.h		TU Wien 19.08.2013
 *  $Id: timer0.h,v 0.2 19.08.2013 15:54:58 mozgan Exp $
 */

#ifndef __TIMER0_H__
#define __TIMER0_H__	1

#include <board/freq.h>
#include <include/common.h>

uint16_t	int_cnt0;	/**< timer 0 interrupt counter */



void		(*timer0_handler)(void);    /**< call back function from interrupt */

extern void	timer0_init_f(uint16_t, void (*)(void));
extern void	timer0_stop(void);



#endif /* __TIMER0_H__ */


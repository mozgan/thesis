/*-
 * Copyright (c) 2013, mozgan.
 * All Rights Reserved with BSD License.
 * Read LICENSE file.
 */

/**
 * @file	icp.h
 * @brief	header file for input capture pin operations
 *
 * @author	M. Ozgan, <mozgan@mozgan.org>
 * @version	0.1
 * @date	22.08.2013 15:56:37
 * @internal
 *	$Compiler:	gcc (on Mac, and 4.4BSD) $
 *	$Company:	TU Wien $
 *
 *  @bug	none
 *  @todo	none
 */

/*
 *	@(#) driver/icp.h		TU Wien 22.08.2013
 *  $Id: icp.h,v 0.1 22.08.2013 15:56:37 mozgan Exp $
 */

#ifndef __ICP_H__
#define __ICP_H__   1

#include <device/atmega16.h>



void		    (*icp_handler)(uint16_t);	    /**< call back function */
extern void	    icp_init(void (*)(uint16_t));



#endif /* __ICP_H__ */


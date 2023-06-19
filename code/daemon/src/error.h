/*-
 * Copyright (c) 2013, mozgan.
 * All Rights Reserved with BSD License.
 * Read LICENSE file.
 */

/**
 * @file	error.h
 * @brief	header file for error 
 *
 * @author	M. Ozgan, <mozgan@mozgan.org>
 * @version	0.1
 * @date	23.08.2013 22:20:44
 * @internal
 *	$Compiler:	gcc (on Mac, and 4.4BSD) $
 *	$Company:	TU Wien $
 *
 *  @bug	none
 *  @todo	none
 */

/*
 *	@(#) src/error.h		TU Wien 23.08.2013
 *  $Id: error.h,v 0.1 23.08.2013 22:20:44 mozgan Exp $
 */

#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

void		sys_err(const char *);	/* system error */



#endif /* __ERROR_H__ */


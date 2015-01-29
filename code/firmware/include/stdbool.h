/*-
 * Copyright (c) 2013, mozgan.
 * All Rights Reserved with BSD License.
 * Read LICENSE file.
 */

/**
 * @file	stdbool.h
 * @brief	boolean definitions
 *
 * @author	M. Ozgan, <mozgan@mozgan.org>
 * @version	0.1
 * @date	19.08.2013 15:07:52
 * @internal
 *	$Compiler:	gcc (on Mac and 4.4BSD) $
 *	$Company:	TU Wien $
 *
 *  @bug	none
 *  @todo	none
 */

/*
 *	@(#) include/stdbool.h		TU Wien 19.08.2013
 *  $Id: stdbool.h,v 0.1 19.08.2013 15:07:52 mozgan Exp $
 */

#ifndef __STDBOOL_H__
#define __STDBOOL_H__	1

#include <stdio.h>
#include <stdint.h>

#ifndef	    bool	    /**< define the boolean data typ, if not defined */
#define	    bool	    _BOOL
#endif

#ifndef	    _BOOL
#define	    _BOOL	    int
#endif



#endif /* __STDBOOL_H__ */


/*-
 * Copyright (c) 2013, mozgan.
 * All Rights Reserved with BSD License.
 * Read LICENSE file.
 */

/**
 * @file	common.h
 * @brief	some useful definitions
 *
 * @author	M. Ozgan, <mozgan@mozgan.org>
 * @version	0.1
 * @date	19.08.2013 15:06:36
 * @internal
 *	$Compiler:	gcc (on Mac and 4.4BSD) $
 *	$Company:	TU Wien $
 *
 *  @bug	none
 *  @todo	none
 */

/*
 *	@(#) include/common.h		TU Wien 19.08.2013
 *  $Id: common.h,v 0.1 19.08.2013 15:06:36 mozgan Exp $
 */

#ifndef __COMMON_H__
#define __COMMON_H__	1

#include <stdbool.h>

/**
 * @brief find minimum
 *
 * @param x first parameter
 * @param y second parameter
 *
 * @return returns the minimum
 */
#define	    MIN(x, y)	    (((x) < (y)) ? (x) : (y))

/**
 * @brief find maximum
 *
 * @param x first parameter
 * @param y second parameter
 *
 * @return returns the maximum
 */
#define	    MAX(x, y)	    (((x) > (y)) ? (x) : (y))

#ifndef	    TRUE	    /**< if TRUE not defined, define it  */
#define	    TRUE	    (bool)(1)
#endif

#ifndef	    FALSE	    /**< if FALSE not defined, define it */
#define	    FALSE	    (bool)(0)
#endif

#ifndef	    true	    /**< if true not defined, define it  */
#define	    true	    (bool)(1)
#endif

#ifndef	    false	    /**< if false not defined, define it  */
#define	    false	    (bool)(0)
#endif

#ifndef	    NULL	    /**< if NULL not defined, define it  */
#define	    NULL	    (void *)(0)
#endif



#endif /* __COMMON_H__ */


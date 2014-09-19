/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License, Version 1.0 only
 * (the "License").  You may not use this file except in compliance
 * with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright 2008 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _PORT_SYS_DEBUG_H
#define _PORT_SYS_DEBUG_H

#include <assert.h>

/* This definition is copied from assert.h. */
#if defined(__STDC__)
#if __STDC_VERSION__ - 0 >= 199901L
#define zp_verify(EX) (void)((EX) || \
        (__assert_c99(#EX, __FILE__, __LINE__, __func__), 0))
#else
#define zp_verify(EX) (void)((EX) || (__assert(#EX, __FILE__, __LINE__), 0))
#endif /* __STDC_VERSION__ - 0 >= 199901L */
#else
#define zp_verify(EX) (void)((EX) || (_assert("EX", __FILE__, __LINE__), 0))
#endif  /* __STDC__ */

#undef VERIFY
#undef ASSERT

#define VERIFY(EX) zp_verify(EX)
#define ASSERT(EX) assert(EX)

#endif

/*
 * This file is part of the ZFS Linux port.
 *
 *  Copyright (c) 2008 Lawrence Livermore National Security, LLC.
 *  Produced at Lawrence Livermore National Laboratory
 *  Written by:
 *          Brian Behlendorf <behlendorf1@llnl.gov>,
 *          Herb Wartens <wartens2@llnl.gov>,
 *          Jim Garlick <garlick@llnl.gov>
 * LLNL-CODE-403049
 *
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

#ifndef _ZPIOS_CTL_H
#define _ZPIOS_CTL_H

/* Contains shared definitions which both the userspace
 * and kernelspace portions of zpios must agree on.
 */
#ifndef _KERNEL
#include <stdint.h>
#endif

#define ZPIOS_MAJOR			232 /* XXX - Arbitrary */
#define ZPIOS_MINORS                    1
#define ZPIOS_DEV			"/dev/zpios"

#define DMU_IO				0x01

#define DMU_WRITE			0x01
#define DMU_READ			0x02
#define DMU_VERIFY			0x04
#define DMU_REMOVE			0x08
#define DMU_FPP				0x10
#define DMU_WRITE_ZC			0x20 /* Incompatible with DMU_VERIFY */
#define DMU_READ_ZC			0x40 /* Incompatible with DMU_VERIFY */
#define DMU_WRITE_NOWAIT		0x80

#define ZPIOS_NAME_SIZE			16
#define ZPIOS_PATH_SIZE			128

#define PHASE_PRE_RUN			"pre-run"
#define PHASE_PRE_CREATE		"pre-create"
#define PHASE_PRE_WRITE			"pre-write"
#define PHASE_PRE_READ			"pre-read"
#define PHASE_PRE_REMOVE		"pre-remove"
#define PHASE_POST_RUN			"post-run"
#define PHASE_POST_CREATE		"post-create"
#define PHASE_POST_WRITE		"post-write"
#define PHASE_POST_READ			"post-read"
#define PHASE_POST_REMOVE		"post-remove"

#define	ZPIOS_CFG_MAGIC			0x87237190U
typedef struct zpios_cfg {
	uint32_t cfg_magic;		/* Unique magic */
	int32_t cfg_cmd;		/* Config command */
	int32_t cfg_arg1;		/* Config command arg 1 */
	int32_t cfg_rc1;		/* Config response 1 */
} zpios_cfg_t;

typedef struct zpios_time {
	struct timespec start;
	struct timespec stop;
	struct timespec delta;
} zpios_time_t;

typedef struct zpios_stats {
	zpios_time_t total_time;
	zpios_time_t cr_time;
	zpios_time_t rm_time;
	zpios_time_t wr_time;
	zpios_time_t rd_time;
	uint64_t wr_data;
	uint64_t wr_chunks;
	uint64_t rd_data;
	uint64_t rd_chunks;
} zpios_stats_t;

#define	ZPIOS_CMD_MAGIC			0x49715385U
typedef struct zpios_cmd {
	uint32_t cmd_magic;		/* Unique magic */
	uint32_t cmd_id;		/* Run ID */
	char cmd_pool[ZPIOS_NAME_SIZE];	/* Pool name */
	uint64_t cmd_chunk_size;	/* Chunk size */
	uint32_t cmd_thread_count;	/* Thread count */
	uint32_t cmd_region_count;	/* Region count */
	uint64_t cmd_region_size;	/* Region size */
	uint64_t cmd_offset;		/* Region offset */
	uint32_t cmd_region_noise;	/* Region noise */
	uint32_t cmd_chunk_noise;	/* Chunk noise */
	uint32_t cmd_thread_delay;	/* Thread delay */
	uint32_t cmd_flags;		/* Test flags */
        char cmd_pre[ZPIOS_PATH_SIZE];	/* Pre-exec hook */
        char cmd_post[ZPIOS_PATH_SIZE];	/* Post-exec hook */
	char cmd_log[ZPIOS_PATH_SIZE];  /* Requested log dir */
	uint64_t cmd_data_size;		/* Opaque data size */
	char cmd_data_str[0];		/* Opaque data region */
} zpios_cmd_t;

/* Valid ioctls */
#define ZPIOS_CFG				_IOWR('f', 101, long)
#define ZPIOS_CMD				_IOWR('f', 102, long)

/* Valid configuration commands */
#define ZPIOS_CFG_BUFFER_CLEAR		0x001	/* Clear text buffer */
#define ZPIOS_CFG_BUFFER_SIZE		0x002	/* Resize text buffer */

#endif /* _ZPIOS_CTL_H */

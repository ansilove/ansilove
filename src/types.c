/*
 * types.c
 * Ansilove 4.2.1
 * https://www.ansilove.org
 *
 * Copyright (c) 2011-2025 Stefan Vogt, Brian Cassidy, and Frederic Cambus
 * All rights reserved.
 *
 * Ansilove is licensed under the BSD 2-Clause license.
 * See LICENSE file for details.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "ansilove.h"
#include "types.h"

char *types[] = {
	"ans",
	"adf",
	"bin",
	"idf",
	"pcb",
	"tnd",
	"xb",
};

int filetypes[] = {
	ANSILOVE_FILETYPE_ANS,
	ANSILOVE_FILETYPE_ADF,
	ANSILOVE_FILETYPE_BIN,
	ANSILOVE_FILETYPE_IDF,
	ANSILOVE_FILETYPE_PCB,
	ANSILOVE_FILETYPE_TND,
	ANSILOVE_FILETYPE_XB
};

int (*loaders[])(struct ansilove_ctx *, struct ansilove_options *) = {
	ansilove_ansi,
	ansilove_artworx,
	ansilove_binary,
	ansilove_icedraw,
	ansilove_pcboard,
	ansilove_tundra,
	ansilove_xbin
};

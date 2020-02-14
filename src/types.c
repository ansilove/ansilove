/*
 * types.c
 * Ansilove 4.0.7
 * https://www.ansilove.org
 *
 * Copyright (c) 2011-2020 Stefan Vogt, Brian Cassidy, and Frederic Cambus
 * All rights reserved.
 *
 * Ansilove is licensed under the BSD 2-Clause License.
 * See LICENSE file for details.
 */

#include "ansilove.h"

char *types[] = {
	"ans",
	"adf",
	"bin",
	"idf",
	"pcb",
	"tnd",
	"xb",
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

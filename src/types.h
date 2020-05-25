/*
 * types.h
 * Ansilove 4.1.0
 * https://www.ansilove.org
 *
 * Copyright (c) 2011-2020 Stefan Vogt, Brian Cassidy, and Frederic Cambus
 * All rights reserved.
 *
 * Ansilove is licensed under the BSD 2-Clause License.
 * See LICENSE file for details.
 */

#ifndef TYPES_H
#define TYPES_H

#define ANSILOVE_FILETYPE_ANS	1
#define ANSILOVE_FILETYPE_ADF	2
#define ANSILOVE_FILETYPE_BIN	3
#define ANSILOVE_FILETYPE_IDF	4
#define ANSILOVE_FILETYPE_PCB	5
#define ANSILOVE_FILETYPE_TND	6
#define ANSILOVE_FILETYPE_XB	7

struct ansilove_ctx;
struct ansilove_options;

extern char *types[];
extern int filetypes[];
extern int (*loaders[])(struct ansilove_ctx *, struct ansilove_options *);

#endif /* TYPES_H */

/*
 * sauce.h
 * Ansilove 4.2.0
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

#ifndef SAUCE_H
#define SAUCE_H

#include <stdint.h>
#include <stdio.h>

/* sauce records */
#define RECORD_SIZE  128
#define COMMENT_SIZE 64
#define SAUCE_ID     "SAUCE"
#define COMMENT_ID   "COMNT"

struct sauce {
	char ID[6];
	char version[3];
	char title[36];
	char author[21];
	char group[21];
	char date[9];
	int32_t fileSize;
	unsigned char dataType;
	unsigned char fileType;
	unsigned short tinfo1;
	unsigned short tinfo2;
	unsigned short tinfo3;
	unsigned short tinfo4;
	unsigned char comments;
	unsigned char flags;
	char tinfos[23];
	char **comment_lines;
};

struct sauce	*sauceReadFileName(char *);
struct sauce	*sauceReadFile(FILE *);
void		 readRecord(FILE *, struct sauce *);
int		 readComments(FILE *, char **, int32_t);

#endif /* SAUCE_H */

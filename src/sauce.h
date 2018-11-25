/*
 * sauce.h
 * Ansilove 4.0.0
 * https://www.ansilove.org
 *
 * Copyright (c) 2011-2018 Stefan Vogt, Brian Cassidy, and Frederic Cambus
 * All rights reserved.
 *
 * Ansilove is licensed under the BSD 2-Clause License.
 * See LICENSE file for details.
 */

#ifndef SAUCE_H
#define SAUCE_H

#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <stdio.h>

/* sauce records */
#define RECORD_SIZE  128
#define COMMENT_SIZE 64
#define SAUCE_ID     "SAUCE"
#define COMMENT_ID   "COMNT"

typedef struct {
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
} sauce;

sauce	*sauceReadFileName(char *fileName);
sauce	*sauceReadFile(FILE *file);
void	 readRecord(FILE *file, sauce *record);
int	 readComments(FILE *file, char **comment_lines, int32_t comments);

#endif /* SAUCE_H */

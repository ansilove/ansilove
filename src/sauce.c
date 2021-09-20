/*
 * sauce.c
 * Ansilove 4.1.5
 * https://www.ansilove.org
 *
 * Copyright (c) 2011-2021 Stefan Vogt, Brian Cassidy, and Frederic Cambus
 * All rights reserved.
 *
 * Ansilove is licensed under the BSD 2-Clause License.
 * See LICENSE file for details.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "sauce.h"

/* Reads SAUCE via a filename. */
struct sauce *
sauceReadFileName(char *fileName)
{
	FILE *file = fopen(fileName, "r");
	if (file == NULL) {
		return NULL;
	}

	struct sauce *record = sauceReadFile(file);
	fclose(file);
	return record;
}

/* Read SAUCE via a FILE pointer. */
struct sauce *
sauceReadFile(FILE *file)
{
	struct sauce *record;
	record = malloc(sizeof *record);

	if (record != NULL) {
		memset(record, 0, sizeof *record);
		readRecord(file, record);
	}
	return record;
}

#define READ_RECORD(record, size) \
	read_status = fread(record, size, 1, file); \
	if (read_status != 1) \
		return;

void
readRecord(FILE *file, struct sauce *record)
{
	size_t read_status;

	if (fseek(file, 0 - RECORD_SIZE, SEEK_END) != 0) {
		return;
	}

	read_status = fread(record->ID, sizeof (record->ID) - 1, 1, file);
	record->ID[sizeof (record->ID) - 1] = '\0';

	if (read_status != 1 || strcmp(record->ID, SAUCE_ID) != 0) {
		return;
	}
	READ_RECORD(record->version, sizeof(record->version) - 1);
	record->version[sizeof (record->version) - 1] = '\0';
	READ_RECORD(record->title, sizeof(record->title) - 1);
	record->title[sizeof (record->title) - 1] = '\0';
	READ_RECORD(record->author, sizeof(record->author) -1);
	record->author[sizeof (record->author) - 1] = '\0';
	READ_RECORD(record->group, sizeof(record->group) - 1);
	record->group[sizeof (record->group) - 1] = '\0';
	READ_RECORD(record->date, sizeof(record->date) - 1);
	record->date[sizeof (record->date) - 1] = '\0';
	READ_RECORD(&(record->fileSize), sizeof (record->fileSize));
	READ_RECORD(&(record->dataType), sizeof (record->dataType));
	READ_RECORD(&(record->fileType), sizeof (record->fileType));
	READ_RECORD(&(record->tinfo1), sizeof (record->tinfo1));
	READ_RECORD(&(record->tinfo2), sizeof (record->tinfo2));
	READ_RECORD(&(record->tinfo3), sizeof (record->tinfo3));
	READ_RECORD(&(record->tinfo4), sizeof (record->tinfo4));
	READ_RECORD(&(record->comments), sizeof (record->comments));
	READ_RECORD(&(record->flags), sizeof (record->flags));
	READ_RECORD(record->tinfos, sizeof(record->tinfos) - 1);
	record->tinfos[sizeof (record->tinfos) - 1] = '\0';

	if (ferror(file) != 0) {
		return;
	}

	if (record->comments > 0) {
		record->comment_lines = malloc(record->comments *sizeof (*record->comment_lines));

		if (record->comment_lines != NULL) {
			if (readComments(file, record->comment_lines, record->comments) == -1) {
				record->comments = 0;
			}
		}
	}
}

int
readComments(FILE *file, char **comment_lines, int32_t comments)
{
	int32_t i;
	size_t read_status;

	if (fseek(file, 0 - (RECORD_SIZE + 5 + COMMENT_SIZE *comments), SEEK_END) == 0) {
		char ID[6];
		read_status = fread(ID, sizeof (ID) - 1, 1, file);
		if (read_status != 1)
			return -1;

		ID[sizeof (ID) - 1] = '\0';

		if (strcmp(ID, COMMENT_ID) != 0) {
			return -1;
		}

		for (i = 0; i < comments; i++) {
			char buf[COMMENT_SIZE + 1] = "";

			read_status = fread(buf, COMMENT_SIZE, 1, file);
			if (read_status != 1)
				return -1;

			buf[COMMENT_SIZE] = '\0';

			if (ferror(file) == 0) {
				comment_lines[i] = strdup(buf);
				if (comment_lines[i] == NULL) {
					return -1;
				}
			} else {
				return -1;
			}
		}
		return 0;
	}
	return -1;
}

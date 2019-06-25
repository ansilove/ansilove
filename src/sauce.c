/*
 * sauce.c
 * Ansilove 4.0.1
 * https://www.ansilove.org
 *
 * Copyright (c) 2011-2019 Stefan Vogt, Brian Cassidy, and Frederic Cambus
 * All rights reserved.
 *
 * Ansilove is licensed under the BSD 2-Clause License.
 * See LICENSE file for details.
 */

#define _XOPEN_SOURCE 700

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "sauce.h"

/* Reads SAUCE via a filename. */
sauce *
sauceReadFileName(char *fileName)
{
	FILE *file = fopen(fileName, "r");
	if (file == NULL) {
		return NULL;
	}

	sauce *record = sauceReadFile(file);
	fclose(file);
	return record;
}

/* Read SAUCE via a FILE pointer. */
sauce *
sauceReadFile(FILE *file)
{
	sauce *record;
	record = malloc(sizeof *record);

	if (record != NULL) {
		readRecord(file, record);
	}
	return record;
}

void
readRecord(FILE *file, sauce *record)
{
	if (fseek(file, 0 - RECORD_SIZE, SEEK_END) != EXIT_SUCCESS) {
		free(record);
		return;
	}

	size_t read_status = fread(record->ID, sizeof (record->ID) - 1, 1, file);
	record->ID[sizeof (record->ID) - 1] = '\0';

	if (read_status != 1 || strcmp(record->ID, SAUCE_ID) != 0) {
		free(record);
		return;
	}
	fread(record->version, sizeof (record->version) - 1, 1, file);
	record->version[sizeof (record->version) - 1] = '\0';
	fread(record->title, sizeof (record->title) - 1, 1, file);
	record->title[sizeof (record->title) - 1] = '\0';
	fread(record->author, sizeof (record->author) - 1, 1, file);
	record->author[sizeof (record->author) - 1] = '\0';
	fread(record->group, sizeof (record->group) - 1, 1, file);
	record->group[sizeof (record->group) - 1] = '\0';
	fread(record->date, sizeof (record->date) - 1, 1, file);
	record->date[sizeof (record->date) - 1] = '\0';
	fread(&(record->fileSize), sizeof (record->fileSize), 1, file);
	fread(&(record->dataType), sizeof (record->dataType), 1, file);
	fread(&(record->fileType), sizeof (record->fileType), 1, file);
	fread(&(record->tinfo1), sizeof (record->tinfo1), 1, file);
	fread(&(record->tinfo2), sizeof (record->tinfo2), 1, file);
	fread(&(record->tinfo3), sizeof (record->tinfo3), 1, file);
	fread(&(record->tinfo4), sizeof (record->tinfo4), 1, file);
	fread(&(record->comments), sizeof (record->comments), 1, file);
	fread(&(record->flags), sizeof (record->flags), 1, file);
	fread(record->tinfos, sizeof (record->tinfos) - 1, 1, file);
	record->tinfos[sizeof (record->tinfos) - 1] = '\0';

	if (ferror(file) != EXIT_SUCCESS) {
		free(record);
		return;
	}

	if (record->comments > 0) {
		record->comment_lines = malloc(record->comments *sizeof (*record->comment_lines));

		if (record->comment_lines != NULL) {
			if (readComments(file, record->comment_lines, record->comments) == -1) {
				record->comments = 0;
			}
		} else {
			free(record);
			return;
		}
	}
}

int
readComments(FILE *file, char **comment_lines, int32_t comments)
{
	int32_t i;

	if (fseek(file, 0 - (RECORD_SIZE + 5 + COMMENT_SIZE *comments), SEEK_END) == EXIT_SUCCESS) {
		char ID[6];
		fread(ID, sizeof (ID) - 1, 1, file);
		ID[sizeof (ID) - 1] = '\0';

		if (strcmp(ID, COMMENT_ID) != 0) {
			free(comment_lines);
			return -1;
		}

		for (i = 0; i < comments; i++) {
			char buf[COMMENT_SIZE + 1] = "";

			fread(buf, COMMENT_SIZE, 1, file);
			buf[COMMENT_SIZE] = '\0';

			if (ferror(file) == EXIT_SUCCESS) {
				comment_lines[i] = strdup(buf);
				if (comment_lines[i] == NULL) {
					free(comment_lines);
					return -1;
				}
			} else {
				free(comment_lines);
				return -1;
			}
		}
		return 0;
	}
	free(comment_lines);
	return -1;
}

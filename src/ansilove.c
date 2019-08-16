/*
 * ansilove.c
 * Ansilove 4.0.2
 * https://www.ansilove.org
 *
 * Copyright (c) 2011-2019 Stefan Vogt, Brian Cassidy, and Frederic Cambus
 * All rights reserved.
 *
 * Ansilove is licensed under the BSD 2-Clause License.
 * See LICENSE file for details.
 */

#define _GNU_SOURCE
#include <ansilove.h>
#include <err.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef HAVE_PLEDGE
#include "pledge.h"
#endif

#ifndef HAVE_STRTONUM
#include "strtonum.h"
#endif

#include "config.h"
#include "fonts.h"
#include "sauce.h"
#include "strtolower.h"

/* prototypes */
static void synopsis(void);
static void version(void);

static void
synopsis(void)
{
	fprintf(stdout, "\nSYNOPSIS\n"
	    "     ansilove [-dhirsv] [-b bits] [-c columns] [-f font] [-m mode]"
	    " [-o file]\n"
	    "              [-R factor] file\n\n");
}

static void
version(void)
{
	fprintf(stdout, "AnsiLove/C %s - ANSI / ASCII art to PNG converter\n"
	    "Copyright (c) 2011-2019 Stefan Vogt, Brian Cassidy, and "
	    "Frederic Cambus.\n", VERSION);
}

int
main(int argc, char *argv[])
{
	/* SAUCE record related bool types */
	bool justDisplaySAUCE = false;
	bool fileHasSAUCE = false;

	/* analyze options and do what has to be done */
	bool fileIsBinary = false;
	bool fileIsANSi = false;
	bool fileIsPCBoard = false;
	bool fileIsTundra = false;

	int getoptFlag;

	char *input = NULL, *output = NULL;
	char *fileName = NULL;
	char *font = NULL;

	static struct ansilove_ctx ctx;
	static struct ansilove_options options;

	const char *errstr;

	if (ansilove_init(&ctx, &options) == -1)
		errx(EXIT_FAILURE, "%s", ansilove_error(&ctx));

	if (pledge("stdio cpath rpath wpath", NULL) == -1)
		err(EXIT_FAILURE, "pledge");

	while ((getoptFlag = getopt(argc, argv, "b:c:df:him:o:rR:sv")) != -1) {
		switch (getoptFlag) {
		case 'b':
			/* convert numeric command line flags to integer values */
			options.bits = strtonum(optarg, 8, 9, &errstr);

			if (errstr)
				errx(EXIT_FAILURE, "Invalid value for bits (must be 8 or 9).");

			break;
		case 'c':
			/* convert numeric command line flags to integer values */
			options.columns = strtonum(optarg, 1, 4096, &errstr);

			if (errstr)
				errx(EXIT_FAILURE, "\nInvalid value for columns (must range from 1 to 4096).");

			break;
		case 'd':
			options.dos = true;
			break;
		case 'f':
			font = optarg;
			for (size_t loop = 0; loop < FONTS; loop++) {
				if (!strcmp(fonts[loop], font)) {
					options.font = fontsId[loop];
					break;
				}
			}
			break;
		case 'h':
			synopsis();
			return EXIT_SUCCESS;
		case 'i':
			options.icecolors = true;
			break;
		case 'm':
			if (!strcmp(optarg, "ced")) {
				options.mode = ANSILOVE_MODE_CED;
			} else if (!strcmp(optarg, "transparent")) {
				options.mode = ANSILOVE_MODE_TRANSPARENT;
			} else if (!strcmp(optarg, "workbench")) {
				options.mode = ANSILOVE_MODE_WORKBENCH;
			}
			break;
		case 'o':
			output = optarg;
			break;
		case 'r':
			options.scale_factor = 2;
			break;
		case 'R':
			/* convert numeric command line flags to integer values */
			options.scale_factor = strtonum(optarg, 2, 8, &errstr);

			if (errstr)
				errx(EXIT_FAILURE, "Invalid value for retina scale factor (must range from 2 to 8).");

			break;
		case 's':
			justDisplaySAUCE = true;
			break;
		case 'v':
			version();
			return EXIT_SUCCESS;
		}
	}

	if (optind < argc) {
		input = argv[optind];
	} else {
		synopsis();
		return EXIT_SUCCESS;
	}

	argc -= optind;
	argv += optind;

	/* let's check the file for a valid SAUCE record */
	sauce *record = sauceReadFileName(input);

	/* record == NULL also means there is no file, we can stop here */
	if (record == NULL) {
		errx(EXIT_FAILURE, "File %s not found.", input);
	} else {
		/* if we find a SAUCE record, update bool flag */
		if (!strcmp(record->ID, SAUCE_ID)) {
			fileHasSAUCE = true;
		}
	}

	if (!justDisplaySAUCE) {
		/* create output file name if output is not specified */
		if (!output) {
			/* appending ".png" extension to output file name */
			if (asprintf(&fileName, "%s%s", input, ".png") == -1)
				errx(EXIT_FAILURE, "Memory allocation error.");
		} else {
			fileName = output;
		}

		/* display name of input and output files */
		fprintf(stdout, "\nInput File: %s\n", input);
		fprintf(stdout, "Output File: %s\n", fileName);

		/* get file extension */
		char *fext = strrchr(input, '.');
		fext = fext ? strtolower(strdup(++fext)) : "";

		/* check if current file has a .diz extension */
		if (!strcmp(fext, "diz"))
			options.diz = true;

		if (ansilove_loadfile(&ctx, input) == -1)
			errx(EXIT_FAILURE, "%s", ansilove_error(&ctx));

		/* adjust the file size if file contains a SAUCE record */
		if (fileHasSAUCE) {
			sauce *saucerec = sauceReadFileName(input);
			ctx.length -= 129 - (saucerec->comments > 0 ? 5 + 64 * saucerec->comments : 0);
		}

		int (*loader)(struct ansilove_ctx *, struct ansilove_options *);

		/* create the output PNG data by invoking the appropriate function */
		if (!strcmp(fext, "pcb")) {
			loader = ansilove_pcboard;
			fileIsPCBoard = true;
		} else if (!strcmp(fext, "bin")) {
			loader = ansilove_binary;
			fileIsBinary = true;
		} else if (!strcmp(fext, "adf")) {
			loader = ansilove_artworx;
		} else if (!strcmp(fext, "idf")) {
			loader = ansilove_icedraw;
		} else if (!strcmp(fext, "tnd")) {
			loader = ansilove_tundra;
			fileIsTundra = true;
		} else if (!strcmp(fext, "xb")) {
			loader = ansilove_xbin;
		} else {
			loader = ansilove_ansi;
			fileIsANSi = true;
		}

		if (loader(&ctx, &options) == -1)
			errx(EXIT_FAILURE, "%s", ansilove_error(&ctx));

		/* create the output file */
		if (ansilove_savefile(&ctx, fileName) == -1)
			errx(EXIT_FAILURE, "%s", ansilove_error(&ctx));

		/* gather information and report to the command line */
		if (fileIsANSi || fileIsBinary ||
		    fileIsPCBoard || fileIsTundra) {
			fprintf(stdout, "Font: %s\n", font ? font : "80x25");

			fprintf(stdout, "Bits: %d\n", options.bits);
		}

		if (options.icecolors && (fileIsANSi || fileIsBinary))
			fprintf(stdout, "iCE Colors: enabled\n");

		if (fileIsANSi || fileIsBinary || fileIsTundra)
			fprintf(stdout, "Columns: %d\n", options.columns);

		if (options.scale_factor)
			fprintf(stdout, "Scale factor: %d\n", options.scale_factor);
	}

	/* either display SAUCE or tell us if there is no record */
	if (!fileHasSAUCE) {
		fprintf(stdout, "\nFile %s does not have a SAUCE record.\n", input);
	} else {
		fprintf(stdout, "\nId: %s v%s\n", record->ID, record->version);
		fprintf(stdout, "Title: %s\n", record->title);
		fprintf(stdout, "Author: %s\n", record->author);
		fprintf(stdout, "Group: %s\n", record->group);
		fprintf(stdout, "Date: %s\n", record->date);
		fprintf(stdout, "Datatype: %d\n", record->dataType);
		fprintf(stdout, "Filetype: %d\n", record->fileType);
		if (record->flags) {
			fprintf(stdout, "Flags: %d\n", record->flags);
		}
		if (record->tinfo1) {
			fprintf(stdout, "Tinfo1: %d\n", record->tinfo1);
		}
		if (record->tinfo2) {
			fprintf(stdout, "Tinfo2: %d\n", record->tinfo2);
		}
		if (record->tinfo3) {
			fprintf(stdout, "Tinfo3: %d\n", record->tinfo3);
		}
		if (record->tinfo4) {
			fprintf(stdout, "Tinfo4: %d\n", record->tinfo4);
		}
		fprintf(stdout, "Tinfos: %s\n", record->tinfos);
		if (record->comments > 0) {
			fprintf(stdout, "Comments: ");
			for (int32_t i = 0; i < record->comments; i++) {
				fprintf(stdout, "%s\n", record->comment_lines[i]);
			}
		}
	}

	ansilove_clean(&ctx);

	return EXIT_SUCCESS;
}

/*
 * main.c
 * Ansilove 4.0.0
 * https://www.ansilove.org
 *
 * Copyright (c) 2011-2018 Stefan Vogt, Brian Cassidy, and Frederic Cambus
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

/* following the IEEE Std 1003.1 for utility conventions */
static void
synopsis(void)
{
	fprintf(stderr, "\nSYNOPSIS:\n"
	    "  ansilove [options] file\n"
	    "  ansilove -e | -h | -v\n\n"
	    "OPTIONS:\n"
	    "  -b bits	  set to 9 to render 9th column of block characters (default: 8)\n"
	    "  -c columns  adjust number of columns for BIN files (default: 160)\n"
	    "  -d			 enable DOS aspect ratio\n"
	    "  -f font	  select font (default: 80x25)\n"
	    "  -h			 show help\n"
	    "  -i			 enable iCE colors\n"
	    "  -m mode	  set rendering mode for ANS files:\n"
	    "					 ced				black on gray, with 78 columns\n"
	    "					 transparent	 render with transparent background\n"
	    "					 workbench		use Amiga Workbench palette\n"
	    "  -o file	  specify output filename/path\n"
	    "  -r			 creates Retina @2x output file\n"
	    "  -R factor	creates Retina output file with custom scale factor\n"
	    "  -s			 show SAUCE record without generating output\n"
	    "  -v			 show version information\n"
	    "\n");
}

int
main(int argc, char *argv[])
{
	fprintf(stderr, "AnsiLove/C %s - ANSI / ASCII art to PNG converter\n" \
	    "Copyright (c) 2011-2018 Stefan Vogt, Brian Cassidy, and Frederic Cambus.\n", VERSION);

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

	ansilove_init(&ctx, &options);

	if (pledge("stdio cpath rpath wpath", NULL) == -1) {
		err(EXIT_FAILURE, "pledge");
	}

	while ((getoptFlag = getopt(argc, argv, "b:c:def:him:o:rR:sv")) != -1) {
		switch (getoptFlag) {
		case 'b':
			/* convert numeric command line flags to integer values */
			options.bits = strtonum(optarg, 8, 9, &errstr);

			if (errstr) {
				fprintf(stderr, "\nInvalid value for bits (must be 8 or 9).\n\n");
				return EXIT_FAILURE;
			}

			break;
		case 'c':
			/* convert numeric command line flags to integer values */
			options.columns = strtonum(optarg, 1, 4096, &errstr);

			if (errstr) {
				fprintf(stderr, "\nInvalid value for columns (must range from 1 to 4096).\n\n");
				return EXIT_FAILURE;
			}

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

			if (errstr) {
				fprintf(stderr, "\nInvalid value for retina scale factor (must range from 2 to 8).\n\n");
				return EXIT_FAILURE;
			}

			break;
		case 's':
			justDisplaySAUCE = true;
			break;
		case 'v':
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
		fprintf(stderr, "\nFile %s not found.\n\n", input);
		return EXIT_FAILURE;
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
			if (asprintf(&fileName, "%s%s", input, ".png") == -1) {
				fprintf(stderr, "Memory allocation error.\n\n");
				return EXIT_FAILURE;
			}
		} else {
			fileName = output;
		}

		/* default to 80x25 font if font option is not specified */
		if (!font) {
			font = "80x25";
		}

		/* display name of input and output files */
		fprintf(stderr, "\nInput File: %s\n", input);
		fprintf(stderr, "Output File: %s\n", fileName);

		/* get file extension */
		char *fext = strrchr(input, '.');
		fext = fext ? strtolower(strdup(fext)) : "";

		/* check if current file has a .diz extension */
		if (!strcmp(fext, ".diz"))
			options.diz = true;

		ansilove_loadfile(&ctx, input);

		/* adjust the file size if file contains a SAUCE record */
		if (fileHasSAUCE) {
			sauce *saucerec = sauceReadFileName(input);
			ctx.length -= 129 - (saucerec->comments > 0 ? 5 + 64 * saucerec->comments : 0);
		}

		/* create the output PNG data by invoking the appropiate function */
		if (!strcmp(fext, ".pcb")) {
			ansilove_pcboard(&ctx, &options);
			fileIsPCBoard = true;
		} else if (!strcmp(fext, ".bin")) {
			ansilove_binary(&ctx, &options);
			fileIsBinary = true;
		} else if (!strcmp(fext, ".adf")) {
			ansilove_artworx(&ctx, &options);
		} else if (!strcmp(fext, ".idf")) {
			ansilove_icedraw(&ctx, &options);
		} else if (!strcmp(fext, ".tnd")) {
			ansilove_tundra(&ctx, &options);
			fileIsTundra = true;
		} else if (!strcmp(fext, ".xb")) {
			ansilove_xbin(&ctx, &options);
		} else {
			ansilove_ansi(&ctx, &options);
			fileIsANSi = true;
		}

		/* create the output file */
		ansilove_savefile(&ctx, fileName);

		/* gather information and report to the command line */
		if (fileIsANSi || fileIsBinary ||
		    fileIsPCBoard || fileIsTundra) {
			fprintf(stderr, "Font: %s\n", font);

			fprintf(stderr, "Bits: %d\n", options.bits);
		}
		if (options.icecolors && (fileIsANSi || fileIsBinary)) {
			fprintf(stderr, "iCE Colors: enabled\n");
		}
		if (fileIsANSi || fileIsBinary || fileIsTundra) {
			fprintf(stderr, "Columns: %d\n", options.columns);
		}

		if (options.scale_factor) {
			fprintf(stderr, "Scale factor: %d\n", options.scale_factor);
		}

		/* TODO: munmap, with original ctxSize */
	}

	/* either display SAUCE or tell us if there is no record */
	if (!fileHasSAUCE) {
		fprintf(stderr, "\nFile %s does not have a SAUCE record.\n", input);
	} else {
		fprintf(stderr, "\nId: %s v%s\n", record->ID, record->version);
		fprintf(stderr, "Title: %s\n", record->title);
		fprintf(stderr, "Author: %s\n", record->author);
		fprintf(stderr, "Group: %s\n", record->group);
		fprintf(stderr, "Date: %s\n", record->date);
		fprintf(stderr, "Datatype: %d\n", record->dataType);
		fprintf(stderr, "Filetype: %d\n", record->fileType);
		if (record->flags != 0) {
			fprintf(stderr, "Flags: %d\n", record->flags);
		}
		if (record->tinfo1 != 0) {
			fprintf(stderr, "Tinfo1: %d\n", record->tinfo1);
		}
		if (record->tinfo2 != 0) {
			fprintf(stderr, "Tinfo2: %d\n", record->tinfo2);
		}
		if (record->tinfo3 != 0) {
			fprintf(stderr, "Tinfo3: %d\n", record->tinfo3);
		}
		if (record->tinfo4 != 0) {
			fprintf(stderr, "Tinfo4: %d\n", record->tinfo4);
		}
		fprintf(stderr, "Tinfos: %s\n", record->tinfos);
		if (record->comments > 0) {
			fprintf(stderr, "Comments: ");
			for (int32_t i = 0; i < record->comments; i++) {
				fprintf(stderr, "%s\n", record->comment_lines[i]);
			}
		}
	}

	ansilove_clean(&ctx);

	return EXIT_SUCCESS;
}

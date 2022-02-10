/*
 * ansilove.c
 * Ansilove 4.1.6
 * https://www.ansilove.org
 *
 * Copyright (c) 2011-2022 Stefan Vogt, Brian Cassidy, and Frederic Cambus
 * All rights reserved.
 *
 * Ansilove is licensed under the BSD 2-Clause license.
 * See LICENSE file for details.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <sys/time.h>
#include <ansilove.h>
#include <err.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef HAVE_SECCOMP
#include <sys/prctl.h>
#include <linux/seccomp.h>
#include "seccomp.h"
#endif

#include "compat.h"
#include "config.h"
#include "fonts.h"
#include "sauce.h"
#include "strtolower.h"
#include "types.h"

/* prototypes */
static void synopsis(void);
static void version(void);

static void
synopsis(void)
{
	fprintf(stdout, "SYNOPSIS\n"
	    "     ansilove [-dhiqrsSv] [-b bits] [-c columns] [-f font]"
	    " [-m mode] [-o file]\n"
	    "              [-R factor] [-t type] file\n");
}

static void
version(void)
{
	fprintf(stdout, "AnsiLove/C %s - ANSI / ASCII art to PNG converter\n"
	    "Copyright (c) 2011-2022 Stefan Vogt, Brian Cassidy, and "
	    "Frederic Cambus.\n", VERSION);
}

int
main(int argc, char *argv[])
{
	FILE *messages = NULL;

	/* SAUCE record related bool types */
	bool justDisplaySAUCE = false;
	bool fileHasSAUCE = false;
	bool useSAUCEInfo = false;

	int opt;

	char *input = NULL, *output = NULL;
	char *fileName = NULL;
	char *font = NULL;
	char *type = NULL;
	int filetype = 0;

	struct timespec begin, end, elapsed;

	static struct ansilove_ctx ctx;
	static struct ansilove_options options;

	const char *errstr;

	if (pledge("stdio cpath rpath wpath", NULL) == -1)
		err(EXIT_FAILURE, "pledge");

#ifdef HAVE_SECCOMP
	if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)) {
		perror("Can't initialize seccomp");
		return EXIT_FAILURE;
	}

	if (prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &ansilove)) {
		perror("Can't load seccomp filter");
		return EXIT_FAILURE;
	}
#endif

	if (ansilove_init(&ctx, &options) == -1)
		errx(EXIT_FAILURE, "%s", ansilove_error(&ctx));

	while ((opt = getopt(argc, argv, "b:c:df:him:o:qrR:sSt:v")) != -1) {
		switch (opt) {
		case 'b':
			options.bits = strtonum(optarg, 8, 9, &errstr);

			if (errstr)
				errx(EXIT_FAILURE, "Invalid value for bits (must be 8 or 9).");

			break;
		case 'c':
			options.columns = strtonum(optarg, 1, 4096, &errstr);

			if (errstr)
				errx(EXIT_FAILURE, "\nInvalid value for columns (must range from 1 to 4096).");

			break;
		case 'd':
			options.dos = true;
			break;
		case 'f':
			font = optarg;
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
		case 'q':
			messages = fopen("/dev/null", "w");
			break;
		case 'r':
			options.scale_factor = 2;
			break;
		case 'R':
			options.scale_factor = strtonum(optarg, 2, 8, &errstr);

			if (errstr)
				errx(EXIT_FAILURE, "Invalid value for retina scale factor (must range from 2 to 8).");

			break;
		case 's':
			justDisplaySAUCE = true;
			break;
		case 'S':
			useSAUCEInfo = true;
			break;
		case 't':
			type = strtolower(optarg);
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

	/* if -q flag was not set, default to stdout */
	if (!messages)
		messages = stdout;

	/* Starting timer */
	clock_gettime(CLOCK_MONOTONIC, &begin);

	/* let's check the file for a valid SAUCE record */
	struct sauce *record = sauceReadFileName(input);

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
		/* gather rendering hints from SAUCE */
		if (useSAUCEInfo && fileHasSAUCE) {
			bool usedSAUCE = false;
			if (record->dataType == 1) {
				if (record->fileType == 0 || record->fileType == 1 || record->fileType == 2) {
					options.columns = record->tinfo1;
					if (record->flags & 1)
						options.icecolors = true;
					if ((record->flags & 6) == 4)
						options.bits = 9;
					if ((record->flags & 24) == 8)
						options.dos = true;
					usedSAUCE = true;
				}
				if (record->fileType == 8) {
					options.columns = record->tinfo1;
					usedSAUCE = true;
				}
			}
			if (record->dataType == 5) {
				options.columns = record->tinfo1;
				usedSAUCE = true;
			}
			/* XBIN (dataType == 6) could also use tinfo1 for width, but we trust the XBIN header more */
			/* font info */
			if ((record->dataType == 1 && (record->fileType == 0 || record->fileType == 1 || record->fileType == 2)) || record->dataType == 5 ) {
				if (strcmp(record->tinfos, "IBM VGA") == 0)
					font = "80x25";

				if (strcmp(record->tinfos, "IBM VGA50") == 0)
					font = "80x50";

				if (strcmp(record->tinfos, "IBM VGA 437") == 0)
					font = "80x25";

				if (strcmp(record->tinfos, "IBM VGA50 437") == 0)
					font = "80x50";

				if (strcmp(record->tinfos, "IBM VGA 775") == 0)
					font = "baltic";

				if (strcmp(record->tinfos, "IBM VGA50 855") == 0)
					font = "cyrillic";

				if (strcmp(record->tinfos, "IBM VGA 863") == 0)
					font = "french-canadian";

				if (strcmp(record->tinfos, "IBM VGA 737") == 0)
					font = "greek";

				if (strcmp(record->tinfos, "IBM VGA 869") == 0)
					font = "greek-869";

				if (strcmp(record->tinfos, "IBM VGA 862") == 0)
					font = "hebrew";

				if (strcmp(record->tinfos, "IBM VGA 861") == 0)
					font = "icelandic";

				if (strcmp(record->tinfos, "IBM VGA 850") == 0)
					font = "latin1";

				if (strcmp(record->tinfos, "IBM VGA 852") == 0)
					font = "latin2";

				if (strcmp(record->tinfos, "IBM VGA 865") == 0)
					font = "nordic";

				if (strcmp(record->tinfos, "IBM VGA 860") == 0)
					font = "portuguese";

				if (strcmp(record->tinfos, "IBM VGA 866") == 0)
					font = "russian";

				if (strcmp(record->tinfos, "IBM VGA 857") == 0)
					font = "turkish";

				if (strcmp(record->tinfos, "Amiga MicroKnight") == 0)
					font = "microknight";

				if (strcmp(record->tinfos, "Amiga MicroKnight+") == 0)
					font = "microknight+";

				if (strcmp(record->tinfos, "Amiga mOsOul") == 0)
					font = "mosoul";

				if (strcmp(record->tinfos, "Amiga P0T-NOoDLE") == 0)
					font = "pot-noodle";

				if (strcmp(record->tinfos, "Amiga Topaz 1") == 0)
					font = " topaz500";

				if (strcmp(record->tinfos, "Amiga Topaz 1+") == 0)
					font = "topaz500+";

				if (strcmp(record->tinfos, "Amiga Topaz 2") == 0)
					font = "topaz";

				if (strcmp(record->tinfos, "Amiga Topaz 2+") == 0)
					font = "topaz+";
			}

			if (usedSAUCE)
				fprintf(messages, "SAUCE info used for rendering hints\n\n");
		}

		if (font) {
			for (size_t loop = 0; loop < FONTS; loop++) {
				if (!strcmp(fonts[loop], font)) {
					options.font = fontsId[loop];
					break;
				}
			}
		}

		/* create output file name if output is not specified */
		if (!output) {
			/* appending ".png" extension to output file name */
			if (asprintf(&fileName, "%s%s", input, ".png") == -1)
				errx(EXIT_FAILURE, "Memory allocation error.");
		} else {
			fileName = strdup(output);

			if (!fileName)
				errx(EXIT_FAILURE, "Memory allocation error.");
		}

		/* display name of input and output files */
		fprintf(messages, "Input File: %s\n", input);
		fprintf(messages, "Output File: %s\n", fileName);

		/* get file extension */
		char *fext = strrchr(input, '.');
		fext = fext ? strtolower(strdup(++fext)) : strdup("");
		if (!fext)
			errx(EXIT_FAILURE, "Memory allocation error.");

		/* check if current file has a .diz extension */
		if (!strcmp(fext, "diz"))
			options.diz = true;

		if (ansilove_loadfile(&ctx, input) == -1)
			errx(EXIT_FAILURE, "%s", ansilove_error(&ctx));

		/* adjust the file size if file contains a SAUCE record */
		if (fileHasSAUCE)
			ctx.length -= 129 - (record->comments > 0 ? 5 + 64 * record->comments : 0);

		int (*loader)(struct ansilove_ctx *, struct ansilove_options *) = NULL;

		/* if type was specified, attempt to find a loader */
		if (type) {
			for (size_t loop = 0; loop < TYPES; loop++) {
				if (!strcmp(types[loop], type)) {
					loader = loaders[loop];
					filetype = filetypes[loop];
					break;
				}
			}

			if (!loader)
				errx(EXIT_FAILURE, "Unknown file type.");
		}

		/* use file extension to find a suitable loader */
		if (!loader) {
			for (size_t loop = 0; loop < TYPES; loop++) {
				if (!strcmp(types[loop], fext)) {
					loader = loaders[loop];
					filetype = filetypes[loop];
					break;
				}
			}
		}

		/* default to ANSI if file extension is unknown */
		if (!loader) {
			loader = ansilove_ansi;
			filetype = ANSILOVE_FILETYPE_ANS;
		}

		if (loader(&ctx, &options) == -1)
			errx(EXIT_FAILURE, "%s", ansilove_error(&ctx));

		/* create the output file */
		if (ansilove_savefile(&ctx, fileName) == -1)
			errx(EXIT_FAILURE, "%s", ansilove_error(&ctx));

		/* gather information and report to the command line */
		switch(filetype) {
		case ANSILOVE_FILETYPE_ANS:
		case ANSILOVE_FILETYPE_BIN:
			if (options.icecolors)
				fprintf(messages, "iCE Colors: enabled\n");

			/* FALLTHROUGH */
		case ANSILOVE_FILETYPE_PCB:
		case ANSILOVE_FILETYPE_TND:
			fprintf(messages, "Font: %s\n", font ? font : "80x25");
			fprintf(messages, "Bits: %d\n", options.bits);
			fprintf(messages, "Columns: %d\n", options.columns);
		}

		if (options.scale_factor)
			fprintf(messages, "Scale factor: %d\n", options.scale_factor);

		free(fileName);
		free(fext);
	}

	/* either display SAUCE or tell us if there is no record */
	if (!fileHasSAUCE) {
		fprintf(messages, "\nFile %s does not have a SAUCE record.\n", input);
	} else {
		fprintf(messages, "\nId: %s v%s\n", record->ID, record->version);
		fprintf(messages, "Title: %s\n", record->title);
		fprintf(messages, "Author: %s\n", record->author);
		fprintf(messages, "Group: %s\n", record->group);
		fprintf(messages, "Date: %s\n", record->date);
		fprintf(messages, "Datatype: %d\n", record->dataType);
		fprintf(messages, "Filetype: %d\n", record->fileType);

		if (record->flags)
			fprintf(messages, "Flags: 0b%d%d%d%d%d%d%d%d\n",
				record->flags >> 7,
				record->flags >> 6 & 1,
				record->flags >> 5 & 1,
				record->flags >> 4 & 1,
				record->flags >> 3 & 1,
				record->flags >> 2 & 1,
				record->flags >> 1 & 1,
				record->flags & 1);

		if (record->tinfo1)
			fprintf(messages, "Tinfo1: %d\n", record->tinfo1);

		if (record->tinfo2)
			fprintf(messages, "Tinfo2: %d\n", record->tinfo2);

		if (record->tinfo3)
			fprintf(messages, "Tinfo3: %d\n", record->tinfo3);

		if (record->tinfo4)
			fprintf(messages, "Tinfo4: %d\n", record->tinfo4);

		fprintf(messages, "Tinfos: %s\n", record->tinfos);
		if (record->comments > 0) {
			fprintf(messages, "Comments: ");
			for (int32_t i = 0; i < record->comments; i++)
				fprintf(messages, "%s\n", record->comment_lines[i]);
		}
	}

	/* Stopping timer */
	clock_gettime(CLOCK_MONOTONIC, &end);

	timespecsub(&end, &begin, &elapsed);

	fprintf(messages, "\nProcessed in %f seconds.\n",
	    elapsed.tv_sec + elapsed.tv_nsec / 1E9);

	ansilove_clean(&ctx);

	free(record->comment_lines);
	free(record);

	return EXIT_SUCCESS;
}

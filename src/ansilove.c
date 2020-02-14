/*
 * ansilove.c
 * Ansilove 4.0.7
 * https://www.ansilove.org
 *
 * Copyright (c) 2011-2020 Stefan Vogt, Brian Cassidy, and Frederic Cambus
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

#ifdef HAVE_SECCOMP
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <linux/audit.h>
#include <linux/filter.h>
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
	    "     ansilove [-dhiqrsv] [-b bits] [-c columns] [-f font]"
	    " [-m mode] [-o file]\n"
	    "              [-R factor] file\n");
}

static void
version(void)
{
	fprintf(stdout, "AnsiLove/C %s - ANSI / ASCII art to PNG converter\n"
	    "Copyright (c) 2011-2020 Stefan Vogt, Brian Cassidy, and "
	    "Frederic Cambus.\n", VERSION);
}

int
main(int argc, char *argv[])
{
	FILE *messages = NULL;

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
	char *type = NULL;

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

	while ((getoptFlag = getopt(argc, argv, "b:c:df:him:o:qrR:st:v")) != -1) {
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
		case 'q':
			messages = fopen("/dev/null", "w");
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
		case 't':
			type = optarg;
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

	/* if -q flag was not set, default to stdout */
	if (!messages)
		messages = stdout;

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
		/* create output file name if output is not specified */
		if (!output) {
			/* appending ".png" extension to output file name */
			if (asprintf(&fileName, "%s%s", input, ".png") == -1)
				errx(EXIT_FAILURE, "Memory allocation error.");
		} else {
			fileName = strdup(output);
		}

		/* display name of input and output files */
		fprintf(messages, "Input File: %s\n", input);
		fprintf(messages, "Output File: %s\n", fileName);

		/* get file extension */
		char *fext = strrchr(input, '.');
		fext = fext ? strtolower(strdup(++fext)) : strdup("");

		/* check if current file has a .diz extension */
		if (!strcmp(fext, "diz"))
			options.diz = true;

		if (ansilove_loadfile(&ctx, input) == -1)
			errx(EXIT_FAILURE, "%s", ansilove_error(&ctx));

		/* adjust the file size if file contains a SAUCE record */
		if (fileHasSAUCE)
			ctx.length -= 129 - (record->comments > 0 ? 5 + 64 * record->comments : 0);

		/* set icecolors to true if defined in SAUCE record ANSiFlags */
		if (fileHasSAUCE && (record->flags & 1))
			options.icecolors = true;

		int (*loader)(struct ansilove_ctx *, struct ansilove_options *) = NULL;

		/* if type was specified, attempt to find a loader */
		if (type) {
			for (size_t loop = 0; loop < 7; loop++) {
				if (!strcmp(types[loop], type)) {
					loader = loaders[loop];
					break;
				}
			}
		}

		/* fall back on file extension if no loader was found */
		if (!loader) {
			for (size_t loop = 0; loop < 7; loop++) {
				if (!strcmp(types[loop], fext)) {
					loader = loaders[loop];
					break;
				}
			}
		}

		if (!loader) {
			loader = ansilove_ansi;
		}

		if (loader(&ctx, &options) == -1)
			errx(EXIT_FAILURE, "%s", ansilove_error(&ctx));

		/* create the output file */
		if (ansilove_savefile(&ctx, fileName) == -1)
			errx(EXIT_FAILURE, "%s", ansilove_error(&ctx));

		/* gather information and report to the command line */
		if (fileIsANSi || fileIsBinary ||
		    fileIsPCBoard || fileIsTundra) {
			fprintf(messages, "Font: %s\n", font ? font : "80x25");

			fprintf(messages, "Bits: %d\n", options.bits);
		}

		if (options.icecolors && (fileIsANSi || fileIsBinary))
			fprintf(messages, "iCE Colors: enabled\n");

		if (fileIsANSi || fileIsBinary || fileIsTundra)
			fprintf(messages, "Columns: %d\n", options.columns);

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
		if (record->flags) {
			fprintf(messages, "Flags: %d\n", record->flags);
		}
		if (record->tinfo1) {
			fprintf(messages, "Tinfo1: %d\n", record->tinfo1);
		}
		if (record->tinfo2) {
			fprintf(messages, "Tinfo2: %d\n", record->tinfo2);
		}
		if (record->tinfo3) {
			fprintf(messages, "Tinfo3: %d\n", record->tinfo3);
		}
		if (record->tinfo4) {
			fprintf(messages, "Tinfo4: %d\n", record->tinfo4);
		}
		fprintf(messages, "Tinfos: %s\n", record->tinfos);
		if (record->comments > 0) {
			fprintf(messages, "Comments: ");
			for (int32_t i = 0; i < record->comments; i++) {
				fprintf(messages, "%s\n", record->comment_lines[i]);
			}
		}
	}

	ansilove_clean(&ctx);

	free(record->comment_lines);
	free(record);

	return EXIT_SUCCESS;
}

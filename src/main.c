//
//  main.c
//  AnsiLove/C
//
//  Copyright (c) 2011-2018 Stefan Vogt, Brian Cassidy, and Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 2-Clause License.
//  See the LICENSE file for details.
//

#define _GNU_SOURCE
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>
#include <unistd.h>
#include <err.h>
#include <ansilove.h>

#ifndef HAVE_PLEDGE
#include "pledge.h"
#endif

#ifndef HAVE_STRTONUM
#include "strtonum.h"
#endif

#include "config.h"
#include "strtolower.h"
#include "ansilove.h"
#include "sauce.h"

// prototypes
void showHelp(void);
void listExamples(void);
void versionInfo(void);
void synopsis(void);

void showHelp(void) {
    fprintf(stderr, "\nSUPPORTED FILE TYPES:\n"
           "  ANS   PCB   BIN   ADF   IDF   TND   XB\n"
           "  Files with custom suffix default to the ANSI renderer.\n\n"
           "PC FONTS:\n"
           "  80x25              icelandic\n"
           "  80x50              latin1\n"
           "  baltic             latin2\n"
           "  cyrillic           nordic\n"
           "  french-canadian    portuguese\n"
           "  greek              russian\n"
           "  greek-869          terminus\n"
           "  hebrew             turkish\n\n"
           "AMIGA FONTS:\n"
           "  amiga              topaz\n"
           "  microknight        topaz+\n"
           "  microknight+       topaz500\n"
           "  mosoul             topaz500+\n"
           "  pot-noodle\n\n"
           "DOCUMENTATION:\n"
           "  Detailed help is available at the AnsiLove/C repository on GitHub.\n"
           "  <https://github.com/ansilove/ansilove>\n\n");
}

void listExamples(void) {
    fprintf(stderr, "\nEXAMPLES:\n");
    fprintf(stderr, "  ansilove file.ans (output path/name identical to input, no options)\n"
           "  ansilove -i file.ans (enable iCE colors)\n"
           "  ansilove -r file.ans (adds Retina @2x output file)\n"
           "  ansilove -R 3 file.ans (adds Retina @3x output file)\n"
           "  ansilove -o dir/file.png file.ans (custom path/name for output)\n"
           "  ansilove -s file.bin (just display SAUCE record, don't generate output)\n"
           "  ansilove -m transparent file.ans (render with transparent background)\n"
           "  ansilove -f amiga file.txt (custom font)\n"
           "  ansilove -f 80x50 -b 9 -c 320 -i file.bin (font, bits, columns, icecolors)\n"
           "\n");
}

void versionInfo(void) {
    fprintf(stderr, "All rights reserved.\n"
           "\nFork me on GitHub: <https://github.com/ansilove/ansilove>\n"
           "Bug reports: <https://github.com/ansilove/ansilove/issues>\n\n"
           "This is free software, released under the 2-Clause BSD license.\n"
           "<https://github.com/ansilove/ansilove/blob/master/LICENSE>\n\n");
}

// following the IEEE Std 1003.1 for utility conventions
void synopsis(void) {
    fprintf(stderr, "\nSYNOPSIS:\n"
           "  ansilove [options] file\n"
           "  ansilove -e | -h | -v\n\n"
           "OPTIONS:\n"
           "  -b bits     set to 9 to render 9th column of block characters (default: 8)\n"
           "  -c columns  adjust number of columns for BIN files (default: 160)\n"
           "  -e          print a list of examples\n"
           "  -f font     select font (default: 80x25)\n"
           "  -h          show help\n"
           "  -i          enable iCE colors\n"
           "  -m mode     set rendering mode for ANS files:\n"
           "                ced            black on gray, with 78 columns\n"
           "                transparent    render with transparent background\n"
           "                workbench      use Amiga Workbench palette\n"
           "  -o file     specify output filename/path\n"
           "  -r          creates additional Retina @2x output file\n"
           "  -R factor   creates additional Retina output file with custom scale factor\n"
           "  -s          show SAUCE record without generating output\n"
           "  -v          show version information\n"
           "\n");
}

int main(int argc, char *argv[]) {
    fprintf(stderr, "AnsiLove/C %s - ANSI / ASCII art to PNG converter\n"\
           "Copyright (c) 2011-2018 Stefan Vogt, Brian Cassidy, and Frederic Cambus.\n", VERSION);

    // SAUCE record related bool types
    bool justDisplaySAUCE = false;
    bool fileHasSAUCE = false;

    // analyze options and do what has to be done
    bool fileIsBinary = false;
    bool fileIsANSi = false;
    bool fileIsPCBoard = false;
    bool fileIsTundra = false;

    int getoptFlag;

    char *input = NULL, *output = NULL;

    struct input inputFile;
    struct output outputFile;

    const char *errstr;

    // default to 8 if bits option is not specified
    outputFile.bits = 8;

    // default to 160 if columns option is not specified
    inputFile.columns = 160;

    // default to 0 if retinaScaleFactor option is not specified
    outputFile.retinaScaleFactor = 0;

    if (pledge("stdio cpath rpath wpath", NULL) == -1) {
        err(EXIT_FAILURE, "pledge");
    }

    while ((getoptFlag = getopt(argc, argv, "b:c:ef:him:o:rR:sv")) != -1) {
        switch(getoptFlag) {
        case 'b':
            // convert numeric command line flags to integer values
            outputFile.bits = strtonum(optarg, 8, 9, &errstr);

            if (errstr) {
                fprintf(stderr, "\nInvalid value for bits (must be 8 or 9).\n\n");
                return EXIT_FAILURE;
            }

            break;
        case 'c':
            // convert numeric command line flags to integer values
            inputFile.columns = strtonum(optarg, 1, 8192, &errstr);

            if (errstr) {
                fprintf(stderr, "\nInvalid value for columns (must range from 1 to 8192).\n\n");
                return EXIT_FAILURE;
            }

            break;
        case 'e':
            listExamples();
            return EXIT_SUCCESS;
        case 'f':
            outputFile.font = optarg;
            break;
        case 'h':
            showHelp();
            return EXIT_SUCCESS;
        case 'i':
            outputFile.icecolors = true;
            break;
        case 'm':
            outputFile.mode = optarg;
            break;
        case 'o':
            output = optarg;
            break;
        case 'r':
            outputFile.retinaScaleFactor = 2;
            break;
        case 'R':
            // convert numeric command line flags to integer values
            outputFile.retinaScaleFactor = strtonum(optarg, 2, 8, &errstr);

            if (errstr) {
                fprintf(stderr, "\nInvalid value for retina scale factor (must range from 2 to 8).\n\n");
                return EXIT_FAILURE;
            }

            break;
        case 's':
            justDisplaySAUCE = true;
            break;
        case 'v':
            versionInfo();
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

    // let's check the file for a valid SAUCE record
    sauce *record = sauceReadFileName(input);

    // record == NULL also means there is no file, we can stop here
    if (record == NULL) {
        fprintf(stderr, "\nFile %s not found.\n\n", input);
        return EXIT_FAILURE;
    } else {
        // if we find a SAUCE record, update bool flag
        if (!strcmp(record->ID, SAUCE_ID)) {
            fileHasSAUCE = true;
        }
    }

    if (!justDisplaySAUCE) {
        // create output file name if output is not specified
        char *outputName;

        if (!output) {
            outputName = input;
            // appending ".png" extension to output file name
            asprintf(&outputFile.fileName, "%s%s", outputName, ".png");
        }
        else {
            outputName = output;
            outputFile.fileName = outputName;
        }

        if (outputFile.retinaScaleFactor) {
            asprintf(&outputFile.retina, "%s@%ix.png", outputFile.fileName, outputFile.retinaScaleFactor);
        }

        // default to empty string if mode option is not specified
        if (!outputFile.mode) {
            outputFile.mode = "";
        }

        // default to 80x25 font if font option is not specified
        if (!outputFile.font) {
            outputFile.font = "80x25";
        }

        // display name of input and output files
        fprintf(stderr, "\nInput File: %s\n", input);
        fprintf(stderr, "Output File: %s\n", outputFile.fileName);

        if (outputFile.retinaScaleFactor) {
            fprintf(stderr, "Retina Output File: %s\n", outputFile.retina);
        }

        // get file extension
        char *fext = strrchr(input, '.');
        fext = fext ? strtolower(strdup(fext)) : "";
        inputFile.fext = fext;

        // load input file
        FILE *input_file = fopen(input, "r");
        if (input_file == NULL) {
            perror("File error");
            return 1;
        }

        // get the file size (bytes)
        struct stat input_file_stat;

        if (fstat(fileno(input_file), &input_file_stat)) {
            perror("Can't stat file");
            return 1;
        }

        inputFile.size=input_file_stat.st_size;

        // next up is loading our file into a dynamically allocated memory buffer

        // allocate memory to contain the whole file
        inputFile.data = (unsigned char *) malloc(sizeof(unsigned char)*inputFile.size + 1);
        if (inputFile.data == NULL) {
            perror("Memory error");
            return 2;
        }

        // copy the file into the buffer
        if (fread(inputFile.data, 1, inputFile.size, input_file) != inputFile.size) {
            perror("Reading error haha");
            return 3;
        } // whole file is now loaded into inputFileBuffer

        inputFile.data[inputFile.size] = '\0';

        // adjust the file size if file contains a SAUCE record
        if(fileHasSAUCE) {
            sauce *saucerec = sauceReadFile(input_file);
            inputFile.size -= 129 - ( saucerec->comments > 0 ? 5 + 64 * saucerec->comments : 0);
        }

        // close input file, we don't need it anymore
        fclose(input_file);

        // create the output file by invoking the appropiate function
        if (!strcmp(fext, ".pcb")) {
            // params: input, output, font, bits, icecolors
            pcboard(&inputFile, &outputFile);
            fileIsPCBoard = true;
        } else if (!strcmp(fext, ".bin")) {
            // params: input, output, columns, font, bits, icecolors
            binary(&inputFile, &outputFile);
            fileIsBinary = true;
        } else if (!strcmp(fext, ".adf")) {
            // params: input, output, bits
            artworx(&inputFile, &outputFile);
        } else if (!strcmp(fext, ".idf")) {
            // params: input, output, bits
            icedraw(&inputFile, &outputFile);
        } else if (!strcmp(fext, ".tnd")) {
            tundra(&inputFile, &outputFile);
            fileIsTundra = true;
        } else if (!strcmp(fext, ".xb")) {
            // params: input, output, bits
            xbin(&inputFile, &outputFile);
        } else {
            // params: input, output, font, bits, icecolors, fext
            ansi(&inputFile, &outputFile);
            fileIsANSi = true;
        }

        // gather information and report to the command line
        if (fileIsANSi || fileIsBinary ||
            fileIsPCBoard || fileIsTundra) {
            fprintf(stderr, "Font: %s\n", outputFile.font);
            fprintf(stderr, "Bits: %d\n", outputFile.bits);
        }
        if (outputFile.icecolors && (fileIsANSi || fileIsBinary)) {
            fprintf(stderr, "iCE Colors: enabled\n");
        }
        if (fileIsBinary) {
            fprintf(stderr, "Columns: %d\n", inputFile.columns);
        }
    }

    // either display SAUCE or tell us if there is no record
    if (!fileHasSAUCE) {
        fprintf(stderr, "\nFile %s does not have a SAUCE record.\n", input);
    } else {
        fprintf(stderr, "\nId: %s v%s\n", record->ID, record->version);
        fprintf(stderr, "Title: %s\n", record->title );
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
        if (record->comments > 0) {
            fprintf(stderr, "Comments: ");
            for (int32_t i = 0; i < record->comments; i++) {
                fprintf(stderr, "%s\n", record->comment_lines[i] );
            }
        }
    }

    return EXIT_SUCCESS;
}

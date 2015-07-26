//
//  main.c
//  AnsiLove/C
//
//  Copyright (C) 2011-2015 Stefan Vogt, Brian Cassidy, Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 3-Clause License.
//  See the file LICENSE for details.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>
#include "alconfig.h"
#include "strtolower.h"
#include "substr.h"
#include "ansilove.h"

// prototypes
void showHelp(void);
void listExamples(void);
void versionInfo(void);
void synopsis(void);

void showHelp(void)
{
    printf("\nSUPPORTED FILE TYPES:\n"
           "  ANS  BIN  ADF  IDF  XB  PCB  TND  ASC  NFO  DIZ\n"
           "  Files with custom suffix default to the ANSi renderer.\n\n"
           "OPERANDS:\n"
           "  Optional values to adjust output. There are certain cases where you need to\n"
           "  set operands for proper rendering. However, this is occassionally. Results\n"
           "  turn out well with the built-in defaults. You may launch AnsiLove with the\n"
           "  option -e to get a list of basic examples, with and without operands. Note\n"
           "  that columns is restricted to BIN files, it won't affect other file types.\n\n"
           "DOCUMENTATION:\n"
           "  Detailed help is available at the AnsiLove/C repository on GitHub.\n"
           "  <https://github.com/ansilove/AnsiLove-C>\n\n");
}

void listExamples(void)
{
    printf("\nEXAMPLES:\n"); 
    printf("  ansilove file.ans -i (output path/name identical to input, no operands)\n"
           "  ansilove file.ans -ir (same as -i, adds Retina @2x output file)\n"
           "  ansilove file.ans -o dir/file (custom path/name for output, no operands)\n"
           "  ansilove file.ans -or dir/file (same as -o, adds Retina @2x output file)\n"
           "  ansilove file.bin -s (just display SAUCE record, don't generate output)\n"
           "  ansilove file.bin -i terminus 8 1 202 (set font, bits, icecolors, columns)\n"
           "  ansilove file.ans -o dir/file terminus 8 1 (custom font, bits, icecolors)\n"
           "  ansilove file.ans -or dir/file 80x25 8 1 (DOS font, bits, iCE, Retina)\n\n"
           "HINT:\n"
           "  Don't add .png suffix when specifying a custom path/name for output as it\n"
           "  will be added automatically.\n\n");
}

void versionInfo(void)
{
    printf("All rights reserved.\n"
           "\nFork me on GitHub: <https://github.com/ansilove/AnsiLove-C>\n"
           "Bug reports: <https://github.com/ansilove/AnsiLove-C/issues>\n\n"
           "This is free software, released under the 3-Clause BSD license.\n"
           "<https://github.com/ansilove/AnsiLove-C/blob/master/LICENSE>\n\n"
           "LibGD is copyright (C) Thomas Boutell, Pierre-Alain Joye and contributors.\n"
           "<https://bitbucket.org/pierrejoye/gd-libgd>\n\n");
}

// following the IEEE Std 1003.1 for utility conventions
void synopsis(void)
{
    printf("\nSYNOPSIS:\n"
           "  ansilove input -i [operands]\n"
           "  ansilove input -ir [operands]\n"
           "  ansilove input -o output [operands]\n"
           "  ansilove input -or output [operands]\n"
           "  ansilove input -s\n"
           "  ansilove -vhe\n\n"
           "OPTIONS:\n"
           "  -i   output identical to input with .png suffix added\n"
           "  -ir  same as -i, creates additional Retina @2x output file\n"
           "  -o   specify custom file name/path for output\n"
           "  -or  same as -o, creates additional Retina @2x output file\n"
           "  -s   display SAUCE record without generating output\n"
           "  -v   version information, equivalent to --version\n"
           "  -h   show help, equivalent to --help\n"
           "  -e   print a list of examples\n\n"
           "OPERANDS:\n"
           "  font bits icecolors columns\n\n");
}

int main(int argc, char *argv[])
{
    printf("AnsiLove/C %s - ANSi / ASCII art to PNG converter\n"\
           "Copyright (C) 2011-2015 Stefan Vogt, Brian Cassidy, Frederic Cambus.\n", VERSION);
    
    // SAUCE record related bool types
    bool justDisplaySAUCE = false;
    bool fileHasSAUCE = false;
    
    // retina output bool type
    bool createRetinaRep = false;
    
    // analyze options and do what has to be done
    bool outputIdentical = false;
    bool fileIsBinary = false;
    bool fileIsANSi = false;
    bool fileIsPCBoard = false;
    bool fileIsTundra = false;
    
    if (argc == 1 || argc >= 9) {
        synopsis();
        return EXIT_SUCCESS;
    }

    int getoptFlag;
    char *bits = NULL;
    char *columns = NULL;
    char *font = NULL;
    char *icecolors = NULL;

    char *input = NULL, *output = NULL;
    char *retinaout = NULL;

    while ((getoptFlag = getopt(argc, argv, "b:c:ef:hi:o:rsv")) != -1) {
        switch(getoptFlag) {
        case 'b':
            bits = optarg;
            break;
        case 'c':
            columns = optarg;
            break;
        case 'e':
            listExamples();
            return EXIT_SUCCESS;
        case 'f':
            font = optarg;
            break;
        case 'h':
            showHelp();
            return EXIT_SUCCESS;
        case 'i':
            input = optarg;
            break;
        case 'o':
            output = optarg;
            break;
        case 'r':
            createRetinaRep = true;
            break;
        case 's':
            justDisplaySAUCE = true;
            break;
        case 'v':
            versionInfo();
            return EXIT_SUCCESS;
        }
    }

    argc -= optind; 
    argv += optind;

    // create output file name if output is not specified
    if (!output) {        
        int outputLen = strlen(input) + 5;
        output = malloc(outputLen);
        snprintf(output, outputLen, "%s%s", input, ".png");
    }

    // get file extension
    char *fext = strrchr(input, '.');
    fext = fext ? strtolower(fext) : "none";

    // create the output file by invoking the appropiate function
    if (strcmp(fext, ".pcb") == 0) {
        // params: input, output, font, bits, icecolors
        alPcBoardLoader(input, output, retinaout, font, bits, createRetinaRep);
        fileIsPCBoard = true;
    }
    else if (strcmp(fext, ".bin") == 0) {
        // params: input, output, columns, font, bits, icecolors
        alBinaryLoader(input, output, retinaout, columns, font, bits, icecolors, createRetinaRep);
        fileIsBinary = true;
    }
    else if (strcmp(fext, ".adf") == 0) {
        // params: input, output, bits
        alArtworxLoader(input, output, retinaout, bits, createRetinaRep);
    }
    else if (strcmp(fext, ".idf") == 0) {
        // params: input, output, bits
        alIcedrawLoader(input, output, retinaout, bits, fileHasSAUCE, createRetinaRep);
    }
    else if (strcmp(fext, ".tnd") == 0) {
        alTundraLoader(input, output, retinaout, font, bits, fileHasSAUCE, createRetinaRep);
        fileIsTundra = true;
    }
    else if (strcmp(fext, ".xb") == 0) {
        // params: input, output, bits
        alXbinLoader(input, output, retinaout, bits, createRetinaRep);
    }
    else {
        // params: input, output, font, bits, icecolors, fext
        //alAnsiLoader(input, output, retinaout, font, bits, icecolors, fext, createRetinaRep);
        alAnsiLoader(input, output, retinaout, "80x25", "9", "1", fext, createRetinaRep);
        fileIsANSi = true;
    }

    return EXIT_SUCCESS;
}

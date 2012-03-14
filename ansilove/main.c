//
//  main.c
//  AnsiLove/C
//
//  Copyright (C) 2011-2012 Stefan Vogt, Brian Cassidy, Frederic Cambus.
//  All rights reserved.
//  https://github.com/ByteProject/AnsiLove-C/
//
//  Use of this source code is governed by a MIT-style license.
//  See the file LICENSE for details.
//

#if defined(__APPLE__) && defined(__MACH__)
#import <Foundation/Foundation.h>
#import "alconfig.h"
#import "strtolower.h"
#import "substr.h"
#import "ansilove.h"
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "alconfig.h"
#include "strtolower.h"
#include "substr.h"
#include "ansilove.h"
#endif

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
           "  <https://github.com/ByteProject/AnsiLove-C/>\n\n");
}

void listExamples(void)
{
    printf("\nEXAMPLES:\n"); 
    printf("  ansilove file.ans -i (output identical input with .png suffix, no operands)\n"
           "  ansilove file.ans -o foo/out.png (custom path for output, no operands)\n"
           "  ansilove file.bin -s (just display SAUCE record, don't generate output)\n"
           "  ansilove file.bin -i terminus 8 1 202 (set font, bits, icecolors, columns)\n"
           "  ansilove file.ans -o out.png terminus 8 1 (custom font, bits, icecolors)\n\n");
}

void versionInfo(void)
{
    printf("All rights reserved.\n"
           "\nFork me on GitHub: <https://github.com/ByteProject/AnsiLove-C/>\n"
           "Bug reports: <https://github.com/ByteProject/AnsiLove-C/issues/>\n\n"
           "This is free software, released under a MIT-style license.\n"
           "<https://github.com/ByteProject/AnsiLove-C/blob/master/LICENSE>\n\n"
           "LibGD is copyright (C) Thomas Boutell, Pierre-Alain Joye and contributors.\n"
           "<https://bitbucket.org/pierrejoye/gd-libgd/>\n\n");
}

// following the IEEE Std 1003.1 for utility conventions
void synopsis(void)
{
    printf("\nSYNOPSIS:\n"
           "  ansilove file -i [operands]\n"
           "  ansilove file -o file.png [operands]\n"
           "  ansilove file -s\n"
           "  ansilove -vhe\n\n"
           "OPTIONS:\n"
           "  -i  output identical to input with .png suffix added\n"
           "  -o  specify custom file name / path for output\n"
           "  -s  display SAUCE record without generating output\n"
           "  -v  version information, equivalent to --version\n"
           "  -h  show help, equivalent to --help\n"
           "  -e  print a list of examples\n\n"
           "OPERANDS:\n"
           "  font bits icecolors columns\n\n");
}

int main(int argc, char *argv[])
{
    printf("AnsiLove/C %s - ANSi / ASCII art to PNG converter\n"\
           "Copyright (C) 2011-2012 Stefan Vogt, Brian Cassidy, Frederic Cambus.\n", VERSION);
    
    // SAUCE record related bool types
    bool justDisplaySAUCE = false;
    bool fileHasSAUCE = false;
    
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
    if ((strcmp(argv[1], "-v") == 0) || (strcmp(argv[1], "--version") == 0)) {
        versionInfo();
        return EXIT_SUCCESS;
    }
    if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)) {
        showHelp();
        return EXIT_SUCCESS;
    }
    if (strcmp(argv[1], "-e") == 0) {
        listExamples();
        return EXIT_SUCCESS;
    }
    if ((argv[2] && (strcmp(argv[2], "-s") == 0)) ||
        (argv[2] && (strcmp(argv[2], "-i") == 0)) ||
        (argv[2] && (strcmp(argv[2], "-o") == 0))) 
    {
        if (strcmp(argv[2], "-s") == 0) {
            justDisplaySAUCE = true;
        }
        
        // let's check the file for a valid SAUCE record
        sauce *record = sauceReadFileName(argv[1]);
        
        // record == NULL also means there is no file, we can stop here
        if (record == NULL) {
            printf("\nFile %s not found.\n\n", argv[1]);
            return EXIT_FAILURE;
        }
        else {
            // if we find a SAUCE record, update bool flag
            if (strcmp(record->ID, SAUCE_ID) == 0) {
                fileHasSAUCE = true;
            }
        }
        
        // this should be self-explanatory
        if (justDisplaySAUCE == false) 
        {
            // declaration of types we pass to ansilove.c
            char *input = argv[1];
            char output[1000] = { 0 };
            char columns[1000] = { 0 };
            char font[1000] = { 0 };
            char bits[1000] = { 0 };
            char icecolors[1000] = { 0 };
            char *fext;
            
            // find last position of char '.' so we can determine the file extension
            size_t index = strrchr(input, '.') - input;
            
            // calculate size of the input string
            size_t inpSize = strlen(input);
            
            // generate size_t result we can pass to our substr() implementation
            size_t result = inpSize - index;
            
            // finally create the file extension string
            fext = substr(input, inpSize - result, result);
            fext = strtolower(fext);
            if (fext == NULL) {
                fext = "none";
            }
            
            // in case we got arguments for input and the '-i' flag is set
            if (strcmp(argv[2], "-i") == 0) {
                // append .png suffix to file name
                sprintf(output, "%s.png", input);
                outputIdentical = true;
            }
            
            if ((strcmp(argv[2], "-o") == 0) && argv[3]) {
                // so the user provided an alternate path / file name
                sprintf(output, "%s", argv[3]);
            }
        
            if ((strcmp(argv[2], "-o") == 0) && !argv[3]) {
                // arrr... matey! setting the option -o without output file argument, eh?
                printf("\nOption -o is invalid without output file argument.\n\n");
                return EXIT_FAILURE;
            }
            
            // check for operands and apply them based on the file extension
            if ((strcmp(fext, ".bin") == 0) && outputIdentical == true)
            {
                // set binary bool value
                fileIsBinary = true;
                
                // font
                if (argc >= 4) {
                    sprintf(font, "%s", argv[3]);
                }
                else {
                    sprintf(font, "%s", "80x25");
                }
                // bits
                if (argc >= 5) {
                    sprintf(bits, "%s", argv[4]);
                }
                else {
                    sprintf(bits, "%s", "8");
                    
                }
                // iCE colors
                if (argc >= 6) {
                    sprintf(icecolors, "%s", argv[5]);
                }
                else {
                    sprintf(icecolors, "%s", "0");
                }
                // columns
                if (argc >= 7) {
                    sprintf(columns, "%s", argv[6]);
                }
                else {
                    sprintf(columns, "%s", "160");
                }
            }
            else if ((strcmp(fext, ".bin") == 0) && outputIdentical == false)
            {
                // font
                if (argc >= 5) {
                    sprintf(font, "%s", argv[4]);
                }
                else {
                    sprintf(font, "%s", "80x25");
                }
                // bits
                if (argc >= 6) {
                    sprintf(bits, "%s", argv[5]);
                }
                else {
                    sprintf(bits, "%s", "8");
                    
                }
                // iCE colors
                if (argc >= 7) {
                    sprintf(icecolors, "%s", argv[6]);
                }
                else {
                    sprintf(icecolors, "%s", "0");
                }
                // columns
                if (argc >= 8) {
                    sprintf(columns, "%s", argv[7]);
                }
                else {
                    sprintf(columns, "%s", "160");
                }
            }
            else {
                if (outputIdentical == true) {
                    // font
                    if (argc >= 4) {
                        sprintf(font, "%s", argv[3]);
                    }
                    else {
                        sprintf(font, "%s", "80x25");
                    }
                    // bits
                    if (argc >= 5) {
                        sprintf(bits, "%s", argv[4]);
                    }
                    else {
                        sprintf(bits, "%s", "8");
                    }
                    // iCE colors
                    if (argc >= 6) {
                        sprintf(icecolors, "%s", argv[5]);
                    }
                    else {
                        sprintf(icecolors, "%s", "0");
                    }
                }
                else {
                    // font
                    if (argc >= 5) {
                        sprintf(font, "%s", argv[4]);
                    }
                    else {
                        sprintf(font, "%s", "80x25");
                    }
                    // bits
                    if (argc >= 6) {
                        sprintf(bits, "%s", argv[5]);
                    }
                    else {
                        sprintf(bits, "%s", "8");
                    }
                    // iCE colors
                    if (argc >= 7) {
                        sprintf(icecolors, "%s", argv[6]);
                    }
                    else {
                        sprintf(icecolors, "%s", "0");
                    }
                }
            }
            
            // create the output file by invoking the appropiate function
            if (strcmp(fext, ".pcb") == 0) {
                // params: input, output, font, bits, icecolors
                alPcBoardLoader(input, output, font, bits);
                fileIsPCBoard = true;
            }
            else if (strcmp(fext, ".bin") == 0) {
                // params: input, output, columns, font, bits, icecolors
                alBinaryLoader(input, output, columns, font, bits, icecolors);
                fileIsBinary = true;
            }
            else if (strcmp(fext, ".adf") == 0) {
                // params: input, output, bits
                alArtworxLoader(input, output, bits);
            }
            else if (strcmp(fext, ".idf") == 0) {
                // params: input, output, bits
                alIcedrawLoader(input, output, bits, fileHasSAUCE);
            }
            else if (strcmp(fext, ".tnd") == 0) {
                alTundraLoader(input, output, font, bits);
                fileIsTundra = true;
            }
            else if (strcmp(fext, ".xb") == 0) {
                // params: input, output, bits
                alXbinLoader(input, output, bits);
            }
            else {
                // params: input, output, font, bits, icecolors, fext
                alAnsiLoader(input, output, font, bits, icecolors, fext);
                fileIsANSi = true;
            }
            
            // gather information and report to the command line
            printf("\nInput File: %s\n", input);
            printf("Output File: %s\n", output);
            if (fileIsANSi == true || fileIsBinary == true || 
                fileIsPCBoard == true || fileIsTundra == true) {
                printf("Font: %s\n", font);
            }
            if (fileIsANSi == true || fileIsBinary == true || 
                fileIsPCBoard == true || fileIsTundra == true) {
                printf("Bits: %s\n", bits);
            }
            if (fileIsANSi == true || fileIsBinary == true || fileIsPCBoard == true) {
                printf("iCE Colors: %s\n", icecolors);
            }
            if (fileIsBinary == true) {
                printf("Columns: %s\n", columns);
            }
        }
        
        // either display SAUCE or tell us if there is no record
        if (fileHasSAUCE == false) {
            printf("\nFile %s does not have a SAUCE record.\n", argv[1]);
        }
        else {
            printf( "\n%s: %s v%s\n", "Id", record->ID, record->version);
            printf( "%s: %s\n", "Title", record->title );
            printf( "%s: %s\n", "Author", record->author);
            printf( "%s: %s\n", "Group", record->group);
            printf( "%s: %s\n", "Date", record->date);
            printf( "%s: %d\n", "Datatype", record->dataType);
            printf( "%s: %d\n", "Filetype", record->fileType);
            if (record->flags != 0) {
                printf( "%s: %d\n", "Flags", record->flags);
            }
            if (record->tinfo1 != 0) {
                printf( "%s: %d\n", "Tinfo1", record->tinfo1);
            }
            if (record->tinfo2 != 0) {
                printf( "%s: %d\n", "Tinfo2", record->tinfo2);
            }
            if (record->tinfo3 != 0) {
                printf( "%s: %d\n", "Tinfo3", record->tinfo3);
            }
            if (record->tinfo4 != 0) {
                printf( "%s: %d\n", "Tinfo4", record->tinfo4);
            }
            if (record->comments > 0) {
                int32_t i;
                printf( "Comments: ");
                for(i = 0; i < record->comments; i++) {
                    printf( "%s\n", record->comment_lines[i] );
                }
            }
        }
        
        // post a message when the output file is created (in case we created output)
        if (justDisplaySAUCE == false) {
            printf("\nSuccessfully created output file.\n\n");
        }
        else {
            printf("\n");
        }
    }
    else {
        // in any other case the synopsis will be just fine
        synopsis();
        return EXIT_SUCCESS;
    }
    return EXIT_SUCCESS;
}

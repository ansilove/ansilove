//
//  main.m
//  AnsiLove/C
//
//  Copyright (c) 2011, Stefan Vogt. All rights reserved.
//  http://byteproject.net
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
#include <stdbool.h>
#include "alconfig.h"
#include "strtolower.h"
#include "substr.h"
#include "ansilove.h"
#endif

// prototypes
void showUsage(void);
void loadPCBoard(void);
void loadArtworx(void);
void loadIceDraw(void);
void loadTundra(void);
void loadXbin(void);

// show how to properly set the command line flags
void showUsage(void)
{
    printf("USAGE:\n");    
    printf("ansilove <inputfile> <outputfile> columns (.BIN only) font bits icecolors\n\n");
    printf("Check the README to have details about supported options for each\n");
    printf("file format. Use flag '-s' for 'outputfile' to write a file to the same\n");
    printf("path, with the same name and .png suffix appended. Use '-r' for 'outputfile'\n");
    printf("to just read and display a SAUCE record, without generating output\n\n");
    printf("EXAMPLES:\n"); 
    printf("ansilove ansi.ans ansi.png\n");
    printf("ansilove ansi.ans ansi.png 80x25 9 1 (80x25 font, 9-bit, iCE colors)\n");
    printf("ansilove ansi.ans -s 80x25 (80x25 font)\n");
    printf("ansilove ansi.ans ansi.png 80x50 9 (80x50 font, 9-bit)\n");
    printf("ansilove ansi.ans -s russian 9 (Russian font, 9-bit)\n");
    printf("ansilove ansi.ans ansi.png amiga (Amiga font)\n");
    printf("ansilove pcboard.pcb pcboard.png\n");
    printf("ansilove pcboard.pcb pcboard.png 80x25 9 (80x25 font, 9-bit)\n");
    printf("ansilove binary.bin -s 160\n");
    printf("ansilove binary.bin binary.png 160 80x25 9 1 (80x25 font, 9-bit, iCE colors)\n");
    printf("ansilove binary.bin binary.png 160 80x50 9 (80x50 font, 9-bit)\n");
    printf("ansilove tundra.tnd tundra.png\n");
    printf("ansilove tundra.tnd -s 80x25 9 (80x25 font, 9-bit)\n");
    printf("ansilove xbin.xb xbin.png\n");
    printf("ansilove ansiwithsauce.ans -r (just display SAUCE record)\n\n");
}

void loadPCBoard(void)
{
    // params: input, output, font, bits, icecolors
}

void loadIceDraw(void)
{
    // params: input, output, bits
}

void loadTundra(void)
{
    // params: input, output, font, bits
}

void loadXbin(void)
{
    // params: input, output, bits
}

int main(int argc, char *argv[])
{
    printf("\n---------------------------------------------------------------------------\n");
    printf("AnsiLove/C %s - copyright (C) 2011 Stefan Vogt\n", VERSION);
    printf("---------------------------------------------------------------------------\n");
    
    // we do this before anything else
    if (argc <= 2) {
        showUsage();
        return EXIT_SUCCESS;
    }
    
    // indicates whether AnsiLove/C should just display SAUCE or not
    bool justDisplaySAUCE = false;
    
    // in case the SAUCE flag is set we set our bool type to 'true'
    if (strcmp(argv[2], "-r") == 0) {
        justDisplaySAUCE = true;
    }
    
    // let's check the file for a valid SAUCE record
    sauce *record = sauceReadFileName(argv[1]);
    
    // record == NULL means there is no file, we can stop here
    if (record == NULL) {
        printf("\nFile %s not found.\n\n", argv[1]);
        return EXIT_FAILURE;
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
        int64_t index = strrchr(input, '.') - input;
        
        // calculate size of the input string
        int64_t inpSize = strlen(input);
        
        // generate size_t result we can pass to our substr() implementation
        size_t result = inpSize - index;
        
        // finally create the file extension string
        fext = substr(input, inpSize - result, result);
        fext = strtolower(fext);
        if (fext == NULL) {
            fext = "none";
        }
        
        // in case we got arguments for input, output and the '-s' flag is set
        if (strcmp(argv[2], "-s") == 0) 
        {
            // append .png suffix to file name
            sprintf(output, "%s.png", input);
        }
        else {
            // so the user provided an alternate path / file name
            sprintf(output, "%s", argv[2]);
        }
        
        // check flags and apply them based on the file extension
        if (strcmp(fext, ".bin") == 0)
        {
            // columns
            if (argc >= 4) {
                sprintf(columns, "%s", argv[3]);
            }
            else {
                sprintf(columns, "%s", "160");
            }        
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
        else {
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
        
        // report all flags to the command line
        printf("\nInput File: %s\n", input);
        printf("Output File: %s\n", output);
        printf("Columns (.BIN only): %s\n", columns);
        printf("Font (.ANS/.BIN only): %s\n", font);
        printf("Bits (.ANS/.BIN only): %s\n", bits);
        printf("iCE Colors (.ANS/.BIN only): %s\n", icecolors);
        
        // create the output file by invoking the appropiate function
        if (strcmp(fext, ".pcb") == 0) {
            loadPCBoard();
        }
        else if (strcmp(fext, ".bin") == 0) {
            // params: input, output, columns, font, bits, icecolors
            alBinaryLoader(input, output, columns, font, bits, icecolors);
        }
        else if (strcmp(fext, ".adf") == 0) {
            // params: input, output, bits
            alArtworxLoader(input, output, bits);
        }
        else if (strcmp(fext, ".idf") == 0) {
            loadIceDraw();
        }
        else if (strcmp(fext, ".tnd") == 0) {
            loadTundra();
        }
        else if (strcmp(fext, ".xb") == 0) {
            loadXbin();
        }
        else {
            // params: input, output, font, bits, icecolors, fext
            alAnsiLoader(input, output, font, bits, icecolors, fext);
        }
    }
    
    // either display SAUCE or tell us if there is no record
    if (strcmp( record->ID, SAUCE_ID ) != 0) {
        printf("\nFile does not have a SAUCE record.\n");
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
            int64_t i;
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
    
    return EXIT_SUCCESS;
}

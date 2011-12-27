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
#include "alconfig.h"
#include "strtolower.h"
#include "substr.h"
#include "ansilove.h"
#endif

// prototypes
void showUsage(void);
void loadPCBoard(void);
void loadBinary(void);
void loadArtworx(void);
void loadIceDraw(void);
void loadTundra(void);
void loadXbin(void);
void loadAnsi(void);

// show how to properly set the command line flags
void showUsage(void)
{
    printf("USAGE:\n");    
    printf("ansilove inputfile outputfile columns (.BIN only) font bits icecolors\n\n");
    printf("Check the README to have details about supported options for each\n");
    printf("file format. Use flag '-s' for 'outputfile' to write a file to the same\n");
    printf("path, with the same name and .png suffix appended.\n\n");
    printf("EXAMPLES:\n"); 
    printf("ansilove ansi.ans ansi.png\n");
    printf("ansilove ansi.ans ansi.png 80x25 9 1 (80x25 font, 9-bit, iCE colors)\n");
    printf("ansilove ansi.ans -s 80x25 thumbnail (80x25 font, thumbnail rendering)\n");
    printf("ansilove ansi.ans ansi.png 80x50 9 (80x50 font, 9-bit)\n");
    printf("ansilove ansi.ans -s russian 9 (Russian font, 9-bit)\n");
    printf("ansilove ansi.ans ansi.png amiga (Amiga font)\n");
    printf("ansilove pcboard.pcb pcboard.png\n");
    printf("ansilove pcboard.pcb pcboard.png 80x25 9 (80x25 font, 9-bit)\n");
    printf("ansilove binary.bin -s 160\n");
    printf("ansilove binary.bin binary.png 160 80x25 9 1 (80x25 font, 9-bit, iCE colors)\n");
    printf("ansilove binary.bin binary.png 160 80x50 9 (80x50 font, 9-bit)\n");
    printf("ansilove adf.adf adf.png\n");
    printf("ansilove idf.idf idf.png\n");
    printf("ansilove tundra.tnd tundra.png\n");
    printf("ansilove tundra.tnd -s 80x25 9 (80x25 font, 9-bit)\n");
    printf("ansilove xbin.xb xbin.png\n\n");
}

void loadPCBoard(void)
{
    // params: input, output, font, bits, icecolors
}

void loadBinary(void)
{
    // params: input, output, columns, font, bits, icecolors
}

void loadArtworx(void)
{
    // params: input, output, bits
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

void loadAnsi(void)
{
    // params: input, output, font, bits, icecolors
}

int main(int argc, char *argv[])
{
    printf("\n---------------------------------------------------------------------------\n");
    printf("AnsiLove/C %s - copyright (C) 2011 Stefan Vogt\n", VERSION);
    printf("---------------------------------------------------------------------------\n\n");
    
    // we do this before anything else
    if (argc <=2) {
        showUsage();
        return EXIT_SUCCESS;
    }
    
    // declarations
    char *input = argv[1];
    char output[1000] = { 0 };
    char columns[1000] = { 0 };
    char font[1000] = { 0 };
    char bits[1000] = { 0 };
    char icecolors[1000] = { 0 };
    char *fext;
        
    // find last position of char '.' so we can determine the file extension
    long index = strrchr(input, '.') - input;
    
    // calculate size of the input string
    long inpSize = strlen(input);
    
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
        // make file name lowercase and append .png suffix
        sprintf(output, "%s.png", strtolower(argv[1]));
    }
    else {
        // so the user provided an alternate path / file name
        sprintf(output, "%s", strtolower(argv[2]));
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
    
    // in case the thumbnail flag is set, append THUMBNAILS_TAG
    if (strcmp(bits, "thumbnail") == 0) {
        sprintf(output, "%s%s.png", strtolower(argv[1]), THUMBNAILS_TAG);
    }
    
    // report all flags to the command line
    printf("Input File: %s\n", input);
    printf("Output File: %s\n", output);
    printf("Columns (.BIN only): %s\n", columns);
    printf("Font (.ANS/.BIN only): %s\n", font);
    printf("Bits (.ANS/.BIN only): %s\n", bits);
    printf("iCE Colors (.ANS/.BIN only): %s\n\n", icecolors);
   
    // create the output file by invoking the appropiate function
    if (strcmp(fext, ".pcb") == 0) {
        loadPCBoard();
    }
    else if (strcmp(fext, ".bin") == 0) {
        loadBinary();
    }
    else if (strcmp(fext, ".adf") == 0) {
        loadArtworx();
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
        loadAnsi();
    }

// Displaying SAUCE is disabled until we're done with porting ansilove.c!
    
//    // display sauce informations
//    input_file_sauce=load_sauce(input);
//    
//    if (input_file_sauce != NULL)
//    {
//        printf("Title: input_file_sauce[Title]\n");
//        printf("Author: input_file_sauce[Author]\n");
//        printf("Group: input_file_sauce[Group]\n");
//        printf("Date: input_file_sauce[Date]\n");
//        printf("Comment: input_file_sauce[Comment]\n\n");
//    }
    
    // exit program
    printf("Successfully created output file\n\n");
    
    return EXIT_SUCCESS;
}

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
#else
#include <stdio.h>
#include <stdlib.h>
#include "alconfig.h"
#include "strtolower.h"
#include "substr.h"
#endif

// show usage                                                             
void showUsage(void)
{
    printf("USAGE:    ansilove inputfile columns (.BIN only) font bits icecolors\n\n");
    printf("          Check the README to have details about supported options for each\n");
    printf("          file format.\n\n");
    printf("EXAMPLES: ansilove ansi.ans\n");
    printf("          ansilove ansi.ans 80x25 9 (80x25 font, 9-bit)\n");
    printf("          ansilove ansi.ans 80x25 thumbnail (80x25 font, thumbnail rendering)\n");
    printf("          ansilove ansi.ans 80x50 9 (80x50 font, 9-bit)\n");
    printf("          ansilove ansi.ans russian 9 (Russian font, 9-bit)\n");
    printf("          ansilove ansi.ans amiga (Amiga font)\n");
    printf("          ansilove pcboard.pcb\n");
    printf("          ansilove pcboard.pcb 80x25 9 (80x25 font, 9-bit)\n");
    printf("          ansilove binary.bin 160\n");
    printf("          ansilove binary.bin 160 80x25 9 (80x25 font, 9-bit)\n");
    printf("          ansilove binary.bin 160 80x50 9 (80x50 font, 9-bit)\n");
    printf("          ansilove adf.adf\n");
    printf("          ansilove idf.idf\n");
    printf("          ansilove tundra.tnd\n");
    printf("          ansilove tundra.tnd 80x25 9 (80x25 font, 9-bit)\n");
    printf("          ansilove xbin.xb\n\n");
 
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    printf("--------------------------------------------------\n");
    printf("AnsiLove/C %s - copyright (C) 2011 Stefan Vogt\n", VERSION);
    printf("--------------------------------------------------\n\n");
    
    char columns[], font[], bits[], icecolors[];
    char input[] = argv[1];
    char output[];
    sprintf(output, "%s.png", argv[1]);

    // check input parameters
    char inputFileExtension[] = strtolower(substr(input, strlen(input)-4, 4));
    
    if (argc == 1) {
        showUsage();
    }
    
    if (inputFileExtension == '.bin')
    {
        if (argv[2]) {
            columns = argv[2];
        }
        if (argv[3]) {
            font = argv[3];
        }
        if (argv[4]) {
            bits = argv[4];
        }
        if (argv[5]) {
            icecolors = argv[5];
        }
    }
    else {
        if (argv[2]) {
            font = argv[2];
        }
        if (argv[3]) {
            bits = argv[3];
        }
        if (argv[3]) {
            icecolors = argv[4];
        }
    }
    
    if (strtolower(substr(input, strlen(input)-3, 3)) == '.xb') {
        inputFileExtension = '.xb';
    }
    
    if (bits == "thumbnail") {
        sprintf(output, "%s%s.png", argv[1], THUMBNAILS_TAG)
        bits = "thumbnail";
    }
    
    printf("Input File: %s\n", input);
    printf("Output File: %s\n", output);
    printf("Columns (.BIN only): %s\n", columns);
    printf("Font (.ANS/.BIN only): %s\n", font);
    printf("Bits (.ANS/.BIN only): %s\n", bits);
    printf("iCE Colors (.ANS/.BIN only): %s\n\n", icecolors);
    
    // create output file
    switch (inputFileExtension)
    {
        case '.pcb':
            load_pcboard(input,output,font,bits,icecolors);
            break;
            
        case '.bin':
            load_binary(input,output,columns,font,bits,icecolors);
            break;
            
        case '.adf':
            load_adf(input,output,bits);
            break;
            
        case '.idf':
            load_idf(input,output,bits);
            break;
            
        case '.tnd':
            load_tundra(input,output,font,bits);
            break;
            
        case '.xb':
            load_xbin(input,output,bits);
            break;
            
        default:
            load_ansi(input,output,font,bits,icecolors);
    }
    
    // display sauce informations
    input_file_sauce=load_sauce(input);
    
    if (input_file_sauce != NULL)
    {
        printf("Title: input_file_sauce[Title]\n");
        printf("Author: input_file_sauce[Author]\n");
        printf("Group: input_file_sauce[Group]\n");
        printf("Date: input_file_sauce[Date]\n");
        printf("Comment: input_file_sauce[Comment]\n\n");
    }
    
    // terminate program
    printf("Successfully created output file\n\n");
    
    return EXIT_SUCCESS;
}





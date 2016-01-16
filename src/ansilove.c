//
//  ansilove.c
//  AnsiLove/C
//
//  Copyright (C) 2011-2016 Stefan Vogt, Brian Cassidy, Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 3-Clause License.
//  See the file LICENSE for details.
//

#include "ansilove.h"

// shared method for drawing characters
void alDrawChar(gdImagePtr im, const unsigned char *font_data, int32_t int_bits, 
                int32_t font_size_y, int32_t position_x, int32_t position_y, 
                int32_t color_background, int32_t color_foreground, unsigned char character)
{
    int32_t column, line;

    gdImageFilledRectangle(im, position_x * int_bits, position_y*font_size_y, position_x * int_bits + 
                           int_bits - 1, position_y * font_size_y + font_size_y - 1, color_background);

    for (line = 0; line < font_size_y; line++) {
        for (column = 0; column < int_bits; column++) {

            if ((font_data[line+character*font_size_y] & (0x80 >> column)) != 0) {
                gdImageSetPixel(im, position_x * int_bits + column, position_y*font_size_y + line, color_foreground);
                
                if (int_bits==9 && column==7 && character > 191 && character < 224)
                {
                    gdImageSetPixel(im, position_x * int_bits + 8, position_y * font_size_y + line, color_foreground);                    
                }
                    
            }
        }
    }
}

// ANSi
void alAnsiLoader(char *input, char *output, char *retinaout, char *font, int32_t int_bits, char *mode, bool icecolors, char *fext, bool createRetinaRep)
{
    // ladies and gentlemen, it's type declaration time
    struct fontStruct fontData;

    int32_t columns = 80;
    
    bool isDizFile = false;
    bool ced = false;
    bool transparent = false;
    bool workbench = false;

    // font selection
    alSelectFont(&fontData, font);
        
    // to deal with the bits flag, we declared handy bool types   
    if (!strcmp(mode, "ced")) {
        ced = true;
    }
    else if (!strcmp(mode, "transparent")) {
        transparent = true;
    }
    else if (!strcmp(mode, "workbench")) {
        workbench = true;
    }
    else if (!strcmp(mode, "workbench-transparent")) {
        workbench = true;
        transparent = true;
    }
    
    // load input file
    FILE *input_file = fopen(input, "r");
    if (input_file == NULL) { 
        fputs("\nFile error.\n\n", stderr); exit (1);
    }
    
    // get the file size (bytes)
    size_t get_file_size = filesize(input);
    int32_t input_file_size = (int32_t)get_file_size;
    
    // next up is loading our file into a dynamically allocated memory buffer
    unsigned char *input_file_buffer;
    int32_t result;
    
    // allocate memory to contain the whole file
    input_file_buffer = (unsigned char *) malloc(sizeof(unsigned char)*input_file_size);
    if (input_file_buffer == NULL) {
        fputs ("\nMemory error.\n\n", stderr); exit (2);
    }
    
    // copy the file into the buffer
    result = fread(input_file_buffer, 1, input_file_size, input_file);
    if (result != input_file_size) {
        fputs ("\nReading error.\n\n", stderr); exit (3);
    } // whole file is now loaded into input_file_buffer
    
    // close input file, we don't need it anymore
    fclose(input_file);

    // check if current file has a .diz extension
    if (!strcmp(fext, ".diz")) {
        isDizFile = true;
    }

    // libgd image pointers
    gdImagePtr im_ANSi;

    // ANSi processing loops
    int32_t loop = 0, ansi_sequence_loop, seq_graphics_loop; 
    
    // character definitions
    int32_t current_character, next_character, character; 
    unsigned char ansi_sequence_character;
    
    // default color values
    int32_t color_background = 0, color_foreground = 7; 
    
    // text attributes
    bool bold = false, underline = false, italics = false, blink = false;
    
    // positions
    int32_t position_x = 0, position_y = 0, position_x_max = 0, position_y_max = 0;
    int32_t saved_position_y = 0, saved_position_x = 0;
    
    // sequence parsing variables
    int32_t seqValue, seqArrayCount, seq_line, seq_column;
    char *seqGrab;
    char **seqArray;
    
    // ANSi buffer structure array definition
    int32_t structIndex = 0;
    struct ansiChar *ansi_buffer, *temp;
    
    // ANSi buffer dynamic memory allocation
    ansi_buffer = malloc(sizeof(struct ansiChar));
    
    // background canvas
    int32_t background_canvas = 0;
    
    // ANSi interpreter
    while (loop < input_file_size)
    {
        current_character = input_file_buffer[loop];
        next_character = input_file_buffer[loop + 1];

        if (position_x==80 && !strcmp(WRAP_COLUMN_80, "1"))
        {
            position_y++;
            position_x=0;
        }
        
        // CR + LF
        if (current_character == 13 && next_character == 10) {
            position_y++;
            position_x = 0;
            loop++;
        }

        // LF
        if (current_character == 10)
        {
            position_y++;
            position_x = 0;
        }
        
        // tab
        if (current_character == 9)
        {
            position_x += 8;
        }
        
        // sub
        if (current_character == 26 && !strcmp(SUBSTITUTE_BREAK, "1"))
        {
            break;
        }
        
        // ANSi sequence
        if (current_character == 27 && next_character == 91)
        {            
            for (ansi_sequence_loop = 0; ansi_sequence_loop < 12; ansi_sequence_loop++)
            {
                ansi_sequence_character = input_file_buffer[loop + 2 + ansi_sequence_loop];
                
                // cursor position
                if (ansi_sequence_character == 'H' || ansi_sequence_character == 'f')
                {
                    // create substring from the sequence's content
                    seqGrab = substr((char *)input_file_buffer, loop+2, ansi_sequence_loop);
                    
                    // create sequence content array
                    seqArrayCount = explode(&seqArray, ';', seqGrab);
                    
                    if (seqArrayCount > 1) {
                        // convert grabbed sequence content to integers
                        seq_line = atoi(seqArray[0]);
                        seq_column = atoi(seqArray[1]);
                        
                        // finally set the positions
                        position_y = seq_line-1;
                        position_x = seq_column-1;
                    }
                    else {
                        // no coordinates specified? we move to the home position
                        position_y = 0;
                        position_x = 0;
                    }
                    loop+=ansi_sequence_loop+2;
                    break;
                }
                
                // cursor up
                if (ansi_sequence_character=='A')
                {
                    // create substring from the sequence's content
                    seqGrab = substr((char *)input_file_buffer, loop+2, ansi_sequence_loop);
                    
                    // now get escape sequence's position value
                    int32_t seq_line = atoi(seqGrab);
                    
                    if (seq_line == 0) {
                        seq_line = 1;
                    }
                    
                    position_y = position_y - seq_line;
                    
                    loop+=ansi_sequence_loop+2;
                    break;
                }
                
                // cursor down
                if (ansi_sequence_character=='B')
                {
                    // create substring from the sequence's content
                    seqGrab = substr((char *)input_file_buffer, loop+2, ansi_sequence_loop);
                    
                    // now get escape sequence's position value
                    int32_t seq_line = atoi(seqGrab);
                    
                    if (seq_line == 0) {
                        seq_line = 1;
                    }
                    
                    position_y = position_y + seq_line;
                     
                    loop+=ansi_sequence_loop+2;
                    break;
                }

                // cursor forward
                if (ansi_sequence_character=='C')
                {
                    // create substring from the sequence's content                    
                    seqGrab = substr((char *)input_file_buffer, loop+2, ansi_sequence_loop);

                    // now get escape sequence's position value
                    int32_t seq_column = atoi(seqGrab);
                    
                    if (seq_column == 0) {
                        seq_column = 1;
                    }
                    
                    position_x = position_x + seq_column;
                    
                    if (position_x>80)
                    {
                        position_x=80;
                    }
                    
                    loop+=ansi_sequence_loop+2;
                    break;
                }
                
                // cursor backward
                if (ansi_sequence_character=='D')
                {
                    // create substring from the sequence's content                    
                    seqGrab = substr((char *)input_file_buffer, loop+2, ansi_sequence_loop);

                    // now get escape sequence's content length
                    int32_t seq_column = atoi(seqGrab);
                    
                    if (seq_column == 0) {
                        seq_column = 1;
                    }
                    
                    position_x = position_x - seq_column;
                    
                    if (position_x < 0)
                    {
                        position_x = 0;
                    }
                    
                    loop+=ansi_sequence_loop+2;
                    break;
                }
                
                // save cursor position
                if (ansi_sequence_character=='s')
                {
                    saved_position_y = position_y;
                    saved_position_x = position_x;
                    
                    loop+=ansi_sequence_loop+2;
                    break;
                }
                
                // restore cursor position
                if (ansi_sequence_character=='u')
                {
                    position_y = saved_position_y;
                    position_x = saved_position_x;
                    
                    loop+=ansi_sequence_loop+2;
                    break;
                }
                
                // erase display
                if (ansi_sequence_character=='J')
                {
                    // create substring from the sequence's content                    
                    seqGrab = substr((char *)input_file_buffer, loop+2, ansi_sequence_loop);
                        
                    // convert grab to an integer
                    int32_t eraseDisplayInt = atoi(seqGrab);
                        
                    if (eraseDisplayInt == 2)
                    {    
                        position_x=0;
                        position_y=0;
                            
                        position_x_max=0;
                        position_y_max=0;
                        
                        // reset ansi buffer
                        free(ansi_buffer);
                        ansi_buffer = malloc(sizeof(struct ansiChar));
                        structIndex=0;
                    }
                    loop+=ansi_sequence_loop+2;
                    break;
                }
                
                // set graphics mode
                if (ansi_sequence_character=='m')
                {                    
                        // create substring from the sequence's content
                        seqGrab = substr((char *)input_file_buffer, loop+2, ansi_sequence_loop);
                        
                        // create sequence content array
                        seqArrayCount = explode(&seqArray, ';', seqGrab);
                        
                        // a loophole in limbo
                        for (seq_graphics_loop = 0; seq_graphics_loop < seqArrayCount; seq_graphics_loop++)
                        {
                            // convert split content value to integer
                            seqValue = atoi(seqArray[seq_graphics_loop]);
                            
                            if (seqValue == 0)
                            {
                                color_background = 0;
                                color_foreground = 7;
                                bold = false;
                                underline = false;
                                italics = false;
                                blink = false;
                            }
                            
                            if (seqValue == 1)
                            {
                                if (!workbench)
                                {
                                    color_foreground+=8;
                                }
                                bold = true;
                            }
                            
                            if (seqValue == 3)
                            {
                                italics = true;
                            }
                            
                            if (seqValue == 4)
                            {
                                underline = true;
                            }
                            
                            if (seqValue == 5)
                            {
                                if (!workbench)
                                {
                                    color_background+=8;
                                }
                                blink = true;
                            }
                            
                            if (seqValue > 29 && seqValue < 38)
                            {
                                color_foreground = seqValue - 30;
                                
                                if (bold)
                                {
                                    color_foreground+=8;
                                }
                            }
                            
                            if (seqValue > 39 && seqValue < 48)
                            {
                                color_background = seqValue - 40;
                                
                                if (blink && icecolors)
                                {
                                    color_background+=8;
                                }
                            }
                        }
                    
                    loop+=ansi_sequence_loop+2;
                    break;
                }
                
                // cursor (de)activation (Amiga ANSi)
                if (ansi_sequence_character == 'p')
                {
                    loop+=ansi_sequence_loop+2;
                    break;
                }

                // skipping set mode and reset mode sequences
                if (ansi_sequence_character == 'h' || ansi_sequence_character == 'l')
                {
                    loop+=ansi_sequence_loop+2;
                    break;
                }
            }
        }
        else if (current_character!=10 && current_character!=13 && current_character!=9)
        {
            // record number of columns and lines used
            if (position_x>position_x_max)
            {
                position_x_max=position_x;
            }
            
            if (position_y>position_y_max)
            {
                position_y_max=position_y;
            }
            
            // write current character in ansiChar structure 
            if (!fontData.isAmigaFont || (current_character != 12 && current_character != 13))
            {
                // reallocate structure array memory
                temp = realloc(ansi_buffer, (structIndex + 1) * sizeof(struct ansiChar));
                ansi_buffer = temp;
                
                ansi_buffer[structIndex].color_background = color_background;
                ansi_buffer[structIndex].color_foreground = color_foreground;
                ansi_buffer[structIndex].current_character = current_character;
                ansi_buffer[structIndex].bold = bold;
                ansi_buffer[structIndex].italics = italics;
                ansi_buffer[structIndex].underline = underline;
                ansi_buffer[structIndex].position_x = position_x;
                ansi_buffer[structIndex].position_y = position_y;
                                
                structIndex++;
                position_x++;
            }
        }
        loop++;
    }
    
    // allocate image buffer memory
    position_x_max++;
    position_y_max++;
    
    if (ced)
    {
        columns = 78;
    }
    
    if (isDizFile) {
        columns = fmin(position_x_max,80);
    }
        
    // create that damn thingy
    im_ANSi = gdImageCreate(columns * int_bits,(position_y_max)*fontData.font_size_y);
    
    if (!im_ANSi) {
        fputs ("\nCan't allocate ANSi buffer image memory.\n\n", stderr); exit (6);
    }
    
    int32_t colors[21];
    
    if (ced)
    {
        colors[0]=gdImageColorAllocate(im_ANSi, 170, 170, 170);

        for (loop=1; loop<16; loop++)
        {     
            colors[loop]=gdImageColorAllocate(im_ANSi, 0, 0, 0);
        }
    }
    else if (workbench)
    {        
        gdImageFill(im_ANSi, 0, 0, 0);
        colors[0] = gdImageColorAllocate(im_ANSi, 170, 170, 170);
        colors[1] = gdImageColorAllocate(im_ANSi, 0, 0, 255);
        colors[2] = gdImageColorAllocate(im_ANSi, 255, 255, 255);
        colors[3] = gdImageColorAllocate(im_ANSi, 0, 255, 255);
        colors[4] = gdImageColorAllocate(im_ANSi, 0, 0, 0);
        colors[5] = gdImageColorAllocate(im_ANSi, 255, 0, 255);
        colors[6] = gdImageColorAllocate(im_ANSi, 102, 136, 187);
        colors[7] = gdImageColorAllocate(im_ANSi, 255, 255, 255);
        colors[8] = gdImageColorAllocate(im_ANSi, 170, 170, 170);
        colors[9] = gdImageColorAllocate(im_ANSi, 0, 0, 255);
        colors[10] = gdImageColorAllocate(im_ANSi, 255, 255, 255);
        colors[11] = gdImageColorAllocate(im_ANSi, 0, 255, 255);
        colors[12] = gdImageColorAllocate(im_ANSi, 0, 0, 0);
        colors[13] = gdImageColorAllocate(im_ANSi, 255, 0, 255);
        colors[14] = gdImageColorAllocate(im_ANSi, 102, 136, 187);
        colors[15] = gdImageColorAllocate(im_ANSi, 255, 255, 255);
    }

    else
    {
        // Allocate standard ANSi color palette
        
        colors[0] = gdImageColorAllocate(im_ANSi, 0, 0, 0);
        colors[1] = gdImageColorAllocate(im_ANSi, 170, 0, 0);
        colors[2] = gdImageColorAllocate(im_ANSi, 0, 170, 0);
        colors[3] = gdImageColorAllocate(im_ANSi, 170, 85, 0);
        colors[4] = gdImageColorAllocate(im_ANSi, 0, 0, 170);
        colors[5] = gdImageColorAllocate(im_ANSi, 170, 0, 170);
        colors[6] = gdImageColorAllocate(im_ANSi, 0, 170, 170);
        colors[7] = gdImageColorAllocate(im_ANSi, 170, 170, 170);
        colors[8] = gdImageColorAllocate(im_ANSi, 85, 85, 85);
        colors[9] = gdImageColorAllocate(im_ANSi, 255, 85, 85);
        colors[10] = gdImageColorAllocate(im_ANSi, 85, 255, 85);
        colors[11] = gdImageColorAllocate(im_ANSi, 255, 255, 85);
        colors[12] = gdImageColorAllocate(im_ANSi, 85, 85, 255);
        colors[13] = gdImageColorAllocate(im_ANSi, 255, 85, 255);
        colors[14] = gdImageColorAllocate(im_ANSi, 85, 255, 255);
        colors[15] = gdImageColorAllocate(im_ANSi, 255, 255, 255);
        colors[20] = gdImageColorAllocate(im_ANSi, 200, 220, 169);

        background_canvas = gdImageColorAllocate(im_ANSi, 0, 0, 0);
    }

    // even more definitions, sigh
    int32_t ansiBufferItems = structIndex;
    
    // render ANSi
    for (loop = 0; loop < ansiBufferItems; loop++)
    {
        // grab ANSi char from our structure array
        color_background = ansi_buffer[loop].color_background;
        color_foreground = ansi_buffer[loop].color_foreground;
        character = ansi_buffer[loop].current_character;
        bold = ansi_buffer[loop].bold;
        italics = ansi_buffer[loop].italics;
        underline = ansi_buffer[loop].underline;
        position_x = ansi_buffer[loop].position_x;
        position_y = ansi_buffer[loop].position_y;
        
        alDrawChar(im_ANSi, fontData.font_data, int_bits, fontData.font_size_y, 
                   position_x, position_y, colors[color_background], colors[color_foreground], character);

    }
    
    // transparent flag used?
    if (transparent)
    {
        gdImageColorTransparent(im_ANSi, background_canvas);
    }

    // create output image
    FILE *file_Out = fopen(output, "wb");
    gdImagePng(im_ANSi, file_Out);
    fclose(file_Out);
    
    // in case Retina image output is wanted
    if (createRetinaRep)
    {
        gdImagePtr im_RetinaANSi;
        
        // make the Retina image @2x as large as im_ANSi
        im_RetinaANSi = gdImageCreate(im_ANSi->sx * 2, im_ANSi->sy * 2);
        
        gdImageCopyResized(im_RetinaANSi, im_ANSi, 0, 0, 0, 0,
                           im_RetinaANSi->sx, im_RetinaANSi->sy,
                           im_ANSi->sx, im_ANSi->sy);
        
        // create retina output image
        FILE *file_RetinaOut = fopen(retinaout, "wb");
        gdImagePng(im_RetinaANSi, file_RetinaOut);
        fclose(file_RetinaOut);
        
        gdImageDestroy(im_RetinaANSi);
    }
    
    // free memory
    free(ansi_buffer);
    
    gdImageDestroy(im_ANSi);
}

// PCB
void alPcBoardLoader(char *input, char *output, char *retinaout, char *font, int32_t int_bits, bool createRetinaRep)
{
    // some type declarations
    struct fontStruct fontData;
    int32_t columns = 80;
    int32_t loop, structIndex;

    // font selection
    alSelectFont(&fontData, font);

    // load input file
    FILE *input_file = fopen(input, "r");
    if (input_file == NULL) { 
        fputs("\nFile error.\n\n", stderr); exit (1);
    }
    
    // get the file size (bytes)
    size_t get_file_size = filesize(input);
    int32_t input_file_size = (int32_t)get_file_size;

    // next up is loading our file into a dynamically allocated memory buffer
    unsigned char *input_file_buffer;
    int32_t result;
    
    // allocate memory to contain the whole file
    input_file_buffer = (unsigned char *) malloc(sizeof(unsigned char)*input_file_size);
    if (input_file_buffer == NULL) {
        fputs ("\nMemory error.\n\n", stderr); exit (2);
    }
    
    // copy the file into the buffer
    result = fread(input_file_buffer, 1, input_file_size, input_file);
    if (result != input_file_size) {
        fputs ("\nReading error.\n\n", stderr); exit (3);
    } // whole file is now loaded into input_file_buffer
    
    // close input file, we don't need it anymore
    fclose(input_file);

    // libgd image pointers
    gdImagePtr im_PCB;
    
    // process PCBoard
    int32_t character, current_character, next_character; 
    int32_t color_background = 0, color_foreground = 7; 
    int32_t position_x = 0, position_y = 0, position_x_max = 0, position_y_max = 0;
    
    // PCB buffer structure array definition
    struct pcbChar *pcboard_buffer, *temp;
    
    // PCB buffer dynamic memory allocation
    pcboard_buffer = malloc(sizeof(struct pcbChar));
    
    // reset loop
    loop = 0;
    structIndex = 0;
        
    while (loop < input_file_size)
    {
        current_character = input_file_buffer[loop];
        next_character = input_file_buffer[loop+1];
        
        if (position_x == 80)
        {
            position_y++;
            position_x = 0;
        }
        
        // CR + LF
        if (current_character == 13 && next_character == 10) {
            position_y++;
            position_x = 0;
            loop++;
        }
        
        // LF
        if (current_character == 10)
        {
            position_y++;
            position_x = 0;
        }

        // Tab
        if (current_character==9)
        {
            position_x+=8;
        }
        
        // Sub
        if (current_character == 26)
        {
            break;
        }
        
        // PCB sequence
        if (current_character == 64 && next_character == 88)
        {
            // set graphics rendition
            color_background = input_file_buffer[loop+2];
            color_foreground = input_file_buffer[loop+3];
            
            loop+=3;
        }
        else if (current_character == 64 && next_character == 67 &&
                 input_file_buffer[loop+2] == 'L' && input_file_buffer[loop+3] == 'S')
        {
            // erase display
            position_x = 0;
            position_y = 0;
            
            position_x_max = 0;
            position_y_max = 0;
            
            loop+=4;
        }
        else if (current_character == 64 && next_character == 80 && input_file_buffer[loop+2] == 'O' 
                 && input_file_buffer[loop+3] == 'S' && input_file_buffer[loop+4]== ':')
        {
            // cursor position
            if (input_file_buffer[loop+6]=='@')
            {
                position_x=((input_file_buffer[loop+5])-48)-1;
                loop+=5;
            }
            else
            {
                position_x = (10 * ((input_file_buffer[loop+5])-48) + (input_file_buffer[loop+6])-48)-1;
                loop+=6;
            }
        }     
        else if (current_character != 10 && current_character != 13 && current_character != 9)
        {
            // record number of columns and lines used
            if (position_x > position_x_max)
            {
                position_x_max = position_x;
            }
            
            if (position_y > position_y_max)
            {
                position_y_max = position_y;
            }
            
            // reallocate structure array memory
            temp = realloc(pcboard_buffer, (structIndex + 1) * sizeof(struct pcbChar));
            pcboard_buffer = temp;
            
            // write current character in pcbChar structure
            pcboard_buffer[structIndex].position_x = position_x;
            pcboard_buffer[structIndex].position_y = position_y;
            pcboard_buffer[structIndex].color_background = color_background;
            pcboard_buffer[structIndex].color_foreground = color_foreground;
            pcboard_buffer[structIndex].current_character = current_character;
            
            position_x++;
            structIndex++;
        }
        loop++;
    }
    position_x_max++;
    position_y_max++;
    
    // allocate buffer image memory
    im_PCB = gdImageCreate(columns * int_bits, (position_y_max)*fontData.font_size_y);
    
    // allocate black color and create background canvas
    gdImageColorAllocate(im_PCB, 0, 0, 0);
    gdImageFill(im_PCB, 0, 0, 0);
    
    // allocate color palette    
    int32_t colors[71];
    
    colors[48] = gdImageColorAllocate(im_PCB, 0, 0, 0);
    colors[49] = gdImageColorAllocate(im_PCB, 0, 0, 170);
    colors[50] = gdImageColorAllocate(im_PCB, 0, 170, 0);
    colors[51] = gdImageColorAllocate(im_PCB, 0, 170, 170);
    colors[52] = gdImageColorAllocate(im_PCB, 170, 0, 0);
    colors[53] = gdImageColorAllocate(im_PCB, 170, 0, 170);
    colors[54] = gdImageColorAllocate(im_PCB, 170, 85, 0);
    colors[55] = gdImageColorAllocate(im_PCB, 170, 170, 170);
    colors[56] = gdImageColorAllocate(im_PCB, 85, 85, 85);
    colors[57] = gdImageColorAllocate(im_PCB, 85, 85, 255);
    colors[65] = gdImageColorAllocate(im_PCB, 85, 255, 85);
    colors[66] = gdImageColorAllocate(im_PCB, 85, 255, 255);
    colors[67] = gdImageColorAllocate(im_PCB, 255, 85, 85);
    colors[68] = gdImageColorAllocate(im_PCB, 255, 85, 255);
    colors[69] = gdImageColorAllocate(im_PCB, 255, 255, 85);
    colors[70] = gdImageColorAllocate(im_PCB, 255, 255, 255);
    
    // the last value of loop tells us how many items are stored in there
    int32_t pcbBufferItems = structIndex;
    
    // render PCB
    for (loop = 0; loop < pcbBufferItems; loop++)
    {
        // grab our chars out of the structure
        position_x = pcboard_buffer[loop].position_x;
        position_y = pcboard_buffer[loop].position_y;
        color_background = pcboard_buffer[loop].color_background;
        color_foreground = pcboard_buffer[loop].color_foreground;
        character = pcboard_buffer[loop].current_character;
        
        alDrawChar(im_PCB, fontData.font_data, int_bits, fontData.font_size_y, 
                   position_x, position_y, colors[color_background], colors[color_foreground], character);
    }
    
    // create output image
    FILE *file_Out = fopen(output, "wb");
    gdImagePng(im_PCB, file_Out);
    fclose(file_Out);
    
    // in case Retina image output is wanted
    if (createRetinaRep)
    {
        gdImagePtr im_RetinaANSi;
        
        // make the Retina image @2x as large as im_PCB
        im_RetinaANSi = gdImageCreate(im_PCB->sx * 2, im_PCB->sy * 2);
        
        gdImageCopyResized(im_RetinaANSi, im_PCB, 0, 0, 0, 0,
                           im_RetinaANSi->sx, im_RetinaANSi->sy,
                           im_PCB->sx, im_PCB->sy);
        
        // create retina output image
        FILE *file_RetinaOut = fopen(retinaout, "wb");
        gdImagePng(im_RetinaANSi, file_RetinaOut);
        fclose(file_RetinaOut);
        
        gdImageDestroy(im_RetinaANSi);
    }
    
    // free memory
    gdImageDestroy(im_PCB);
}

// TUNDRA
void alTundraLoader(char *input, char *output, char *retinaout, char *font, int32_t int_bits, bool fileHasSAUCE, bool createRetinaRep)
{
    // some type declarations
    struct fontStruct fontData;
    int32_t columns = 80;
    char tundra_version;
    char tundra_header[8];

    // font selection
    alSelectFont(&fontData, font);

    // load input file
    FILE *input_file = fopen(input, "r");
    if (input_file == NULL) {
        fputs("\nFile error.\n\n", stderr); exit (1);
    }

    // get the file size (bytes)
    size_t get_file_size = filesize(input);
    int32_t input_file_size = (int32_t)get_file_size;

    // next up is loading our file into a dynamically allocated memory buffer
    unsigned char *input_file_buffer;
    int32_t result;

    // allocate memory to contain the whole file
    input_file_buffer = (unsigned char *) malloc(sizeof(unsigned char)*input_file_size);
    if (input_file_buffer == NULL) {
        fputs ("\nMemory error.\n\n", stderr); exit (2);
    }

    // copy the file into the buffer
    result = fread(input_file_buffer, 1, input_file_size, input_file);
    if (result != input_file_size) {
        fputs ("\nReading error.\n\n", stderr); exit (3);
    } // whole file is now loaded into input_file_buffer

    // exclude SAUCE record from file buffer
    if(fileHasSAUCE) {
        sauce *saucerec = sauceReadFile(input_file);
        input_file_size -= 129 - ( saucerec->comments > 0 ? 5 + 64 * saucerec->comments : 0);
    }
    // close input file, we don't need it anymore
    fclose(input_file);

    // libgd image pointers
    gdImagePtr im_Tundra;

    // extract tundra header
    tundra_version = input_file_buffer[0];
    memcpy(&tundra_header,input_file_buffer+1,8);

    // need to add check for "TUNDRA24" string in the header
    if (tundra_version != 24)
    {
        fputs ("\nInput file is not a TUNDRA file.\n\n", stderr); exit (4);
    }

    // read tundra file a first time to find the image size
    int32_t character, color_background = 0, color_foreground = 0;
    int32_t loop = 0, position_x = 0, position_y = 0;

    loop=9;

    while (loop < input_file_size)
    {
        if (position_x == 80)
        {
            position_x = 0;
            position_y++;
        }

        character = input_file_buffer[loop];

        if (character == 1)
        {
            position_y =
                    (input_file_buffer[loop + 1] << 24) + (input_file_buffer[loop + 2] << 16) +
                            (input_file_buffer[loop + 3] << 8) + input_file_buffer[loop+4];

            position_x =
                    (input_file_buffer[loop + 5] << 24) + (input_file_buffer[loop + 6] << 16) +
                            (input_file_buffer[loop + 7] << 8) + input_file_buffer[loop+8];

            loop+=8;
        }

        if (character == 2)
        {
            character = input_file_buffer[loop + 1];

            loop+=5;
        }

        if (character == 4)
        {
            character = input_file_buffer[loop + 1];

            loop+=5;
        }

        if (character == 6)
        {
            character = input_file_buffer[loop + 1];

            loop+=9;
        }

        if (character !=1 && character !=2 && character !=4 && character != 6)
        {
            position_x++;
        }

        loop++;
    }
    position_y++;

    // allocate buffer image memory
    im_Tundra = gdImageCreateTrueColor(columns * int_bits , (position_y) * fontData.font_size_y);

    if (!im_Tundra) {
        fputs ("\nError, can't allocate buffer image memory.\n\n", stderr); exit (6);
    }

    // process tundra
    position_x = 0;
    position_y = 0;

    loop = 9;

    while (loop < input_file_size)
    {
        if (position_x == 80)
        {
            position_x = 0;
            position_y++;
        }

        character = input_file_buffer[loop];

        if (character == 1)
        {
            position_y =
                    (input_file_buffer[loop + 1] << 24) + (input_file_buffer[loop + 2] << 16) +
                            (input_file_buffer[loop + 3] << 8) + input_file_buffer[loop + 4];

            position_x =
                    (input_file_buffer[loop + 5] << 24) + (input_file_buffer[loop + 6] << 16) +
                            (input_file_buffer[loop + 7] << 8) + input_file_buffer[loop + 8];

            loop+=8;
        }

        if (character == 2)
        {
            color_foreground =
                    (input_file_buffer[loop + 3] << 16) + (input_file_buffer[loop + 4] << 8) +
                            input_file_buffer[loop + 5];

            character = input_file_buffer[loop+1];

            loop+=5;
        }

        if (character == 4)
        {
            color_background = (input_file_buffer[loop + 3] << 16) + (input_file_buffer[loop + 4] << 8) +
                    input_file_buffer[loop+5];

            character = input_file_buffer[loop+1];

            loop+=5;
        }

        if (character==6)
        {
            color_foreground =
                    (input_file_buffer[loop + 3] << 16) + (input_file_buffer[loop + 4] << 8) +
                            input_file_buffer[loop+5];

            color_background =
                    (input_file_buffer[loop + 7] << 16) + (input_file_buffer[loop + 8] << 8) +
                            input_file_buffer[loop+9];

            character = input_file_buffer[loop+1];

            loop+=9;
        }

        if (character !=1 && character !=2 && character !=4 && character !=6)
        {
            alDrawChar(im_Tundra, fontData.font_data, int_bits, fontData.font_size_y,
                    position_x, position_y, color_background, color_foreground, character);

            position_x++;
        }

        loop++;
    }

    // create output image
    FILE *file_Out = fopen(output, "wb");
    gdImagePng(im_Tundra, file_Out);
    fclose(file_Out);

    // in case Retina image output is wanted
    if (createRetinaRep)
    {
        gdImagePtr im_RetinaANSi;

        // make the Retina image @2x as large as im_Tundra
        im_RetinaANSi = gdImageCreate(im_Tundra->sx * 2, im_Tundra->sy * 2);

        gdImageCopyResized(im_RetinaANSi, im_Tundra, 0, 0, 0, 0,
                im_RetinaANSi->sx, im_RetinaANSi->sy,
                im_Tundra->sx, im_Tundra->sy);

        // create retina output image
        FILE *file_RetinaOut = fopen(retinaout, "wb");
        gdImagePng(im_RetinaANSi, file_RetinaOut);
        fclose(file_RetinaOut);

        gdImageDestroy(im_RetinaANSi);
    }

    // free memory
    gdImageDestroy(im_Tundra);
}

// XBIN
void alXbinLoader(char *input, char *output, char *retinaout, bool createRetinaRep)
{
    const unsigned char *font_data;
    unsigned char *font_data_xbin;
    
    // load input file
    FILE *input_file = fopen(input, "r");
    if (input_file == NULL) { 
        fputs("\nFile error.\n\n", stderr); exit (1);
    }
    
    // get the file size (bytes)
    size_t get_file_size = filesize(input);
    int32_t input_file_size = (int32_t)get_file_size;
    
    // next up is loading our file into a dynamically allocated memory buffer
    unsigned char *input_file_buffer;
    int32_t result;
    
    // allocate memory to contain the whole file
    input_file_buffer = (unsigned char *) malloc(sizeof(unsigned char)*input_file_size);
    if (input_file_buffer == NULL) {
        fputs ("\nMemory error.\n\n", stderr); exit (2);
    }
    
    // copy the file into the buffer
    result = fread(input_file_buffer, 1, input_file_size, input_file);
    if (result != input_file_size) {
        fputs ("\nReading error.\n\n", stderr); exit (3);
    } // whole file is now loaded into input_file_buffer
    
    // close input file, we don't need it anymore
    fclose(input_file);

    if (strncmp((char *)input_file_buffer, "XBIN\x1a", 5) != 0) {
        fputs("\nNot an XBin.\n\n", stderr); exit (4);
    }

    int32_t xbin_width = (input_file_buffer[ 6 ] << 8) + input_file_buffer[ 5 ];
    int32_t xbin_height = (input_file_buffer[ 8 ] << 8) + input_file_buffer[ 7 ];
    int32_t xbin_fontsize = input_file_buffer[ 9 ];
    int32_t xbin_flags = input_file_buffer[ 10 ];

    gdImagePtr im_XBIN;
    
    im_XBIN = gdImageCreate(8 * xbin_width, xbin_fontsize * xbin_height);
    
    if (!im_XBIN) {
        fputs ("\nError, can't allocate buffer image memory.\n\n", stderr); exit (6);
    }
    
    // allocate black color
    gdImageColorAllocate(im_XBIN, 0, 0, 0);
    
    int32_t colors[16];
    int32_t offset = 11;

    // palette
    if( (xbin_flags & 1) == 1 ) {
        int32_t loop;
        int32_t index;
        
        for (loop = 0; loop < 16; loop++)
        {
            index = (loop * 3) + offset;
            
            colors[loop] = gdImageColorAllocate(im_XBIN, (input_file_buffer[index] << 2 | input_file_buffer[index] >> 4), 
                                                (input_file_buffer[index + 1] << 2 | input_file_buffer[index + 1] >> 4), 
                                                (input_file_buffer[index + 2] << 2 | input_file_buffer[index + 2] >> 4));
        }

        offset += 48;
    }
    else {
        colors[0] = gdImageColorAllocate(im_XBIN, 0, 0, 0);
        colors[1] = gdImageColorAllocate(im_XBIN, 0, 0, 170);
        colors[2] = gdImageColorAllocate(im_XBIN, 0, 170, 0);
        colors[3] = gdImageColorAllocate(im_XBIN, 0, 170, 170);
        colors[4] = gdImageColorAllocate(im_XBIN, 170, 0, 0);
        colors[5] = gdImageColorAllocate(im_XBIN, 170, 0, 170);
        colors[6] = gdImageColorAllocate(im_XBIN, 170, 85, 0);
        colors[7] = gdImageColorAllocate(im_XBIN, 170, 170, 170);
        colors[8] = gdImageColorAllocate(im_XBIN, 85, 85, 85);
        colors[9] = gdImageColorAllocate(im_XBIN, 85, 85, 255);
        colors[10] = gdImageColorAllocate(im_XBIN, 85, 255, 85);
        colors[11] = gdImageColorAllocate(im_XBIN, 85, 255, 255);
        colors[12] = gdImageColorAllocate(im_XBIN, 255, 85, 85);
        colors[13] = gdImageColorAllocate(im_XBIN, 255, 85, 255);
        colors[14] = gdImageColorAllocate(im_XBIN, 255, 255, 85);
        colors[15] = gdImageColorAllocate(im_XBIN, 255, 255, 255);
    }

    // font
    if( (xbin_flags & 2) == 2 ) {
        int32_t numchars = ( xbin_flags & 0x10 ? 512 : 256 );
        
        // allocate memory to contain the XBin font
        font_data_xbin = (unsigned char *) malloc(sizeof(unsigned char)*(xbin_fontsize * numchars));
        if (font_data_xbin == NULL) {
            fputs ("\nMemory error.\n\n", stderr); exit (5);
        }
        memcpy(font_data_xbin,input_file_buffer+offset,(xbin_fontsize * numchars));

        font_data=font_data_xbin;

        offset += ( xbin_fontsize * numchars );
    }
    else {
        // using default 80x25 font
        font_data = font_pc_80x25;
    }

    int32_t position_x = 0, position_y = 0; 
    int32_t character, attribute, color_foreground, color_background;

    // read compressed xbin
    if( (xbin_flags & 4) == 4) {
        while(offset < input_file_size && position_y != xbin_height )
        {
            int32_t ctype = input_file_buffer[ offset ] & 0xC0;
            int32_t counter = ( input_file_buffer[ offset ] & 0x3F ) + 1;

            character = -1;
            attribute = -1;

            offset++;
            while( counter-- ) {
                // none
                if( ctype == 0 ) {
                    character = input_file_buffer[ offset ];
                    attribute = input_file_buffer[ offset + 1 ];
                    offset += 2;
                }
                // char
                else if ( ctype == 0x40 ) {
                    if( character == -1 ) {
                        character = input_file_buffer[ offset ];
                        offset++;
                    }
                    attribute = input_file_buffer[ offset ];
                    offset++;
                                    }
                // attr
                else if ( ctype == 0x80 ) {
                    if( attribute == -1 ) {
                        attribute = input_file_buffer[ offset ];
                        offset++;
                    }
                    character = input_file_buffer[ offset ];
                    offset++;
                }
                // both
                else {
                    if( character == -1 ) {
                        character = input_file_buffer[ offset ];
                        offset++;
                    }
                    if( attribute == -1 ) {
                        attribute = input_file_buffer[ offset ];
                        offset++;
                    }
                }

                color_background = (attribute & 240) >> 4;
                color_foreground = attribute & 15;
             
                alDrawChar(im_XBIN, font_data, 8, 16, position_x, position_y, colors[color_background], colors[color_foreground], character);

                position_x++;

                if (position_x == xbin_width)
                {
                    position_x = 0;
                    position_y++;
                }
            }
        }
    }
    // read uncompressed xbin
    else {
        while(offset < input_file_size && position_y != xbin_height )
        {
            if (position_x == xbin_width)
            {
                position_x = 0;
                position_y++;
            }
            
            character = input_file_buffer[offset];
            attribute = input_file_buffer[offset+1];
            
            color_background = (attribute & 240) >> 4;
            color_foreground = attribute & 15;

            alDrawChar(im_XBIN, font_data, 8, xbin_fontsize, position_x, position_y, colors[color_background], colors[color_foreground], character);
            
            position_x++;
            offset+=2;
        }
    }

    // create output file
    FILE *file_Out = fopen(output, "wb");
    gdImagePng(im_XBIN, file_Out);
    fclose(file_Out);
    
    // in case Retina image output is wanted
    if (createRetinaRep)
    {
        gdImagePtr im_RetinaANSi;
        
        // make the Retina image @2x as large as im_XBIN
        im_RetinaANSi = gdImageCreate(im_XBIN->sx * 2, im_XBIN->sy * 2);
        
        gdImageCopyResized(im_RetinaANSi, im_XBIN, 0, 0, 0, 0,
                           im_RetinaANSi->sx, im_RetinaANSi->sy,
                           im_XBIN->sx, im_XBIN->sy);
        
        // create retina output image
        FILE *file_RetinaOut = fopen(retinaout, "wb");
        gdImagePng(im_RetinaANSi, file_RetinaOut);
        fclose(file_RetinaOut);
        
        gdImageDestroy(im_RetinaANSi);
    }
    
    // nuke garbage
    gdImageDestroy(im_XBIN);
}

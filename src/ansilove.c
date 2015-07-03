//
//  ansilove.c
//  AnsiLove/C
//
//  Copyright (C) 2011-2015 Stefan Vogt, Brian Cassidy, Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 3-Clause License.
//  See the file LICENSE for details.
//

#include "ansilove.h"

// shared method for drawing characters
void alDrawChar(gdImagePtr im, const unsigned char *font_data, int32_t int_bits, 
                int32_t font_size_x, int32_t font_size_y, int32_t position_x, int32_t position_y, 
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
void alAnsiLoader(char *input, char output[], char retinaout[], char font[], char bits[], char icecolors[], char *fext, bool createRetinaRep)
{
    const unsigned char *font_data;

    // ladies and gentlemen, it's type declaration time
    int32_t columns = 80;
    int32_t font_size_x;
    int32_t font_size_y;
    bool isAmigaFont = false;
    bool isDizFile = false;
    bool ced = false;
    bool transparent = false;
    bool workbench = false;
    bool pixelCarry = false;
    
    // determine the font we use to render the output
    if (strcmp(font, "80x25") == 0) {
        font_data = font_pc_80x25;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "80x50") == 0) {
        font_data = font_pc_80x50;
        font_size_x = 9;
        font_size_y = 8;
    }
    else if (strcmp(font, "terminus") == 0) {
        font_data = font_pc_terminus;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "baltic") == 0) {
        font_data = font_pc_baltic;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "cyrillic") == 0) {
        font_data = font_pc_cyrillic;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "french-canadian") == 0) {
        font_data = font_pc_french_canadian;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "greek") == 0) {
        font_data = font_pc_greek;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "greek-869") == 0) {
        font_data = font_pc_greek_869;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "hebrew") == 0) {
        font_data = font_pc_hebrew;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "icelandic") == 0) {
        font_data = font_pc_icelandic;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "latin1") == 0) {
        font_data = font_pc_latin1;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "latin2") == 0) {
        font_data = font_pc_latin2;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "nordic") == 0) {
        font_data = font_pc_nordic;
        font_size_x = 9;
        font_size_y = 16; 
    }
    else if (strcmp(font, "portuguese") == 0) {
        font_data = font_pc_portuguese;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "russian") == 0) {
        font_data = font_pc_russian;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "turkish") == 0) {
        font_data = font_pc_turkish;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "amiga") == 0) {
        isAmigaFont = true;
        font_data = font_amiga_topaz_1200;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "microknight") == 0) {
        isAmigaFont = true;
        font_data = font_amiga_microknight;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "microknight+") == 0) {
        isAmigaFont = true;
        font_data = font_amiga_microknight_plus;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "mosoul") == 0) {
        isAmigaFont = true;
        font_data = font_amiga_mosoul;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "pot-noodle") == 0) {
        isAmigaFont = true;
        font_data = font_amiga_pot_noodle;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "topaz") == 0) {
        isAmigaFont = true;
        font_data = font_amiga_topaz_1200;
        font_size_x = 8;
        font_size_y = 16;   
    }
    else if (strcmp(font, "topaz+") == 0) {
        isAmigaFont = true;
        font_data = font_amiga_topaz_1200_plus;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "topaz500") == 0) {
        isAmigaFont = true;
        font_data = font_amiga_topaz_500;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "topaz500+") == 0) {
        isAmigaFont = true;
        font_data = font_amiga_topaz_500_plus;
        font_size_x = 8;
        font_size_y = 16;
    }
    else {
        // in all other cases use the standard DOS font
        font_data = font_pc_80x25;
        font_size_x = 9;
        font_size_y = 16;
    }
    
    // to deal with the bits flag, we declared handy bool types   
    if (strcmp(bits, "ced") == 0) {
        ced = true;
    }
    else if (strcmp(bits, "transparent") == 0) {
        transparent = true;
    }
    else if (strcmp(bits, "workbench") == 0) {
        workbench = true;
    }
    else if (strcmp(bits, "workbench-transparent") == 0) {
        workbench = true;
        transparent = true;
    }
    
    // force defaults... exactly now!
    if (strcmp(bits, "8") != 0 && strcmp(bits, "9") != 0) {
        sprintf(bits, "%s", "8");
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
    size_t result;
    
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
    rewind(input_file);
    fclose(input_file);
    
    // create array of DIZ extensions
    char **dizArray;
    int32_t dizCount, i;
    
    dizCount = explode(&dizArray, ',', DIZ_EXTENSIONS);
    
    // compare current file extension with the ones in our DIZ array
    for (i = 0; i < dizCount; i++) {
        if (strcmp(fext, dizArray[i]) == 0) {
            isDizFile = true;
        }            
    }
    // in case we got a DIZ file here, do specific optimizations
    if (isDizFile == true) 
    {
        char *stripped_file_buffer;
        stripped_file_buffer = str_replace((const char *)input_file_buffer, "\r\n", "");
        input_file_buffer = (unsigned char *)stripped_file_buffer;
        input_file_size = (int32_t)strlen((const char *)input_file_buffer);
    }
    
    // libgd image pointers
    gdImagePtr im_ANSi, im_Backgrnd, im_Font;
    
    im_Backgrnd = gdImageCreate(9*16,16);

    // Allocate font image buffer
    im_Font = gdImageCreate(font_size_x*256,font_size_y*16);
    
    // set transparent color index for the font
    gdImageColorTransparent(im_Font, 20);
    
    // convert numeric command line flags to integer values
    int32_t int_bits = atoi(bits);
    int32_t int_icecolors = atoi(icecolors);

    // ANSi processing loops
    int32_t loop = 0, ansi_sequence_loop, seq_graphics_loop; 
    
    // character definitions
    int32_t current_character, next_character, character; 
    unsigned char ansi_sequence_character;
    
    // default color values
    int32_t color_background = 0, color_foreground = 7; 
    
    // text attributes
    bool bold, underline, italics, blink;
    
    // positions
    int32_t position_x = 0, position_y = 0, position_x_max = 0, position_y_max = 0;
    int32_t saved_position_y, saved_position_x;
    
    // sequence parsing variables
    int32_t seqContent, seqValue, seqArrayCount, seq_line, seq_column;
    char *seqGrab;
    char **seqArray;
    
    // ANSi buffer structure array definition
    int32_t structIndex = 0;
    struct ansiChar *ansi_buffer, *temp;
    
    // ANSi buffer dynamic memory allocation
    ansi_buffer = malloc(sizeof(struct ansiChar));
    
    // background canvas
    int32_t background_canvas;
    
    // ANSi interpreter
    while (loop < input_file_size)
    {
        current_character = input_file_buffer[loop];
        next_character = input_file_buffer[loop + 1];
        
        // also define sequence content starting point
        seqContent = input_file_buffer[loop + 2];
        
        if (position_x==80 && (strcmp(WRAP_COLUMN_80, "1") == 0))
        {
            position_y++;
            position_x=0;
        }
        
        // CR + LF
        if (current_character == 13)
        {
            if (next_character == 10)
            {
                position_y++;
                position_x = 0;
                loop++;
            }
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
        if (current_character == 26 && (strcmp(SUBSTITUTE_BREAK, "1") == 0))
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
                                if (workbench == false)
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
                                if (workbench == false)
                                {
                                    color_background+=8;
                                }
                                blink = true;
                            }
                            
                            if (seqValue > 29 && seqValue < 38)
                            {
                                color_foreground = seqValue - 30;
                                
                                if (bold == true)
                                {
                                    color_foreground+=8;
                                }
                            }
                            
                            if (seqValue > 39 && seqValue < 48)
                            {
                                color_background = seqValue - 40;
                                
                                if (blink == true && int_icecolors == 1)
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
            if (isAmigaFont == false || (current_character != 12 && current_character != 13))
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
    
    if (ced == true)
    {
        columns = 78;
    }
    
    if (isDizFile == true) {
        columns = fmin(position_x_max,80);
    }
        
    // create that damn thingy
    im_ANSi = gdImageCreate(columns * int_bits,(position_y_max)*font_size_y);
    
    if (!im_ANSi) {
        fputs ("\nCan't allocate ANSi buffer image memory.\n\n", stderr); exit (6);
    }
    
    int32_t colors[21];
    
    if (ced == true)
    {
        // get ced colors from configuration
        char **cedBackgroundArray, **cedForegroundArray;
        int32_t cedBackgroundCnt, cedForegroundCnt;
        int32_t cedBackgroundColor[3], cedForegroundColor[3];
        
        cedBackgroundCnt = explode(&cedBackgroundArray, ',', CED_BACKGROUND_COLOR);
        cedForegroundCnt = explode(&cedForegroundArray, ',', CED_FOREGROUND_COLOR);
        
        // convert string values to integers
        for (i = 0; i < cedBackgroundCnt; i++) {
            cedBackgroundColor[i] = atoi(cedBackgroundArray[i]);
        }
        for (i = 0; i < cedForegroundCnt; i++) {
            cedForegroundColor[i] = atoi(cedForegroundArray[i]);
        }
        
        for (loop=0; loop<16; loop++)
        {     
            colors[loop]=gdImageColorAllocate(im_ANSi, cedBackgroundColor[0], cedBackgroundColor[1], cedBackgroundColor[2]);
        }

        int32_t ced_color;
        ced_color = gdImageColorAllocate(im_ANSi, cedBackgroundColor[0], cedBackgroundColor[1], cedBackgroundColor[2]);
        ced_color = gdImageColorAllocate(im_Backgrnd, cedBackgroundColor[0], cedBackgroundColor[1], cedBackgroundColor[2]);
        
        gdImageFill(im_ANSi,0,0,ced_color);
        gdImageFilledRectangle(im_Backgrnd, 0, 0, 144, 16, ced_color);
        
    }
    else if (workbench == true)
    {
        // get workbench colors from configuration
        char **wbColorArray, *wbcStorage[8][3];
        int32_t wbColorCnt, wbColorMAX = 8;
        int32_t workbench_color[8][3], y;
        
        // process workbench colors into multi-dimensional char array
        wbColorCnt = explode(&wbColorArray, ',', WORKBENCH_COLOR_0);
        for (i = 0; i < wbColorCnt; i++) {
            wbcStorage[0][i] = wbColorArray[i];
        }
        wbColorCnt = explode(&wbColorArray, ',', WORKBENCH_COLOR_4);
        for (i = 0; i < wbColorCnt; i++) {
            wbcStorage[1][i] = wbColorArray[i];
        }
        wbColorCnt = explode(&wbColorArray, ',', WORKBENCH_COLOR_2);
        for (i = 0; i < wbColorCnt; i++) {
            wbcStorage[2][i] = wbColorArray[i];
        }
        wbColorCnt = explode(&wbColorArray, ',', WORKBENCH_COLOR_6);
        for (i = 0; i < wbColorCnt; i++) {
            wbcStorage[3][i] = wbColorArray[i];
        }
        wbColorCnt = explode(&wbColorArray, ',', WORKBENCH_COLOR_1);
        for (i = 0; i < wbColorCnt; i++) {
            wbcStorage[4][i] = wbColorArray[i];
        }
        wbColorCnt = explode(&wbColorArray, ',', WORKBENCH_COLOR_5);
        for (i = 0; i < wbColorCnt; i++) {
            wbcStorage[5][i] = wbColorArray[i];
        }
        wbColorCnt = explode(&wbColorArray, ',', WORKBENCH_COLOR_3);
        for (i = 0; i < wbColorCnt; i++) {
            wbcStorage[6][i] = wbColorArray[i];
        }
        wbColorCnt = explode(&wbColorArray, ',', WORKBENCH_COLOR_7);
        for (i = 0; i < wbColorCnt; i++) {
            wbcStorage[7][i] = wbColorArray[i];
        }
        
        // convert multi-dimensional char array to multi-dimensional integer array *sigh*
        for (i = 0; i < wbColorMAX; i++) {
            for (y = 0; y < wbColorCnt; y++) {
                workbench_color[i][y] = atoi(wbcStorage[i][y]);
            }
        }
        
        // process workbench colors
        gdImageColorAllocate(im_ANSi, workbench_color[0][0], workbench_color[0][1], workbench_color[0][2]);
        
        int32_t workbench_background = 0;
        
        gdImageFill(im_ANSi, 0, 0, workbench_background);
        
        for (loop=0; loop<8; loop++)
        {
            colors[loop]=gdImageColorAllocate(im_Backgrnd, workbench_color[loop][0], workbench_color[loop][1], workbench_color[loop][2]);
            colors[loop+8]=gdImageColorAllocate(im_Backgrnd, workbench_color[loop][0], workbench_color[loop][1], workbench_color[loop][2]);
            colors[loop]=gdImageColorAllocate(im_Font, workbench_color[loop][0], workbench_color[loop][1], workbench_color[loop][2]);
            colors[loop+8]=gdImageColorAllocate(im_Font, workbench_color[loop][0], workbench_color[loop][1], workbench_color[loop][2]);
        }
    }

    else
    {
        // Allocate standard ANSi color palette
        
        colors[0] = gdImageColorAllocate(im_Font, 0, 0, 0);
        colors[1] = gdImageColorAllocate(im_Font, 170, 0, 0);
        colors[2] = gdImageColorAllocate(im_Font, 0, 170, 0);
        colors[3] = gdImageColorAllocate(im_Font, 170, 85, 0);
        colors[4] = gdImageColorAllocate(im_Font, 0, 0, 170);
        colors[5] = gdImageColorAllocate(im_Font, 170, 0, 170);
        colors[6] = gdImageColorAllocate(im_Font, 0, 170, 170);
        colors[7] = gdImageColorAllocate(im_Font, 170, 170, 170);
        colors[8] = gdImageColorAllocate(im_Font, 85, 85, 85);
        colors[9] = gdImageColorAllocate(im_Font, 255, 85, 85);
        colors[10] = gdImageColorAllocate(im_Font, 85, 255, 85);
        colors[11] = gdImageColorAllocate(im_Font, 255, 255, 85);
        colors[12] = gdImageColorAllocate(im_Font, 85, 85, 255);
        colors[13] = gdImageColorAllocate(im_Font, 255, 85, 255);
        colors[14] = gdImageColorAllocate(im_Font, 85, 255, 255);
        colors[15] = gdImageColorAllocate(im_Font, 255, 255, 255);
        colors[20] = gdImageColorAllocate(im_Font, 200, 220, 169);
        
        gdImagePaletteCopy(im_Backgrnd, im_Font);
        
        background_canvas = gdImageColorAllocate(im_ANSi, 0, 0, 0);
    }
    
    // color array and RGB definitions
    int32_t Red, Green, Blue;
    
    // generating ANSi colors array in order to draw underlines
    for (loop = 0; loop < 16; loop++)
    {
        Red = gdImageRed(im_Backgrnd, loop);
        Green = gdImageGreen(im_Backgrnd, loop);
        Blue = gdImageBlue(im_Backgrnd, loop);
        
        colors[loop] = gdImageColorAllocate(im_ANSi, Red, Green, Blue);
    }
    
    // reconstruct font bitmap from bitfonts data
    int32_t j , k = 0;
    
    for (k=0;k<16;k++)
    {
        for (j=0;j<256;j++)
        {
            alDrawChar(im_Font, font_data, font_size_x, font_size_x, font_size_y, 
                       j, k, 20, k, j);
        }
    }
        
    // reconstruct background bitmap
    for (loop = 0; loop < 16; loop++)
    {
        gdImageFilledRectangle(im_Backgrnd, loop * 9, 0, loop * 9 + 9, 16, loop);
    }
    
    // even more definitions, sigh
    int32_t ansiBufferItems = structIndex;
    int32_t loop_column;
    int32_t character_size_x;
    
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
        
        if (isAmigaFont == false)
        {
            gdImageCopy(im_ANSi, im_Backgrnd, position_x * int_bits, 
                        position_y * font_size_y, color_background * 9, 0, int_bits, font_size_y);
            
            gdImageCopy(im_ANSi, im_Font, position_x * int_bits, position_y * font_size_y, 
                        character * font_size_x, color_foreground * font_size_y, int_bits, font_size_y);
        }
        else
        {
            if (color_background != 0 || italics == false)
            {
                gdImageCopy(im_ANSi, im_Backgrnd, position_x * int_bits, 
                            position_y * font_size_y, color_background * 9, 0, int_bits, font_size_y);
            }
            
            if (italics == false)
            {
                gdImageCopy(im_ANSi, im_Font, position_x * int_bits, position_y * font_size_y, 
                            character * font_size_x, color_foreground * font_size_y, int_bits, font_size_y);
            }
            else
            {
                gdImageCopy(im_ANSi, im_Font, position_x * int_bits + 3, position_y * font_size_y, 
                            character * font_size_x, color_foreground * font_size_y, int_bits,2);
                
                gdImageCopy(im_ANSi, im_Font, position_x * int_bits + 2, position_y * font_size_y + 2,
                            character * font_size_x, color_foreground * font_size_y + 2, int_bits, 4);
                
                gdImageCopy(im_ANSi, im_Font, position_x * int_bits + 1, position_y * font_size_y + 6, 
                            character * font_size_x, color_foreground * font_size_y + 6, int_bits, 4);
                
                gdImageCopy(im_ANSi, im_Font, position_x * int_bits, position_y * font_size_y + 10,
                            character * font_size_x, color_foreground * font_size_y + 10, int_bits,4);
                
                gdImageCopy(im_ANSi, im_Font, position_x * int_bits - 1, position_y * font_size_y + 14,
                            character * font_size_x, color_foreground * font_size_y + 14, int_bits, 2);
            }
            
            if (italics == true && bold == true)
            {
                gdImageCopy(im_ANSi, im_Font, position_x * int_bits + 3 + 1, position_y * font_size_y, 
                            character * font_size_x, color_foreground * font_size_y ,int_bits, 2);
                
                gdImageCopy(im_ANSi, im_Font, position_x * int_bits + 2 + 1, position_y * font_size_y + 2, 
                            character * font_size_x, color_foreground * font_size_y + 2, int_bits, 4);
                
                gdImageCopy(im_ANSi, im_Font, position_x * int_bits + 1 + 1, position_y * font_size_y + 6, 
                            character * font_size_x, color_foreground * font_size_y + 6, int_bits, 4);
                
                gdImageCopy(im_ANSi, im_Font, position_x * int_bits + 1, position_y * font_size_y + 10,
                            character * font_size_x, color_foreground * font_size_y + 10, int_bits, 4);
                
                gdImageCopy(im_ANSi, im_Font, position_x * int_bits - 1 + 1, position_y * font_size_y + 14,
                            character * font_size_x, color_foreground * font_size_y + 14, int_bits, 2);
            }
            
            if (bold == true && italics == false && (ced == true || workbench == true))
            {
                gdImageCopy(im_ANSi, im_Font, 1 + position_x * int_bits, position_y * font_size_y, 
                            character * font_size_x, color_foreground * font_size_y, int_bits, font_size_y);
            }
            
            if (underline == true)
            {
                loop_column = 0;
                character_size_x = 8;
                
                if (bold == true)
                {
                    character_size_x++;
                }
                
                if (italics == true)
                {
                    loop_column=-1;
                    character_size_x = 11;
                }
                
                while (loop_column < character_size_x)
                {
                    if (gdImageGetPixel(im_ANSi, position_x * int_bits + loop_column, 
                                        position_y * font_size_y + 15) == color_background && 
                        gdImageGetPixel(im_ANSi, position_x * int_bits +loop_column + 1, 
                                        position_y * font_size_y + 15) == color_background)
                    {
                        gdImageSetPixel(im_ANSi, position_x * int_bits + loop_column, 
                                        position_y * font_size_y + 14, colors[color_foreground]);
                        
                        gdImageSetPixel(im_ANSi, position_x * int_bits + loop_column, 
                                        position_y * font_size_y + 15, colors[color_foreground]);
                    }
                    else if (gdImageGetPixel(im_ANSi, position_x * int_bits + loop_column,
                                             position_y * font_size_y + 15) != color_background && 
                             gdImageGetPixel(im_ANSi, position_x * int_bits + loop_column + 1,
                                             position_y * font_size_y + 15) == color_background)
                    {
                        loop_column++;
                    }                    
                    loop_column++;
                }
                
                if (pixelCarry == true)
                {
                    gdImageSetPixel(im_ANSi, position_x * int_bits, 
                                    position_y * font_size_y + 14, colors[color_foreground]);
                    
                    gdImageSetPixel(im_ANSi, position_x * int_bits, 
                                    position_y * font_size_y + 15, colors[color_foreground]);
                    
                    pixelCarry = false;
                }
                
                if (gdImageGetPixel(im_Font, character * font_size_x, 
                                    color_foreground * font_size_y + 15) != 20)
                {
                    gdImageSetPixel(im_ANSi, position_x * int_bits - 1, 
                                    position_y * font_size_y + 14, colors[color_foreground]);
                    
                    gdImageSetPixel(im_ANSi, position_x * int_bits - 1, 
                                    position_y * font_size_y + 15, colors[color_foreground]);
                }
                
                if (gdImageGetPixel(im_Font, character * font_size_x + character_size_x - 1, 
                                    color_foreground * font_size_y + 15) != 20)
                {
                    pixelCarry = true;
                }
            }
        }
    }
    
    // transparent flag used?
    if (transparent == true)
    {
        gdImageColorTransparent(im_ANSi, background_canvas);
    }

    // create output image
    FILE *file_Out = fopen(output, "wb");
    gdImagePng(im_ANSi, file_Out);
    fclose(file_Out);
    
    // in case Retina image output is wanted
    if (createRetinaRep == true)
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
    gdImageDestroy(im_Backgrnd);
    gdImageDestroy(im_Font);
}

// PCB
void alPcBoardLoader(char *input, char output[], char retinaout[], char font[], char bits[], bool createRetinaRep)
{
    // some type declarations
    int32_t font_size_x;
    int32_t font_size_y;
    int32_t columns = 80;
    const unsigned char *font_data;
        
    // let's see what font we should use to render output
    if (strcmp(font, "80x25") == 0) {
        font_data = font_pc_80x25;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "80x50") == 0) {
        font_data = font_pc_80x50;
        font_size_x = 9;
        font_size_y = 8;
    }
    else if (strcmp(font, "terminus") == 0) {
        font_data = font_pc_terminus;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "baltic") == 0) {
        font_data = font_pc_baltic;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "cyrillic") == 0) {
        font_data = font_pc_cyrillic;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "french-canadian") == 0) {
        font_data = font_pc_french_canadian;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "greek") == 0) {
        font_data = font_pc_greek;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "greek-869") == 0) {
        font_data = font_pc_greek_869;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "hebrew") == 0) {
        font_data = font_pc_hebrew;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "icelandic") == 0) {
        font_data = font_pc_icelandic;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "latin1") == 0) {
        font_data = font_pc_latin1;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "latin2") == 0) {
        font_data = font_pc_latin2;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "nordic") == 0) {
        font_data = font_pc_nordic;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "portuguese") == 0) {
        font_data = font_pc_portuguese;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "russian") == 0) {
        font_data = font_pc_russian;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "turkish") == 0) {
        font_data = font_pc_turkish;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "amiga") == 0) {
        font_data = font_amiga_topaz_1200;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "microknight") == 0) {
        font_data = font_amiga_microknight;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "microknight+") == 0) {
        font_data = font_amiga_microknight_plus;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "mosoul") == 0) {
        font_data = font_amiga_mosoul;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "pot-noodle") == 0) {
        font_data = font_amiga_pot_noodle;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "topaz") == 0) {
        font_data = font_amiga_topaz_1200;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "topaz+") == 0) {
        font_data = font_amiga_topaz_1200_plus;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "topaz500") == 0) {
        font_data = font_amiga_topaz_500;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "topaz500+") == 0) {
        font_data = font_amiga_topaz_500_plus;
        font_size_x = 8;
        font_size_y = 16;
    }
    else {
        // in all other cases use the standard DOS font
        font_data = font_pc_80x25;
        font_size_x = 9;
        font_size_y = 16;
    }

    // now set bits to 8 if not already value 8 or 9
    if (strcmp(bits, "8") != 0 && strcmp(bits, "9") != 0) {
        sprintf(bits, "%s", "8");
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
    size_t result;
    
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
    rewind(input_file);
    fclose(input_file);

    // libgd image pointers
    gdImagePtr im_PCB;

    // convert numeric command line flags to integer values
    int32_t int_bits = atoi(bits);

    // defines for stripping PCBoard codes
    char *stripped_file_buffer;
    char **pcbStripCodes;
    int32_t stripCount, loop, structIndex;
    
    // create array of PCBoard strip codes defined in alconfig.h
    stripCount = explode(&pcbStripCodes, ',', PCBOARD_STRIP_CODES);
    
    // remove all specified PCB strip code occurances in input_file_buffer
    for (loop = 0; loop < stripCount; loop++) {
        stripped_file_buffer = str_replace((const char *)input_file_buffer, pcbStripCodes[loop], "");
        input_file_buffer = (unsigned char *)stripped_file_buffer;
    }
    
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
        if (current_character == 13)
        {
            if (next_character == 10)
            {
                position_y++;
                position_x = 0;
                loop++;
            }
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
    im_PCB = gdImageCreate(columns * int_bits, (position_y_max)*font_size_y);
    
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
        
        alDrawChar(im_PCB, font_data, int_bits, font_size_x, font_size_y, 
                   position_x, position_y, colors[color_background], colors[color_foreground], character);
    }
    
    // create output image
    FILE *file_Out = fopen(output, "wb");
    gdImagePng(im_PCB, file_Out);
    fclose(file_Out);
    
    // in case Retina image output is wanted
    if (createRetinaRep == true)
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

// BINARY
void alBinaryLoader(char *input, char output[], char retinaout[], char columns[], char font[], char bits[], char icecolors[], bool createRetinaRep)
{
    // some type declarations
    int32_t font_size_x;
    int32_t font_size_y;
    const unsigned char *font_data;

    // let's see what font we should use to render output
    if (strcmp(font, "80x25") == 0) {
        font_data = font_pc_80x25;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "80x50") == 0) {
        font_data = font_pc_80x50;
        font_size_x = 9;
        font_size_y = 8;
    }
    else if (strcmp(font, "terminus") == 0) {
        font_data = font_pc_terminus;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "baltic") == 0) {
        font_data = font_pc_baltic;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "cyrillic") == 0) {
        font_data = font_pc_cyrillic;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "french-canadian") == 0) {
        font_data = font_pc_french_canadian;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "greek") == 0) {
        font_data = font_pc_greek;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "greek-869") == 0) {
        font_data = font_pc_greek_869;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "hebrew") == 0) {
        font_data = font_pc_hebrew;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "icelandic") == 0) {
        font_data = font_pc_icelandic;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "latin1") == 0) {
        font_data = font_pc_latin1;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "latin2") == 0) {
        font_data = font_pc_latin2;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "nordic") == 0) {
        font_data = font_pc_nordic;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "portuguese") == 0) {
        font_data = font_pc_portuguese;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "russian") == 0) {
        font_data = font_pc_russian;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "turkish") == 0) {
        font_data = font_pc_turkish;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "amiga") == 0) {
        font_data = font_amiga_topaz_1200;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "microknight") == 0) {
        font_data = font_amiga_microknight;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "microknight+") == 0) {
        font_data = font_amiga_microknight_plus;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "mosoul") == 0) {
        font_data = font_amiga_mosoul;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "pot-noodle") == 0) {
        font_data = font_amiga_pot_noodle;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "topaz") == 0) {
        font_data = font_amiga_topaz_1200;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "topaz+") == 0) {
        font_data = font_amiga_topaz_1200_plus;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "topaz500") == 0) {
        font_data = font_amiga_topaz_500;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "topaz500+") == 0) {
        font_data = font_amiga_topaz_500_plus;
        font_size_x = 8;
        font_size_y = 16;
    }
    else {
        // in all other cases use the standard DOS font
        font_data = font_pc_80x25;
        font_size_x = 9;
        font_size_y = 16;
    }
    
    // now set bits to 8 if not already value 8 or 9
    if (strcmp(bits, "8") != 0 && strcmp(bits, "9") != 0) {
        sprintf(bits, "%s", "8");
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
    size_t result;
    
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
    rewind(input_file);
    fclose(input_file);
    
    // libgd image pointers
    gdImagePtr im_Binary;

    // convert numeric command line flags to integer values
    int32_t int_columns = atoi(columns);
    int32_t int_bits = atoi(bits);
    int32_t int_icecolors = atoi(icecolors);
    
    // allocate buffer image memory
    im_Binary = gdImageCreate(int_columns * int_bits, 
                              ((input_file_size / 2) / int_columns * font_size_y));
    
    if (!im_Binary) {
        fputs ("\nError, can't allocate buffer image memory.\n\n", stderr); exit (6);
    }
    
    // allocate black color
    gdImageColorAllocate(im_Binary, 0, 0, 0);

    // allocate color palette    
    int32_t colors[16];
    
    colors[0] = gdImageColorAllocate(im_Binary, 0, 0, 0);
    colors[1] = gdImageColorAllocate(im_Binary, 0, 0, 170);
    colors[2] = gdImageColorAllocate(im_Binary, 0, 170, 0);
    colors[3] = gdImageColorAllocate(im_Binary, 0, 170, 170);
    colors[4] = gdImageColorAllocate(im_Binary, 170, 0, 0);
    colors[5] = gdImageColorAllocate(im_Binary, 170, 0, 170);
    colors[6] = gdImageColorAllocate(im_Binary, 170, 85, 0);
    colors[7] = gdImageColorAllocate(im_Binary, 170, 170, 170);
    colors[8] = gdImageColorAllocate(im_Binary, 85, 85, 85);
    colors[9] = gdImageColorAllocate(im_Binary, 85, 85, 255);
    colors[10] = gdImageColorAllocate(im_Binary, 85, 255, 85);
    colors[11] = gdImageColorAllocate(im_Binary, 85, 255, 255);
    colors[12] = gdImageColorAllocate(im_Binary, 255, 85, 85);
    colors[13] = gdImageColorAllocate(im_Binary, 255, 85, 255);
    colors[14] = gdImageColorAllocate(im_Binary, 255, 255, 85);
    colors[15] = gdImageColorAllocate(im_Binary, 255, 255, 255);

    // process binary
    int32_t character, attribute, color_background, color_foreground;
    int32_t loop = 0, position_x = 0, position_y = 0;

    while (loop < input_file_size)
    {
        if (position_x == int_columns) 
        {
            position_x = 0;
            position_y++;
        }
        
        character = input_file_buffer[loop];
        attribute = input_file_buffer[loop+1];
        
        color_background = (attribute & 240) >> 4;
        color_foreground = (attribute & 15);

        
        if (color_background > 8 && int_icecolors == 0)
        {
            color_background -= 8;
        }

        alDrawChar(im_Binary, font_data, int_bits, font_size_x, font_size_y, 
                   position_x, position_y, colors[color_background], colors[color_foreground], character);
     
        position_x++;
        loop+=2;
    }
  
    // create output image
    FILE *file_Out = fopen(output, "wb");
    gdImagePng(im_Binary, file_Out);
    fclose(file_Out);
    
    // in case Retina image output is wanted
    if (createRetinaRep == true)
    {
        gdImagePtr im_RetinaANSi;
        
        // make the Retina image @2x as large as im_Binary
        im_RetinaANSi = gdImageCreate(im_Binary->sx * 2, im_Binary->sy * 2);
        
        gdImageCopyResized(im_RetinaANSi, im_Binary, 0, 0, 0, 0,
                           im_RetinaANSi->sx, im_RetinaANSi->sy,
                           im_Binary->sx, im_Binary->sy);
        
        // create retina output image
        FILE *file_RetinaOut = fopen(retinaout, "wb");
        gdImagePng(im_RetinaANSi, file_RetinaOut);
        fclose(file_RetinaOut);
        
        gdImageDestroy(im_RetinaANSi);
    }

    // free memory
    gdImageDestroy(im_Binary);
}

// ADF
void alArtworxLoader(char *input, char output[], char retinaout[], char bits[], bool createRetinaRep)
{
    const unsigned char *font_data;
    unsigned char *font_data_adf;    
    
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
    size_t result;
    
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
    rewind(input_file);
    fclose(input_file);
    
    // libgd image pointers
    gdImagePtr im_ADF;

    // create ADF instance
    im_ADF = gdImageCreate(640,(((input_file_size - 192 - 4096 -1) / 2) / 80) * 16);
    
    // error output
    if (!im_ADF) {
        fputs ("\nCan't allocate buffer image memory.\n\n", stderr); exit (7);
    }
    
    // ADF color palette array
    int32_t adf_colors[16] = { 0, 1, 2, 3, 4, 5, 20, 7, 56, 57, 58, 59, 60, 61, 62, 63 };
    
    int32_t loop;
    int32_t index;
    int32_t colors[16];
            
    // process ADF font
    font_data_adf = (unsigned char *) malloc(sizeof(unsigned char)*4096);
    if (font_data_adf == NULL) {
        fputs ("\nMemory error.\n\n", stderr); exit (7);
    }
    memcpy(font_data_adf,input_file_buffer+193,4096);
    
    font_data=font_data_adf;

    // process ADF palette    
    for (loop = 0; loop < 16; loop++)
    {
        index = (adf_colors[loop] * 3) + 1;
        colors[loop] = gdImageColorAllocate(im_ADF, (input_file_buffer[index] << 2 | input_file_buffer[index] >> 4), 
                                            (input_file_buffer[index + 1] << 2 | input_file_buffer[index + 1] >> 4), 
                                            (input_file_buffer[index + 2] << 2 | input_file_buffer[index + 2] >> 4));
    }
    
    gdImageColorAllocate(im_ADF, 0, 0, 0);
       
    // process ADF
    int32_t position_x = 0, position_y = 0; 
    int32_t character, attribute, color_foreground, color_background;
    loop = 192 + 4096 + 1;
    
    while(loop < input_file_size)
    {
        if (position_x == 80)
        {
            position_x = 0;
            position_y++;
        }
        
        character = input_file_buffer[loop];
        attribute = input_file_buffer[loop+1];
        
        color_background = (attribute & 240) >> 4;
        color_foreground = attribute & 15;

        alDrawChar(im_ADF, font_data, 8, 8, 16, position_x, position_y, color_background, color_foreground, character);
        
        position_x++;
        loop+=2;
    }
    
    // create output file
    FILE *file_Out = fopen(output, "wb");
    gdImagePng(im_ADF, file_Out);
    fclose(file_Out);
    
    // in case Retina image output is wanted
    if (createRetinaRep == true)
    {
        gdImagePtr im_RetinaANSi;
        
        // make the Retina image @2x as large as im_ADF
        im_RetinaANSi = gdImageCreate(im_ADF->sx * 2, im_ADF->sy * 2);
        
        gdImageCopyResized(im_RetinaANSi, im_ADF, 0, 0, 0, 0,
                           im_RetinaANSi->sx, im_RetinaANSi->sy,
                           im_ADF->sx, im_ADF->sy);
        
        // create retina output image
        FILE *file_RetinaOut = fopen(retinaout, "wb");
        gdImagePng(im_RetinaANSi, file_RetinaOut);
        fclose(file_RetinaOut);
        
        gdImageDestroy(im_RetinaANSi);
    }

    // nuke garbage
    gdImageDestroy(im_ADF);
}

// IDF
void alIcedrawLoader(char *input, char output[], char retinaout[], char bits[], bool fileHasSAUCE, bool createRetinaRep)
{
    const unsigned char *font_data;
    unsigned char *font_data_idf;
    
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
    size_t result;
    
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
    
    // just like a tape, you know?
    rewind(input_file);

    // IDF related: file contains a SAUCE record? adjust the file size
    if(fileHasSAUCE == true) {
        sauce *saucerec = sauceReadFile(input_file);
        input_file_size -= 129 - ( saucerec->comments > 0 ? 5 + 64 * saucerec->comments : 0);
        rewind(input_file);
    }
    
    // close input file, we don't need it anymore
    fclose(input_file);

    // extract relevant part of the IDF header, 16-bit endian unsigned short    
    int32_t x2 = (input_file_buffer[9] << 8) + input_file_buffer[8];

    // libgd image pointers
    gdImagePtr im_IDF;

    int32_t loop;
    int32_t index;
    int32_t colors[16];
    
    // process IDF font
    font_data_idf = (unsigned char *) malloc(sizeof(unsigned char)*4096);
    if (font_data_idf == NULL) {
        fputs ("\nMemory error.\n\n", stderr); exit (7);
    }
    memcpy(font_data_idf,input_file_buffer+(input_file_size - 48 - 4096),4096);
    
    font_data=font_data_idf;

    // process IDF
    loop = 12;
    int32_t idf_sequence_length, idf_sequence_loop, i = 0;
    
    // dynamically allocated memory buffer for IDF data
    unsigned char *idf_buffer, *temp;
    idf_buffer = malloc(sizeof(unsigned char));
        
    int16_t idf_data, idf_data_length;

    while (loop < input_file_size - 4096 - 48) 
    {
        memcpy(&idf_data,input_file_buffer+loop,2);
        
        // RLE compressed data
        if (idf_data==1)
        {
            memcpy(&idf_data_length,input_file_buffer+loop+2,2);
            
            idf_sequence_length = idf_data_length & 255;
            
            for (idf_sequence_loop = 0; idf_sequence_loop < idf_sequence_length; idf_sequence_loop++) 
            {
                // reallocate IDF buffer memory
                temp = realloc(idf_buffer, (i + 2) * sizeof(unsigned char));
                if (idf_buffer != NULL) {
                    idf_buffer = temp;
                }
                else {
                    fputs ("\nError allocating IDF buffer memory.\n\n", stderr); exit (7);
                }
                
                idf_buffer[i] = input_file_buffer[loop + 4];
                idf_buffer[i+1] = input_file_buffer[loop + 5];
                i+=2;
            }
            loop += 4;
        }
        else { 
            // reallocate IDF buffer memory
            temp = realloc(idf_buffer, (i + 2) * sizeof(unsigned char));
            if (idf_buffer != NULL) {
                idf_buffer = temp;
            }
            else {
                fputs ("\nError allocating IDF buffer memory.\n\n", stderr); exit (8);
            }
            
            // normal character
            idf_buffer[i] = input_file_buffer[loop];
            idf_buffer[i+1] = input_file_buffer[loop + 1];
            i+=2;
        }
        loop += 2;
    }
    
    // create IDF instance
    im_IDF = gdImageCreate((x2 + 1) * 8, i / 2 / 80 * 16);
    
    // error output
    if (!im_IDF) {
        fputs ("\nCan't allocate buffer image memory.\n\n", stderr); exit (9);
    }
    gdImageColorAllocate(im_IDF, 0, 0, 0);
    
    // process IDF palette
    for (loop = 0; loop < 16; loop++)
    {
        index = (loop * 3) + input_file_size - 48;
        colors[loop] = gdImageColorAllocate(im_IDF, (input_file_buffer[index] << 2 | input_file_buffer[index] >> 4), 
                                            (input_file_buffer[index + 1] << 2 | input_file_buffer[index + 1] >> 4), 
                                            (input_file_buffer[index + 2] << 2 | input_file_buffer[index + 2] >> 4));
    }

    // render IDF    
    int32_t position_x = 0, position_y = 0; 
    int32_t character, attribute, color_foreground, color_background;
    
    for (loop = 0; loop < i ; loop +=2) 
    {
        if (position_x == x2 + 1)
        {
            position_x = 0;
            position_y++;
        }
        
        character = idf_buffer[loop];
        attribute = idf_buffer[loop+1];
        
        color_background = (attribute & 240) >> 4;
        color_foreground = attribute & 15;
        
        alDrawChar(im_IDF, font_data, 8, 8, 16, position_x, position_y, colors[color_background], colors[color_foreground], character);
        
        position_x++;
    }
    
    // free dynamically allocated memory
    free(idf_buffer);
    
    // create output file
    FILE *file_Out = fopen(output, "wb");
    gdImagePng(im_IDF, file_Out);
    fclose(file_Out);
    
    // in case Retina image output is wanted
    if (createRetinaRep == true)
    {
        gdImagePtr im_RetinaANSi;
        
        // make the Retina image @2x as large as im_IDF
        im_RetinaANSi = gdImageCreate(im_IDF->sx * 2, im_IDF->sy * 2);
        
        gdImageCopyResized(im_RetinaANSi, im_IDF, 0, 0, 0, 0,
                           im_RetinaANSi->sx, im_RetinaANSi->sy,
                           im_IDF->sx, im_IDF->sy);
        
        // create retina output image
        FILE *file_RetinaOut = fopen(retinaout, "wb");
        gdImagePng(im_RetinaANSi, file_RetinaOut);
        fclose(file_RetinaOut);
        
        gdImageDestroy(im_RetinaANSi);
    }
    
    // nuke garbage
    gdImageDestroy(im_IDF);
}

// TUNDRA
void alTundraLoader(char *input, char output[], char retinaout[], char font[], char bits[], bool fileHasSAUCE, bool createRetinaRep)
{
    int32_t columns = 80;
    int32_t font_size_x;
    int32_t font_size_y;
    const unsigned char *font_data;
    char tundra_version;
    char tundra_header[8];

    // determine the font we use to render the output
    if (strcmp(font, "80x25") == 0) {
        font_data = font_pc_80x25;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "80x50") == 0) {
        font_data = font_pc_80x50;
        font_size_x = 9;
        font_size_y = 8;
    }
    else if (strcmp(font, "terminus") == 0) {
        font_data = font_pc_terminus;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "baltic") == 0) {
        font_data = font_pc_baltic;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "cyrillic") == 0) {
        font_data = font_pc_cyrillic;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "french-canadian") == 0) {
        font_data = font_pc_french_canadian;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "greek") == 0) {
        font_data = font_pc_greek;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "greek-869") == 0) {
        font_data = font_pc_greek_869;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "hebrew") == 0) {
        font_data = font_pc_hebrew;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "icelandic") == 0) {
        font_data = font_pc_icelandic;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "latin1") == 0) {
        font_data = font_pc_latin1;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "latin2") == 0) {
        font_data = font_pc_latin2;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "nordic") == 0) {
        font_data = font_pc_nordic;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "portuguese") == 0) {
        font_data = font_pc_portuguese;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "russian") == 0) {
        font_data = font_pc_russian;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "turkish") == 0) {
        font_data = font_pc_turkish;
        font_size_x = 9;
        font_size_y = 16;
    }
    else if (strcmp(font, "amiga") == 0) {
        font_data = font_amiga_topaz_1200;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "microknight") == 0) {
        font_data = font_amiga_microknight;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "microknight+") == 0) {
        font_data = font_amiga_microknight_plus;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "mosoul") == 0) {
        font_data = font_amiga_mosoul;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "pot-noodle") == 0) {
        font_data = font_amiga_pot_noodle;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "topaz") == 0) {
        font_data = font_amiga_topaz_1200;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "topaz+") == 0) {
        font_data = font_amiga_topaz_1200_plus;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "topaz500") == 0) {
        font_data = font_amiga_topaz_500;
        font_size_x = 8;
        font_size_y = 16;
    }
    else if (strcmp(font, "topaz500+") == 0) {
        font_data = font_amiga_topaz_500_plus;
        font_size_x = 8;
        font_size_y = 16;
    }
    else {
        // in all other cases use the standard DOS font
        font_data = font_pc_80x25;
        font_size_x = 9;
        font_size_y = 16;
    }

    // now set bits to 8 if not already value 8 or 9
    if (strcmp(bits, "8") != 0 && strcmp(bits, "9") != 0) {
        sprintf(bits, "%s", "8");
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
    size_t result;

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

    // rewind the input file
    rewind(input_file);

    // exclude SAUCE record from file buffer
    if(fileHasSAUCE == true) {
        sauce *saucerec = sauceReadFile(input_file);
        input_file_size -= 129 - ( saucerec->comments > 0 ? 5 + 64 * saucerec->comments : 0);
        rewind(input_file);
    }
    // close input file, we don't need it anymore
    fclose(input_file);

    // libgd image pointers
    gdImagePtr im_Tundra;

    // convert numeric command line flags to integer values
    int32_t int_bits = atoi(bits);

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
    im_Tundra = gdImageCreateTrueColor(columns * int_bits , (position_y) * font_size_y);

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
            alDrawChar(im_Tundra, font_data, int_bits, font_size_x, font_size_y,
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
    if (createRetinaRep == true)
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
void alXbinLoader(char *input, char output[], char retinaout[], char bits[], bool createRetinaRep)
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
    size_t result;
    
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
    rewind(input_file);
    fclose(input_file);

    if (strcmp(strndup((char *)input_file_buffer, 5), "XBIN\x1a") != 0) {
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
             
                alDrawChar(im_XBIN, font_data, 8, 8, 16, position_x, position_y, colors[color_background], colors[color_foreground], character);

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

            alDrawChar(im_XBIN, font_data, 8, 8, xbin_fontsize, position_x, position_y, colors[color_background], colors[color_foreground], character);
            
            position_x++;
            offset+=2;
        }
    }

    // create output file
    FILE *file_Out = fopen(output, "wb");
    gdImagePng(im_XBIN, file_Out);
    fclose(file_Out);
    
    // in case Retina image output is wanted
    if (createRetinaRep == true)
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

// recursive string replacement
char *str_replace(const char *string, const char *substr, const char *replacement)
{
    char *tok = NULL;
    char *newstr = NULL;
    char *oldstr = NULL;
    char *head = NULL;
    
    // if either substr or replacement is NULL, duplicate string and let caller handle it
    if (substr == NULL || replacement == NULL) return strdup(string);
    newstr = strdup(string);
    head = newstr;
    
    while ((tok = strstr(head, substr)))
    {
        oldstr = newstr;
        newstr = malloc(strlen(oldstr) - strlen(substr) + strlen(replacement) + 1);
        
        // failed to allocate memory, free old string and return NULL
        if (newstr == NULL) {
            free (oldstr);
            return NULL;
        }
        memcpy (newstr, oldstr, tok - oldstr);
        memcpy (newstr + (tok - oldstr), replacement, strlen (replacement));
        memcpy (newstr + (tok - oldstr) + strlen(replacement), 
                tok + strlen (substr), strlen (oldstr) - strlen (substr) - (tok - oldstr));
        memset (newstr + strlen (oldstr) - strlen (substr) + strlen (replacement) , 0, 1);
        
        // move back head right after the last replacement
        head = newstr + (tok - oldstr) + strlen(replacement);
        free (oldstr);
    }
    return newstr;
}

// Reads SAUCE via a filename.
sauce *sauceReadFileName(char *fileName) 
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        return NULL;
    }
    
    sauce *record = sauceReadFile(file);
    fclose(file);
    return record;
}

// Read SAUCE via a FILE pointer.
sauce *sauceReadFile(FILE *file) 
{
    sauce *record;
    record = malloc(sizeof *record);
    
    if (record != NULL) {
        readRecord(file, record);
    }
    return record;
}

void readRecord(FILE *file, sauce *record) 
{
    if (fseek(file, 0 - RECORD_SIZE, SEEK_END) != EXIT_SUCCESS) {
        free(record);
        return;
    }
    
    size_t read_status = fread(record->ID, sizeof(record->ID) - 1, 1, file);
    record->ID[sizeof(record->ID) - 1] = '\0';
    
    if (read_status != 1 || strcmp(record->ID, SAUCE_ID) != 0) {
        free(record);
        return;
    }
    fread(record->version, sizeof(record->version) - 1, 1, file);
    record->version[sizeof(record->version) - 1] = '\0';
    fread(record->title, sizeof(record->title) - 1, 1, file);    
    record->title[sizeof(record->title) - 1] = '\0';
    fread(record->author, sizeof(record->author) - 1, 1, file);
    record->author[sizeof(record->author) - 1] = '\0';
    fread(record->group, sizeof(record->group) - 1, 1, file);    
    record->group[sizeof(record->group) - 1] = '\0';
    fread(record->date, sizeof(record->date) - 1, 1, file);
    record->date[sizeof(record->date) - 1] = '\0';
    fread(&(record->fileSize), sizeof(record->fileSize), 1, file);    
    fread(&(record->dataType), sizeof(record->dataType), 1, file);    
    fread(&(record->fileType), sizeof(record->fileType), 1, file);
    fread(&(record->tinfo1), sizeof(record->tinfo1), 1, file);
    fread(&(record->tinfo2), sizeof(record->tinfo2), 1, file);
    fread(&(record->tinfo3), sizeof(record->tinfo3), 1, file);
    fread(&(record->tinfo4), sizeof(record->tinfo4), 1, file);
    fread(&(record->comments), sizeof(record->comments), 1, file);
    fread(&(record->flags), sizeof(record->flags), 1, file);
    fread(record->filler, sizeof(record->filler) - 1, 1, file);
    record->filler[sizeof(record->filler) - 1] = '\0';
    
    if (ferror(file) != EXIT_SUCCESS) {
        free(record);
        return;
    }
    
    if (record->comments > 0) {
        record->comment_lines = malloc(record->comments *sizeof(*record->comment_lines));
        
        if (record->comment_lines != NULL) {
            readComments(file, record->comment_lines, record->comments);
        }
        else {
            free(record);
            return;
        }
    }
}

void readComments(FILE *file, char **comment_lines, int32_t comments) 
{
    int32_t i;
    
    if (fseek(file, 0 - (RECORD_SIZE + 5 + COMMENT_SIZE *comments), SEEK_END) == EXIT_SUCCESS) {
        char ID[6];
        fread(ID, sizeof(ID) - 1, 1, file);
        ID[sizeof(ID) - 1] = '\0';
        
        if (strcmp(ID, COMMENT_ID) != 0) {
            free(comment_lines);
            return;
        }
        
        for (i = 0; i < comments; i++) {
            char buf[COMMENT_SIZE + 1] = "";
            
            fread(buf, COMMENT_SIZE, 1, file);
            buf[COMMENT_SIZE] = '\0';
            
            if (ferror(file) == EXIT_SUCCESS) {
                comment_lines[i] = strdup(buf);
                if (comment_lines[i] == NULL) {
                    free(comment_lines);
                    return;
                }
            }
            else {
                free(comment_lines);
                return;
            }
        }
        return;
    }    
    free(comment_lines);
    return;
}

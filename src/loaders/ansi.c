//
//  ansi.c
//  AnsiLove/C
//
//  Copyright (c) 2011-2018 Stefan Vogt, Brian Cassidy, and Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 2-Clause License.
//  See the LICENSE file for details.
//

#define _XOPEN_SOURCE 700
#define _NETBSD_SOURCE
#include <string.h>

#include "ansi.h"

void ansi(unsigned char *inputFileBuffer, int32_t inputFileSize, char *outputFile, char *retinaout, char *font, int32_t bits, char *mode, bool icecolors, char *fext, int retinaScaleFactor)
{
    // ladies and gentlemen, it's type declaration time
    struct fontStruct fontData;

    int32_t columns = 80;

    bool isDizFile = false;
    bool ced = false;
    bool transparent = false;
    bool workbench = false;

    const char *errstr;

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

    // check if current file has a .diz extension
    if (!strcmp(fext, ".diz")) {
        isDizFile = true;
    }

    // libgd image pointers
    gdImagePtr canvas;

    // ANSi processing loops
    int32_t loop = 0, ansi_sequence_loop, seq_graphics_loop;

    // character definitions
    int32_t current_character, next_character, character;
    unsigned char ansi_sequence_character;

    // default color values
    int32_t background = 0, foreground = 7;

    // text attributes
    bool bold = false, underline = false, italics = false, blink = false;

    // positions
    int32_t column = 0, row = 0, columnMax = 0, rowMax = 0;
    int32_t saved_row = 0, saved_column = 0;

    // sequence parsing variables
    int32_t seqValue, seqArrayCount, seq_line, seq_column;
    char *seqGrab;
    char **seqArray;

    // ANSi buffer structure array definition
    int32_t structIndex = 0;
    struct ansiChar *ansi_buffer, *temp;

    // ANSi buffer dynamic memory allocation
    ansi_buffer = malloc(sizeof(struct ansiChar));

    // ANSi interpreter
    while (loop < inputFileSize)
    {
        current_character = inputFileBuffer[loop];
        next_character = inputFileBuffer[loop + 1];

        if (column==80)
        {
            row++;
            column=0;
        }

        // CR + LF
        if (current_character == 13 && next_character == 10) {
            row++;
            column = 0;
            loop++;
        }

        // LF
        if (current_character == 10)
        {
            row++;
            column = 0;
        }

        // tab
        if (current_character == 9)
        {
            column += 8;
        }

        // sub
        if (current_character == 26)
        {
            break;
        }

        // ANSi sequence
        if (current_character == 27 && next_character == 91)
        {
            for (ansi_sequence_loop = 0; ansi_sequence_loop < 14; ansi_sequence_loop++)
            {
                ansi_sequence_character = inputFileBuffer[loop + 2 + ansi_sequence_loop];

                // cursor position
                if (ansi_sequence_character == 'H' || ansi_sequence_character == 'f')
                {
                    // create substring from the sequence's content
                    seqGrab = strndup((char *)inputFileBuffer + loop + 2, ansi_sequence_loop);

                    // create sequence content array
                    seqArrayCount = explode(&seqArray, ';', seqGrab);
                    free(seqGrab);

                    if (seqArrayCount > 1) {
                        // convert grabbed sequence content to integers
                        seq_line = strtonum(seqArray[0], 0, INT32_MAX, &errstr);
                        seq_column = strtonum(seqArray[1], 0, INT32_MAX, &errstr);

                        // finally set the positions
                        row = seq_line-1;
                        column = seq_column-1;
                    }
                    else {
                        // no coordinates specified? we move to the home position
                        row = 0;
                        column = 0;
                    }
                    loop+=ansi_sequence_loop+2;
                    break;
                }

                // cursor up
                if (ansi_sequence_character=='A')
                {
                    // create substring from the sequence's content
                    seqGrab = strndup((char *)inputFileBuffer + loop + 2, ansi_sequence_loop);

                    // now get escape sequence's position value
                    int32_t seq_line = strtonum(seqGrab, 0, INT32_MAX, &errstr);
                    free(seqGrab);

                    row -= seq_line ? seq_line : 1;

                    loop+=ansi_sequence_loop+2;
                    break;
                }

                // cursor down
                if (ansi_sequence_character=='B')
                {
                    // create substring from the sequence's content
                    seqGrab = strndup((char *)inputFileBuffer + loop + 2, ansi_sequence_loop);

                    // now get escape sequence's position value
                    int32_t seq_line = strtonum(seqGrab, 0, INT32_MAX, &errstr);
                    free(seqGrab);

                    row += seq_line ? seq_line : 1;

                    loop+=ansi_sequence_loop+2;
                    break;
                }

                // cursor forward
                if (ansi_sequence_character=='C')
                {
                    // create substring from the sequence's content
                    seqGrab = strndup((char *)inputFileBuffer + loop + 2, ansi_sequence_loop);

                    // now get escape sequence's position value
                    int32_t seq_column = strtonum(seqGrab, 0, INT32_MAX, &errstr);
                    free(seqGrab);

                    column += seq_column ? seq_column : 1;

                    if (column>80)
                    {
                        column=80;
                    }

                    loop+=ansi_sequence_loop+2;
                    break;
                }

                // cursor backward
                if (ansi_sequence_character=='D')
                {
                    // create substring from the sequence's content
                    seqGrab = strndup((char *)inputFileBuffer + loop + 2, ansi_sequence_loop);

                    // now get escape sequence's content length
                    int32_t seq_column = strtonum(seqGrab, 0, INT32_MAX, &errstr);
                    free(seqGrab);

                    column -= seq_column ? seq_column : 1;

                    if (column < 0)
                    {
                        column = 0;
                    }

                    loop+=ansi_sequence_loop+2;
                    break;
                }

                // save cursor position
                if (ansi_sequence_character=='s')
                {
                    saved_row = row;
                    saved_column = column;

                    loop+=ansi_sequence_loop+2;
                    break;
                }

                // restore cursor position
                if (ansi_sequence_character=='u')
                {
                    row = saved_row;
                    column = saved_column;

                    loop+=ansi_sequence_loop+2;
                    break;
                }

                // erase display
                if (ansi_sequence_character=='J')
                {
                    // create substring from the sequence's content
                    seqGrab = strndup((char *)inputFileBuffer + loop + 2, ansi_sequence_loop);

                    // convert grab to an integer
                    int32_t eraseDisplayInt = strtonum(seqGrab, 0, INT32_MAX, &errstr);
                    free(seqGrab);

                    if (eraseDisplayInt == 2)
                    {
                        column=0;
                        row=0;

                        columnMax=0;
                        rowMax=0;

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
                        seqGrab = strndup((char *)inputFileBuffer + loop + 2, ansi_sequence_loop);

                        // create sequence content array
                        seqArrayCount = explode(&seqArray, ';', seqGrab);
                        free(seqGrab);

                        // a loophole in limbo
                        for (seq_graphics_loop = 0; seq_graphics_loop < seqArrayCount; seq_graphics_loop++)
                        {
                            // convert split content value to integer
                            seqValue = strtonum(seqArray[seq_graphics_loop], 0, INT32_MAX, &errstr);

                            if (seqValue == 0)
                            {
                                background = 0;
                                foreground = 7;
                                bold = false;
                                underline = false;
                                italics = false;
                                blink = false;
                            }

                            if (seqValue == 1)
                            {
                                if (!workbench)
                                {
                                    foreground+=8;
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
                                    background+=8;
                                }
                                blink = true;
                            }

                            if (seqValue > 29 && seqValue < 38)
                            {
                                foreground = seqValue - 30;

                                if (bold)
                                {
                                    foreground+=8;
                                }
                            }

                            if (seqValue > 39 && seqValue < 48)
                            {
                                background = seqValue - 40;

                                if (blink && icecolors)
                                {
                                    background+=8;
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

                // skipping erase in line (EL) sequences
                if (ansi_sequence_character == 'K')
                {
                    loop+=ansi_sequence_loop+2;
                    break;
                }
            }
        }
        else if (current_character!=10 && current_character!=13 && current_character!=9)
        {
            // record number of columns and lines used
            if (column>columnMax)
            {
                columnMax=column;
            }

            if (row>rowMax)
            {
                rowMax=row;
            }

            // write current character in ansiChar structure
            if (!fontData.isAmigaFont || (current_character != 12 && current_character != 13))
            {
                // reallocate structure array memory
                temp = realloc(ansi_buffer, (structIndex + 1) * sizeof(struct ansiChar));
                ansi_buffer = temp;

                ansi_buffer[structIndex].background = background;
                ansi_buffer[structIndex].foreground = foreground;
                ansi_buffer[structIndex].current_character = current_character;
                ansi_buffer[structIndex].bold = bold;
                ansi_buffer[structIndex].italics = italics;
                ansi_buffer[structIndex].underline = underline;
                ansi_buffer[structIndex].column = column;
                ansi_buffer[structIndex].row = row;

                structIndex++;
                column++;
            }
        }
        loop++;
    }

    // allocate image buffer memory
    columnMax++;
    rowMax++;

    if (ced)
    {
        columns = 78;
    }

    if (isDizFile) {
        columns = fmin(columnMax,80);
    }

    // create that damn thingy
    canvas = gdImageCreate(columns * bits,(rowMax)*fontData.height);

    if (!canvas) {
        perror("Can't allocate ANSi buffer image memory");
        exit(6);
    }

    int32_t colors[16];

    int32_t ced_background = 0, ced_foreground = 0;

    if (ced)
    {
        ced_background = gdImageColorAllocate(canvas, 170, 170, 170);
        ced_foreground = gdImageColorAllocate(canvas, 0, 0, 0);
        gdImageFill(canvas, 0, 0, ced_background);
    }
    else if (workbench)
    {
        gdImageFill(canvas, 0, 0, 0);

        for (int i=0; i<16; i++) {
            colors[i] = gdImageColorAllocate(canvas, workbench_palette[i*3],
                                             workbench_palette[i*3+1],
                                             workbench_palette[i*3+2]);
        }
    }
    else
    {
        // Allocate standard ANSi color palette

        for (int i=0; i<16; i++) {
            colors[i] = gdImageColorAllocate(canvas, ansi_palette[i*3],
                                             ansi_palette[i*3+1],
                                             ansi_palette[i*3+2]);
        }
    }

    // even more definitions, sigh
    int32_t ansiBufferItems = structIndex;

    // render ANSi
    for (loop = 0; loop < ansiBufferItems; loop++)
    {
        // grab ANSi char from our structure array
        background = ansi_buffer[loop].background;
        foreground = ansi_buffer[loop].foreground;
        character = ansi_buffer[loop].current_character;
        bold = ansi_buffer[loop].bold;
        italics = ansi_buffer[loop].italics;
        underline = ansi_buffer[loop].underline;
        column = ansi_buffer[loop].column;
        row = ansi_buffer[loop].row;

        if (ced) {
            drawchar(canvas, fontData.font_data, bits, fontData.height,
                   column, row, ced_background, ced_foreground, character);
        } else {
            drawchar(canvas, fontData.font_data, bits, fontData.height,
                   column, row, colors[background], colors[foreground], character);
        }

    }

    // transparent flag used?
    if (transparent)
    {
        gdImageColorTransparent(canvas, 0);
    }

    // create output image
    output(canvas, outputFile, retinaout, retinaScaleFactor);

    // free memory
    free(ansi_buffer);
}

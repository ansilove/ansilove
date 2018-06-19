//
//  tundra.c
//  AnsiLove/C
//
//  Copyright (c) 2011-2018 Stefan Vogt, Brian Cassidy, and Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 2-Clause License.
//  See the LICENSE file for details.
//

#include "tundra.h"

void tundra(unsigned char *inputFileBuffer, int32_t inputFileSize, char *outputFile, char *retinaout, char *font, int32_t bits, int retinaScaleFactor)
{
    // some type declarations
    struct fontStruct fontData;
    int32_t columns = 80;
    char tundra_version;
    char tundra_header[8];

    // font selection
    alSelectFont(&fontData, font);

    // libgd image pointers
    gdImagePtr canvas;

    // extract tundra header
    tundra_version = inputFileBuffer[0];
    memcpy(&tundra_header,inputFileBuffer+1,8);

    // need to add check for "TUNDRA24" string in the header
    if (tundra_version != 24)
    {
        fputs ("\nInput file is not a TUNDRA file.\n\n", stderr); exit (4);
    }

    // read tundra file a first time to find the image size
    int32_t character, background = 0, foreground = 0;
    int32_t loop = 9, column = 0, row = 1;

    while (loop < inputFileSize)
    {
        if (column == 80)
        {
            column = 0;
            row++;
        }

        character = inputFileBuffer[loop];

        if (character == 1)
        {
            row =
                    (inputFileBuffer[loop + 1] << 24) + (inputFileBuffer[loop + 2] << 16) +
                            (inputFileBuffer[loop + 3] << 8) + inputFileBuffer[loop+4];

            column =
                    (inputFileBuffer[loop + 5] << 24) + (inputFileBuffer[loop + 6] << 16) +
                            (inputFileBuffer[loop + 7] << 8) + inputFileBuffer[loop+8];

            loop+=8;
        }

        if (character == 2)
        {
            character = inputFileBuffer[loop + 1];

            loop+=5;
        }

        if (character == 4)
        {
            character = inputFileBuffer[loop + 1];

            loop+=5;
        }

        if (character == 6)
        {
            character = inputFileBuffer[loop + 1];

            loop+=9;
        }

        if (character !=1 && character !=2 && character !=4 && character != 6)
        {
            column++;
        }

        loop++;
    }

    // allocate buffer image memory
    canvas = gdImageCreateTrueColor(columns * bits , (row) * fontData.height);

    if (!canvas) {
        perror("Error, can't allocate buffer image memory");
        exit (6);
    }

    // process tundra
    column = 0;
    row = 0;

    loop = 9;

    while (loop < inputFileSize)
    {
        if (column == 80)
        {
            column = 0;
            row++;
        }

        character = inputFileBuffer[loop];

        if (character == 1)
        {
            row =
                    (inputFileBuffer[loop + 1] << 24) + (inputFileBuffer[loop + 2] << 16) +
                            (inputFileBuffer[loop + 3] << 8) + inputFileBuffer[loop + 4];

            column =
                    (inputFileBuffer[loop + 5] << 24) + (inputFileBuffer[loop + 6] << 16) +
                            (inputFileBuffer[loop + 7] << 8) + inputFileBuffer[loop + 8];

            loop+=8;
        }

        if (character == 2)
        {
            foreground =
                    (inputFileBuffer[loop + 3] << 16) + (inputFileBuffer[loop + 4] << 8) +
                            inputFileBuffer[loop + 5];

            character = inputFileBuffer[loop+1];

            loop+=5;
        }

        if (character == 4)
        {
            background = (inputFileBuffer[loop + 3] << 16) + (inputFileBuffer[loop + 4] << 8) +
                    inputFileBuffer[loop+5];

            character = inputFileBuffer[loop+1];

            loop+=5;
        }

        if (character==6)
        {
            foreground =
                    (inputFileBuffer[loop + 3] << 16) + (inputFileBuffer[loop + 4] << 8) +
                            inputFileBuffer[loop+5];

            background =
                    (inputFileBuffer[loop + 7] << 16) + (inputFileBuffer[loop + 8] << 8) +
                            inputFileBuffer[loop+9];

            character = inputFileBuffer[loop+1];

            loop+=9;
        }

        if (character !=1 && character !=2 && character !=4 && character !=6)
        {
            drawchar(canvas, fontData.font_data, bits, fontData.height,
                    column, row, background, foreground, character);

            column++;
        }

        loop++;
    }

    // create output image
    output(canvas, outputFile, retinaout, retinaScaleFactor);
}


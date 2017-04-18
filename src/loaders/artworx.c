//
//  artworx.c
//  AnsiLove/C
//
//  Copyright (C) 2011-2017 Stefan Vogt, Brian Cassidy, and Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 2-Clause License.
//  See the file LICENSE for details.
//

#include "artworx.h"

void artworx(unsigned char *inputFileBuffer, int32_t inputFileSize, char *outputFile, char *retinaout, bool createRetinaRep)
{
    const unsigned char *font_data;
    unsigned char *font_data_adf;

    // libgd image pointers
    gdImagePtr im_ADF;

    // create ADF instance
    im_ADF = gdImageCreate(640,(((inputFileSize - 192 - 4096 -1) / 2) / 80) * 16);

    // error output
    if (!im_ADF) {
        perror("Can't allocate buffer image memory");
        exit (7);
    }

    // ADF color palette array
    int32_t adf_colors[16] = { 0, 1, 2, 3, 4, 5, 20, 7, 56, 57, 58, 59, 60, 61, 62, 63 };

    int32_t loop;
    int32_t index;

    // process ADF font
    font_data_adf = (unsigned char *) malloc(sizeof(unsigned char)*4096);
    if (font_data_adf == NULL) {
        perror("Memory error");
        exit (7);
    }
    memcpy(font_data_adf,inputFileBuffer+193,4096);

    font_data=font_data_adf;

    // process ADF palette
    for (loop = 0; loop < 16; loop++)
    {
        index = (adf_colors[loop] * 3) + 1;
        gdImageColorAllocate(im_ADF, (inputFileBuffer[index] << 2 | inputFileBuffer[index] >> 4),
                                            (inputFileBuffer[index + 1] << 2 | inputFileBuffer[index + 1] >> 4),
                                            (inputFileBuffer[index + 2] << 2 | inputFileBuffer[index + 2] >> 4));
    }

    gdImageColorAllocate(im_ADF, 0, 0, 0);

    // process ADF
    int32_t position_x = 0, position_y = 0;
    int32_t character, attribute, foreground, background;
    loop = 192 + 4096 + 1;

    while(loop < inputFileSize)
    {
        if (position_x == 80)
        {
            position_x = 0;
            position_y++;
        }

        character = inputFileBuffer[loop];
        attribute = inputFileBuffer[loop+1];

        background = (attribute & 240) >> 4;
        foreground = attribute & 15;

        alDrawChar(im_ADF, font_data, 8, 16, position_x, position_y, background, foreground, character);

        position_x++;
        loop+=2;
    }

    // create output file
    output(im_ADF, outputFile, retinaout, createRetinaRep);

    // nuke garbage
    free(font_data_adf);
}

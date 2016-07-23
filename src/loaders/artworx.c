//
//  artworx.c
//  AnsiLove/C
//
//  Copyright (C) 2011-2016 Stefan Vogt, Brian Cassidy, Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 2-Clause License.
//  See the file LICENSE for details.
//

#include "artworx.h"

void artworx(unsigned char *inputFileBuffer, int32_t inputFileSize, char *output, char *retinaout, bool createRetinaRep)
{
    const unsigned char *font_data;
    unsigned char *font_data_adf;

    // libgd image pointers
    gdImagePtr im_ADF;

    // create ADF instance
    im_ADF = gdImageCreate(640,(((inputFileSize - 192 - 4096 -1) / 2) / 80) * 16);

    // error output
    if (!im_ADF) {
        fputs ("\nCan't allocate buffer image memory.\n\n", stderr); exit (7);
    }

    // ADF color palette array
    int32_t adf_colors[16] = { 0, 1, 2, 3, 4, 5, 20, 7, 56, 57, 58, 59, 60, 61, 62, 63 };

    int32_t loop;
    int32_t index;

    // process ADF font
    font_data_adf = (unsigned char *) malloc(sizeof(unsigned char)*4096);
    if (font_data_adf == NULL) {
        fputs ("\nMemory error.\n\n", stderr); exit (7);
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
    int32_t character, attribute, color_foreground, color_background;
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

        color_background = (attribute & 240) >> 4;
        color_foreground = attribute & 15;

        alDrawChar(im_ADF, font_data, 8, 16, position_x, position_y, color_background, color_foreground, character);

        position_x++;
        loop+=2;
    }

    // create output file
    FILE *file_Out = fopen(output, "wb");
    gdImagePng(im_ADF, file_Out);
    fclose(file_Out);

    // in case Retina image output is wanted
    if (createRetinaRep)
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

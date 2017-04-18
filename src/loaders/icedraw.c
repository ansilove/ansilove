//
//  icedraw.c
//  AnsiLove/C
//
//  Copyright (C) 2011-2017 Stefan Vogt, Brian Cassidy, and Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 2-Clause License.
//  See the file LICENSE for details.
//

#include "icedraw.h"

void icedraw(unsigned char *inputFileBuffer, int32_t inputFileSize, char *outputFile, char *retinaout, bool createRetinaRep)
{
    const unsigned char *font_data;
    unsigned char *font_data_idf;

    // extract relevant part of the IDF header, 16-bit endian unsigned short
    int32_t x2 = (inputFileBuffer[9] << 8) + inputFileBuffer[8];

    // libgd image pointers
    gdImagePtr im_IDF;

    int32_t loop;
    int32_t index;
    int32_t colors[16];

    // process IDF font
    font_data_idf = (unsigned char *) malloc(sizeof(unsigned char)*4096);
    if (font_data_idf == NULL) {
        perror("Memory error");
        exit (7);
    }
    memcpy(font_data_idf,inputFileBuffer+(inputFileSize - 48 - 4096),4096);

    font_data=font_data_idf;

    // process IDF
    loop = 12;
    int32_t idf_sequence_length, idf_sequence_loop, i = 0;

    // dynamically allocated memory buffer for IDF data
    unsigned char *idf_buffer, *temp;
    idf_buffer = malloc(sizeof(unsigned char));

    int16_t idf_data, idf_data_length;

    while (loop < inputFileSize - 4096 - 48)
    {
        memcpy(&idf_data,inputFileBuffer+loop,2);

        // RLE compressed data
        if (idf_data==1)
        {
            memcpy(&idf_data_length,inputFileBuffer+loop+2,2);

            idf_sequence_length = idf_data_length & 255;

            for (idf_sequence_loop = 0; idf_sequence_loop < idf_sequence_length; idf_sequence_loop++)
            {
                // reallocate IDF buffer memory
                temp = realloc(idf_buffer, (i + 2) * sizeof(unsigned char));
                if (idf_buffer != NULL) {
                    idf_buffer = temp;
                }
                else {
                    perror("Error allocating IDF buffer memory");
                    exit (7);
                }

                idf_buffer[i] = inputFileBuffer[loop + 4];
                idf_buffer[i+1] = inputFileBuffer[loop + 5];
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
                perror("Error allocating IDF buffer memory");
                exit (8);
            }

            // normal character
            idf_buffer[i] = inputFileBuffer[loop];
            idf_buffer[i+1] = inputFileBuffer[loop + 1];
            i+=2;
        }
        loop += 2;
    }

    // create IDF instance
    im_IDF = gdImageCreate((x2 + 1) * 8, i / 2 / 80 * 16);

    // error output
    if (!im_IDF) {
        perror("Can't allocate buffer image memory");
        exit (9);
    }
    gdImageColorAllocate(im_IDF, 0, 0, 0);

    // process IDF palette
    for (loop = 0; loop < 16; loop++)
    {
        index = (loop * 3) + inputFileSize - 48;
        colors[loop] = gdImageColorAllocate(im_IDF, (inputFileBuffer[index] << 2 | inputFileBuffer[index] >> 4),
                                            (inputFileBuffer[index + 1] << 2 | inputFileBuffer[index + 1] >> 4),
                                            (inputFileBuffer[index + 2] << 2 | inputFileBuffer[index + 2] >> 4));
    }

    // render IDF
    int32_t position_x = 0, position_y = 0;
    int32_t character, attribute, foreground, background;

    for (loop = 0; loop < i ; loop +=2)
    {
        if (position_x == x2 + 1)
        {
            position_x = 0;
            position_y++;
        }

        character = idf_buffer[loop];
        attribute = idf_buffer[loop+1];

        background = (attribute & 240) >> 4;
        foreground = attribute & 15;

        alDrawChar(im_IDF, font_data, 8, 16, position_x, position_y, colors[background], colors[foreground], character);

        position_x++;
    }

    // create output file
    output(im_IDF, outputFile, retinaout, createRetinaRep);

    // free memory
    free(font_data_idf);
    free(idf_buffer);
}

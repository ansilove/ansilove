//
//  tundra.c
//  AnsiLove/C
//
//  Copyright (C) 2011-2016 Stefan Vogt, Brian Cassidy, Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 3-Clause License.
//  See the file LICENSE for details.
//

#include "ansilove.h"

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


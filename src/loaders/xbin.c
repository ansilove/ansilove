//
//  xbin.c
//  AnsiLove/C
//
//  Copyright (C) 2011-2016 Stefan Vogt, Brian Cassidy, Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 2-Clause License.
//  See the file LICENSE for details.
//

#include "xbin.h"

void xbin(unsigned char *inputFileBuffer, int32_t inputFileSize, char *output, char *retinaout, bool createRetinaRep)
{
    const unsigned char *font_data;
    unsigned char *font_data_xbin;

    if (strncmp((char *)inputFileBuffer, "XBIN\x1a", 5) != 0) {
        fputs("\nNot an XBin.\n\n", stderr); exit (4);
    }

    int32_t xbin_width = (inputFileBuffer[ 6 ] << 8) + inputFileBuffer[ 5 ];
    int32_t xbin_height = (inputFileBuffer[ 8 ] << 8) + inputFileBuffer[ 7 ];
    int32_t xbin_fontsize = inputFileBuffer[ 9 ];
    int32_t xbin_flags = inputFileBuffer[ 10 ];

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

            colors[loop] = gdImageColorAllocate(im_XBIN, (inputFileBuffer[index] << 2 | inputFileBuffer[index] >> 4),
                                                (inputFileBuffer[index + 1] << 2 | inputFileBuffer[index + 1] >> 4),
                                                (inputFileBuffer[index + 2] << 2 | inputFileBuffer[index + 2] >> 4));
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
        memcpy(font_data_xbin,inputFileBuffer+offset,(xbin_fontsize * numchars));

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
        while(offset < inputFileSize && position_y != xbin_height )
        {
            int32_t ctype = inputFileBuffer[ offset ] & 0xC0;
            int32_t counter = ( inputFileBuffer[ offset ] & 0x3F ) + 1;

            character = -1;
            attribute = -1;

            offset++;
            while( counter-- ) {
                // none
                if( ctype == 0 ) {
                    character = inputFileBuffer[ offset ];
                    attribute = inputFileBuffer[ offset + 1 ];
                    offset += 2;
                }
                // char
                else if ( ctype == 0x40 ) {
                    if( character == -1 ) {
                        character = inputFileBuffer[ offset ];
                        offset++;
                    }
                    attribute = inputFileBuffer[ offset ];
                    offset++;
                                    }
                // attr
                else if ( ctype == 0x80 ) {
                    if( attribute == -1 ) {
                        attribute = inputFileBuffer[ offset ];
                        offset++;
                    }
                    character = inputFileBuffer[ offset ];
                    offset++;
                }
                // both
                else {
                    if( character == -1 ) {
                        character = inputFileBuffer[ offset ];
                        offset++;
                    }
                    if( attribute == -1 ) {
                        attribute = inputFileBuffer[ offset ];
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
        while(offset < inputFileSize && position_y != xbin_height )
        {
            if (position_x == xbin_width)
            {
                position_x = 0;
                position_y++;
            }

            character = inputFileBuffer[offset];
            attribute = inputFileBuffer[offset+1];

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

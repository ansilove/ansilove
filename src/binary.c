//
//  binary.c
//  AnsiLove/C
//
//  Copyright (C) 2011-2016 Stefan Vogt, Brian Cassidy, Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 3-Clause License.
//  See the file LICENSE for details.
//

#include "ansilove.h"

void binary(char *input, char *output, char *retinaout, int32_t int_columns, char *font, int32_t int_bits, bool icecolors, bool createRetinaRep)
{
    // some type declarations
    struct fontStruct fontData;

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
    gdImagePtr im_Binary;
    
    // allocate buffer image memory
    im_Binary = gdImageCreate(int_columns * int_bits, 
                              ((input_file_size / 2) / int_columns * fontData.font_size_y));
    
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

        
        if (color_background > 8 && !icecolors)
        {
            color_background -= 8;
        }

        alDrawChar(im_Binary, fontData.font_data, int_bits, fontData.font_size_y, 
                   position_x, position_y, colors[color_background], colors[color_foreground], character);
     
        position_x++;
        loop+=2;
    }
  
    // create output image
    FILE *file_Out = fopen(output, "wb");
    gdImagePng(im_Binary, file_Out);
    fclose(file_Out);
    
    // in case Retina image output is wanted
    if (createRetinaRep)
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

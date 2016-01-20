//
//  icedraw.c
//  AnsiLove/C
//
//  Copyright (C) 2011-2016 Stefan Vogt, Brian Cassidy, Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 3-Clause License.
//  See the file LICENSE for details.
//

#include "icedraw.h"

void icedraw(char *input, char *output, char *retinaout, bool fileHasSAUCE, bool createRetinaRep)
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

    // IDF related: file contains a SAUCE record? adjust the file size
    if(fileHasSAUCE) {
        sauce *saucerec = sauceReadFile(input_file);
        input_file_size -= 129 - ( saucerec->comments > 0 ? 5 + 64 * saucerec->comments : 0);
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
        
        alDrawChar(im_IDF, font_data, 8, 16, position_x, position_y, colors[color_background], colors[color_foreground], character);
        
        position_x++;
    }
    
    // free dynamically allocated memory
    free(idf_buffer);
    
    // create output file
    FILE *file_Out = fopen(output, "wb");
    gdImagePng(im_IDF, file_Out);
    fclose(file_Out);
    
    // in case Retina image output is wanted
    if (createRetinaRep)
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

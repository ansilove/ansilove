//
//  ansilove.c
//  AnsiLove/C
//
//  Copyright (C) 2011-2016 Stefan Vogt, Brian Cassidy, Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 3-Clause License.
//  See the file LICENSE for details.
//

#include "ansilove.h"

// shared method for drawing characters
void alDrawChar(gdImagePtr im, const unsigned char *font_data, int32_t int_bits,
                int32_t font_size_y, int32_t position_x, int32_t position_y,
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

//
//  ansilove.c
//  AnsiLove/C
//
//  Copyright (C) 2011-2017 Stefan Vogt, Brian Cassidy, and Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 2-Clause License.
//  See the file LICENSE for details.
//

#include "ansilove.h"

// shared method for drawing characters
void drawchar(gdImagePtr im, const unsigned char *font_data, int32_t bits,
                int32_t height, int32_t position_x, int32_t position_y,
                int32_t background, int32_t foreground, unsigned char character)
{
    int32_t column, line;

    gdImageFilledRectangle(im, position_x * bits, position_y*height, position_x * bits +
                           bits - 1, position_y * height + height - 1, background);

    for (line = 0; line < height; line++) {
        for (column = 0; column < bits; column++) {

            if ((font_data[line+character*height] & (0x80 >> column)) != 0) {
                gdImageSetPixel(im, position_x * bits + column, position_y*height + line, foreground);

                if (bits==9 && column==7 && character > 191 && character < 224)
                {
                    gdImageSetPixel(im, position_x * bits + 8, position_y * height + line, foreground);
                }
            }
        }
    }
}

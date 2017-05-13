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
                int32_t height, int32_t row, int32_t column,
                int32_t background, int32_t foreground, unsigned char character)
{
    int32_t x, y;

    gdImageFilledRectangle(im, row * bits, column*height, row * bits +
                           bits - 1, column * height + height - 1, background);

    for (y = 0; y < height; y++) {
        for (x = 0; x < bits; x++) {

            if ((font_data[y+character*height] & (0x80 >> x)) != 0) {
                gdImageSetPixel(im, row * bits + x, column*height + y, foreground);

                if (bits==9 && x==7 && character > 191 && character < 224)
                {
                    gdImageSetPixel(im, row * bits + 8, column * height + y, foreground);
                }
            }
        }
    }
}

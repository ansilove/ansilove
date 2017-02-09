//
//  pcboard.h
//  AnsiLove/C
//
//  Copyright (C) 2011-2017 Stefan Vogt, Brian Cassidy, and Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 2-Clause License.
//  See the file LICENSE for details.
//

#include "../ansilove.h"

#ifndef pcboard_h
#define pcboard_h

// Character structure
struct pcbChar {
    int32_t position_x;
    int32_t position_y;
    int32_t color_background;
    int32_t color_foreground;
    int32_t current_character;
};

void pcboard(unsigned char *inputFileBuffer, int32_t inputFileSize, char *output, char *retinaout, char *font, int32_t bits, bool createRetinaRep);

#endif

//
//  ansi.h
//  AnsiLove/C
//
//  Copyright (C) 2011-2016 Stefan Vogt, Brian Cassidy, Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 2-Clause License.
//  See the file LICENSE for details.
//

#include "../ansilove.h"

#ifndef ansi_h
#define ansi_h

// Character structure
struct ansiChar {
    int32_t position_x;
    int32_t position_y;
    int32_t color_background;
    int32_t color_foreground;
    int32_t current_character;
    bool bold;
    bool italics;
    bool underline;
};

void ansi(unsigned char *inputFileBuffer, int32_t inputFileSize, char *output, char *retinaout, char *font, int32_t bits, char *mode, bool icecolors, char *fext, bool createRetinaRep);

#endif

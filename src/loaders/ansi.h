//
//  ansi.h
//  AnsiLove/C
//
//  Copyright (c) 2011-2018 Stefan Vogt, Brian Cassidy, and Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 2-Clause License.
//  See the LICENSE file for details.
//

#include "../ansilove.h"

#ifndef ansi_h
#define ansi_h

// Character structure
struct ansiChar {
    int32_t column;
    int32_t row;
    int32_t background;
    int32_t foreground;
    int32_t current_character;
    bool bold;
    bool italics;
    bool underline;
};

void ansi(unsigned char *inputFileBuffer, int32_t inputFileSize, char *outputFile, char *retinaout, char *font, int32_t bits, char *mode, bool icecolors, char *fext, int retinaScaleFactor);

#endif

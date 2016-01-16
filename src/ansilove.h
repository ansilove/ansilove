//
//  ansilove.h
//  AnsiLove/C
//
//  Copyright (C) 2011-2016 Stefan Vogt, Brian Cassidy, Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 3-Clause License.
//  See the file LICENSE for details.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <gd.h>
#include "alconfig.h"
#include "albinfonts.h"
#include "strtolower.h"
#include "substr.h"
#include "explode.h"
#include "filesize.h"
#include "sauce.h"

#ifndef ansilove_h
#define ansilove_h

// prototypes
void alDrawChar(gdImagePtr im, const unsigned char *font_data, int32_t int_bits, 
                int32_t font_size_y, int32_t position_x, int32_t position_y, 
                int32_t color_background, int32_t color_foreground, unsigned char character);

void alAnsiLoader(char *input, char *output, char *retinaout, char *font, int32_t int_bits, char *mode, bool icecolors, char *fext, bool createRetinaRep);
void alPcBoardLoader(char *input, char *output, char *retinaout, char *font, int32_t int_bits, bool createRetinaRep);
void alTundraLoader(char *input, char *output, char *retinaout, char *font, int32_t int_bits, bool fileHasSAUCE, bool createRetinaRep);

// helper functions
char *str_replace(const char *string, const char *substr, const char *replacement);

// character structures
struct pcbChar {
    int32_t position_x;
    int32_t position_y;
    int32_t color_background;
    int32_t color_foreground;
    int32_t current_character;
};

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

#endif

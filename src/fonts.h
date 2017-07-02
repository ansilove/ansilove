//
//  fonts.h
//  AnsiLove/C
//
//  Copyright (C) 2011-2017 Stefan Vogt, Brian Cassidy, and Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 2-Clause License.
//  See the LICENSE file for details.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifndef albinfonts_h
#define albinfonts_h

struct fontStruct {
    unsigned char *font_data;
    int32_t width;
    int32_t height;
    bool isAmigaFont;
};

void alSelectFont(struct fontStruct* fontData, char *font);

// Binary font and image data.

unsigned char font_pc_80x25[4096];
unsigned char font_pc_80x50[2048];
unsigned char font_pc_baltic[4096];
unsigned char font_pc_cyrillic[4096];
unsigned char font_pc_french_canadian[4096];
unsigned char font_pc_greek[4096];
unsigned char font_pc_greek_869[4096];
unsigned char font_pc_hebrew[4096];
unsigned char font_pc_icelandic[4096];
unsigned char font_pc_latin1[4096];
unsigned char font_pc_latin2[4096];
unsigned char font_pc_nordic[4096];
unsigned char font_pc_portuguese[4096];
unsigned char font_pc_russian[4096];
unsigned char font_pc_terminus[4096];
unsigned char font_pc_turkish[4096];

unsigned char font_amiga_microknight[4096];
unsigned char font_amiga_microknight_plus[4096];
unsigned char font_amiga_mosoul[4096];
unsigned char font_amiga_pot_noodle[4096];
unsigned char font_amiga_topaz_1200[4096];
unsigned char font_amiga_topaz_1200_plus[4096];
unsigned char font_amiga_topaz_500[4096];
unsigned char font_amiga_topaz_500_plus[4096];

#endif

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

#ifndef ansilove_h
#define ansilove_h

// prototypes
void alDrawChar(gdImagePtr im, const unsigned char *font_data, int32_t int_bits, 
                int32_t font_size_y, int32_t position_x, int32_t position_y, 
                int32_t color_background, int32_t color_foreground, unsigned char character);

void alAnsiLoader(char *input, char *output, char *retinaout, char *font, int32_t int_bits, char *mode, bool icecolors, char *fext, bool createRetinaRep);
void alPcBoardLoader(char *input, char *output, char *retinaout, char *font, int32_t int_bits, bool createRetinaRep);
void alBinaryLoader(char *input, char *output, char *retinaout, int32_t int_columns, char *font, int32_t int_bits, bool icecolors, bool createRetinaRep);
void alArtworxLoader(char *input, char *output, char *retinaout, bool createRetinaRep);
void alIcedrawLoader(char *input, char *output, char *retinaout, bool fileHasSAUCE, bool createRetinaRep);
void alTundraLoader(char *input, char *output, char *retinaout, char *font, int32_t int_bits, bool fileHasSAUCE, bool createRetinaRep);
void alXbinLoader(char *input, char *output, char *retinaout, bool createRetinaRep);

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

struct fontStruct {
    unsigned char *font_data;
    int32_t font_size_x;
    int32_t font_size_y;
    bool isAmigaFont;
};

// sauce records
#define RECORD_SIZE  128
#define COMMENT_SIZE 64
#define SAUCE_ID     "SAUCE"
#define COMMENT_ID   "COMNT"

typedef struct {
    char             ID[6];
    char             version[3];
    char             title[36];
    char             author[21];
    char             group[21];
    char             date[9];
    int32_t          fileSize;
    unsigned char    dataType;
    unsigned char    fileType;
    unsigned short   tinfo1;
    unsigned short   tinfo2;
    unsigned short   tinfo3;
    unsigned short   tinfo4;
    unsigned char    comments;
    unsigned char    flags;
    char             filler[23];
    char             **comment_lines;
} sauce;

sauce *sauceReadFileName(char *fileName);
sauce *sauceReadFile(FILE *file);
void  readRecord(FILE *file, sauce *record);
void  readComments(FILE *file, char **comment_lines, int32_t comments);

#endif

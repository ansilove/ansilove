//
//  ansilove.h
//  AnsiLove/C
//
//  Copyright (c) 2011-2012 "the international ANSi conspiracy".
//  Project leads: Stefan Vogt, Brian Cassidy, Frederic Cambus.
//  All rights reserved.
//  https://github.com/ByteProject/AnsiLove-C/
//
//  Use of this source code is governed by a MIT-style license.
//  See the file LICENSE for details.
//

#if defined(__APPLE__) && defined(__MACH__)
#import <Foundation/Foundation.h>
#import <gd.h>
#import "alconfig.h"
#import "albinfonts.h"
#import "strtolower.h"
#import "substr.h"
#import "explode.h"
#import "filesize.h"
#else
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gd.h>
#include "alconfig.h"
#include "albinfonts.h"
#include "strtolower.h"
#include "substr.h"
#include "explode.h"
#include "filesize.h"
#endif

#ifndef ansilove_h
#define ansilove_h

#if !defined(MIN)
#define MIN(A,B) ({ __typeof__(A) __a = (A); __typeof__(B) __b = (B); __a < __b ? __a : __b; })
#endif

// prototypes
void alDrawChar(gdImagePtr im, const unsigned char *font_data, int32_t font_size_x, int32_t font_size_y, int32_t position_x, int32_t position_y, int32_t color_background, int32_t color_foreground, unsigned char character);

void alAnsiLoader(char *input, char output[], char font[], char bits[], char icecolors[], char *fext);
void alPcBoardLoader(char *input, char output[], char font[], char bits[]);
void alBinaryLoader(char *input, char output[], char columns[], char font[], char bits[], char icecolors[]);
void alArtworxLoader(char *input, char output[], char bits[]);
void alIcedrawLoader(char *input, char output[], char bits[], bool fileHasSAUCE);
void alTundraLoader(char *input, char output[], char font[], char bits[]);
void alXbinLoader(char *input, char output[], char bits[]);

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

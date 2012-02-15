//
//  ansilove.h
//  AnsiLove/C
//
//  Copyright (c) 2011, Stefan Vogt. All rights reserved.
//  http://byteproject.net
//
//  Use of this source code is governed by a MIT-style license.
//  See the file LICENSE for details.
//

#if defined(__APPLE__) && defined(__MACH__)
#import <Foundation/Foundation.h>
#import <gd.h>
#import "alconfig.h"
#import "strtolower.h"
#import "substr.h"
#import "explode.h"
#import "filesize.h"
#else
#include <stdio.h>
#include <stdlib.h>
#include <gd.h>
#include "alconfig.h"
#include "strtolower.h"
#include "substr.h"
#include "explode.h"
#include "filesize.h"
#endif

#ifndef ansilove_h
#define ansilove_h

// prototypes
void alAnsiLoader(char *input, char output[], char font[], char bits[], char icecolors[], char *fext);
void alBinaryLoader(char *input, char output[], char columns[], char font[], char bits[], char icecolors[]);
void alArtworxLoader(char *input, char output[], char bits[]);
void alXbinLoader(char *input, char output[], char bits[]);

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
void  readComments(FILE *file, char **comment_lines, int64_t comments);

#endif

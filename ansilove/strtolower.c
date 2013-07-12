//
//  strtolower.m
//  AnsiLove/C
//
//  Copyright (C) 2011-2013 Stefan Vogt, Brian Cassidy, Frederic Cambus.
//  All rights reserved.
//  https://github.com/ByteProject/AnsiLove-C/
//
//  Use of this source code is governed by a MIT-style license.
//  See the file LICENSE for details.
//

#if defined(__APPLE__) && defined(__MACH__)
#import "strtolower.h"
#else
#include "strtolower.h"
#endif

char *strtolower(char *str)
{
    char *p;
    for (p = str; *p != '\0'; ++p) 
    {
        *p = tolower(*p);
    }
    return str;
}

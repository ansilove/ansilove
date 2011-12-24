//
//  strtolower.m
//  AnsiLove/C
//
//  Copyright (c) 2011, Stefan Vogt. All rights reserved.
//  http://byteproject.net
//
//  Use of this source code is governed by a MIT-style license.
//  See the file LICENSE for details.
//

#if defined(__APPLE__) && defined(__MACH__)
#import "strtolower.h"
#else
#include "strtolower.h"
#endif

void strtolower(char str[])
{
    char *p;
    for (p = str; *p != '\0'; ++p)
    {
        *p = tolower(*p);
    }
}

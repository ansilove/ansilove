//
//  substr.m
//  AnsiLove/C
//
//  Copyright (c) 2011, Stefan Vogt. All rights reserved.
//  http://byteproject.net
//
//  Use of this source code is governed by a MIT-style license.
//  See the file LICENSE for details.
//

#if defined(__APPLE__) && defined(__MACH__)
#import "substr.h"
#else
#include "substr.h"
#endif

char *substr(char *str, size_t begin, size_t len) 
{ 
    if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)) 
        return 0; 
    
    return strndup(str + begin, len);
} 

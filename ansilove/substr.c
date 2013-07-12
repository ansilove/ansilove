//
//  substr.m
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
#import "substr.h"
#else
#include "substr.h"
#endif

char *substr(char *str, size_t begin, size_t len)
{ 
    if (str == 0 || strlen(str) == 0) 
        return 0; 
    
    return strndup(str + begin, len);
} 

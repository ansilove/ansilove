//
//  substr.m
//  AnsiLove/C
//
//  Copyright (C) 2011-2015 Stefan Vogt, Brian Cassidy, Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 3-Clause License.
//  See the file LICENSE for details.
//

#include "substr.h"

char *substr(char *str, size_t begin, size_t len)
{ 
    if (str == 0 || strlen(str) == 0) 
        return 0; 
    
    return strndup(str + begin, len);
} 

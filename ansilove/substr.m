//
//  substr.m
//  AnsiLove/ObjC
//
//  Copyright (c) 2011, Stefan Vogt. All rights reserved.
//  http://byteproject.net
//
//  Use of this source code is governed by a MIT-style license.
//  See the file LICENSE for details.
//

#import "substr.h"

char *substring(const char *str, size_t begin, size_t len) 
{ 
    if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)) 
        return 0; 
    
    return strndup(str + begin, len);
} 

//
//  explode.h
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
#else
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#endif

#ifndef explode_h
#define explode_h

// Converts a delimited string into a string array. Other than PHP's
// explode() function it will return an integer of strings found. I
// consider this as much better approach as you can access the strings
// via array pointer and you don't have to determine how many string
// instances were stored overall as this is what you're getting.

int64_t explode(char ***arr_ptr, char delimiter, char *str);

#endif

//
//  strtolower.h
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
#include <ctype.h>
#endif

#ifndef strtolower_h
#define strtolower_h

// In-place modification of a string to be all lower case.
void strtolower(char str[]);

#endif

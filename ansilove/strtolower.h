//
//  strtolower.h
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
#import <Foundation/Foundation.h>
#else
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#endif

#ifndef strtolower_h
#define strtolower_h

// In-place modification of a string to be all lower case. 

char *strtolower(char *str);

#endif

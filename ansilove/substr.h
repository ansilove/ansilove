//
//  substr.h
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
#include <string.h>
#endif

#ifndef substr_h
#define substr_h

// Returns portion of a string specified by start and length parameters.

char *substr(char *str, size_t begin, size_t len);

#endif

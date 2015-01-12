//
//  strtolower.h
//  AnsiLove/C
//
//  Copyright (C) 2011-2015 Stefan Vogt, Brian Cassidy, Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 3-Clause License.
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

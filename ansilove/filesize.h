//
//  filesize.h
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
#endif

#ifndef filesize_h
#define filesize_h

// Returns size of a file at a given path as integer.

int64_t filesize(char *filepath);

#endif

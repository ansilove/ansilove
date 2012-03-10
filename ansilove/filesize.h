//
//  filesize.h
//  AnsiLove/C
//
//  Copyright (C) 2011-2012 Stefan Vogt, Brian Cassidy, Frederic Cambus.
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
#endif

#ifndef filesize_h
#define filesize_h

// Returns size of a file at a given path as integer.

size_t filesize(char *filepath);

#endif

//
//  albinfonts.h
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

#ifndef albinfonts_h
#define albinfonts_h

// Binary font and image data.

const unsigned char font_pc_80x25[4096];
const unsigned char font_pc_80x50[2048];

#endif

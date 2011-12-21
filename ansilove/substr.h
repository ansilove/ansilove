//
//  substr.h
//  AnsiLove/C
//
//  Copyright (c) 2011, Stefan Vogt. All rights reserved.
//  http://byteproject.net
//
//  Use of this source code is governed by a MIT-style license.
//  See the file LICENSE for details.
//

#import <Foundation/Foundation.h>

// Returns the portion of a string specified by start and length parameters.

char *substr(const char *str, size_t begin, size_t len);

//
//  substr.h
//  AnsiLove/C
//
//  Copyright (C) 2011-2015 Stefan Vogt, Brian Cassidy, Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 3-Clause License.
//  See the file LICENSE for details.
//

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#ifndef substr_h
#define substr_h

// Returns portion of a string specified by start and length parameters.

char *substr(char *str, size_t begin, size_t len);

#endif

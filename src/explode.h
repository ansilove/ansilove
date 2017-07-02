//
//  explode.h
//  AnsiLove/C
//
//  Copyright (C) 2011-2017 Stefan Vogt, Brian Cassidy, and Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 2-Clause License.
//  See the LICENSE file for details.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifndef explode_h
#define explode_h

// Converts a delimited string into a string array. Other than PHP's
// explode() function it will return an integer of strings found. I
// consider this as much better approach as you can access the strings
// via array pointer and you don't have to determine how many string
// instances were stored overall as this is what you're getting.

int32_t explode(char ***arr_ptr, char delimiter, char *str);

#endif

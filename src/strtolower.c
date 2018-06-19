//
//  strtolower.c
//  AnsiLove/C
//
//  Copyright (C) 2011-2018 Stefan Vogt, Brian Cassidy, and Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 2-Clause License.
//  See the LICENSE file for details.
//

#include "strtolower.h"

char *strtolower(char *str)
{
    char *p = str;

    while (*p) {
        *p = tolower((unsigned char) *p);
        p++;
    }

    return str;
}

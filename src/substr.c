//
//  substr.c
//  AnsiLove/C
//
//  Copyright (C) 2011-2017 Stefan Vogt, Brian Cassidy, and Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 2-Clause License.
//  See the file LICENSE for details.
//

#define _XOPEN_SOURCE 700
#define _NETBSD_SOURCE
#include <string.h>

char *substr(char *str, size_t begin, size_t len)
{
    if (str == 0 || strlen(str) == 0)
        return 0;

    return strndup(str + begin, len);
}

//
//  explode.c
//  AnsiLove/C
//
//  Copyright (C) 2011-2016 Stefan Vogt, Brian Cassidy, Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 3-Clause License.
//  See the file LICENSE for details.
//

#include "explode.h"

int32_t explode(char ***arr_ptr, char delimiter, char *str)
{
    char *src = str, *end, *dst;
    char **arr;
    int32_t size = 1, i;
    
    while ((end = strchr(src, delimiter)) != NULL)
    {
        ++size;
        src = end + 1;
    }
    
    arr = malloc(size * sizeof(char *) + (strlen(str) + 1) * sizeof(char));
    
    src = str;
    dst = (char *) arr + size * sizeof(char *);
    for (i = 0; i < size; ++i)
    {
        if ((end = strchr(src, delimiter)) == NULL)
            end = src + strlen(src);
        arr[i] = dst;
        strncpy(dst, src, end - src);
        dst[end - src] = '\0';
        dst += end - src + 1;
        src = end + 1;
    }
    *arr_ptr = arr;
    
    return size;
}

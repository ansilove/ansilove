//
//  explode.m
//  AnsiLove/C
//
//  Copyright (c) 2011, Stefan Vogt. All rights reserved.
//  http://byteproject.net
//
//  Use of this source code is governed by a MIT-style license.
//  See the file LICENSE for details.
//

#if defined(__APPLE__) && defined(__MACH__)
#import "explode.h"
#else
#include "explode.h"
#endif

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
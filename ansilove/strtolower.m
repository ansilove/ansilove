//
//  strtolower.m
//  AnsiLove/ObjC
//
//  Copyright (c) 2011, Stefan Vogt. All rights reserved.
//  http://byteproject.net
//
//  Use of this source code is governed by a MIT-style license.
//  See the file LICENSE for details.
//

#import "strtolower.h"

void strtolower(char str[]) {
    while(*str != 0) {
        if (*str >= 'A' && *str <= 'Z') {
            *str = *str + 'a' - 'A';
        }
        str++;
    }
}

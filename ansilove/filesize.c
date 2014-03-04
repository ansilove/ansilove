//
//  filesize.m
//  AnsiLove/C
//
//  Copyright (C) 2011-2014 Stefan Vogt, Brian Cassidy, Frederic Cambus.
//  All rights reserved.
//  https://github.com/ByteProject/AnsiLove-C/
//
//  Use of this source code is governed by a MIT-style license.
//  See the file LICENSE for details.
//

#if defined(__APPLE__) && defined(__MACH__)
#import "filesize.h"
#else
#include "filesize.h"
#endif

size_t filesize(char *filepath) 
{
    // pointer to file at path
    size_t size;
    FILE *file;
    
    // To properly determine the size, we open it in binary mode.
    file = fopen(filepath, "rb");
    
    if(file != NULL)
    {
        // Error while seeking to end of file?
        if(fseek(file, 0, SEEK_END)) {
            rewind(file);
            fclose(file);
            return -1;
        }
        
        size = ftell(file);
        // Close file and return the file size.
        rewind(file);
        fclose(file);
        return size;
    } 
    
    // In case we encounter an error.
    return -1;
}

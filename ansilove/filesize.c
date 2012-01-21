//
//  filesize.m
//  AnsiLove/C
//
//  Copyright (c) 2011, Stefan Vogt. All rights reserved.
//  http://byteproject.net
//
//  Use of this source code is governed by a MIT-style license.
//  See the file LICENSE for details.
//

#if defined(__APPLE__) && defined(__MACH__)
#import "filesize.h"
#else
#include "filesize.h"
#endif

int64_t filesize(char *filepath) 
{
    // pointer to file at path
    int64_t size;
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

//
//  filesize.c
//  AnsiLove/C
//
//  Copyright (C) 2011-2016 Stefan Vogt, Brian Cassidy, Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 3-Clause License.
//  See the file LICENSE for details.
//

#include "filesize.h"

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

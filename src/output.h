//
//  output.h
//  AnsiLove/C
//
//  Copyright (C) 2011-2017 Stefan Vogt, Brian Cassidy, and Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 2-Clause License.
//  See the file LICENSE for details.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <gd.h>

#ifndef output_h
#define output_h

// prototypes
void output(gdImagePtr im_Source, char *output, char *retinaout, bool createRetinaRep);

#endif

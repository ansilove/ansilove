//
//  retina.c
//  AnsiLove/C
//
//  Copyright (C) 2011-2017 Stefan Vogt, Brian Cassidy, and Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 2-Clause License.
//  See the file LICENSE for details.
//

#include "retina.h"

void retina(gdImagePtr im_Source, char *retinaout) {
    gdImagePtr im_Retina;

    // make the Retina image @2x as large as im_Source
    im_Retina = gdImageCreate(im_Source->sx * 2, im_Source->sy * 2);

    gdImageCopyResized(im_Retina, im_Source, 0, 0, 0, 0,
                       im_Retina->sx, im_Retina->sy,
                       im_Source->sx, im_Source->sy);

    // create retina output image
    FILE *file_RetinaOut = fopen(retinaout, "wb");
    gdImagePng(im_Retina, file_RetinaOut);
    fclose(file_RetinaOut);

    gdImageDestroy(im_Retina);
}

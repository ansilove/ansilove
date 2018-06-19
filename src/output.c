//
//  output.c
//  AnsiLove/C
//
//  Copyright (c) 2011-2018 Stefan Vogt, Brian Cassidy, and Frederic Cambus.
//  All rights reserved.
//
//  This source code is licensed under the BSD 2-Clause License.
//  See the LICENSE file for details.
//

#include "output.h"

void output(gdImagePtr im_Source, char *output, char *retinaout, int retinaScaleFactor) {
    FILE *file_Out = fopen(output, "wb");

    if (file_Out) {
        gdImagePng(im_Source, file_Out);
        fclose(file_Out);
    } else {
        perror("Can't create output file");
        exit(1);
    }

    // in case Retina image output is wanted
    if (retinaScaleFactor) {
        gdImagePtr im_Retina;

        // make the Retina image retinaScaleFactor as large as im_Source
        im_Retina = gdImageCreate(im_Source->sx * retinaScaleFactor,
                                  im_Source->sy * retinaScaleFactor);

        gdImageCopyResized(im_Retina, im_Source, 0, 0, 0, 0,
                           im_Retina->sx, im_Retina->sy,
                           im_Source->sx, im_Source->sy);

        // create retina output image
        FILE *file_RetinaOut = fopen(retinaout, "wb");

        if (file_RetinaOut) {
            gdImagePng(im_Retina, file_RetinaOut);
            fclose(file_RetinaOut);
        } else {
            perror("Can't create output file");
            exit(1);
        }

        gdImageDestroy(im_Retina);
    }

    gdImageDestroy(im_Source);
}

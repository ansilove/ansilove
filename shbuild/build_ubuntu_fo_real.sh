#!/bin/sh
#########################################################
# This UNIX script builds AnsiLove/C under Ubuntu Linux #
# and links it against libgd.                           #
#########################################################
# modify alconfig.h to configure the resulting binary   #
#########################################################
# build script version 1.2, updated by h3rb gi11iland   #
# originally created by Stefan Vogt                     #
#########################################################

echo "========================================="
echo "AnsiLove/C build script --> Ubuntu Linux "
echo "========================================="
echo "... building"
gcc -Wall -lgd -ljpeg -lpng -lz -lfreetype -lm ../ansilove/main.c \
        ../ansilove/alconfig.h ../ansilove/ansilove.h ../ansilove/ansilove.c \
        ../ansilove/substr.h ../ansilove/substr.c ../ansilove/strtolower.h \
        ../ansilove/strtolower.c ../ansilove/explode.h ../ansilove/explode.c \
        ../ansilove/filesize.h ../ansilove/filesize.c ../ansilove/albinfonts.h \
        ../ansilove/albinfonts.c -o ansilove
echo "... done.  Get on with that looooove!"

exit

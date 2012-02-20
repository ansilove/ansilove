#!/bin/sh
#########################################################
# This UNIX script builds AnsiLove/C under Ubuntu Linux #
# and links it against libgd.							#
#########################################################
# modify alconfig.h to configure the resulting binary   #
#########################################################
# build script version 1.1, created by Stefan Vogt      #
#########################################################

echo "========================================="
echo "AnsiLove/C build script --> Ubuntu Linux "
echo "========================================="
echo "... building"
gcc -Wall -I../lib/MacOSX/libgd/include/ ../ansilove/main.c ../ansilove/alconfig.h ../ansilove/ansilove.h ../ansilove/ansilove.c ../ansilove/fonts.h ../ansilove/substr.h ../ansilove/substr.c ../ansilove/strtolower.h ../ansilove/strtolower.c ../ansilove/explode.h ../ansilove/explode.c ../ansilove/filesize.h ../ansilove/filesize.c  /usr/lib/libgd.so.2 -o ansilove
echo "... done."

exit

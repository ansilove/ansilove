#!/bin/bash
#
# cleanup.h for AnsiLove/C
#
# This script cleans the AnsiLove/C project directory. It will delete all
# CMake and Make generated files, as well as compiled AnsiLove/C binaries.
# Use on *NIX systems only, tested on Linux Mint.
#
rm -Rf CMakeFiles
rm cmake_install.cmake
rm CMakeCache.txt
rm Makefile
echo "Make/CMake files cleaned successfully."
if [ ! -f ansilove ]; then
    echo "AnsiLove/C binary not existing and bypassed."
else
  rm ansilove
  echo "AnsiLove/C binary cleaned successfully."
fi
